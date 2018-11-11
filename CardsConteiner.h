#ifndef PLAYERCARDS_H
#define PLAYERCARDS_H

#include <QList>
#include <QPoint>
#include <QPixmap>
#include <QWidget>
#include <QLabel>

#include <unordered_map>

#include "common.h"

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
class QMouseEvent;
QT_END_NAMESPACE

class CardsConteiner: public QWidget
{
 Q_OBJECT

public:
   CardsConteiner(uint8_t cards_count, QWidget* parent = nullptr);
   void addCard(QPixmap pixmap, int8_t card);
   QList<int8_t> _cards;
   std::unordered_map<int8_t, QLabel*> _cards_items;
   QRect _highlighted_rect;

protected:
   void dragEnterEvent(QDragEnterEvent*);
   void dragLeaveEvent(QDragLeaveEvent*);
   void dragMoveEvent(QDragMoveEvent*);
   void dropEvent(QDropEvent*);
   void mousePressEvent(QMouseEvent*);
   void paintEvent(QPaintEvent*);

private:
   int8_t findCard(const QRect& pieceRect) const;
   const QRect targetSquare(const QPoint &position) const;

   // for drawing background
   QList<QPixmap> _card_pixmaps;
   QList<QRect> _card_rects;

};

#endif
