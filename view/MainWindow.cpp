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
	actionMergeDebevec->setShortcut(QKeySequence(Qt::Key_Q));
	actionMergeDebevec->setStatusTip(tr("Merge files with Debevec method"));
	connect(actionMergeDebevec, &QAction::triggered, this, &MainWindow::mergeDebevec);

	actionTonemapDrago = new QAction(tr("&Tonemap with Drago"), this);
	actionTonemapDrago->setShortcut(QKeySequence(Qt::Key_W));
	actionTonemapDrago->setStatusTip(tr("Map images to a LDR image using Drago method"));
	connect(actionTonemapDrago, &QAction::triggered, this, &MainWindow::tonemapDrago);
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
	menuTonemap->addAction(actionTonemapDrago);
}

/**
 * Exécute toutes les actions
 */
void MainWindow::executePipeline() {
	switch (pipeline.align) {
		case Align::NONE:
			break;
		case Align::MTB:
			images->alignMTB();
			break;
	}
	switch (pipeline.merge) {
		case Merge::NONE:
			break;
		case Merge::Debevec:
			result->loadImage(images->mergeDebevec());
			break;
		case Merge::Mertens:
			break;
	}
	switch (pipeline.tonemap) {
		case Tonemap::NONE:
			break;
		case Tonemap::Drago:
			result->getImage()->tonemapDrago();
			break;
	}
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
	pipeline.align = Align::MTB;
	executePipeline();
}

/**
 * Slot action: merge les images avec la méthode de Debevec.
 */
void MainWindow::mergeDebevec() {
	pipeline.merge = Merge::Debevec;
	executePipeline();
}

/**
 * Slot action: applique un mappage ton local avec la méthode de Drago.
 */
void MainWindow::tonemapDrago() {
	pipeline.tonemap = Tonemap::Drago;
	executePipeline();
}