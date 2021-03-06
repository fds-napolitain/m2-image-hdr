#include <opencv2/opencv.hpp>
#include "StackImage.hpp"

StackImage::StackImage() = default;

void StackImage::addImage(Image *image) {
	images.push_back(image);
}

/**
 * Retourne une liste de matrices OpenCV
 * @return
 */
std::vector<cv::Mat> StackImage::getMatrices() {
	std::vector<cv::Mat> matrices(images.size());
	for (int i = 0; i < images.size(); ++i) {
		matrices[i] = images[i]->matrix;
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
	mergeDebevec->process(matrices, resultDebevec, exposures);
	return Image(resultDebevec);
}

/**
 * Applique le merge de Robertson.
 * Fusion d'images avec connaissances des temps d'expositions.
 * @return
 */
Image StackImage::mergeRobertson() {
	cv::Mat responseRobertson;
	cv::Mat resultRobertson;
	std::vector<cv::Mat> matrices = getMatrices();
	std::vector<float> exposures = getExposures();

	cv::Ptr<cv::CalibrateRobertson> calibrateRobertson = cv::createCalibrateRobertson();
	calibrateRobertson->process(matrices, responseRobertson, exposures);

	cv::Ptr<cv::MergeRobertson> mergeRobertson = cv::createMergeRobertson();
	mergeRobertson->process(matrices, resultRobertson, exposures);
	return Image(resultRobertson);
}

/**
 * Applique le merge de Mertens.
 * Fusion de temps d'exposition, donc sans connaissances des temps d'expositions.
 * https://learnopencv.com/exposure-fusion-using-opencv-cpp-python/
 * @return
 */
Image StackImage::mergeMertens(bool s) {
	cv::Mat resultMertens;
	std::vector<cv::Mat> matrices = getMatrices();
	if (!s) {
		cv::Ptr<cv::MergeMertens> mergeMertens = cv::createMergeMertens();
		mergeMertens->process(matrices, resultMertens);
		return Image(resultMertens);
	} else {
		resultMertens = 0.0;
		double size = static_cast<double>(this->images.size());
		for (const auto &image: images) {
			resultMertens += image->matrix / size;
		}
	}
}

/**
 * Must be aligned first, MTB for example.
 * @return
 */
Image StackImage::merge() {
	cv::Mat resultDenoise(cv::Size(images[0]->matrix.cols, images[0]->matrix.rows), CV_8UC3);
	resultDenoise = 0.0;
	double size = static_cast<double>(this->images.size());
	for (const auto &image: images) {
		resultDenoise += image->matrix / size;
	}
	return Image(resultDenoise);
}
