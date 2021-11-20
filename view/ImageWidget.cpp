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
	this->setParent(parent);
}

/**
 * Destructeur
 */
ImageWidget::~ImageWidget() {
	delete label;
}

/**
 * Charge une image et initialise ses composants graphiques.
 * @param filename
 */
void ImageWidget::loadImage(const QString& filename, QGroupBox *stack) {
	image = Image(filename);
    label->setGeometry(QRect(20, 10, 371, 311));
	reloadImage();
    stack->layout()->addWidget(label);
}

/**
 * Charge une image à partir d'une image existante.
 * @param image à copier
 */
void ImageWidget::loadImage(const Image& image) {
	this->image = Image(image);
    this->image.image.convertTo(this->image.image, CV_8U);
	reloadImage();
}

/**
 * Retourne l'image avec cv::Mat
 * @return
 */
Image* ImageWidget::getImage() {
	return &image;
}

/**
 * Retourne le label d'affichage de l'image.
 * @return
 */
QLabel* ImageWidget::getQLabel() {
	return label;
}

/**
 * Recharge l'image sur la page.
 */
void ImageWidget::reloadImage() {
	double w = image.getQImage().width() / 300.0;
	double h = image.getQImage().height() / 400.0;
	if (w > h) {
		label->resize(image.getQImage().width() / w, image.getQImage().height() / w);
	} else {
		label->resize(image.getQImage().width() / h, image.getQImage().height() / h);
	}
	label->setPixmap(QPixmap::fromImage(image.getQImage().scaled(label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)));
}
