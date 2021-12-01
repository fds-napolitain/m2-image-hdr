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
	this->parent = parent;
	label = new QLabel(parent);
	label->setScaledContents(true);
	label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	label->show();
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
	this->image = Image(image.image);
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
	QImage img = image.getQImage();
	double w = img.width() / 500.0;
	double h = img.height() / 500.0;
	if (w > h) {
		label->resize(img.width() / w, img.height() / w);
	}
	else {
		label->resize(img.width() / h, img.height() / h);
	}
	std::cout << "Entropy: " << image.getAverageEntropy() << "\n";
	label->setPixmap(QPixmap::fromImage(img.scaled(label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)));
}

/**
 * Reset image view
 */
void ImageWidget::reset() {
	label->clear();
}
