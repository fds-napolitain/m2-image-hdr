#include <opencv2/opencv.hpp>
#include "StackImage.hpp"

StackImage::StackImage() = default;

/**
 * Crée et charge un ensemble d'images à partir d'une liste de chemins de fichiers
 * @param filenames liste de chemins de fichiers
 */
StackImage::StackImage(const QStringList& filenames) {
	loadImages(filenames);
}

/**
 * Charge un ensemble d'images à partir d'une liste de chemins de fichiers
 * @param filenames liste de chemins de fichiers
 */
void StackImage::loadImages(const QStringList& filenames) {
	images.reserve(filenames.size());
	int i = 0;
	for (const QString &image: filenames) {
		images[i] = Image(image);
	}
}

/**
 * Retourne une liste de matrices OpenCV
 * @return
 */
std::vector<cv::Mat> StackImage::getMatrices() {
	std::vector<cv::Mat> matrices(images.size());
	for (int i = 0; i < images.size(); ++i) {
		matrices[i] = images[i].getMat();
	}
	return matrices;
}

/**
 * Retourne une liste d'expositions des images
 * @return
 */
std::vector<float> StackImage::getExposures() {
	std::vector<float> exposures(images.size());
	for (int i = 0; i < images.size(); ++i) {
		exposures[i] = images[i].getExposure();
	}
	return exposures;
}

/**
 * Applique le merge de Debevec.
 * https://learnopencv.com/high-dynamic-range-hdr-imaging-using-opencv-cpp-python/
 * @return
 */
Image StackImage::mergeDebevec() {
	cv::Mat responseDebevec;
	cv::Mat result;
	std::vector<cv::Mat> matrices = getMatrices();
	std::vector<float> exposures = getExposures();
	cv::Ptr<cv::CalibrateDebevec> calibrateDebevec = cv::createCalibrateDebevec();
	calibrateDebevec->process(matrices, responseDebevec, exposures);
	cv::Ptr<cv::MergeDebevec> mergeDebevec = cv::createMergeDebevec();
	mergeDebevec->process(matrices, result, exposures, responseDebevec);
	return Image(result, true);
}
