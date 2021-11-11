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
	actionOpenFiles = new QAction(tr("&Open Files"), this);

    actionOpenFiles->setShortcut(QKeySequence(Qt::Key_O));
    actionOpenFiles->setStatusTip(tr("Open a set of images"));
	connect(actionOpenFiles, &QAction::triggered, this, &MainWindow::openFiles);

    actionOpenFolder = new QAction(tr("&Open Folder"), this);
    actionOpenFolder->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    actionOpenFolder->setStatusTip(tr("Open a folder of images"));
    connect(actionOpenFolder, &QAction::triggered, this, &MainWindow::openFolder);
}

/**
 * Crée les menus
 */
void MainWindow::createMenus() {
	menuFile = menuBar()->addMenu(tr("&File"));
	menuFile->addAction(actionOpenFiles);
    menuFile->addAction(actionOpenFolder);
}

/**
 * Slot action: ouvrir une ou plusieurs images
 */
void MainWindow::openFiles() {
	QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open Images"), "../images/", tr("Image Files (*.png *.jpg *.JPG *.bmp)"));
	if (fileNames.empty()) {
		return;
	}
	image.loadImages(fileNames);
	qDebug() << fileNames;
    myLabel->resize(image.getImage().width()/10, image.getImage().height()/10);
	myLabel->setPixmap(QPixmap::fromImage(image.getImage().scaled(myLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)));
}

/**
 * Slot action: ouvrir un dossier d'images
 */
void MainWindow::openFolder() {
    QDir directory(QFileDialog::getExistingDirectory(this, tr("Open folder"), "../images/"));
	QStringList fileNames = directory.entryList(QStringList() << "*.jpg" << "*.JPG", QDir::Files);
	if (fileNames.empty()) {
		return;
	}
	image.loadImages(fileNames);
	qDebug() << fileNames;
	myLabel->resize(image.getImage().width()/10, image.getImage().height()/10); // faudrait trouver mieux adapter
	myLabel->setPixmap(QPixmap::fromImage(image.getImage().scaled(myLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)));

	/*int nbcol = fileNames.size() / 5;
    int i = 0;
    for (const QString &img: fileNames) {
        qDebug() << img;

    }*/
}
