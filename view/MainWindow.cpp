//
// Created by Maxime Boucher on 30/10/2021.
//

#include "MainWindow.hpp"

MainWindow::MainWindow() {
    auto *menu_file = new QMenu("&File");
    menu_file->addAction("&Open", qApp, SLOT(quit()), Qt::CTRL + Qt::Key_O);
    menu_file->addAction("&Save as...", qApp, SLOT(quit()), Qt::CTRL + Qt::Key_S);
    auto *menu_hdr = new QMenu("&HDR");
    menu_hdr->addAction("&Merge", qApp, SLOT(quit()), Qt::CTRL + Qt::Key_M);

    QMenuBar *menu_bar = menuBar();
    menu_bar->addMenu(menu_file);
    menu_bar->addMenu(menu_hdr);
    menu_bar->show();
    setMenuBar(menu_bar);
}
