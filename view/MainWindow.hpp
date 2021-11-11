
#ifndef QTHDR_MAINWINDOW_HPP
#define QTHDR_MAINWINDOW_HPP

#include <QtWidgets>
#include <QString>
#include "../model/Image.hpp"

class MainWindow : public QMainWindow {

	Q_OBJECT

public:
	MainWindow();

private:
	QMenu* menuFile;
	QMenu* menuHDR;
	QAction* actionOpenFiles;
    QAction* actionOpenFolder;
	QWidget* widget;
	QPixmap* pm;
	QLabel* myLabel;;
	Image image;
	void createActions();
	void createMenus();

private slots:
	void openFiles();
    void openFolder();
};

#endif //QTHDR_MAINWINDOW_HPP
