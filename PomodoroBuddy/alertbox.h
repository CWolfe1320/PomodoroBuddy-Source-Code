#ifndef ALERTBOX_H
#define ALERTBOX_H

#include <QWidget>
#include <QBrush>
#include <QPalette>
#include <QColor>
#include <QPainter>
#include <QMouseEvent>

namespace Ui {
class alertBox;
}

class alertBox : public QWidget
{
    Q_OBJECT

public:
    explicit alertBox(QWidget *parent = nullptr);
    ~alertBox();
    QSize sizeHint() const;

    //Accessors and Mutators
    void setMessage(int message);
    bool getAcknowledge();
    int getCurrMessage();
    void setAcknowledge();

private:
    //Misc variables
    Ui::alertBox *ui;
    QPoint m_Diff;

    //Switches
    bool acknowledged = false;
    int currMessage = 1;

protected: //Handles alertBox window behavior
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private slots: //Handles button click behaviors
    void on_closeButton_clicked();
    void on_okBtn_clicked();
};

#endif // ALERTBOX_H
