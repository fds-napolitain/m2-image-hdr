#include "MainWindow.hpp"

MainWindow::MainWindow() {
    auto *menu_file = new QMenu("&File");
	menu_file->addAction("&Open...", this, SLOT(open()), Qt::CTRL + Qt::Key_O);
	menu_file->addAction("&Save as...", qApp, SLOT(quit()), Qt::CTRL + Qt::Key_S);
    auto *menu_hdr = new QMenu("&HDR");
    menu_hdr->addAction("&Merge", qApp, SLOT(quit()), Qt::CTRL + Qt::Key_M);

    QMenuBar *menu_bar = menuBar();
    menu_bar->addMenu(menu_file);
    menu_bar->addMenu(menu_hdr);
    menu_bar->show();
    setMenuBar(menu_bar);

	QImage myImage;
	myImage.load("images/s1/IMG_0478.JPG");

	QPixmap pm(QPixmap::fromImage(myImage)); // <- path to image file


	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home/jana", tr("Image Files (*.png *.jpg *.bmp)"));

	QLabel myLabel;
	myLabel.resize(400, 400);
	myLabel.setPixmap(pm);
//	myLabel.setPixmap(QPixmap::fromImage(myImage));

	myLabel.show();
}

bool MainWindow::open() {
	std::cout << "Open file.\n";

	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home/jana", tr("Image Files (*.png *.jpg *.bmp)"));
}
