#ifndef STATSBOX_H
#define STATSBOX_H

#include <QWidget>
#include <QMouseEvent>
#include <QBrush>
#include <QPalette>
#include <QColor>
#include <QPainter>
#include "iowrapper.h"
#include <utility>

namespace Ui {
class statsBox;
}

class statsBox : public QWidget
{
    Q_OBJECT

public: //Constructors, Destructors, Accessors
    explicit statsBox(QWidget *parent = nullptr);
    ~statsBox();
    QSize sizeHint() const;

    int getPomHighscore();
private:
    //Misc. Variables
    Ui::statsBox *ui;
    QPoint m_Diff;

    //Boolean switches that keep track of what is ascending or descending
    bool durationSwitch = false;
    bool dateSwitch = false;
    bool pomSwitch = false;

    //Sorted vectors of data
    std::vector<std::string> dateAscend;
    std::vector<std::string> dateDescend;
    std::vector<std::string> durationAscend;
    std::vector<std::string> durationDescend;
    std::vector<std::string> pomodoroAscend;
    std::vector<std::string> pomodoroDescend;

    //Private Functions
    void startupDisplay();
    void sortStats();
    void sortPomodoro();
    void sortDate();
    void sortDuration();
    int getPomodoroStat(std::string stat);
    int getDurationStat(std::string stat);

    //Highscore variable
    int highscore = 0;

protected: //These handle the behavior of the stats window
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);


private slots: //These handle the behavior of clicked buttons
    void on_closeBtn_clicked();
    void on_dateBtn_clicked();
    void on_pomodoroBtn_clicked();
    void on_durationBtn_clicked();
};

#endif // STATSBOX_H
