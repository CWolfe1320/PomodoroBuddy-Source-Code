#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QTimer>
#include <QtGui>
#include <QBrush>
#include <QPalette>
#include <QColor>
#include <chrono>
#include <ctime>

#include "alertbox.h"
#include "statsbox.h"
#include "iowrapper.h"
#include "settingsbox.h"



QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public: //Constructors + public classes
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QSize sizeHint() const;

public slots: //Functions hooked to timers
    void timerFunction();
    void interruptFunction();
    void settingsUpdateFunction();

private slots: //Deals with actions of button clicks
    void on_closeBtn_clicked();

    void on_minimizeBtn_clicked();

    void on_startBtn_clicked();

    void on_stopBtn_clicked();

    void on_interruptBtn_clicked();

    void on_statsBtn_clicked();

    void on_settingsBtn_clicked();

private:
    //Misc. variables
    Ui::Widget *ui;
    QPoint m_Diff;
    QTimer *timer;
    QTimer *settingsTimer;

    //Timer boolean variables
    bool timerProc = false;
    bool interruptProc = false;
    bool currSession = false;

    //Time deconstruction
    QString masterTime;
    QString minutes;
    QString seconds;

    //Time variables
    int iMinutes;
    int iSeconds;

    //Hard time variables
    int mMinutes;
    int mSeconds;

    //Study time variables
    int sMinutes;
    int sSeconds;

    //Break time variables
    int bMinutes;
    int bSeconds;

    int lBMinutes;
    int lBSeconds;

    //Date/Time tracking
    std::chrono::time_point<std::chrono::system_clock> startTime;
    std::chrono::time_point<std::chrono::system_clock> endTime;

    std::chrono::duration<double> elapsedTime;

    std::time_t endDate;

    //Private functions
    void timerSetup();
    void timerAssemble();
    void messageBox();
    void messageAccepted();
    void pomodoroAssemble();
    void statTime(bool startSwitch);

    //Additional windows
    alertBox *alert = new alertBox();
    statsBox *stats = new statsBox();
    settingsBox *settings = new settingsBox();

    //Pomodoro Counter
    int pomCounter = 0;

protected: //Deals with behavior of the PomodoroBuddy window
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);



};
#endif // WIDGET_H
