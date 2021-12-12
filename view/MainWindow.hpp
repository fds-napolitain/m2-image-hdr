#ifndef QTHDR_MAINWINDOW_HPP
#define QTHDR_MAINWINDOW_HPP

#include <QtWidgets>
#include <QString>
#include "StackImageWidget.hpp"
#include "ImageWidget.hpp"
#include "Pipeline.hpp"
#include "ToneMapSettings.hpp"
#include <QPixmap>
#include <iostream>
#include <QSizePolicy>

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
	QActionGroup* actionGroupAlign;
	QAction* actionAlignMTB;
	QActionGroup* actionGroupMerge;
	QAction* actionMergeDebevec;
	QAction* actionMergeRobertson;
	QAction* actionMergeMertens;
	QAction* actionMergeDenoise;
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

    ToneMapSettings* toneMapSettings;
	StackImageWidget* images;
	ImageWidget* result;
	Image cache;
	Pipeline pipeline;
	void createActions();
	void createMenus();
	void resetAll();
	void executePipeline();

private slots:
	void openFiles();
	void openFolder();
	void save();
	void alignMTB();
	void mergeDebevec();
	void mergeRobertson();
	void mergeMertens();
	void mergeDenoise();
	void tonemapNone();
	void tonemapDrago();
	void tonemapReinhard();
	void contrastNone();
	void contrastHistogram();

};

#endif //QTHDR_MAINWINDOW_HPP
