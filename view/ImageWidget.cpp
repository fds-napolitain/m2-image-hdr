//
// Created by Maxime Boucher on 13/11/2021.
//

#include "ImageWidget.hpp"
#include <QGuiApplication>


ImageWidget::ImageWidget() {
	delete label;
}

/**
 * Initialise un widget Image à partir de son parent.
 * @param parent
 */
ImageWidget::ImageWidget(QWidget* parent)
{
    this->parent = parent;
    layout = new QBoxLayout(QBoxLayout::LeftToRight, this);

    label = new QLabel(parent);
    // add spacer, then your widget, then spacer
    layout->addWidget(label);

    label->setBackgroundRole(QPalette::Base);
    label->setScaledContents(true);

   // scrollArea= new QScrollArea(this);

//    scrollArea->setBackgroundRole(QPalette::Dark);
//    scrollArea->setWidget(label);
//    scrollArea->setVisible(true);

//    resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
}

/**
 * Destructeur
 */
ImageWidget::~ImageWidget() = default;

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
    double h = RESULT_SIZE / static_cast<double>(img.height());
    arHeight = RESULT_SIZE;
	arWidth = img.width() * h;
	label->resize(static_cast<int>(this->arWidth), static_cast<int>(this->arHeight));
	std::cout << "Entropie locale moyenne: " << image.getAverageEntropy() << "\n";
	//std::cout << "SNR: " << image.getSNR() << "\n";
	label->setPixmap(QPixmap::fromImage(img.scaled(label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)));
}

/**
 * Reset image view
 */
void ImageWidget::reset() {
	label->clear();
}

/**
 *
 * @param event
 */
void ImageWidget::resizeEvent(QResizeEvent *event) {
	float thisAspectRatio = static_cast<float>(event->size().width()) / static_cast<float>(event->size().height());
	int widgetStretch, outerStretch;

	if (thisAspectRatio > (arWidth/arHeight)) // too wide
	{
		layout->setDirection(QBoxLayout::LeftToRight);
		widgetStretch = static_cast<int>(static_cast<float>(this->height()) * (this->arWidth / this->arHeight)); // i.e., my width
		outerStretch = (width() - widgetStretch) / 2 + 0.5;
	}
	else // too tall
	{
		layout->setDirection(QBoxLayout::TopToBottom);
		widgetStretch = width() * (arHeight/arWidth); // i.e., my height
		outerStretch = (height() - widgetStretch) / 2 + 0.5;
	}

	layout->setStretch(0, outerStretch);
	layout->setStretch(1, widgetStretch);
	layout->setStretch(2, outerStretch);}
