#include<QApplication>

#include "CashFlowWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CashFlowWindow w;
    w.show();
    return a.exec();
}
