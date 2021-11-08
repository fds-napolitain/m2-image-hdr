//
// Created by Maxime Boucher on 08/11/2021.
//

#ifndef QTHDR_STACKIMAGE_HPP
#define QTHDR_STACKIMAGE_HPP


#include <vector>
#include <QDir>
#include "Image.hpp"

class StackImage {

private:
	std::vector<Image> images;
public:
	StackImage();
	explicit StackImage(const QString& foldername);
	bool loadImages(const QString& foldername);
};


#endif //QTHDR_STACKIMAGE_HPP
