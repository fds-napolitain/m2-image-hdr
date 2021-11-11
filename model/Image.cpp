//
// Created by Maxime Boucher on 30/10/2021.
//

#include "Image.hpp"

Image::Image() = default;

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
 * Charge une image avec OpenCV
 * @param filename QString filename
 */
void Image::loadImage(const QString& filename) {
	image = cv::imread(filename.toStdString());
}

/**
 * Retourne une image au format QImage (à utiliser dans les widgets UI Qt).
 * @return
 */
QImage Image::getImage() const {
	return QImage(image.data, image.cols, image.rows, QImage::Format_RGB888).rgbSwapped();
}
