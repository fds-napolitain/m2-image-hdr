#include "MainWindow.hpp"
#include <QPixmap>
#include <iostream>

// https://doc.qt.io/qt-5/qtwidgets-mainwindows-menus-example.html

MainWindow::MainWindow() : QMainWindow() {
	QWidget *widget = new QWidget;
	setCentralWidget(widget);

	QWidget *topFiller = new QWidget;
	topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	labelInfo = new QLabel(tr("<i>Choose a menu option, or right-click to "
							  "invoke a context menu</i>"));
	labelInfo->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
	labelInfo->setAlignment(Qt::AlignCenter);

	QWidget *bottomFiller = new QWidget;
	bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	createActions();
	createMenus();

	QPixmap pm;

	QLabel myLabel;
	myLabel.resize(400, 400);
	myLabel.setPixmap(pm);
//	myLabel.setPixmap(QPixmap::fromImage(myImage));
	myLabel.show();
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
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home/jana", tr("Image Files (*.png *.jpg *.bmp)"));
	image.loadImage(fileName);

	std::cout << "Open file: " << fileName.toStdString() << std::endl;
}
