#include <opencv2/opencv.hpp>
#include "StackImage.hpp"

StackImage::StackImage() = default;

StackImage::StackImage(int n) {
	images.resize(n);
}

StackImage::~StackImage() {
	for (auto &image: images) {
		delete image;
	}
}

void StackImage::addImage(Image *image) {
	images.push_back(image);
}

void StackImage::addImage(Image *image, int i) {
	images[i] = image;
}

/**
 * Retourne une liste de matrices OpenCV
 * @return
 */
std::vector<cv::Mat> StackImage::getMatrices() {
	std::vector<cv::Mat> matrices(images.size());
	for (int i = 0; i < images.size(); ++i) {
		matrices[i] = images[i]->image;
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
		exposures[i] = images[i]->getExposure();
	}
	return exposures;
}

/**
 * Alignement MTB: aligne les images dans le cas où les images n'ont pas été prises du même endroit.
 * Utilisation de la valeur de luminance médiane, puis seuillage sur cette dernière.
 */
void StackImage::alignMTB() {
	std::vector<cv::Mat> matrices = getMatrices();
	cv::Ptr<cv::AlignMTB> alignMTB = cv::createAlignMTB();
	alignMTB->process(matrices, matrices);
}

/**
 * Applique le merge de Debevec.
 * Fusion d'images avec connaissances des temps d'expositions.
 * https://learnopencv.com/high-dynamic-range-hdr-imaging-using-opencv-cpp-python/
 * @return
 */
Image StackImage::mergeDebevec() {
	cv::Mat responseDebevec;
	cv::Mat resultDebevec;
	std::vector<cv::Mat> matrices = getMatrices();
	std::vector<float> exposures = getExposures();

	cv::Ptr<cv::CalibrateDebevec> calibrateDebevec = cv::createCalibrateDebevec();
	calibrateDebevec->process(matrices, responseDebevec, exposures);

	cv::Ptr<cv::MergeDebevec> mergeDebevec = cv::createMergeDebevec();
	mergeDebevec->process(matrices, resultDebevec, exposures, responseDebevec);
	return Image(resultDebevec);
}

/**
 * Applique le merge de Mertens.
 * Fusion de temps d'exposition, donc sans connaissances des temps d'expositions.
 * https://learnopencv.com/exposure-fusion-using-opencv-cpp-python/
 * @return
 */
Image StackImage::mergeMertens() {
	cv::Mat resultMertens;
	std::vector<cv::Mat> matrices = getMatrices();
	std::vector<float> exposures = getExposures();

	cv::Ptr<cv::MergeMertens> mergeMertens = cv::createMergeMertens();
	mergeMertens->process(matrices, resultMertens);
	return Image(resultMertens);
}
