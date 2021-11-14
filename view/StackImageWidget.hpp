//
// Created by Maxime Boucher on 14/11/2021.
//

#ifndef QTHDR_STACKIMAGEWIDGET_HPP
#define QTHDR_STACKIMAGEWIDGET_HPP

#include <vector>
#include <QGroupBox>
#include "ImageWidget.hpp"

class StackImageWidget {

private:
	std::vector<ImageWidget*> images;
	QGroupBox* stack;
public:
	StackImageWidget();
	explicit StackImageWidget(QWidget* parent);
	void loadImages(const QStringList& filenames);

};


#endif //QTHDR_STACKIMAGEWIDGET_HPP
