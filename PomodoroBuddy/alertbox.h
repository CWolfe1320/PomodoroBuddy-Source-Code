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

    void setMessage(int message);
    bool getAcknowledge();
    int getCurrMessage();
    void setAcknowledge();

private:
    Ui::alertBox *ui;
    QPoint m_Diff;
    bool acknowledged = false;
    int currMessage = 1;

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void on_closeButton_clicked();
    void on_okBtn_clicked();
};

#endif // ALERTBOX_H
