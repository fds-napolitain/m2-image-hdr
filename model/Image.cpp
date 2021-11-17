//
// Created by Maxime Boucher on 30/10/2021.
//


#include <utility>
#include "Image.hpp"


Image::Image() = default;

Image::Image(cv::Mat image, bool isHDR) {
	this->image = std::move(image);
	this->isHDR = isHDR;
}

/**
 * Initialise une image avec OpenCV.
 * @param filename
 * @param isHDR
 */
Image::Image(const QString& filename, bool isHDR) {
	loadImage(filename);
	this->isHDR = isHDR;
	QStringList tmp = filename.split('/');
	this->exposure = 1 / tmp.at(tmp.size()-1).split('_').at(1).split('.').at(0).toFloat();
	std::cout << this->exposure;
}

/**
 * Destructeur
 */
Image::~Image() = default;

/**
 * Charge une image avec OpenCV
 * @param filename chemin d'accès à l'image
 */
void Image::loadImage(const QString& filename) {
	image = cv::imread(filename.toStdString());
}

/**
 * Retourne une image au format QImage (à utiliser dans les widgets UI Qt).
 * @return
 */
QImage Image::getQImage() const {
	return QImage(image.data, image.cols, image.rows, image.step1(), QImage::Format_RGB888).rgbSwapped();
}

/**
 * Applique sur place une image à gamme dynamique classique mais étalonnée à partir des images HDR, de 0 à 255.
 * @return
 */
void Image::tonemapDrago() {
	cv::Mat result;
	cv::Ptr<cv::TonemapDrago> tonemap = cv::createTonemapDrago(3, 3);
    image.convertTo(image, CV_32F);
	tonemap->process(image, result);
	result *= 255;
	cv::imwrite("../images/test.jpg", result);
	image = std::move(result);
}
