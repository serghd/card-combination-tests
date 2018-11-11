#include <QDebug>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPaintEvent>
#include <QPainter>
#include <QFile>
#include <QDateTime>
#include <QTextCodec>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Holdem.h"
#include "Omaha.h"
#include "Deck.h"
#include "CardsConteiner.h"

MainWindow::MainWindow()
{
   _ui = new Ui::MainWindowUi;
   _ui->setupUi(this);
   init();
}

MainWindow::~MainWindow() {
   delete _ui;
}

void MainWindow::init()
{
   // basic deck
   _deck_wt = new Deck(this);
   _ui->ltDeck->addWidget(_deck_wt);

   // set deck
   addCardsToDeck();

   // actions
   QObject::connect(_ui->btnApply, SIGNAL(clicked()), SLOT(apply()));
   QObject::connect(_ui->btnCancel, SIGNAL(clicked()), SLOT(cancel()));
   QObject::connect(_ui->btnLog, SIGNAL(clicked()), SLOT(logCards()));
   QObject::connect(_ui->bgGameTypes, SIGNAL(buttonClicked(int)), SLOT(changeGameType(int)));

   _table_cards_wt = new CardsConteiner(5, this);
   _player_cards_wt = new CardsConteiner(4, this);

   _lt_table_cards = new QHBoxLayout;
   _lt_table_cards->addWidget(_table_cards_wt);
   _lt_player_cards = new QHBoxLayout;
   _lt_player_cards->addWidget(_player_cards_wt);

   _ui->gbTableCards->setLayout(_lt_table_cards);
   _ui->gbPlayerCards->setLayout(_lt_player_cards);

   _ui->bgGameTypes->setId(_ui->rbTexasHoldem, 1);
   _ui->bgGameTypes->setId(_ui->rbOmaha, 2);

   setGameType(e_game_type::texas_holdem);

   //QWidget::adjustSize();
}

void MainWindow::addCardsToDeck()
{
   for (int8_t i = 0; i < 52; ++i)
   {
      QPixmap pm(":/img/" + QString::number(i + 1) + ".png");
      QSize true_size = pm.size() / 4;
      //qDebug() << trueSize;
      //width: 38; height: 56
      _deck_wt->addCard(pm.scaled(true_size), i);
   }
}

void MainWindow::apply()
{
   int8_t table_cards_count = static_cast<int8_t>(_table_cards_wt->_cards.size());
   int8_t player_cards_count = static_cast<int8_t>(_player_cards_wt->_cards.size());
   e_game_type game_type = (_ui->bgGameTypes->checkedId() == 1) ? e_game_type::texas_holdem : e_game_type::omaha;

   if (table_cards_count != 5)
   {
      QMessageBox::warning(this,
                           tr("Warning"),
                           tr("Wrong table cards number"),
                       QMessageBox::Ok, QMessageBox::Ok);
      return;
   }

   // texas holdem
   if (game_type == e_game_type::texas_holdem)
   {
      if (player_cards_count != 2)
      {
         QMessageBox::warning(this,
                             tr("Warning"),
                             tr("Wrong cards number of Holdem-player"),
                             QMessageBox::Ok, QMessageBox::Ok);
         return;
      }
   }
   // omaha
   else
   {
      if (player_cards_count != 4)
      {
         QMessageBox::warning(this,
                             tr("Warning"),
                             tr("Wrong cards number of Omaha-player"),
                             QMessageBox::Ok, QMessageBox::Ok);
         return;
      }
   }

   /**************** tests ****************/

   ns_api::ns_table::cards hand_cards = _player_cards_wt->_cards.toVector().toStdVector();
   ns_api::ns_table::cards table_cards = _table_cards_wt->_cards.toVector().toStdVector();

   ns_api::ns_table::cards_combination_t combination;

   // texas holdem
   if (game_type == e_game_type::texas_holdem) {
      combination = Holdem::get_best_combination(table_cards, hand_cards);
   }
   // omaha
   else {
      combination = Omaha::get_best_combination(table_cards, hand_cards);
   }

   _game_type = game_type;
   _table_cards = table_cards;
   _hand_cards = hand_cards;
   _win_combination = combination;

   highlightWinCards();
}

void MainWindow::logCards()
{
   if ( (_table_cards.size() == 0) ||
        (_hand_cards.size() == 0) ||
        (_win_combination._cards.size() == 0) )
   {
      QMessageBox::information(this,
                               tr("Warning"),
                               tr("Not enought data for writing into log"),
                               QMessageBox::Ok, QMessageBox::Ok);
      return;
   }

   // -------------

   QFile file("combinations.log");
   if (!file.open(QIODevice::Append | QIODevice::Text))
   {
      QMessageBox::critical(this,
                            tr("Error"),
                            tr("Error of log-file opening"),
                            QMessageBox::Ok, QMessageBox::Ok);
      return;
   }

   QTextStream out(&file);
   out.setCodec("UTF-8");

   // table cards
   QString table_cards_unicode;
   QString table_cards_orig;
   for (const int8_t& card: _table_cards)
   {
      table_cards_unicode += ns_cards_info::get_card(card) + " ";
      table_cards_orig += QString::number(card) + " ";
   }
   table_cards_unicode = table_cards_unicode.trimmed();
   table_cards_orig = table_cards_orig.trimmed();

   // hand cards
   QString hand_cards_unicode;
   QString hand_cards_orig;
   for (const int8_t& card: _hand_cards)
   {
      hand_cards_unicode += ns_cards_info::get_card(card) + " ";
      hand_cards_orig += QString::number(card) + " ";
   }
   hand_cards_unicode = hand_cards_unicode.trimmed();
   hand_cards_orig = hand_cards_orig.trimmed();

   // win cards
   QString win_cards_unicode;
   QString win_cards_orig;
   for (const int8_t& card: _win_combination._cards)
   {
      win_cards_unicode += ns_cards_info::get_card(card) + " ";
      win_cards_orig += QString::number(card) + " ";
   }
   win_cards_unicode = win_cards_unicode.trimmed();
   win_cards_orig = win_cards_orig.trimmed();

   // game type
   QString game_type = ns_cards_info::get_str_game_type(_game_type);

   // combination name
   QString comb_name = ns_cards_info::get_str_win_combination(_win_combination._combination);

   out << QDateTime::currentDateTime().toString("[yyyy.MM.dd, hh:mm:ss] ")
       << endl
       << game_type << ", " << tr("win combination - ") << comb_name
       << tr(", cards: ") << win_cards_unicode << " (" << win_cards_orig << "); " << endl
       << tr("table cards: ") << table_cards_unicode << " (" << table_cards_orig << "); " << endl
       << tr("player cards: ") << hand_cards_unicode << " (" << hand_cards_orig << ") " << endl
       << "-------------------------------------------------------------------------------"
       << endl << endl;

   file.close();

   QMessageBox::information(this,
                            tr("error log"),
                            tr("Record saved successfully"),
                          QMessageBox::Ok, QMessageBox::Ok);
}

void MainWindow::highlightWinCards()
{
   std::unordered_map<int8_t, QLabel*> cards_items = _table_cards_wt->_cards_items;
   for (const auto& item: _player_cards_wt->_cards_items) {
      cards_items[item.first] = item.second;
   }

   std::vector<int8_t> cards = _win_combination._cards;

   // for (const auto& card: cards) {
   //  std::cout << (int)card << " ";
   // }
   // std::cout << std::endl;

   // highlight win combination
   for (const auto& win_card: cards)
   {
      for (const auto& item: cards_items)
      {
         if (win_card == item.first)
         {
            QPixmap pix(*item.second->pixmap());
            QPainter painter(&pix);
            painter.setBrush(QBrush(QColor(180, 180, 20, 128)));
            painter.drawRect(pix.rect());
            item.second->setPixmap(pix);
         }
      }
   }

   // show combination type
   showWinCombination(_win_combination._combination);
}

void MainWindow::showWinCombination(ns_api::ns_table::e_cards_combination comb)
{
   QString combname = ns_cards_info::get_str_win_combination(comb);
   QString str_combination = tr("Win combination: <b>") + combname + "</b>";

   _ui->lblCardsCombination->setText(str_combination);
}

void MainWindow::cancel() {
   setGameType(e_game_type::texas_holdem);
}

void MainWindow::setGameType(e_game_type g_type)
{
   _table_cards_wt->deleteLater();
   _player_cards_wt->deleteLater();
   _deck_wt->deleteLater();

   _table_cards.clear();
   _hand_cards.clear();
   _win_combination._cards.clear();

   _player_cards_wt->deleteLater();

   _deck_wt = new Deck(this);
   _ui->ltDeck->addWidget(_deck_wt);
   _ui->lblCardsCombination->clear();

   addCardsToDeck();

   _table_cards_wt = new CardsConteiner(5, this);
   _lt_table_cards->addWidget(_table_cards_wt);

   if (g_type == e_game_type::texas_holdem)
   {
      _player_cards_wt = new CardsConteiner(2, this);
      _ui->rbTexasHoldem->setChecked(true);
   }
   else
   {
      _player_cards_wt = new CardsConteiner(4, this);
      _ui->rbOmaha->setChecked(true);
   }

   _lt_player_cards->addWidget(_player_cards_wt);
}

void MainWindow::changeGameType(int val)
{
   if (val == 1) {
      setGameType(e_game_type::texas_holdem);
   }
   else {
      setGameType(e_game_type::omaha);
   }
}


