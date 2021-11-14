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
	QMenu* menuAlign;
	QMenu* menuMerge;
	QMenu* menuTonemap;
	QAction* actionOpenFiles;
    QAction* actionOpenFolder;
	QAction* actionAlignMTB;
	QAction* actionMergeNaive;
	QAction* actionMergeDebevec;
	QWidget* widget;
	QGroupBox* hdrbox;
	StackImageWidget* images;
	ImageWidget* result;
	void createActions();
	void createMenus();
private slots:
	void openFiles();
    void openFolder();
	void alignMTB();
	void mergeDebevec();

};

#endif //QTHDR_MAINWINDOW_HPP
