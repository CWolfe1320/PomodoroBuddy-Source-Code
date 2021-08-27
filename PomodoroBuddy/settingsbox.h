#ifndef SETTINGSBOX_H
#define SETTINGSBOX_H

#include <QWidget>
#include <QBrush>
#include <QPalette>
#include <QColor>
#include <QPainter>
#include <QMouseEvent>
#include "iowrapper.h"

namespace Ui {
class settingsBox;
}

class settingsBox : public QWidget
{
    Q_OBJECT

public:
    explicit settingsBox(QWidget *parent = nullptr);
    ~settingsBox();
    QSize sizeHint() const;
    std::string getTrueStudyMinutes();
    int getIntStudyMinutes();
    int getIntBreakMinutes();
    int getIntLongBreakMinutes();
    void refreshSettings();

private:
    //Misc variables
    Ui::settingsBox *ui;
    QPoint m_Diff;

    //Record of setting preferences
    std::string trueStudyMinutes;
    std::string trueBreakMinutes;
    std::string trueLongBreakMinutes;

    int intStudyMinutes;
    int intBreakMinutes;
    int intLongBreakMinutes;

    //Initializes settings to default to saved preferences in settings.txt
    void setupSettings();


protected: //Handles the settings window's behavior
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private slots: //Handles button clicks
    void on_closeBtn_clicked();
    void on_studytimeBox_currentTextChanged(const QString &arg1);
    void on_breaktimeBox_currentTextChanged(const QString &arg1);
    void on_longbreaktimeBox_currentTextChanged(const QString &arg1);
};

#endif // SETTINGSBOX_H
