
#ifndef QTHDR_MAINWINDOW_HPP
#define QTHDR_MAINWINDOW_HPP

#include <QtWidgets>
#include <QString>
#include "../model/StackImage.hpp"

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
	std::vector<QLabel*> stackWidget;
	QLabel* resultWidget;
	StackImage images;
	Image result;
	void createActions();
	void createMenus();

private slots:
	void openFiles();
    void openFolder();
};

#endif //QTHDR_MAINWINDOW_HPP
