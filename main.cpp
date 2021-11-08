#include <QApplication>
#include "view/MainWindow.hpp"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow window;
    window.resize(1000, 800);
    window.show();
    return QApplication::exec();
}
