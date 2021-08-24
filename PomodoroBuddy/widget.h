#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QTimer>

#include "alertbox.h"
#include "statsbox.h"
#include "iowrapper.h"



QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QSize sizeHint() const;

public slots:
    void timerFunction();
    void interruptFunction();

private slots:
    void on_closeBtn_clicked();

    void on_minimizeBtn_clicked();

    void on_startBtn_clicked();

    void on_stopBtn_clicked();

    void on_interruptBtn_clicked();

    void on_statsBtn_clicked();

private:
    Ui::Widget *ui;
    QPoint m_Diff;
    QTimer *timer;

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


    alertBox *alert = new alertBox();
    statsBox *stats = new statsBox();

    int pomCounter = 0;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);



};
#endif // WIDGET_H
