#ifndef QTHDR_MAINWINDOW_HPP
#define QTHDR_MAINWINDOW_HPP

#include <QtWidgets>
#include <QString>
#include "StackImageWidget.hpp"
#include "ZoomableImageWidget.hpp"
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
	QMenu* menuContrast;
	// actions et actiongroup
	QAction* actionOpenFiles;
    QAction* actionOpenFolder;
    QAction* actionSave;
    QAction* actionQuit;
	QActionGroup* actionGroupAlign;
	QAction* actionAlignMTB;
	QActionGroup* actionGroupMerge;
	QAction* actionMergeDebevec;
	QAction* actionMergeRobertson;
	QAction* actionMergeMertens;
	QAction* actionMergeKalantari;
	QActionGroup* actionGroupTonemap;
	QAction* actionTonemapNone;
	QAction* actionTonemapDrago;
	QAction* actionTonemapReinhard;
	QActionGroup* actionGroupContrast;
	QAction* actionContrastNone;
	QAction* actionContrastHistogram;
	// widget d'affichage et fonctionnels
	QWidget* widget;
	QGroupBox* hdrbox;
    QGroupBox* settingsBox;
    QLabel* tonemapGamma;
    QSlider* tonemapSlider;
	StackImageWidget* images;
	ImageWidget* result;
	Image cache;
	Pipeline pipeline;
	ZoomedWindow* zoomedWindow;
	void createActions();
	void createMenus();
	void resetAll();
	void executePipeline();

private slots:
	static void quit();
	void openFiles();
	void openFolder();
	void save();
	void alignMTB();
	void mergeDebevec();
	void mergeRobertson();
	void mergeMertens();
	void tonemapNone();
	void tonemapDrago();
	void tonemapReinhard();
	void contrastNone();
	void contrastHistogram();

};

#endif //QTHDR_MAINWINDOW_HPP
