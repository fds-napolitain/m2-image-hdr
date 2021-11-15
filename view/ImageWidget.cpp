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
 * Charge une image et initialise ses composants graphiques.
 * @param filename
 */
void ImageWidget::loadImage(const QString& filename, QGroupBox *stack) {
	image = Image(filename);
    label->setGeometry(QRect(20, 10, 371, 311));
	image.getQImage().save("../images/test1.jpg"); // marche
	reloadImage();
    stack->layout()->addWidget(label);
}

/**
 * Charge une image à partir d'une image existante.
 * @param image à copier
 */
void ImageWidget::loadImage(const Image& image) {
	this->image = Image(image);
	cv::imwrite("../images/test2bis.jpg", this->image.image); // marche
	this->image.getQImage().save("../images/test2.jpg"); // marche pas
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
	label->resize(image.getQImage().width() / 10, image.getQImage().height() / 10); // faudrait trouver mieux adapter
	label->setPixmap(QPixmap::fromImage(image.getQImage().scaled(label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)));
}
