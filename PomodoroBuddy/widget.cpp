#include "widget.h"
#include "ui_widget.h"
#include <QtGui>
#include <QDebug>
#include <QBrush>
#include <QPalette>
#include <QColor>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    ui->timerCounter->setText("0:05");

    masterTime = ui->timerCounter->text();

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerFunction()));
    connect(timer,SIGNAL(timeout()),this,SLOT(interruptFunction()));
    timerSetup();
    timer->start(1000);


}

Widget::~Widget()
{
    delete ui;
}

QSize Widget::sizeHint() const
{
    //Forces the window size to be 1280x720 pixels.

    return QSize(1280,720);
}

void Widget::timerFunction()
{
    if(timerProc){
        iSeconds--;
        if (iSeconds < 0 && iMinutes > 0){
            iSeconds = 59;
            iMinutes--;
        }
        else if (iMinutes == 0 && iSeconds < 0){
            iSeconds = 0;
            messageBox();

        }
        timerAssemble();
    }
}

void Widget::interruptFunction()
{
    if(interruptProc){
        if(alert->getAcknowledge()){
            messageAccepted();
        }
        iSeconds++;
        if(iSeconds > 59 && iMinutes != mMinutes){
            iSeconds = 0;
            iMinutes++;

            if(iMinutes == mMinutes && iSeconds == mSeconds){
                on_stopBtn_clicked();
            }

        }
        timerAssemble();
    }
}


void Widget::on_closeBtn_clicked()
{
    //Closes the window if the close button is pressed.

    close();
}


void Widget::on_minimizeBtn_clicked()
{
    //Minimizes the window if the minimize button is pressed.

    showMinimized();
}

void Widget::timerSetup()
{
    QString fullTime = ui->timerCounter->text();
    QStringList timeSplit = fullTime.split(":");

    minutes = timeSplit[0];
    seconds = timeSplit[1];

    iMinutes = minutes.toInt();
    iSeconds = seconds.toInt();

    mMinutes = iMinutes;
    mSeconds = iSeconds;

    sMinutes = 0; //CHANGE THESE LATER
    sSeconds = 10;

    bMinutes = 0;
    bSeconds = 5;

    lBMinutes = 0;
    lBSeconds = 30;
}

void Widget::timerAssemble()
{
    QString fSeconds = QString::number(iSeconds);
    if(fSeconds.toInt() < 10){
        fSeconds = "0" + fSeconds;
    }
    QString fullTime = QString::number(iMinutes) + ":" + fSeconds;
    ui->timerCounter->setText(fullTime);
}

void Widget::messageBox()
{
    timerProc = false;
    interruptProc = true;

    alert->show();

    ui->startBtn->setDisabled(true);
    ui->interruptBtn->setDisabled(true);
}

void Widget::messageAccepted()
{
    interruptProc = false;


    if(alert->getCurrMessage() == 1){
        iMinutes = bMinutes;
        mMinutes = bMinutes;
        iSeconds = bSeconds - 1;
        mSeconds = bSeconds;
        timerAssemble();

        pomCounter++;
        pomodoroAssemble();

        alert->setMessage(2);
    }
    else if(alert->getCurrMessage() == 2){
        iMinutes = sMinutes;
        mMinutes = sMinutes;
        iSeconds = sSeconds - 1;
        mSeconds = sSeconds;
        timerAssemble();

        alert->setMessage(1);

        if(pomCounter % 5 == 4){
            alert->setMessage(3);
        }
        else{
            alert->setMessage(1);
        }
    }
    else if(alert->getCurrMessage() == 3){
        iMinutes = lBMinutes;
        mMinutes = lBMinutes;
        iSeconds = lBSeconds - 1;
        mSeconds = lBSeconds;
        timerAssemble();

        pomCounter++;
        pomodoroAssemble();

        alert->setMessage(1);
    }
    alert->setAcknowledge();
    timerProc = true;


    ui->startBtn->setDisabled(true);
    ui->interruptBtn->setDisabled(false);
}

void Widget::pomodoroAssemble()
{
    QString pomodoroStreak = QString::number(pomCounter);
    ui->pomCounter->setText(pomodoroStreak);
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    //This method tests whether or not the mouse is clicked onto the widget window.
    //If it is the point clicked on is stored in a private variable.

    m_Diff = event->pos();
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    //This method verifies that the mouse has been released when dragging around the application window.

    Q_UNUSED(event);
}

void   Widget::mouseMoveEvent(QMouseEvent *event)
{
    //This method is the magic that allows for the clicking and dragging around of the application window.
    //Basically the QPoint p keeps track of where the mouse is while it is being held down. The window is moved to wherever the mouse moves.

    QPoint p = event->globalPos();

    window()->move(p - m_Diff);
}

void Widget::paintEvent(QPaintEvent *event)
{
    //This method paints the background of the PomodoroBuddy window the distinct shade of green.

    QPainter painter(this);

    QBrush background (QColor(194,249,187));

    painter.setBrush(background);

    painter.setPen (Qt::NoPen);

    painter.drawRect(0,0, width(), height());
}

void Widget::on_startBtn_clicked()
{
    interruptProc = false;
    timerProc = true;
    ui->startBtn->setDisabled(true);
    ui->interruptBtn->setDisabled(false);

    currSession = true;

}


void Widget::on_stopBtn_clicked()
{
    timerProc = false;
    interruptProc = false;
    ui->timerCounter->setText(masterTime);
    timerSetup();
    ui->startBtn->setDisabled(false);
    ui->interruptBtn->setDisabled(false);

    alert->setAcknowledge();
    alert->setMessage(1);
    alert->hide();

    pomCounter = 0;
    pomodoroAssemble();

    currSession = false;
}


void Widget::on_interruptBtn_clicked()
{
    interruptProc = true;
    timerProc = false;
    ui->startBtn->setDisabled(false);
}

