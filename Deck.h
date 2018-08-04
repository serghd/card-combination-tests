#ifndef CARDSLIST_H
#define CARDSLIST_H

#include <QListWidget>
#include <boost/cstdint.hpp>
#include "common.h"

class Deck: public QListWidget
{
 Q_OBJECT

public:
 Deck(QWidget* parent = 0);
 void addCard(QPixmap pixmap, boost::int8_t card);
 QList<boost::int8_t> _cards;

protected:
 void dragEnterEvent(QDragEnterEvent*);
 void dragMoveEvent(QDragMoveEvent*);
 void dropEvent(QDropEvent*);
 void startDrag(Qt::DropActions);
};

#endif

