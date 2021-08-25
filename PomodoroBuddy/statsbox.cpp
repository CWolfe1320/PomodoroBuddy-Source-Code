#include "statsbox.h"
#include "ui_statsbox.h"

statsBox::statsBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::statsBox)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    ioWrapper statWrapper = ioWrapper("stats.txt");
    dateAscend = statWrapper.getDateAscendStats();
    startupDisplay();
    sortStats();


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

void statsBox::startupDisplay()
{
    for(int i = 0; i < dateAscend.size(); i++){
        ui->statsDisplay->append(QString::fromStdString(dateAscend.at(i)) + "\n");
    }
}

void statsBox::sortStats()
{
    sortPomodoro();
    sortDate();
    sortDuration();
}

void statsBox::sortPomodoro()
{
    std::pair<int,std::string> sortedPomodoros;
    std::vector<std::string> tempVector = dateAscend;

    std::vector<std::pair<int,std::string>> pomPairs;

    for(int i = 0; i < tempVector.size(); ++i){
        int pomStat = getPomodoroStat(tempVector.at(i));
        std::string stringStat = tempVector.at(i);

        std::pair<int,std::string> newPair;
        newPair.first = pomStat;
        newPair.second = stringStat;
        pomPairs.push_back(newPair);
    }
    sort(pomPairs.begin(), pomPairs.end());
    highscore = pomPairs.at(pomPairs.size() - 1).first;
    for(int k = 0; k < pomPairs.size(); k++){
        pomodoroAscend.push_back(pomPairs.at(k).second);
    }
    for(int z = pomodoroAscend.size() - 1; z >= 0; z--){
        pomodoroDescend.push_back(pomodoroAscend.at(z));
    }
}

void statsBox::sortDate()
{
    for(int i = dateAscend.size() - 1; i >= 0; i--){
        dateDescend.push_back(dateAscend.at(i));
    }
}

void statsBox::sortDuration()
{
    std::vector<std::string> tempVector = dateAscend;

    std::vector<std::pair<int,std::string>> durPairs;

    for(int i = 0; i < tempVector.size(); ++i){
        int durStat = getDurationStat(tempVector.at(i));
        std::string stringStat = tempVector.at(i);

        std::pair<int,std::string> newPair;
        newPair.first = durStat;
        newPair.second = stringStat;
        durPairs.push_back(newPair);
    }
    sort(durPairs.begin(), durPairs.end());
    for(int k = 0; k < durPairs.size(); k++){
        durationAscend.push_back(durPairs.at(k).second);
    }
    for(int z = durationAscend.size() - 1; z >= 0; z--){
        durationDescend.push_back(durationAscend.at(z));
    }
}

int statsBox::getPomodoroStat(std::string stat)
{
    std::string tempString = stat;

    tempString = tempString.substr(25,tempString.length());

    std::string pomString = "";

    for(auto x : tempString){
        if (x == ' '){
            break;
        }
        else{
            pomString = pomString + x;
        }
    }
    return stoi(pomString);
}

int statsBox::getDurationStat(std::string stat)
{
    std::string tempString = stat;

    tempString = tempString.substr(25,tempString.length());

    std::string durString = "";

    for(auto x : tempString){
        if (x == ' '){
            durString = "";
        }
        else{
            durString = durString + x;
        }
    }

    std::string finDurString;

    for(auto x : durString){
        if (x != ':'){
            finDurString = finDurString + x;
        }
    }

    return stoi(finDurString);
}

int statsBox::getPomHighscore()
{
    return highscore;
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
    ui->statsDisplay->clear();

    dateSwitch = !dateSwitch;

    if(dateSwitch){
        ui->dateBtn->setStyleSheet("border-image: url(:/resources/dateDescend.png)");
        for(int i = 0; i < dateDescend.size(); i++){
            ui->statsDisplay->append(QString::fromStdString(dateDescend.at(i)) + "\n");
        }
    }
    else if(!dateSwitch){
        ui->dateBtn->setStyleSheet("border-image: url(:/resources/dateAscend.png)");
        for(int i = 0; i < dateAscend.size(); i++){
            ui->statsDisplay->append(QString::fromStdString(dateAscend.at(i)) + "\n");
        }
    }
}


void statsBox::on_pomodoroBtn_clicked()
{
    ui->dateBtn->setStyleSheet("border-image: url(:/resources/dateBtn.png)");
    ui->durationBtn->setStyleSheet("border-image: url(:/resources/durationBtn.png)");
    ui->statsDisplay->clear();

    pomSwitch = !pomSwitch;

    if(pomSwitch){
        ui->pomodoroBtn->setStyleSheet("border-image: url(:/resources/pomodoroDescend.png)");
        for(int i = 0; i < pomodoroDescend.size(); i++){
            ui->statsDisplay->append(QString::fromStdString(pomodoroDescend.at(i)) + "\n");
        }
    }
    else if(!pomSwitch){
        ui->pomodoroBtn->setStyleSheet("border-image: url(:/resources/pomodoroAscend.png)");
        for(int i = 0; i < pomodoroAscend.size(); i++){
            ui->statsDisplay->append(QString::fromStdString(pomodoroAscend.at(i)) + "\n");
        }
    }
}


void statsBox::on_durationBtn_clicked()
{
    ui->dateBtn->setStyleSheet("border-image: url(:/resources/dateBtn.png)");
    ui->pomodoroBtn->setStyleSheet("border-image: url(:/resources/pomodoroBtn.png)");
    ui->statsDisplay->clear();

    durationSwitch = !durationSwitch;

    if(durationSwitch){
        ui->durationBtn->setStyleSheet("border-image: url(:/resources/durationDescend.png)");
        for(int i = 0; i < durationDescend.size(); i++){
            ui->statsDisplay->append(QString::fromStdString(durationDescend.at(i)) + "\n");
        }
    }
    else if(!durationSwitch){
        ui->durationBtn->setStyleSheet("border-image: url(:/resources/durationAscend.png)");
        for(int i = 0; i < durationAscend.size(); i++){
            ui->statsDisplay->append(QString::fromStdString(durationAscend.at(i)) + "\n");
        }
    }
}

