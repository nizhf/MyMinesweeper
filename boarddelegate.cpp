#include "boarddelegate.h"

//static int countElse = 0;

BoardDelegate::BoardDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
    leftPress = false;
    rightPress = false;
    timerLeftPress = new QTimer(this);
    timerLeftPress->setSingleShot(true);
    timerLeftPress->setInterval(200);
    timerRightPress = new QTimer(this);
    timerRightPress->setSingleShot(true);
    timerRightPress->setInterval(200);
    connect(timerLeftPress, &QTimer::timeout, [=](){
        leftPress = false;
        emit leftClick(currentIndex);
    });
    connect(timerRightPress, &QTimer::timeout, [=](){
        rightPress = false;
        emit rightClick(currentIndex);
    });
}

void BoardDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    //first digit: 1 normal, 2 clicked, 3 flag, 4 flag false, 5 game over boom
    //second digit: 0 none, 1-8 mines around, 9 mine
    painter->setBrush(QBrush(Qt::black));
    painter->setPen(Qt::black);
    int temp = index.model()->data(index).toInt();
    int status = temp / 10;
    int count = temp % 10;

    int width = 40;
    int height = 40;
    QRect rect = option.rect;
    int x = rect.x() + rect.width() / 2 - width / 2;
    int y = rect.y() + rect.height() / 2 - height / 2;
    if (status == 1) {
        painter->setBrush(QBrush(QColor(230, 230, 230)));
        painter->drawRect(rect.x(), rect.y(), 40, 40);
    }
    else if (status == 2) {
        if (count == 0) {
            painter->setBrush(QBrush(Qt::gray));
            painter->drawRect(rect.x(), rect.y(), 40, 40);
        }
        else if (count == 9) {
            painter->drawPixmap(x, y, QPixmap(":/image/image/mine_clicked.png").scaledToHeight(40));
        }
        else {
            painter->setFont(QFont("Arial", 20, 70));
            switch (count) {
            case 1:
                //tianyi blue
                painter->setPen(QColor(102, 204, 255));
                break;
            case 2:
                //green
                painter->setPen(QColor(0, 128, 0));
                break;
            case 3:
                //magenta
                painter->setPen(QColor(255, 0, 255));
                break;
            case 4:
                //blue
                painter->setPen(QColor(0, 0, 255));
                break;
            case 5:
                //red
                painter->setPen(QColor(255, 0, 0));
                break;
            case 6:
                //gold
                painter->setPen(QColor(255, 215, 0));
                break;
            case 7:
                //maroon
                painter->setPen(QColor(128, 0, 0));
                break;
            case 8:
                //orange
                painter->setPen(QColor(255, 165, 0));
                break;
            default:
                break;
            }
            painter->drawText(rect.x() + 12, rect.y() + 30, tr("%1").arg(count));
        }
    }
    else if (status == 3) {
        painter->drawPixmap(x, y, QPixmap(":/image/image/flag.png").scaledToHeight(40));
    }
    else if (status == 4) {
        painter->drawPixmap(x, y, QPixmap(":/image/image/flag_incorrect.png").scaledToHeight(40));
    }
    else if (status == 5) {
        painter->drawPixmap(x, y, QPixmap(":/image/image/mine.png").scaledToHeight(40));
    }
    else {
        painter->drawPixmap(x, y, QPixmap(":/image/image/mine.png").scaledToHeight(40));
    }


}

bool BoardDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) {
    QMouseEvent *e = (QMouseEvent *) event;
    //first digit: 1 normal, 2 clicked, 3 flag, 4 ?; second digit: 0 none, 1-8 mines around, 9 mine
    int status = model->data(index).toInt() / 10;
    if (index.column() != currentIndex.column() || index.row() != currentIndex.row()) { //not the same grid clicked
        if (timerLeftPress->isActive()) {
            emit leftClick(currentIndex);
        }
        timerLeftPress->stop();
        if (timerRightPress->isActive()) {
            emit rightClick(currentIndex);
        }
        timerRightPress->stop();
        leftPress = false;
        rightPress = false;
    }
    currentIndex = index;

    emit mouseMove(e->pos());
    //left click
    if (e->button() == Qt::LeftButton) {
        if (e->type() == QMouseEvent::MouseButtonPress) {
            leftPress = true;
        }
        if (e->type() == QMouseEvent::MouseButtonRelease) {
            //on a normal or flag grid
            if (status == 1 || status == 3) {
                //left right click on an unavailable grid
                if (rightPress) {
//                    timerLeftPress->stop();
                    timerRightPress->stop();
//                    leftPress = false;
                    rightPress = false;
                }
                //just left click
                else {
                    timerLeftPress->stop();
                    timerRightPress->stop();
                    leftPress = false;
                    rightPress = false;
                    emit leftClick(index);
                }
            }
            //on a clicked grid
            else if (status == 2) {
                //double click left
                if (timerLeftPress->isActive()) {
                    timerLeftPress->stop();
                    timerRightPress->stop();
                    leftPress = false;
                    rightPress = false;
                    emit doubleClick(index);
                }
                //left right click
                else if (timerRightPress->isActive()) {
                    timerLeftPress->stop();
                    timerRightPress->stop();
                    leftPress = false;
                    rightPress = false;
                    emit leftRightClick(index);
                }
                else {
                    timerLeftPress->start();
                }
            }
        }
        return true;
    }

    //right click
    else if (e->button() == Qt::RightButton) {
        if (e->type() == QMouseEvent::MouseButtonPress) {
            rightPress = true;
        }
        if (e->type() == QMouseEvent::MouseButtonRelease) {
            //on a normal or flag grid
            if (status == 1 || status == 3) {
                //left right click on an unavailable grid
                if (leftPress) {
                    timerLeftPress->stop();
//                    timerRightPress->stop();
                    leftPress = false;
//                    rightPress = false;
                }
                //just right click
                else {
                    timerLeftPress->stop();
                    timerRightPress->stop();
                    leftPress = false;
                    rightPress = false;
                    emit rightClick(index);
                }
            }
            //on a clicked grid
            else if (status == 2) {
                //double click right
                if (timerRightPress->isActive()) {
                    timerLeftPress->stop();
                    timerRightPress->stop();
                    leftPress = false;
                    rightPress = false;
                    emit doubleClick(index);
                }
                //left right click
                else if (timerLeftPress->isActive()) {
                    timerLeftPress->stop();
                    timerRightPress->stop();
                    leftPress = false;
                    rightPress = false;
                    emit leftRightClick(index);
                }
                else {
                    timerRightPress->start();
                }
            }
        }
        return true;
    }
    else {
//        qDebug() << "else" << countElse++;
        return false;
    }
}
