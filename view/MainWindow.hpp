#ifndef QTHDR_MAINWINDOW_HPP
#define QTHDR_MAINWINDOW_HPP

#include <QtWidgets>
#include <QString>
#include "StackImageWidget.hpp"
#include "ImageWidget.hpp"
#include "../model/Pipeline.hpp"

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
	QActionGroup* actionGroupAlign;
	QAction* actionAlignMTB;
	QActionGroup* actionGroupMerge;
	QAction* actionMergeDebevec;
	QActionGroup* actionGroupTonemap;
	QAction* actionTonemapDrago;
	QAction* actionTonemapReinhard;
	QWidget* widget;
	QGroupBox* hdrbox;
	StackImageWidget* images;
	ImageWidget* result;
	Pipeline pipeline;
	void createActions();
	void createMenus();
	void executePipeline();
private slots:
	void openFiles();
    void openFolder();
	void alignMTB();
	void mergeDebevec();
	void tonemapDrago();
	void tonemapReinhard();
};

#endif //QTHDR_MAINWINDOW_HPP
