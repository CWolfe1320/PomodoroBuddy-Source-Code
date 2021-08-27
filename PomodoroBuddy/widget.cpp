#include "widget.h"
#include "ui_widget.h"



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this); //creates /this/ ui widget
    setWindowFlags(Qt::FramelessWindowHint);
    ui->timerCounter->setText(QString::fromStdString(settings->getTrueStudyMinutes()));

    //ensures these buttons remain off until needed
    ui->interruptBtn->setDisabled(true);
    ui->stopBtn->setDisabled(true);

    //sets up a timer that procs every 1/2 a second or second and triggers certain functions.
    //Responsible for how the timer for the application functions, settings calls, and the interrupt function
    timer = new QTimer(this);
    settingsTimer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerFunction()));
    connect(timer,SIGNAL(timeout()),this,SLOT(interruptFunction()));
    connect(settingsTimer,SIGNAL(timeout()),this,SLOT(settingsUpdateFunction()));
    timerSetup();
    timer->start(1000);
    settingsTimer->start(500);

    ui->highscoreText->setText(QString::number(stats->getPomHighscore()));
}

Widget::~Widget()
{
    //ui Widget object destructor

    delete ui;
}

QSize Widget::sizeHint() const
{
    //Forces the window size to be 1280x720 pixels.

    return QSize(1280,720);
}

void Widget::timerFunction()
{
    //responsible for altering the timer. decrememting the current time

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
    //interrupts the pomodoro buddy application when the end of a session occurs

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

void Widget::settingsUpdateFunction()
{
    //will proc every 1/2 a second when timer is stopped in order to check for updated settings

    if(!currSession && !interruptProc){
        settings->refreshSettings();
        ui->timerCounter->setText(QString::fromStdString(settings->getTrueStudyMinutes()));
        timerSetup();
    }
}

void Widget::on_closeBtn_clicked()
{
    //Closes the window if the close button is pressed.

    if(timerProc){
        on_stopBtn_clicked();
    }

    close();
}


void Widget::on_minimizeBtn_clicked()
{
    //Minimizes the window if the minimize button is pressed.

    showMinimized();
}

void Widget::timerSetup()
{
    //responsible for managing timer values.

    QString fullTime = ui->timerCounter->text();
    QStringList timeSplit = fullTime.split(":");

    minutes = timeSplit[0];
    seconds = timeSplit[1];

    iMinutes = minutes.toInt();
    iSeconds = seconds.toInt();

    mMinutes = iMinutes;
    mSeconds = iSeconds;

    sMinutes = settings->getIntStudyMinutes(); //CHANGE THESE LATER
    sSeconds = 0;

    bMinutes = settings->getIntBreakMinutes();
    bSeconds = 0;

    lBMinutes = settings->getIntLongBreakMinutes();
    lBSeconds = 0;
}

void Widget::timerAssemble()
{
    //Puts the timer together so that it may be displayed

    QString fSeconds = QString::number(iSeconds);
    if(fSeconds.toInt() < 10){
        fSeconds = "0" + fSeconds;
    }
    QString fullTime = QString::number(iMinutes) + ":" + fSeconds;
    ui->timerCounter->setText(fullTime);
}

void Widget::messageBox()
{
    //calls the alert box when timer reaches 0

    timerProc = false;
    interruptProc = true;

    alert->show();

    QApplication::beep();

    ui->startBtn->setDisabled(true);
    ui->interruptBtn->setDisabled(true);
}

void Widget::messageAccepted()
{
    //Responsible for the behaviour of an accepted message. This is the switch between study->break->long break

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
    //displays current pomodoro streak

    QString pomodoroStreak = QString::number(pomCounter);
    ui->pomCounter->setText(pomodoroStreak);
}

void Widget::statTime(bool startSwitch)
{
    //tracks date,time, and duration

    if (startSwitch){
        startTime = std::chrono::system_clock::now();
    }
    else if(!startSwitch){
        endTime = std::chrono::system_clock::now();

        elapsedTime = endTime - startTime;

        endDate = std::chrono::system_clock::to_time_t(endTime);
    }
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
    //starts the timer and initializes sought after behavior

    interruptProc = false;
    timerProc = true;
    ui->startBtn->setDisabled(true);
    ui->interruptBtn->setDisabled(false);
    ui->stopBtn->setDisabled(false);

    currSession = true;

    statTime(true);
}


void Widget::on_stopBtn_clicked()
{
    //stops the timer and initializes sought after behavior

    timerProc = false;
    interruptProc = false;
    ui->startBtn->setDisabled(false);
    ui->interruptBtn->setDisabled(true);

    alert->setAcknowledge();
    alert->setMessage(1);
    alert->hide();

    currSession = false;

    statTime(false);

    ioWrapper(pomCounter, elapsedTime, endDate);

    //Input sending class that will take pomCounter, endDate, and elapsedTime. Wrapper for stats output.

    pomCounter = 0;
    pomodoroAssemble();
}


void Widget::on_interruptBtn_clicked()
{
    //interrupts the timer

    interruptProc = true;
    timerProc = false;
    ui->startBtn->setDisabled(false);
}


void Widget::on_statsBtn_clicked()
{
    //calls the stat window

    stats = new statsBox();
    stats->show();
}


void Widget::on_settingsBtn_clicked()
{
    //calls the settings window

    settings->show();
}

