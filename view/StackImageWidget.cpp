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
    stack->setLayout(new QHBoxLayout);
	this->parent = parent;
	this->setParent(parent);
}

/**
 * Destructeur
 */
StackImageWidget::~StackImageWidget() {
	for (auto &image: images) {
		delete image;
	}
}

/**
 * Charge un lot d'images
 * @param filenames
 */
void StackImageWidget::loadImages(const QStringList &filenames) {
	images.resize(filenames.size());
	QSize size;
	for (int i = 0; i < filenames.size(); i++) {
		images[i] = new ImageWidget(stack);
		images[i]->loadImage(filenames[i], stack);
		size = images[i]->getQLabel()->size();
	}
	stack->resize(size.width()*filenames.size(), size.height());
	parent->resize(size.width()*filenames.size(), size.height()*2);
}

/**
 * Retourne les Image sous forme de StackImage (pour HDR)
 * @return
 */
StackImage StackImageWidget::getImages() {
	StackImage stackImage;
	for (const auto &image: images) {
		stackImage.addImage(image->getImage());
	}
	return stackImage;
}

/**
 * Aligne les images (photos prises par téléphone).
 * @return
 */
void StackImageWidget::alignMTB() {
	getImages().alignMTB();
	for (const auto &image: images) {
		image->reloadImage();
	}
}

/**
 * Applique le merge de Debevec sur une StackImage.
 * @return
 */
Image StackImageWidget::mergeDebevec() {
	return getImages().mergeDebevec();
}
