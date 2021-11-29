#include <QApplication>
#include "view/MainWindow.hpp"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow window;
	window.showFullScreen();
    return QApplication::exec();
}
