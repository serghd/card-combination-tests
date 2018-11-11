#pragma once

#include <QListWidget>

#include "common.h"

class Deck: public QListWidget
{
 Q_OBJECT

public:
 Deck(QWidget* parent = 0);
 void addCard(QPixmap pixmap, int8_t card);
 QList<int8_t> _cards;

protected:
 void dragEnterEvent(QDragEnterEvent*);
 void dragMoveEvent(QDragMoveEvent*);
 void dropEvent(QDropEvent*);
 void startDrag(Qt::DropActions);
};

