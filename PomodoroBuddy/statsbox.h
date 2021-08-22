#ifndef STATSBOX_H
#define STATSBOX_H

#include <QWidget>
#include <QMouseEvent>
#include <QBrush>
#include <QPalette>
#include <QColor>
#include <QPainter>

namespace Ui {
class statsBox;
}

class statsBox : public QWidget
{
    Q_OBJECT

public:
    explicit statsBox(QWidget *parent = nullptr);
    ~statsBox();
    QSize sizeHint() const;

private:
    Ui::statsBox *ui;
    QPoint m_Diff;

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);


private slots:
    void on_closeBtn_clicked();
};

#endif // STATSBOX_H