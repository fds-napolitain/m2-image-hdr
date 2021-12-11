//
// Created by Maxime Boucher on 13/11/2021.
//

#ifndef QTHDR_IMAGEWIDGET_HPP
#define QTHDR_IMAGEWIDGET_HPP


#include <QLabel>
#include "../model/Image.hpp"
#include "../model/Pipeline.hpp"
#include <QHBoxLayout>
#include <QGroupBox>
#include <QGridLayout>
#include <QMouseEvent>

/**
 * Widget englobant une image.
 */
class ImageWidget : public QWidget {

private:
	QWidget* parent;
	Image image;
	QLabel* label;
	QBoxLayout *layout;
	float arWidth; // aspect ratio width
	float arHeight; // aspect ratio height
public:
	Merge merged = Merge::NONE;
	Tonemap tonemapped = Tonemap::NONE;
	Contrast contrasted = Contrast::NONE;
	ImageWidget();
	explicit ImageWidget(QWidget* parent);
	~ImageWidget() override;
	void loadImage(const Image& image);
	void reloadImage();
	Image* getImage();
	void loadImage(const QString& filename, QGroupBox *stack);
	QLabel* getQLabel();
	void reset();
	void resizeEvent(QResizeEvent *event) override;

};


#endif //QTHDR_IMAGEWIDGET_HPP
