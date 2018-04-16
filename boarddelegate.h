#ifndef BOARDDELEGATE_H
#define BOARDDELEGATE_H

#include <QStyledItemDelegate>
#include <QApplication>
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include <QDebug>
#include <QTimer>

class BoardDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:    
    BoardDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

private:    
    bool leftPress;
    bool rightPress;
    QTimer *timerLeftPress;
    QTimer *timerRightPress;
    QModelIndex currentIndex;

signals:
    void leftClick(const QModelIndex &index);
    void rightClick(const QModelIndex &index);
    void doubleClick(const QModelIndex &index);
    void leftRightClick(const QModelIndex &index);
    void mouseMove(const QPoint pos);

};

#endif // BOARDDELEGATE_H