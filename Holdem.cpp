#include <boost/foreach.hpp>
#include "Holdem.h"

namespace Holdem {

 ns_api::ns_table::cards_combination_t get_best_combination(const ns_api::ns_table::cards& table_cards, const ns_api::ns_table::cards &player_cards)
 {
  ns_api::ns_table::cards tmp_hand(5, -1);

  ns_api::ns_table::cards_combination_t win_combination;

  ns_api::ns_table::cards all_cards(table_cards.size() + player_cards.size(), -1);
  auto it = std::copy(table_cards.begin(), table_cards.end(), all_cards.begin());
  std::copy(player_cards.begin(), player_cards.end(), it);

  for(size_t idx1 = 0; idx1 < all_cards.size(); ++idx1)
  {
      for(size_t idx2 = idx1 + 1; idx2 < all_cards.size(); ++idx2)
      {
          for(size_t idx3 = idx2 + 1;	idx3 < all_cards.size(); ++idx3)
          {
              for(size_t idx4 = idx3 + 1; idx4 < all_cards.size(); ++idx4)
              {
                  for(size_t idx5 = idx4 + 1; idx5 < all_cards.size(); ++idx5)
                  {
                      tmp_hand[0] = all_cards.at(idx1);
                      tmp_hand[1] = all_cards.at(idx2);
                      tmp_hand[2] = all_cards.at(idx3);
                      tmp_hand[3] = all_cards.at(idx4);
                      tmp_hand[4] = all_cards.at(idx5);

                      std::sort(tmp_hand.begin(), tmp_hand.end(), sort_greater_card);

                      win_combination = std::max(win_combination, best_combination(tmp_hand));
                  }
              }
          }
      }
  }

  return win_combination;
 }

 
} // namespace Holdem
