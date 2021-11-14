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

	hdrbox = new QGroupBox(widget);
	hdrbox->setLayout(new QVBoxLayout);
	images = new StackImageWidget(hdrbox);
	result = new ImageWidget(hdrbox);
}

/**
 * Crée les actions
 */
void MainWindow::createActions() {
	actionOpenFiles = new QAction(tr("&Open Files"), this);

    actionOpenFiles->setShortcut(QKeySequence(Qt::Key_O));
    actionOpenFiles->setStatusTip(tr("Open a set of images"));
	connect(actionOpenFiles, &QAction::triggered, this, &MainWindow::openFiles);

    actionOpenFolder = new QAction(tr("&Open Folder"), this);
    actionOpenFolder->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    actionOpenFolder->setStatusTip(tr("Open a folder of images"));
    connect(actionOpenFolder, &QAction::triggered, this, &MainWindow::openFolder);

	actionAlignMTB = new QAction(tr("&Align images"), this);
	actionAlignMTB->setShortcut(QKeySequence(Qt::Key_A));
	actionAlignMTB->setStatusTip(tr("Open a folder of images"));
	connect(actionAlignMTB, &QAction::triggered, this, &MainWindow::alignMTB);

	actionMergeNaive = new QAction(tr("&Merge naively"), this);
	actionMergeDebevec = new QAction(tr("&Merge with Debevec"), this);
	actionMergeDebevec->setShortcut(QKeySequence(Qt::Key_D));
	actionMergeDebevec->setStatusTip(tr("Merge files with Debevec method"));
	connect(actionMergeDebevec, &QAction::triggered, this, &MainWindow::mergeDebevec);
}

/**
 * Crée les menus
 */
void MainWindow::createMenus() {
	menuFile = menuBar()->addMenu(tr("&File"));
	menuFile->addAction(actionOpenFiles);
    menuFile->addAction(actionOpenFolder);

	menuAlign = menuBar()->addMenu(tr("&Align"));
	menuAlign->addAction(actionAlignMTB);

	menuMerge = menuBar()->addMenu(tr("&Merge"));
	menuMerge->addAction(actionMergeNaive);
	menuMerge->addAction(actionMergeDebevec);

	menuTonemap = menuBar()->addMenu(tr("&Tonemap"));
}

/**
 * Slot action: ouvrir une ou plusieurs images
 */
void MainWindow::openFiles() {
	QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open Images"), "../images/", tr("Image Files (*.png *.jpg *.JPG *.bmp)"));
	if (fileNames.empty()) {
		qDebug() << tr("Empty file list");
		return;
	}
	images->loadImages(fileNames);
	qDebug() << fileNames;
}

/**
 * Slot action: ouvrir un dossier d'images
 */
void MainWindow::openFolder() {
    QDir directory(QFileDialog::getExistingDirectory(this, tr("Open folder"), "../images/"));
	QStringList fileNames = directory.entryList(QStringList() << tr("*.jpg") << tr("*.JPG"), QDir::Files);
	for (QString& fileName: fileNames) {
		fileName = directory.path().append(tr("/")).append(fileName);
	}
	if (fileNames.empty()) {
		qDebug() << tr("Empty folder");
		return;
	}
	images->loadImages(fileNames);
	qDebug() << fileNames;
}

/**
 * Slot action: alignement MTB
 */
void MainWindow::alignMTB() {
	images->alignMTB();
}

/**
 * Slot action: merge les images avec la méthode de Debevec.
 */
void MainWindow::mergeDebevec() {
	result->loadImage(images->mergeDebevec());
}
