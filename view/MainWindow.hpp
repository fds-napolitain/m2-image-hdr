#ifndef QTHDR_MAINWINDOW_HPP
#define QTHDR_MAINWINDOW_HPP

#include <QtWidgets>
#include <QString>
#include "StackImageWidget.hpp"
#include "ImageWidget.hpp"

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
	StackImageWidget* images;
	ImageWidget* result;
	void createActions();
	void createMenus();

private slots:
	void openFiles();
    void openFolder();
};

#endif //QTHDR_MAINWINDOW_HPP
