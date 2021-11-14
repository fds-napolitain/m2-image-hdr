//
// Created by Maxime Boucher on 14/11/2021.
//

#include <QHBoxLayout>
#include "StackImageWidget.hpp"

StackImageWidget::StackImageWidget() = default;

StackImageWidget::StackImageWidget(QWidget *parent) {
	stack = new QGroupBox(parent);
}

void StackImageWidget::loadImages(const QStringList &filenames) {
	images.resize(filenames.size());
	for (int i = 0; i < filenames.size(); i++) {
		images[i] = new ImageWidget(stack);
		images[i]->loadImage(filenames[i]);
		QSize size = images[i]->getQLabel()->size();
		stack->resize(size.width()*3, size.height());
		stack->setLayout(new QHBoxLayout);
	}
}

