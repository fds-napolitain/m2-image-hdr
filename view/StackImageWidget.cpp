//
// Created by Maxime Boucher on 14/11/2021.
//

#include <QHBoxLayout>
#include "StackImageWidget.hpp"

StackImageWidget::StackImageWidget() = default;

/**
 * Crée un stack d'image à partir d'un parent
 * @param parent
 */
StackImageWidget::StackImageWidget(QWidget *parent) {
	stack = new QGroupBox(parent);
}

/**
 * Charge un lot d'images
 * @param filenames
 */
void StackImageWidget::loadImages(const QStringList &filenames) {
	images.resize(filenames.size());
	for (int i = 0; i < filenames.size(); i++) {
		images[i] = new ImageWidget(stack);
		images[i]->loadImage(filenames[i]);
		QSize size = images[i]->getQLabel()->size();
		stack->resize(size.width()*filenames.size(), size.height());
		stack->setLayout(new QHBoxLayout);
	}
}

StackImage StackImageWidget::getImages() {
	StackImage stackImage;
	for (const auto &image: images) {
		stackImage.addImage(image->getImage());
	}
	return stackImage;
}
