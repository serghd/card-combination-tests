#pragma once

#include <QDialog>
#include <QScopedPointer>

#include "common.h"

namespace Ui {
   class MainWindowUi;
}
class Deck;
class CardsConteiner;
class QHBoxLayout;

class MainWindow: public QDialog
{
 Q_OBJECT

public:
   MainWindow();
   ~MainWindow();
   void init();
   void addCardsToDeck();
   void setGameType(e_game_type g_type = e_game_type::texas_holdem);
   void highlightWinCards();
   void showWinCombination(ns_api::ns_table::e_cards_combination comb);

   e_game_type _game_type;
   std::vector<int8_t> _table_cards;
   std::vector<int8_t> _hand_cards;
   ns_api::ns_table::cards_combination_t _win_combination;

private:
   Ui::MainWindowUi* _ui;
   Deck* _deck_wt;
   QHBoxLayout* _lt_table_cards;
   QHBoxLayout* _lt_player_cards;
   CardsConteiner* _table_cards_wt;
   CardsConteiner* _player_cards_wt;

public slots:
   void changeGameType(int);
   void cancel();
   void apply();
   void logCards();

};
