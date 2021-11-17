//
// Created by Maxime Boucher on 13/11/2021.
//

#ifndef QTHDR_IMAGEWIDGET_HPP
#define QTHDR_IMAGEWIDGET_HPP


#include <QLabel>
#include "../model/Image.hpp"

#include <QHBoxLayout>
#include <QGroupBox>
#include <QGridLayout>

/**
 * Widget englobant une image.
 */
class ImageWidget : public QWidget {

private:
	Image image;
	QLabel* label;
public:
	ImageWidget();
	explicit ImageWidget(QWidget* parent);
	~ImageWidget() override;
	void loadImage(const Image& image);
	void reloadImage();
	Image* getImage();
	void loadImage(const QString& filename, QGroupBox *stack);
	QLabel* getQLabel();

};


#endif //QTHDR_IMAGEWIDGET_HPP
