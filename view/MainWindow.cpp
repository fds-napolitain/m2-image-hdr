#include "MainWindow.hpp"
#include <QPixmap>
#include <iostream>
#include <QSizePolicy>
/**
 * Fenêtre principale
 */
MainWindow::MainWindow() : QMainWindow() {
	widget = new QWidget;
    QGridLayout* widgetLayout = new QGridLayout(widget);
    widget->setLayout(widgetLayout);

    //widget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	setCentralWidget(widget);

    createActions();
    createMenus();
    hdrbox      = new QGroupBox(widget);
    settingsBox = new QGroupBox(widget);
//    settingsBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);




    hdrbox->setLayout(new QVBoxLayout);
    settingsBox->setLayout(new QVBoxLayout);
   // settingsBox->layout()->setContentsMargins(0,0,1500,0);
    images = new StackImageWidget(hdrbox);
    result = new ImageWidget(hdrbox);
    hdrbox->layout()->addWidget(images->stack);

    tonemapGamma = new QLabel("1");
    tonemapSlider = new QSlider(Qt::Horizontal, hdrbox);
    tonemapSlider->setTickPosition(QSlider::TicksAbove);
    tonemapSlider->setValue(1);
    settingsBox->layout()->addWidget(tonemapSlider);
    settingsBox->layout()->addWidget(tonemapGamma);
    widgetLayout->addWidget(hdrbox,0,0,1,8);
    widgetLayout->addWidget(settingsBox,1,0,1,2);





    result->getQLabel()->setScaledContents(false);
    hdrbox->layout()->addWidget(result->getQLabel());
    QObject::connect(tonemapSlider, &QSlider::valueChanged, this, [=] () {
        tonemapGamma->setText(QString::number(tonemapSlider->value() * 0.25f));
		result->tonemapped = Tonemap::NONE;
		executePipeline();
    });
}

/**
 * Destructeur
 * TODO: vérifier que ca marche
 */
MainWindow::~MainWindow() {
	delete widget;
	delete hdrbox;
	delete images;
	delete result;
	delete actionOpenFiles;
	delete actionOpenFolder;
	delete actionSave;
	delete actionQuit;
	delete actionAlignMTB;
	delete actionGroupAlign;
	delete actionMergeDebevec;
	delete actionMergeRobertson;
	delete actionMergeMertens;
	delete actionGroupMerge;
	delete actionTonemapNone;
	delete actionTonemapDrago;
	delete actionTonemapReinhard;
	delete actionGroupTonemap;
	delete actionContrastNone;
	delete actionContrastHistogram;
	delete actionGroupContrast;
	delete menuFile;
	delete menuAlign;
	delete menuMerge;
	delete menuTonemap;
	delete zoomedWindow;
	delete tonemapSlider;
	delete tonemapGamma;
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
    actionSave = new QAction(tr("&Save HDR image"), this);
    actionSave->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    actionSave->setStatusTip(tr("Save HDR image"));
    connect(actionSave, &QAction::triggered, this, &MainWindow::save);
    actionQuit = new QAction(tr("&Quit"), this);
    actionQuit->setShortcut(QKeySequence(Qt::Key_Escape));
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
	actionMergeRobertson = new QAction(tr("&Merge with Robertson"), this);
	actionMergeRobertson->setShortcut(QKeySequence(Qt::Key_S));
	actionMergeRobertson->setStatusTip(tr("Merge files with Debevec method"));
	actionMergeRobertson->setCheckable(true);
	connect(actionMergeRobertson, &QAction::triggered, this, &MainWindow::mergeRobertson);
	actionMergeMertens = new QAction(tr("&Merge with Mertens"), this);
	actionMergeMertens->setShortcut(QKeySequence(Qt::Key_X));
	actionMergeMertens->setStatusTip(tr("Merge files with Mertens method"));
	actionMergeMertens->setCheckable(true);
	connect(actionMergeMertens, &QAction::triggered, this, &MainWindow::mergeMertens);
	actionMergeKalantari = new QAction(tr("&Merged with Kalantari"), this);
	actionMergeKalantari->setCheckable(true);
	actionGroupMerge = new QActionGroup(this);
	actionGroupMerge->addAction(actionMergeDebevec);
	actionGroupMerge->addAction(actionMergeRobertson);
	actionGroupMerge->addAction(actionMergeMertens);
	actionGroupMerge->addAction(actionMergeKalantari);
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

	actionContrastNone = new QAction(tr("&None"), this);
	actionContrastNone->setShortcut(QKeySequence(Qt::Key_R));
	actionContrastNone->setStatusTip(tr("None"));
	actionContrastNone->setCheckable(true);
	connect(actionContrastNone, &QAction::triggered, this, &MainWindow::contrastNone);
	actionContrastHistogram = new QAction(tr("&Contrast with histogram"), this);
	actionContrastHistogram->setShortcut(QKeySequence(Qt::Key_F));
	actionContrastHistogram->setStatusTip(tr("Add more contrast using histogram method"));
	actionContrastHistogram->setCheckable(true);
	connect(actionContrastHistogram, &QAction::triggered, this, &MainWindow::contrastHistogram);
	actionGroupContrast = new QActionGroup(this);
	actionGroupContrast->addAction(actionContrastNone);
	actionGroupContrast->addAction(actionContrastHistogram);
}

/**
 * Assemble la barre de menus.
 */
void MainWindow::createMenus() {
	menuFile = menuBar()->addMenu(tr("&File"));
	menuFile->addAction(actionOpenFiles);
    menuFile->addAction(actionOpenFolder);
    menuFile->addAction(actionSave);
    menuFile->addAction(actionQuit);

	menuAlign = menuBar()->addMenu(tr("&Align"));
	menuAlign->addAction(actionAlignMTB);

	menuMerge = menuBar()->addMenu(tr("&Merge"));
	menuMerge->addAction(actionMergeDebevec);
	menuMerge->addAction(actionMergeRobertson);
	menuMerge->addAction(actionMergeMertens);
	menuMerge->addAction(actionMergeKalantari);

	menuTonemap = menuBar()->addMenu(tr("&Tonemap"));
	menuTonemap->addAction(actionTonemapNone);
	menuTonemap->addAction(actionTonemapDrago);
	menuTonemap->addAction(actionTonemapReinhard);

	menuContrast = menuBar()->addMenu(tr("&Contrast"));
	menuContrast->addAction(actionContrastNone);
	menuContrast->addAction(actionContrastHistogram);
}

/**
 * Réinitialise les actions (ce qui est coché est décoché).
 */
void MainWindow::resetAll() {
	actionAlignMTB->setChecked(false);
	actionMergeDebevec->setChecked(false);
	actionMergeRobertson->setChecked(false);
	actionMergeMertens->setChecked(false);
	actionTonemapNone->setChecked(false);
	actionTonemapDrago->setChecked(false);
	actionTonemapReinhard->setChecked(false);
	actionContrastNone->setChecked(false);
	actionContrastHistogram->setChecked(false);
	pipeline.align = Align::NONE;
	pipeline.merge = Merge::NONE;
	pipeline.tonemap = Tonemap::NONE;
	pipeline.contrast = Contrast::NONE;
}

/**
 * Exécute toutes les actions
 */
void MainWindow::executePipeline() {
	std::cout << "========== PIPELINE RUN START ===========\n";
	if (images->aligned != pipeline.align) {
		switch (pipeline.align) {
			case Align::NONE:
				result->merged = Merge::NONE;
				break;
			case Align::MTB:
				images->alignMTB();
				images->aligned = Align::MTB;
				result->merged = Merge::NONE;
				break;
		}
	}
	if (result->merged != pipeline.merge) {
		switch (pipeline.merge) {
			case Merge::NONE:
				break;
			case Merge::Debevec:
				cache = Image(images->mergeDebevec());
				result->merged = Merge::Debevec;
				result->tonemapped = Tonemap::NONE;
				break;
			case Merge::Robertson:
				cache = Image(images->mergeRobertson());
				result->merged = Merge::Robertson;
				result->tonemapped = Tonemap::NONE;
				break;
			case Merge::Mertens:
				cache = Image(images->mergeMertens());
				result->merged = Merge::Mertens;
				result->tonemapped = Tonemap::NONE;
				break;
			case Merge::Kalantari:
				cache = Image(result->getImage()->image);
				result->merged = Merge::Kalantari;
				result->tonemapped = Tonemap::NONE;
				break;
		}
		result->loadImage(cache);
	}
	if (result->merged != Merge::NONE && (result->tonemapped != pipeline.tonemap || result->contrasted != pipeline.contrast)) {
		result->loadImage(cache);
		switch (pipeline.tonemap) {
			case Tonemap::NONE:
				result->contrasted = Contrast::NONE;
				break;
			case Tonemap::Drago:
				result->getImage()->tonemapDrago(tonemapSlider->value());
				result->tonemapped = Tonemap::Drago;
				result->contrasted = Contrast::NONE;
				break;
			case Tonemap::Reinhard:
				result->getImage()->tonemapReinhard(tonemapSlider->value());
				result->tonemapped = Tonemap::Reinhard;
				result->contrasted = Contrast::NONE;
				break;
		}
	}
	if (result->merged != Merge::NONE && (result->contrasted != pipeline.contrast)) {
		switch (pipeline.contrast) {
			case Contrast::NONE:
				result->contrasted = Contrast::NONE;
			case Contrast::Histogram:
				result->getImage()->image = result->getImage()->calcEqualization(true);
				result->contrasted = Contrast::Histogram;
				break;
		}
	}
	result->reloadImage();
	std::cout << "========== PIPELINE RUN END ===========\n";
}

/**
 * Quitte l'application
 */
void MainWindow::quit() {
	QApplication::quit();
}

/**
 * Slot action: ouvrir une ou plusieurs images
 */
void MainWindow::openFiles() {
	QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open Images"), "../images/", tr("Image Files (*.png *.jpg *.JPG *.bmp *.hdr *.HDR)"));
	if (fileNames.empty()) {
		qDebug() << tr("Empty file list");
		return;
	}
	if (fileNames[0].endsWith(tr(".hdr"))) { // hdr generated by ai
		pipeline.merge = Merge::Kalantari;
		result->loadImage(fileNames[0], hdrbox);
		actionMergeKalantari->setChecked(true);
		executePipeline();
	} else {
		images->loadImages(fileNames); // ldr images
		resetAll();
		result->reset();
	}
	qDebug() << fileNames;
}

/**
 * Slot action: ouvrir un dossier d'images
 */
void MainWindow::openFolder() {
    QDir directory(QFileDialog::getExistingDirectory(this, tr("Open folder"), "../images/"));
	QStringList fileNames = directory.entryList(QStringList() << tr("*.jpg") << tr("*.JPG") << tr("*.png")  << tr("*.bmp"), QDir::Files);
	for (QString& fileName: fileNames) {
		fileName = directory.path().append(tr("/")).append(fileName);
	}
	if (fileNames.empty()) {
		qDebug() << tr("Empty folder");
		return;
	}
	images->loadImages(fileNames);
	resetAll();
	result->reset();
	qDebug() << fileNames;
}

/**
 * Enregistre l'image sur le système de fichiers.
 */
void MainWindow::save() {
	if (result->merged != Merge::NONE) {
		QString filename = QFileDialog::getSaveFileName();
		result->getImage()->getQImage().save(filename);
	} else {
		std::cout << "No HDR image found.\n";
	}
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
void MainWindow::mergeRobertson() {
	pipeline.merge = Merge::Robertson;
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

/**
 * Reset contrast
 */
void MainWindow::contrastNone() {
	pipeline.contrast = Contrast::NONE;
	executePipeline();
}

/**
 * Slot action: applique une égalisation d'histogramme pour rehausser le contraste.
 */
void MainWindow::contrastHistogram() {
	pipeline.contrast = Contrast::Histogram;
	executePipeline();
}
