#ifndef SETTINGSBOX_H
#define SETTINGSBOX_H

#include <QWidget>
#include <QBrush>
#include <QPalette>
#include <QColor>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
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


private:
    Ui::settingsBox *ui;
    QPoint m_Diff;

    std::string trueStudyMinutes;
    std::string trueBreakMinutes;
    std::string trueLongBreakMinutes;

    int intStudyMinutes;
    int intBreakMinutes;
    int intLongBreakMinutes;

    void setupSettings();


protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void on_closeBtn_clicked();
    void on_studytimeBox_currentTextChanged(const QString &arg1);
    void on_breaktimeBox_currentTextChanged(const QString &arg1);
    void on_longbreaktimeBox_currentTextChanged(const QString &arg1);
};

#endif // SETTINGSBOX_H
