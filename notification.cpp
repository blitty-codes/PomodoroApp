#include "notification.h"

Notification::Notification(QWidget *parent, const QString &label) :
    QDialog(parent),
    ui(new Ui::Notification)
{
    this->setFixedSize(QSize(270, 160));

    ui->setupUi(this);
    ui->msg->setText(label);

    QRect parentGeometry = parent->geometry();
    int x = parentGeometry.x() + parentGeometry.width();
    int y = parentGeometry.y();
    this->move(x, y);
}

Notification::~Notification()
{
    delete ui;
}
