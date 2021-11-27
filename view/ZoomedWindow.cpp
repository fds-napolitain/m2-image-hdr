//
// Created by Maxime Boucher on 27/11/2021.
//

#include "ZoomedWindow.hpp"

#include "MainWindow.hpp"
#include <QPixmap>
#include <iostream>

/**
 * Fenêtre principale
 */
ZoomedWindow::ZoomedWindow() : QMainWindow() {
	widget = new QWidget;
	setCentralWidget(widget);

	createActions();
	createMenus();

	result = new ImageWidget;
	result->getQLabel()->setScaledContents(false);

}

ZoomedWindow::~ZoomedWindow() {
	delete result;
	delete widget;
}

/**
 * Crée les actions de la barre de menu.
 */
void ZoomedWindow::createActions() {
	actionQuit = new QAction(tr("&Quit"), this);
	actionQuit->setShortcut(QKeySequence(Qt::Key_Escape));
	actionQuit->setStatusTip(tr("Quit"));
	connect(actionQuit, &QAction::triggered, this, &ZoomedWindow::quit);
}

/**
 * Assemble la barre de menus.
 */
void ZoomedWindow::createMenus() {
	menuFile = menuBar()->addMenu(tr("&File"));
	menuFile->addAction(actionQuit);
}

/**
 * Initialise l'image
 */
void ZoomedWindow::setImage(const Image& image) {
	result->loadImage(image);
	result->reloadImage();
}

/**
 * Slot action: quit window
 */
void ZoomedWindow::quit() {
	std::cout << "quitter";
}
