#ifndef QTHDR_MAINWINDOW_HPP
#define QTHDR_MAINWINDOW_HPP

#include <QtWidgets>
#include <QString>
#include "StackImageWidget.hpp"
#include "ImageWidget.hpp"
#include "../model/Pipeline.hpp"
#include "ZoomedWindow.hpp"

class MainWindow : public QMainWindow {

	Q_OBJECT

public:
	MainWindow();
	~MainWindow() override;

private:
	// menus
	QMenu* menuFile;
	QMenu* menuAlign;
	QMenu* menuMerge;
	QMenu* menuTonemap;
	// actions et actiongroup
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
	// widget d'affichage et fonctionnels
	QWidget* widget;
	QGroupBox* hdrbox;
	StackImageWidget* images;
	ImageWidget* result;
	Pipeline pipeline;
	ZoomedWindow* zoomedWindow;
	void createActions();
	void createMenus();
	void executePipeline();

private slots:
	static void quit();
	void openFiles();
	void openFolder();
	void alignMTB();
	void mergeDebevec();
	void mergeMertens();
	void tonemapNone();
	void tonemapDrago();
	void tonemapReinhard();
};

#endif //QTHDR_MAINWINDOW_HPP
