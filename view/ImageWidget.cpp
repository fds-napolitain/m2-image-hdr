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
	reloadImage();
    stack->layout()->addWidget(label);
}

/**
 * Charge une image à partir d'une image existante.
 * @param image à copier
 */
void ImageWidget::loadImage(const Image& image) {
	this->image = Image(image.matrix);
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
	if (img.isNull()) return;
	double w = img.width() / 400.0;
	double h = img.height() / 400.0;
	if (w > h) {
		label->resize(img.width() / w, img.height() / w);
	} else {
		label->resize(img.width() / h, img.height() / h);
	}
	std::cout << "Entropie locale moyenne: " << image.getAverageEntropy() << "\n";
	std::cout << "SNR: " << image.getSNR() << "\n";
	label->setPixmap(QPixmap::fromImage(img.scaled(label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)));
}

/**
 * Reset image view
 */
void ImageWidget::reset() {
	label->clear();
}
