#include "settingsbox.h"
#include "ui_settingsbox.h"

settingsBox::settingsBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::settingsBox)
{
    //Constructor constructing

    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    try {
        ioWrapper settingsWrapper = ioWrapper("settings.txt", true);

        intStudyMinutes = settingsWrapper.getStudyMinutes();
        intBreakMinutes = settingsWrapper.getBreakMinutes();
        intLongBreakMinutes = settingsWrapper.getLongBreakMinutes();

        trueStudyMinutes = std::to_string(intStudyMinutes) + ":00";
        trueBreakMinutes = std::to_string(intBreakMinutes) + ":00";
        trueLongBreakMinutes = std::to_string(intLongBreakMinutes) + ":00";
    }  catch (...) {
        std::string studyTime = "25:00";
        std::string breakTime = "5:00";
        std::string longBreakTime = "30:00";
        ioWrapper(studyTime, breakTime, longBreakTime);

        ioWrapper settingsWrapper = ioWrapper("settings.txt", true);

        intStudyMinutes = settingsWrapper.getStudyMinutes();
        intBreakMinutes = settingsWrapper.getBreakMinutes();
        intLongBreakMinutes = settingsWrapper.getLongBreakMinutes();

        trueStudyMinutes = std::to_string(intStudyMinutes) + ":00";
        trueBreakMinutes = std::to_string(intBreakMinutes) + ":00";
        trueLongBreakMinutes = std::to_string(intLongBreakMinutes) + ":00";
    }

    setupSettings();


}

settingsBox::~settingsBox()
{
    //Settings ui widget destructor

    delete ui;
}

QSize settingsBox::sizeHint() const
{
    //Forces the window size to be 400x250 pixels.

    return QSize(400,250);
}

std::string settingsBox::getTrueStudyMinutes()
{
    //trueStudyMinutes accessor

    return trueStudyMinutes;
}

int settingsBox::getIntStudyMinutes()
{
    //intStudyMinutes accessor

    return intStudyMinutes;
}

int settingsBox::getIntBreakMinutes()
{
    //intBreakMinutes accessor

    return intBreakMinutes;
}

int settingsBox::getIntLongBreakMinutes()
{
    //intLongBreakMinutes accessor

    return intLongBreakMinutes;
}

void settingsBox::refreshSettings()
{
    //This function will effectively redo the constructor for this class. It is called in the main widget application class when settings are refreshed.

    ioWrapper settingsWrapper = ioWrapper("settings.txt", true);

    intStudyMinutes = settingsWrapper.getStudyMinutes();
    intBreakMinutes = settingsWrapper.getBreakMinutes();
    intLongBreakMinutes = settingsWrapper.getLongBreakMinutes();

    trueStudyMinutes = std::to_string(intStudyMinutes) + ":00";
    trueBreakMinutes = std::to_string(intBreakMinutes) + ":00";
    trueLongBreakMinutes = std::to_string(intLongBreakMinutes) + ":00";

    setupSettings();
}

void settingsBox::setupSettings()
{
    //Initializes settings to whatever is in settings.txt

    int counter = 0;
    while(trueStudyMinutes != ui->studytimeBox->currentText().toStdString()){
        ui->studytimeBox->setCurrentIndex(counter);
        if(trueStudyMinutes != ui->studytimeBox->currentText().toStdString()){
            counter++;
        }
    }
    counter = 0;
    while(trueBreakMinutes != ui->breaktimeBox->currentText().toStdString()){
        ui->breaktimeBox->setCurrentIndex(counter);
        if(trueBreakMinutes != ui->breaktimeBox->currentText().toStdString()){
            counter++;
        }
    }
    counter = 0;
    while(trueLongBreakMinutes != ui->longbreaktimeBox->currentText().toStdString()){
        ui->longbreaktimeBox->setCurrentIndex(counter);
        if(trueLongBreakMinutes != ui->longbreaktimeBox->currentText().toStdString()){
            counter++;
        }
    }
}

void settingsBox::paintEvent(QPaintEvent *event)
{
    //This method paints the background of the PomodoroBuddy alertBox the distinct shade of green.

    QPainter painter(this);

    QBrush background (QColor(194,249,187));

    painter.setBrush(background);

    painter.setPen (Qt::NoPen);

    painter.drawRect(0,0, width(), height());
}

void settingsBox::mousePressEvent(QMouseEvent *event)
{
    //This method tests whether or not the mouse is clicked onto the widget window.
    //If it is the point clicked on is stored in a private variable.

    m_Diff = event->pos();
}

void settingsBox::mouseReleaseEvent(QMouseEvent *event)
{
    //This method verifies that the mouse has been released when dragging around the application window.

    Q_UNUSED(event);
}

void settingsBox::mouseMoveEvent(QMouseEvent *event)
{
    //This method is the magic that allows for the clicking and dragging around of the application window.
    //Basically the QPoint p keeps track of where the mouse is while it is being held down. The window is moved to wherever the mouse moves.

    QPoint p = event->globalPos();

    window()->move(p - m_Diff);
}

void settingsBox::on_closeBtn_clicked()
{
    //Closes settings window

    hide();
}


void settingsBox::on_studytimeBox_currentTextChanged(const QString &arg1)
{
    //Deals with handling the logic when study timing is changed

    std::string studyTime = arg1.toStdString();
    std::string breakTime = ui->breaktimeBox->currentText().toStdString();
    std::string longBreakTime = ui->longbreaktimeBox->currentText().toStdString();
    ioWrapper(studyTime, breakTime, longBreakTime);
}


void settingsBox::on_breaktimeBox_currentTextChanged(const QString &arg1)
{
    //Deals with handling the logic when break timing is changed

    std::string studyTime = ui->studytimeBox->currentText().toStdString();
    std::string breakTime = arg1.toStdString();
    std::string longBreakTime = ui->longbreaktimeBox->currentText().toStdString();
    ioWrapper(studyTime, breakTime, longBreakTime);
}


void settingsBox::on_longbreaktimeBox_currentTextChanged(const QString &arg1)
{
    //Deals with handling the logic when long break timing is changed

    std::string studyTime = ui->studytimeBox->currentText().toStdString();
    std::string breakTime = ui->breaktimeBox->currentText().toStdString();
    std::string longBreakTime = arg1.toStdString();
    ioWrapper(studyTime, breakTime, longBreakTime);
}

