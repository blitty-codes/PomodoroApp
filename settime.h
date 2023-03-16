#ifndef SETTIME_H
#define SETTIME_H

#include "timecounter.h"
#include <QDialog>

namespace Ui {
class setTime;
}

class setTime : public QDialog
{
    Q_OBJECT

public:
    explicit setTime(QWidget *parent = nullptr);
    ~setTime();

signals:
    void sendMessage(TimeCounter &msg);

public slots:
    void buttonConfirm();
    void timeSelector();

private:
    Ui::setTime *ui;
};

#endif // SETTIME_H
