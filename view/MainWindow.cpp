//
// Created by Maxime Boucher on 30/10/2021.
//

#include "MainWindow.hpp"

MainWindow::MainWindow() {
    auto *quit = new QAction("&Quit", this);
    QMenu *file = menuBar()->addMenu("&File");
    file->addAction(quit);
    connect(quit, &QAction::triggered, qApp, QApplication::quit);
}
