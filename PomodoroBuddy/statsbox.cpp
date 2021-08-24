#include "statsbox.h"
#include "ui_statsbox.h"

statsBox::statsBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::statsBox)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
}

statsBox::~statsBox()
{
    delete ui;
}

QSize statsBox::sizeHint() const
{
    //Forces the window size to be 400x250 pixels.

    return QSize(800,600);
}

void statsBox::paintEvent(QPaintEvent *event)
{
    //This method paints the background of the PomodoroBuddy alertBox the distinct shade of green.

    QPainter painter(this);

    QBrush background (QColor(194,249,187));

    painter.setBrush(background);

    painter.setPen (Qt::NoPen);

    painter.drawRect(0,0, width(), height());
}

void statsBox::mousePressEvent(QMouseEvent *event)
{
    //This method tests whether or not the mouse is clicked onto the widget window.
    //If it is the point clicked on is stored in a private variable.

    m_Diff = event->pos();
}

void statsBox::mouseReleaseEvent(QMouseEvent *event)
{
    //This method verifies that the mouse has been released when dragging around the application window.

    Q_UNUSED(event);
}

void statsBox::mouseMoveEvent(QMouseEvent *event)
{
    //This method is the magic that allows for the clicking and dragging around of the application window.
    //Basically the QPoint p keeps track of where the mouse is while it is being held down. The window is moved to wherever the mouse moves.

    QPoint p = event->globalPos();

    window()->move(p - m_Diff);
}

void statsBox::on_closeBtn_clicked()
{
    hide();
}


void statsBox::on_dateBtn_clicked()
{
    ui->pomodoroBtn->setStyleSheet("border-image: url(:/resources/pomodoroBtn.png)");
    ui->durationBtn->setStyleSheet("border-image: url(:/resources/durationBtn.png)");

    dateSwitch = !dateSwitch;

    if(dateSwitch){
        ui->dateBtn->setStyleSheet("border-image: url(:/resources/dateDescend.png)");
    }
    else if(!dateSwitch){
        ui->dateBtn->setStyleSheet("border-image: url(:/resources/dateAscend.png)");
    }
}


void statsBox::on_pomodoroBtn_clicked()
{
    ui->dateBtn->setStyleSheet("border-image: url(:/resources/dateBtn.png)");
    ui->durationBtn->setStyleSheet("border-image: url(:/resources/durationBtn.png)");

    pomSwitch = !pomSwitch;

    if(pomSwitch){
        ui->pomodoroBtn->setStyleSheet("border-image: url(:/resources/pomodoroDescend.png)");
    }
    else if(!pomSwitch){
        ui->pomodoroBtn->setStyleSheet("border-image: url(:/resources/pomodoroAscend.png)");
    }
}


void statsBox::on_durationBtn_clicked()
{
    ui->dateBtn->setStyleSheet("border-image: url(:/resources/dateBtn.png)");
    ui->pomodoroBtn->setStyleSheet("border-image: url(:/resources/pomodoroBtn.png)");

    durationSwitch = !durationSwitch;

    if(durationSwitch){
        ui->durationBtn->setStyleSheet("border-image: url(:/resources/durationDescend.png)");
    }
    else if(!durationSwitch){
        ui->durationBtn->setStyleSheet("border-image: url(:/resources/durationAscend.png)");
    }
}

