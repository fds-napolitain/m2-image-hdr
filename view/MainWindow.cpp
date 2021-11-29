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
	hdrbox->layout()->addWidget(images->stack);

    result->getQLabel()->setScaledContents(false);
	hdrbox->layout()->addWidget(result->getQLabel());

}

/**
 * Destructeur (utile ici? pas sur)
 */
MainWindow::~MainWindow() {
	delete widget;
	delete hdrbox;
	delete images;
	delete result;
}

/**
 * Crée les actions de la barre de menu.
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
    actionQuit = new QAction(tr("&Quit"), this);
    actionQuit->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    actionQuit->setStatusTip(tr("Quit"));
    connect(actionQuit, &QAction::triggered, this, &MainWindow::quit);

	actionAlignMTB = new QAction(tr("&Align images"), this);
	actionAlignMTB->setShortcut(QKeySequence(Qt::Key_A));
	actionAlignMTB->setStatusTip(tr("Align images using MTB"));
	actionAlignMTB->setCheckable(true);
	connect(actionAlignMTB, &QAction::triggered, this, &MainWindow::alignMTB);
	actionGroupAlign = new QActionGroup(this);
	actionGroupAlign->addAction(actionAlignMTB);
	actionGroupAlign->setExclusive(true);

	actionMergeDebevec = new QAction(tr("&Merge with Debevec"), this);
	actionMergeDebevec->setShortcut(QKeySequence(Qt::Key_Z));
	actionMergeDebevec->setStatusTip(tr("Merge files with Debevec method"));
	actionMergeDebevec->setCheckable(true);
	connect(actionMergeDebevec, &QAction::triggered, this, &MainWindow::mergeDebevec);
	actionMergeMertens = new QAction(tr("&Merge with Mertens"), this);
	actionMergeMertens->setShortcut(QKeySequence(Qt::Key_S));
	actionMergeMertens->setStatusTip(tr("Merge files with Mertens method"));
	actionMergeMertens->setCheckable(true);
	connect(actionMergeMertens, &QAction::triggered, this, &MainWindow::mergeMertens);
	actionGroupMerge = new QActionGroup(this);
	actionGroupMerge->addAction(actionMergeDebevec);
	actionGroupMerge->addAction(actionMergeMertens);
	actionGroupMerge->setExclusive(true);

	actionTonemapNone = new QAction(tr("&None"), this);
	actionTonemapNone->setShortcut(QKeySequence(Qt::Key_E));
	actionTonemapNone->setStatusTip(tr("None"));
	actionTonemapNone->setCheckable(true);
	connect(actionTonemapNone, &QAction::triggered, this, &MainWindow::tonemapNone);
	actionTonemapDrago = new QAction(tr("&Tonemap with Drago"), this);
	actionTonemapDrago->setShortcut(QKeySequence(Qt::Key_D));
	actionTonemapDrago->setStatusTip(tr("Map images to a LDR image using Drago method"));
	actionTonemapDrago->setCheckable(true);
	connect(actionTonemapDrago, &QAction::triggered, this, &MainWindow::tonemapDrago);
	actionTonemapReinhard = new QAction(tr("&Tonemap with Reinhard"), this);
	actionTonemapReinhard->setShortcut(QKeySequence(Qt::Key_C));
	actionTonemapReinhard->setStatusTip(tr("Map images to a LDR image using Reinhard method"));
	actionTonemapReinhard->setCheckable(true);
	connect(actionTonemapReinhard, &QAction::triggered, this, &MainWindow::tonemapReinhard);
	actionGroupTonemap = new QActionGroup(this);
	actionGroupTonemap->addAction(actionTonemapNone);
	actionGroupTonemap->addAction(actionTonemapDrago);
	actionGroupTonemap->addAction(actionTonemapReinhard);
	actionGroupTonemap->setExclusive(true);
}

/**
 * Assemble la barre de menus.
 */
void MainWindow::createMenus() {
	menuFile = menuBar()->addMenu(tr("&File"));
	menuFile->addAction(actionOpenFiles);
    menuFile->addAction(actionOpenFolder);
    menuFile->addAction(actionQuit);

	menuAlign = menuBar()->addMenu(tr("&Align"));
	menuAlign->addAction(actionAlignMTB);

	menuMerge = menuBar()->addMenu(tr("&Merge"));
	menuMerge->addAction(actionMergeDebevec);
	menuMerge->addAction(actionMergeMertens);

	menuTonemap = menuBar()->addMenu(tr("&Tonemap"));
	menuTonemap->addAction(actionTonemapNone);
	menuTonemap->addAction(actionTonemapDrago);
	menuTonemap->addAction(actionTonemapReinhard);
}

/**
 * Exécute toutes les actions
 */
void MainWindow::executePipeline() {
	std::cout << "========== PIPELINE RUN START ===========\n";
	if (images->aligned != pipeline.align) {
		switch (pipeline.align) {
			case Align::NONE:
				break;
			case Align::MTB:
				images->alignMTB();
				images->aligned = Align::MTB;
				break;
		}
	}
	if (result->merged != pipeline.merge || result->tonemapped != pipeline.tonemap) {
		switch (pipeline.merge) {
			case Merge::NONE:
				break;
			case Merge::Debevec:
				result->loadImage(images->mergeDebevec());
				result->merged = Merge::Debevec;
				result->tonemapped = Tonemap::NONE;
				break;
			case Merge::Mertens:
				result->loadImage(images->mergeMertens());
				result->merged = Merge::Mertens;
				result->tonemapped = Tonemap::NONE;
				break;
		}
	}
	if (result->tonemapped != pipeline.tonemap) {
		switch (pipeline.tonemap) {
			case Tonemap::NONE:
				result->reloadImage();
				break;
			case Tonemap::Drago:
				result->getImage()->tonemapDrago();
				result->reloadImage();
				result->tonemapped = Tonemap::Drago;
				break;
			case Tonemap::Reinhard:
				result->getImage()->tonemapReinhard();
				result->reloadImage();
				result->tonemapped = Tonemap::Reinhard;
				break;
		}
	}
	std::cout << "========== PIPELINE RUN END ===========\n";
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
 * Quitte l'application
 */
void MainWindow::quit() {
	QApplication::quit();
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
 * Slot action: merge les images avec la méthode de Debevec.
 */
void MainWindow::mergeMertens() {
	pipeline.merge = Merge::Mertens;
	executePipeline();
}

/**
 * Reset tonemap
 */
void MainWindow::tonemapNone() {
	pipeline.tonemap = Tonemap::NONE;
	executePipeline();
}

/**
 * Slot action: applique un mappage ton local avec la méthode de Drago.
 */
void MainWindow::tonemapDrago() {
	pipeline.tonemap = Tonemap::Drago;
	executePipeline();
}

/**
 * Slot action: applique un mappage ton local avec la méthode de Reinhard.
 */
void MainWindow::tonemapReinhard() {
	pipeline.tonemap = Tonemap::Reinhard;
	executePipeline();
}
