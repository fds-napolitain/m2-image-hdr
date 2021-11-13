//
// Created by Maxime Boucher on 13/11/2021.
//

#include "ImageWidget.hpp"

ImageWidget::ImageWidget() {

}

ImageWidget::ImageWidget(QWidget* parent) {
	label = new QLabel(parent);
	label->setScaledContents(true);
	label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	label->show();
}
