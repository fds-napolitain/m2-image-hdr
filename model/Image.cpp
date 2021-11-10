//
// Created by Maxime Boucher on 30/10/2021.
//

#include "Image.hpp"

Image::Image() {

}

Image::Image(const QString& filename, bool isHDR) {
	loadImage(filename);
	this->isHDR = isHDR;
}

/**
 * Charge une image
 * @param filename
 * @return
 */
bool Image::loadImage(const QString& filename) {
	image.load(filename);
}

QImage Image::getImage() {
	return image;
}
