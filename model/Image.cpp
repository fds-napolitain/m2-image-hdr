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
 * Retourne l'image format cv::Mat
 * @return
 */
cv::Mat Image::getMat() {
	return image;
}

/**
 * Retourne une image au format QImage (à utiliser dans les widgets UI Qt).
 * @return
 */
QImage Image::getQImage() const {
	return QImage(image.data, image.cols, image.rows, QImage::Format_RGB888).rgbSwapped();
}

/**
 * Retourne le temps d'exposition en millieme de secondes
 * @return
 */
float Image::getExposure() const {
	return exposure;
}

/**
 * Retourne la longueur focale en millimètre
 * @return
 */
float Image::getFocal() const {
	return focal;
}

/**
 * Retourne la valeur ISO
 * @return
 */
float Image::getISO() const {
	return ISO;
}
