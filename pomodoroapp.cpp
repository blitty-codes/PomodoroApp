#include "pomodoroapp.h"
#include "notification.h"
#include "ui_pomodoroapp.h"
#include "settime.h"

PomodoroApp::PomodoroApp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PomodoroApp)
{
    this->setFixedSize(QSize(400, 300));

    ui->setupUi(this);

    this->timeDisplay = new setTime(this);

    this->n_pomodoros = 0;
    this->hours = 0;
    this->mins = 25;
    this->pomo_hours = this->hours;
    this->pomo_mins = this->mins;

    // Default 20% pomo
    int break_time = (this->hours * 60 + this->mins) * 0.2;
    this->break_hours = break_time / 100;
    this->break_mins = break_time % 100;

    this->pomodoro_start = false;
    this->pomodoro_time = true;

    this->audioOutput = new QAudioOutput;
    this->audioOutput->setVolume(50);

    // Player when the break starts
    this->player = new QMediaPlayer;
    this->player->setAudioOutput(this->audioOutput);

    ui->format->setText("Work time!");

    ui->lcdHour->setDecMode();
    ui->lcdMin->setDecMode();

    ui->lcdHour->display(this->hours);
    ui->lcdMin->display(this->mins);

    this->timer = new QTimer(this);

    connect(this->timer, SIGNAL(timeout()), this, SLOT(funcionActivacionTimer()));
    connect(ui->startButton, SIGNAL(released()), this, SLOT(togglePomodoro()));
}

PomodoroApp::~PomodoroApp()
{
    delete ui;
    delete timeDisplay;
    delete timer;
    delete audioOutput;
    delete player;
}

void PomodoroApp::receiveMessage(TimeCounter &msg)
{
    // qInfo("%dh - %dm - is_break_time: %d", msg.getHour(), msg.getMin(), msg.getIs_break_time());

    if (!msg.getIs_break_time())
    {
        // Pomo time
        this->pomo_hours = msg.getHour();
        this->pomo_mins = msg.getMin();
    }
    else
    {
        // Break time
        this->break_hours = msg.getHour();
        this->break_mins = msg.getMin();
    }

    if (this->pomodoro_time) {
        this->hours = this->pomo_hours;
        this->mins = this->pomo_mins;
    } else {
        this->hours = this->break_hours;
        this->mins = this->break_mins;
    }

    // qInfo("(XX) %dh - %dm - pomodoro_time: %d", this->hours, this->mins, this->pomodoro_time);
    ui->lcdHour->display(this->hours);
    ui->lcdMin->display(this->mins);
}

void PomodoroApp::on_actionSet_Pomodoro_triggered()
{
    this->timeDisplay->show();
}

void PomodoroApp::togglePomodoro()
{
    // Text is the inverted
    if (!this->pomodoro_start)
    {
        ui->startButton->setText("Pause pomodoro");
        this->timer->start(60000);
    }
    else
    {
        ui->startButton->setText("Start pomodoro");
        this->timer->stop();
    }

    this->pomodoro_start = !this->pomodoro_start;
}

void PomodoroApp::funcionActivacionTimer()
{
    this->mins--;

    if (this->hours == 0 && this->mins == 0)
    {
        qInfo("Pomodoro has ended!!");
        if (this->pomodoro_time)
        {
            ui->format->setText("Break time!");

            // start counter for break time
            this->hours = this->break_hours;
            this->mins = this->break_mins;

            this->player->setSource(QUrl("qrc:/sounds/hehe_minion_sound.mp3"));
            this->player->play();

            // Notify free time is starting
            Notification *n = new Notification(this, "It is time to have a break!!");
            n->show();

            this->n_pomodoros++;
        }
        else
        {
            ui->format->setText("Work time!");

            // start counter for working time
            this->hours = this->pomo_hours;
            this->mins = this->pomo_mins;

            this->player->setSource(QUrl("qrc:/sounds/water_minion_sound.mp3"));
            this->player->play();

            // Notify work time is starting
            Notification *n = new Notification(this, "It is time to start the work again!!");
            n->show();
        }

        this->pomodoro_time = !this->pomodoro_time;
    }
    else if (this->mins == 0)
    {
        this->hours--;
        this->mins = 59;

        ui->lcdHour->display(this->hours);
    }

    ui->lcdNPomodoros->display(this->n_pomodoros);
    ui->lcdMin->display(this->mins);
}
