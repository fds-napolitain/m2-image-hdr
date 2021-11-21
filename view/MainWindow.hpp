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
	~MainWindow();
private:
	QMenu* menuFile;
	QMenu* menuAlign;
	QMenu* menuMerge;
	QMenu* menuTonemap;
	QAction* actionOpenFiles;
    QAction* actionOpenFolder;
    QAction* actionQuit;
	QActionGroup* actionGroupAlign;
	QAction* actionAlignMTB;
	QActionGroup* actionGroupMerge;
	QAction* actionMergeDebevec;
	QAction* actionMergeMertens;
	QActionGroup* actionGroupTonemap;
	QAction* actionTonemapNone;
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
	static void quit();
	void alignMTB();
	void mergeDebevec();
	void mergeMertens();
	void tonemapNone();
	void tonemapDrago();
	void tonemapReinhard();
};

#endif //QTHDR_MAINWINDOW_HPP
