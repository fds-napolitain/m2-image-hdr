
#ifndef QTHDR_MAINWINDOW_HPP
#define QTHDR_MAINWINDOW_HPP

#include <QtWidgets>
#include "../model/Image.hpp"
#include <QString>

class MainWindow : public QMainWindow {

private:
	bool open();
public:
    MainWindow();
};


#endif //QTHDR_MAINWINDOW_HPP
