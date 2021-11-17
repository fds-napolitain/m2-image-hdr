//
// Created by Maxime Boucher on 14/11/2021.
//

#ifndef QTHDR_STACKIMAGEWIDGET_HPP
#define QTHDR_STACKIMAGEWIDGET_HPP

#include <vector>
#include <QGroupBox>
#include "ImageWidget.hpp"
#include "../model/StackImage.hpp"

class StackImageWidget : public QWidget {

private:
	std::vector<ImageWidget*> images;
	QWidget* parent;
public:
	QGroupBox* stack;
	StackImageWidget();
	explicit StackImageWidget(QWidget* parent);
	~StackImageWidget() override;
	void loadImages(const QStringList& filenames);
	StackImage getImages();
	// -- méthodes hdr
	void alignMTB();
	Image mergeDebevec();

};


#endif //QTHDR_STACKIMAGEWIDGET_HPP
