#include "MainWindow.hpp"
#include <QPixmap>
#include <iostream>

/**
 * Fenêtre principale
 */
MainWindow::MainWindow() : QMainWindow() {
	widget = new QWidget;
	setCentralWidget(widget);

	createActions();
	createMenus();

	myLabel = new QLabel(widget);
    myLabel->setScaledContents(true);
    myLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

	myLabel->show();
}

/**
 * Crée les actions
 */
void MainWindow::createActions() {
	actionOpen = new QAction(tr("&Open"), this);
	actionOpen->setShortcuts(QKeySequence::New);
	actionOpen->setStatusTip(tr("Open an image"));
	connect(actionOpen, &QAction::triggered, this, &MainWindow::open);
}

/**
 * Crée les menus
 */
void MainWindow::createMenus() {
	menuFile = menuBar()->addMenu(tr("&File"));
	menuFile->addAction(actionOpen);
}

/**
 * Slot action: ouvrir un dossier de fichiers
 * (Pour le moment, 1 seul)
 */
void MainWindow::open() {
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "../images/", tr("Image Files (*.png *.jpg *.bmp .JPG)"));
	image.loadImage(fileName);
	std::cout << "Open file: " << fileName.toStdString() << std::endl;
    myLabel->resize(image.getImage().width()/10, image.getImage().height()/10);
    myLabel->setPixmap(QPixmap::fromImage(image.getImage().scaled(myLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)));
}
