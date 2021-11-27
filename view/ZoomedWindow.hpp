//
// Created by Maxime Boucher on 27/11/2021.
//

#ifndef QTHDR_ZOOMEDWINDOW_HPP
#define QTHDR_ZOOMEDWINDOW_HPP


#include <QMainWindow>
#include "ImageWidget.hpp"

class ZoomedWindow : public QMainWindow {

public:
	ZoomedWindow();
	~ZoomedWindow() override;

private:
	QMenu* menuFile;
	QAction* actionQuit;
	QWidget* widget;
	ImageWidget* result;
	void createActions();
	void createMenus();

private slots:
	void quit();

};


#endif //QTHDR_ZOOMEDWINDOW_HPP
