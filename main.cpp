#include "pomodoroapp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PomodoroApp w;
    w.show();
    return a.exec();
}
