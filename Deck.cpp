#include <QtGui>
#include <stdint.h>
#include "Deck.h"

Deck::Deck(QWidget *parent): QListWidget(parent)
{
   QListWidget::setViewMode(QListView::IconMode);
   QListWidget::setIconSize(QSize(CARD_WIDTH, CARD_HEIGHT));
   QListWidget::setSpacing(10);
   QListWidget::setAcceptDrops(true);
   QListWidget::setDropIndicatorShown(true);
   QWidget::setFixedWidth(748);
   QWidget::setFixedHeight(300);
}

void Deck::dragEnterEvent(QDragEnterEvent *event)
{
   if (event->mimeData()->hasFormat("image/card"))
   {
      event->accept();
      return;
   }
   event->ignore();
}

void Deck::dragMoveEvent(QDragMoveEvent* event)
{
   if (event->mimeData()->hasFormat("image/card"))
   {
      event->setDropAction(Qt::MoveAction);
      event->accept();
      return;
   }
   event->ignore();
}

void Deck::dropEvent(QDropEvent* event)
{
   if (event->mimeData()->hasFormat("image/card"))
   {
      QByteArray pieceData = event->mimeData()->data("image/card");
      QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
      QPixmap pixmap;
      int8_t card_rating;
      dataStream >> pixmap >> card_rating;

      addCard(pixmap, card_rating);

      event->setDropAction(Qt::MoveAction);
      event->accept();
      return;
   }
   event->ignore();
}

void Deck::addCard(QPixmap pixmap, int8_t card)
{
   QListWidgetItem* cardItem = new QListWidgetItem(this);
   cardItem->setIcon(QIcon(pixmap));
   cardItem->setData(Qt::UserRole, QVariant(pixmap));
   cardItem->setData(Qt::UserRole + 1, card);
   cardItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
   _cards << card;
   //qDebug() << "table cards: " << this->cards;
}

void Deck::startDrag(Qt::DropActions)
{
   QListWidgetItem* item = this->currentItem();

   QByteArray itemData;
   QDataStream dataStream(&itemData, QIODevice::WriteOnly);
   //QPixmap pixmap = qVariantValue<QPixmap>(item->data(Qt::UserRole));
   QPixmap pixmap = item->data(Qt::UserRole).value<QPixmap>();

   int8_t card = static_cast<int8_t>(item->data(Qt::UserRole + 1).toInt());

   dataStream << pixmap << card;
   _cards.removeAt(_cards.indexOf(card));

   QMimeData* mimeData = new QMimeData;
   mimeData->setData("image/card", itemData);

   QDrag* drag = new QDrag(this);
   drag->setMimeData(mimeData);
   drag->setHotSpot(QPoint(pixmap.width()/2, pixmap.height()/2));
   drag->setPixmap(pixmap);

   if (drag->exec(Qt::MoveAction) == Qt::MoveAction) {
      delete takeItem(row(item));
   }
}
