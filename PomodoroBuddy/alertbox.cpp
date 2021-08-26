#include "alertbox.h"
#include "ui_alertbox.h"

alertBox::alertBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::alertBox)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
}

alertBox::~alertBox()
{
    delete ui;
}

QSize alertBox::sizeHint() const
{
    //Forces the window size to be 400x250 pixels.

    return QSize(400,250);
}

void alertBox::setMessage(int message)
{
    //1 message1 (study->break)
    //2 message2 (break->study)
    //3 message3 (study->extended break)

    if(message == 1){
        ui->message->setStyleSheet("border-image: url(:/resources/message1.png)");
        currMessage = 1;
    }
    else if(message == 2){
        ui->message->setStyleSheet("border-image: url(:/resources/message2.png)");
        currMessage = 2;
    }
    else if(message == 3){
        ui->message->setStyleSheet("border-image: url(:/resources/message3.png)");
        currMessage = 3;
    }
}

bool alertBox::getAcknowledge()
{
    return acknowledged;
}

int alertBox::getCurrMessage()
{
    return currMessage;
}

void alertBox::setAcknowledge()
{
    acknowledged = false;
}

void alertBox::paintEvent(QPaintEvent *event)
{
    //This method paints the background of the PomodoroBuddy alertBox the distinct shade of green.

    QPainter painter(this);

    QBrush background (QColor(194,249,187));

    painter.setBrush(background);

    painter.setPen (Qt::NoPen);

    painter.drawRect(0,0, width(), height());
}

void alertBox::mousePressEvent(QMouseEvent *event)
{
    //This method tests whether or not the mouse is clicked onto the widget window.
    //If it is the point clicked on is stored in a private variable.

    m_Diff = event->pos();
}

void alertBox::mouseReleaseEvent(QMouseEvent *event)
{
    //This method verifies that the mouse has been released when dragging around the application window.

    Q_UNUSED(event);
}

void alertBox::mouseMoveEvent(QMouseEvent *event)
{
    //This method is the magic that allows for the clicking and dragging around of the application window.
    //Basically the QPoint p keeps track of where the mouse is while it is being held down. The window is moved to wherever the mouse moves.

    QPoint p = event->globalPos();

    window()->move(p - m_Diff);
}

void alertBox::on_closeButton_clicked()
{
    hide();
    acknowledged = true;
}


void alertBox::on_okBtn_clicked()
{
    hide();
    acknowledged = true;
}

