
#ifndef QTHDR_MAINWINDOW_HPP
#define QTHDR_MAINWINDOW_HPP

#include <QtWidgets>
#include "../model/Image.hpp"
#include <QString>

class MainWindow : public QMainWindow {

	Q_OBJECT

public:
	MainWindow();

private:
	QMenu* menuFile;
	QMenu* menuHDR;
	QAction* actionOpen;
	QWidget* widget;
	QPixmap* pm;
	QLabel* myLabel;;
	Image image;
	void createActions();
	void createMenus();

private slots:
	void open();
};

#endif //QTHDR_MAINWINDOW_HPP
