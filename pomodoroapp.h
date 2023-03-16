#ifndef POMODOROAPP_H
#define POMODOROAPP_H

#include "settime.h"
#include <QDebug>
#include <QMainWindow>
#include <QTimer>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>

QT_BEGIN_NAMESPACE
namespace Ui { class PomodoroApp; }
QT_END_NAMESPACE

class PomodoroApp : public QMainWindow
{
    Q_OBJECT

public:
    PomodoroApp(QWidget *parent = nullptr);
    ~PomodoroApp();

public slots:
    void receiveMessage(TimeCounter &msg);

private slots:
    void on_actionSet_Pomodoro_triggered();
    void togglePomodoro();
    void funcionActivacionTimer();

private:
    Ui::PomodoroApp *ui;
    setTime *timeDisplay;
    QTimer *timer;
    QAudioOutput *audioOutput;
    QMediaPlayer *player;
    int n_pomodoros;
    int hours, pomo_hours, break_hours;
    int mins, pomo_mins, break_mins;
    bool pomodoro_start, pomodoro_time;
};
#endif // POMODOROAPP_H
