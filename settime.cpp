#include "settime.h"
#include "notification.h"
#include "ui_settime.h"

setTime::setTime(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setTime)
{
    this->setFixedSize(QSize(340, 150));

    ui->setupUi(this);

    QRect parentGeometry = parent->geometry();
    int x = parentGeometry.x() + parentGeometry.width();
    int y = parentGeometry.y();
    this->move(x, y);

    connect(ui->ConfirmButton, SIGNAL(accepted()), this, SLOT(buttonConfirm()));
    connect(ui->ConfirmButton, &QDialogButtonBox::rejected, this, &QDialog::reject);

    // https://www.youtube.com/watch?v=ZGnuPIFKSJc
    // connect child's "sendMessage" signal to the parent's "receiveMessage"
    connect(this, SIGNAL(sendMessage(TimeCounter&)), parent, SLOT(receiveMessage(TimeCounter&)));
}

setTime::~setTime()
{
    delete ui;
}

void setTime::buttonConfirm()
{
    int hour = ui->hoursInput->value(), minute = ui->minutesInput->value();
    int is_break_time = 0;

    if (ui->isBreakTime->checkState())
    {
        is_break_time = 1;
    }

    if (hour >= 0 && hour <= 4 && minute > 0 && minute <= 59)
    {
        TimeCounter *t = new TimeCounter(hour, minute, is_break_time);
        emit sendMessage(*t);
    }
    else
    {
        Notification *n = new Notification(this, "Sorry, the maximum time is 4h 59min");
        n->show();
    }
}

void setTime::timeSelector()
{
    ui->isBreakTime->checkState();
}
