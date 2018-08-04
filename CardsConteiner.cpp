#include <QtGui>
#include "CardsConteiner.h"

CardsConteiner::CardsConteiner(boost::uint8_t cards_cells_count, QWidget* parent): 
 QWidget(parent)
{
 QWidget::setAcceptDrops(true);
 QWidget::setFixedHeight(CARD_HEIGHT);
 QWidget::setStyleSheet("border: 0px");
 QWidget::setFixedWidth(CARD_WIDTH * cards_cells_count);
}

void CardsConteiner::dragEnterEvent(QDragEnterEvent *event)
{
 if (event->mimeData()->hasFormat("image/card"))
 {
  event->accept();
  return;
 }
 event->ignore();
}

void CardsConteiner::dragLeaveEvent(QDragLeaveEvent* event)
{
 QRect updateRect = _highlighted_rect;
 _highlighted_rect = QRect();
 QWidget::update(updateRect);
 event->accept();
}

void CardsConteiner::dragMoveEvent(QDragMoveEvent* event)
{
 QRect updateRect = _highlighted_rect.united(targetSquare(event->pos()));

 if ( event->mimeData()->hasFormat("image/card") && 
      (findCard(targetSquare(event->pos())) == -1) )
 {
  _highlighted_rect = targetSquare(event->pos());
  event->setDropAction(Qt::MoveAction);
  event->accept();
 }
 else
 {
  _highlighted_rect = QRect();
  event->ignore();
 }

 QWidget::update(updateRect);
}

void CardsConteiner::dropEvent(QDropEvent* event)
{
 if ( event->mimeData()->hasFormat("image/card") && 
      (findCard(targetSquare(event->pos())) == -1) )
 {
  QByteArray pieceData = event->mimeData()->data("image/card");
  QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
  QRect square = targetSquare(event->pos());
  QPixmap pixmap;
  boost::int8_t card;
  dataStream >> pixmap >> card;
  
  QLabel* newCard = new QLabel(this);
  newCard->setFixedSize(CARD_WIDTH, CARD_HEIGHT);
  newCard->setPixmap(pixmap);
  newCard->move(square.topLeft());
  newCard->show();
  newCard->setAttribute(Qt::WA_DeleteOnClose);

  _card_pixmaps.append(pixmap);
  _card_rects.append(square);
  _cards.append(card);
  _cards_items[card] = newCard;

  _highlighted_rect = QRect();
  QWidget::update(square);

  event->setDropAction(Qt::MoveAction);
  event->accept();
  return;
 }
 _highlighted_rect = QRect();
 event->ignore();
}

boost::int8_t CardsConteiner::findCard(const QRect &pieceRect) const
{
 for (int i = 0; i < _card_rects.size(); ++i)
 {
  if (pieceRect == _card_rects[i])
   return i;
 }
 return -1;
}

void CardsConteiner::mousePressEvent(QMouseEvent* event)
{
 QRect square = targetSquare(event->pos());
 boost::int8_t found = findCard(square);
 if (found == -1)
     return;

 QLabel* child = static_cast<QLabel*>(QWidget::childAt(event->pos()));
 if (!child)
   return;

 QPixmap pixmap = _card_pixmaps[found];
 boost::int8_t card = _cards[found];
 _card_pixmaps.removeAt(found);

 
 QLabel* lbl(0);
 auto iter = _cards_items.find(_cards.at(found));
 if (iter != _cards_items.end())
 {
  lbl = iter->second;
  _cards_items.erase(iter);
 }
 _cards.removeAt(found);

 _card_rects.removeAt(found);
 
 QWidget::update(square);

 QByteArray itemData;
 QDataStream dataStream(&itemData, QIODevice::WriteOnly);

 dataStream << pixmap << card;

 QMimeData* mimeData = new QMimeData;
 mimeData->setData("image/card", itemData);

 QDrag* drag = new QDrag(this);
 drag->setMimeData(mimeData);
 drag->setHotSpot(event->pos() - square.topLeft());
 drag->setPixmap(pixmap);

 if (!(drag->exec(Qt::MoveAction) == Qt::MoveAction))
 {
  _card_pixmaps.insert(found, pixmap);
  _cards.insert(found, card);
  _cards_items[card] = lbl;
  
  _card_rects.insert(found, square);
  child->show();
  child->setPixmap(pixmap);
  QWidget::update(targetSquare(event->pos()));
 }
 else
  child->close();
}

void CardsConteiner::paintEvent(QPaintEvent* event)
{
 QPainter painter;
 painter.begin(this);
 painter.fillRect(event->rect(), Qt::white);

 if (_highlighted_rect.isValid())
 {
  painter.setBrush(QColor("#ffcccc"));
  painter.setPen(Qt::NoPen);
  painter.drawRect(_highlighted_rect.adjusted(0, 0, -1, -1));
 }

 for (int i = 0; i < _card_rects.size(); ++i)
  painter.drawPixmap(_card_rects[i], _card_pixmaps[i]);
 painter.end();
}

const QRect CardsConteiner::targetSquare(const QPoint& position) const
{
 QRect rect = QRect(position.x() / CARD_WIDTH * CARD_WIDTH, position.y() / CARD_HEIGHT * CARD_HEIGHT, CARD_WIDTH, CARD_HEIGHT);
 return rect;
}

void CardsConteiner::addCard(QPixmap pixmap, boost::int8_t card)
{
 int offset(0);
 for (int i = 0; i < _card_rects.size(); ++i)
  offset += CARD_WIDTH;

 // new card 
 QLabel* lbl = new QLabel(this);
 lbl->setFixedSize(CARD_WIDTH, CARD_HEIGHT);
 lbl->setPixmap(pixmap);
 lbl->move((lbl->x() + offset), lbl->y());
 _card_pixmaps.append(pixmap);
 QRect rectlbl = targetSquare(lbl->pos());
 _card_rects.append(rectlbl);
 _cards.append(card);
 _cards_items[card] = lbl;
}