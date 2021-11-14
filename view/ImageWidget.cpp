//
// Created by Maxime Boucher on 13/11/2021.
//

#include "ImageWidget.hpp"

ImageWidget::ImageWidget() = default;

/**
 * Initialise un widget Image à partir de son parent.
 * @param parent
 */
ImageWidget::ImageWidget(QWidget* parent) {
	label = new QLabel(parent);
	label->setScaledContents(true);
	label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	label->show();
}

/**
 * Charge une image et initialise ses composants graphiques.
 * @param filename
 */
void ImageWidget::loadImage(const QString& filename) {
	image = Image(filename);
	label->resize(image.getQImage().width() / 10, image.getQImage().height() / 10); // faudrait trouver mieux adapter
	label->setPixmap(QPixmap::fromImage(image.getQImage().scaled(label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)));
}

Image ImageWidget::getImage() {
	return image;
}

QLabel *ImageWidget::getQLabel() {
	return label;
}
