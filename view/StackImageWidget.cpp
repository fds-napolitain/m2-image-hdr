//
// Created by Maxime Boucher on 14/11/2021.
//

#include "StackImageWidget.hpp"

StackImageWidget::StackImageWidget() = default;

/**
 * Crée un stack d'images à partir d'un parent
 * @param parent
 */
StackImageWidget::StackImageWidget(QWidget *parent) {
    scrollLayout = new QVBoxLayout(this);
	scrollLayout->setParent(this);
	scroll = new QScrollArea(parent);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollLayout->addWidget(scroll);
	stack = new QGroupBox(scroll);
	stack->setLayout(new QHBoxLayout);

//    stack->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::MinimumExpanding);

    QSizePolicy myPol;
    //myPol.setWidthForHeight(true);
    //myPol.setHeightForWidth(true);
    myPol.setRetainSizeWhenHidden(true);
    myPol.setHorizontalPolicy(QSizePolicy::Fixed);
    myPol.setVerticalPolicy(QSizePolicy::MinimumExpanding);
    stack->setSizePolicy(myPol);

    scroll->setWidget(stack);
	scroll->setHorizontalScrollBar(new QScrollBar);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    //scroll->setFixedWidth(700);

	scroll->show();
	this->parent = parent;
	this->setParent(parent);
}

/**
 * Destructeur
 */
StackImageWidget::~StackImageWidget() = default;

/**
 * Charge un lot d'images et supprimes si besoin les anciennes images chargées.
 * @param filenames
 */
void StackImageWidget::loadImages(const QStringList &filenames) {
	std::cout << "1. Charge les images\n";
	for (auto &image: images) {
		delete image;
	}
	aligned = Align::NONE;
	images.resize(filenames.size());
	QSize size;
	for (int i = 0; i < filenames.size(); i++) {
        images[i] = new ImageViewerUp(stack);
		images[i]->loadImage(filenames[i], stack);
		size = images[i]->getQLabel()->size();
	}
	stack->resize(size.width()*filenames.size(), size.height());
    stack->setMinimumWidth(size.width()*filenames.size());
	parent->resize(size.width()*filenames.size(), size.height()*2);
    scroll->show();
}

/**
 * Retourne les Image sous forme de StackImage (pour HDR)
 * @return
 */
StackImage StackImageWidget::getImages() {
	StackImage stackImage;
	for (auto &image: images) {
		stackImage.addImage(image->getImage());
	}
	return stackImage;
}

/**
 * Aligne les images sans trépied.
 * @return
 */
void StackImageWidget::alignMTB() {
	std::cout << "2. Exécute l'alignement MTB\n";
	getImages().alignMTB();
	for (auto &image: images) {
		image->reloadImage();
	}
}

/**
 * Applique le merge de Debevec sur une StackImage.
 * @return
 */
Image StackImageWidget::mergeDebevec() {
	std::cout << "3. Exécute le merge de Debevec\n";
	return getImages().mergeDebevec();
}

/**
 * Applique le merge de Robertson sur une StackImage.
 * @return
 */
Image StackImageWidget::mergeRobertson() {
	std::cout << "3. Exécute le merge de Robertson\n";
	return getImages().mergeRobertson();
}

/**
 * Applique le merge de Mertens sur une StackImage.
 * @return
 */
Image StackImageWidget::mergeMertens(bool s) {
	std::cout << "3. Exécute le merge de Mertens.\n";
	return getImages().mergeMertens();
}

/**
 * Applique le merge de Mertens sur une StackImage.
 * @return
 */
Image StackImageWidget::merge() {
	std::cout << "3. Exécute le merge de débruitage.\n";
	return getImages().merge();
}
