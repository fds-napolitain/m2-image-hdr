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

	images = new StackImageWidget(widget);
	result = new ImageWidget(widget);
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

	actionMergeDebevec = new QAction(tr("&Merge with Debevec"), this);
	actionMergeDebevec->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
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
 * Slot action: merge les images avec la méthode de Debevec.
 */
void MainWindow::mergeDebevec() {

}
