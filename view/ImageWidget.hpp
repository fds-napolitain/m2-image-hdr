//
// Created by Maxime Boucher on 13/11/2021.
//

#ifndef QTHDR_IMAGEWIDGET_HPP
#define QTHDR_IMAGEWIDGET_HPP


#include <QLabel>
#include "../model/Image.hpp"

/**
 * Widget englobant une image.
 */
class ImageWidget : QWidget {

private:
	Image image;
	QLabel* label;
public:
	ImageWidget();
	explicit ImageWidget(QWidget* parent);
	void loadImage(const QString& filename);
	Image* getImage();
	QLabel* getQLabel();

};


#endif //QTHDR_IMAGEWIDGET_HPP
