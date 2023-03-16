#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include "ui_notification.h"
#include <QDialog>

namespace Ui {
class Notification;
}

class Notification : public QDialog
{
    Q_OBJECT

public:
    explicit Notification(QWidget *parent, const QString &label);
    ~Notification();

private:
    Ui::Notification *ui;
};

#endif // NOTIFICATION_H
