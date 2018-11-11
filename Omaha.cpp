#include <assert.h>
#include <boost/foreach.hpp>
#include <vector>
#include "Omaha.h"

ns_api::ns_table::cards_combination_t
Omaha::choose_best_combination(const std::vector<ns_api::ns_table::cards>& v_hand_cards, const ns_api::ns_table::cards& tablecards)
{
   std::vector<ns_api::ns_table::cards_combination_t> cc_list;

   for (const auto& cards_item: v_hand_cards)
   {
      ns_api::ns_table::cards_combination_t cc = get_best_combination(cards_item, tablecards);
      cc_list.push_back(cc);
   }

   ns_api::ns_table::cards_combination_t ret_val;
   ns_api::ns_table::cards_combination_t max_cc;

   for (const auto& cards_item: cc_list)
   {
      if (cards_item > max_cc)
      {
         max_cc = cards_item;
         ret_val = cards_item;
      }
      else if (cards_item == max_cc) {
         ret_val = cards_item;
      }
   }

   return ret_val;
}

ns_api::ns_table::cards_combination_t Omaha::get_best_combination(const ns_api::ns_table::cards& table_cards, const ns_api::ns_table::cards& player_cards) 
{
 ns_api::ns_table::cards tmp_hand(5, -1);

 ns_api::ns_table::cards_combination_t win_combination;

 for(size_t idx1 = 0; idx1 < table_cards.size(); ++idx1)
 {
    for(size_t idx2 = idx1 + 1; idx2 < table_cards.size(); ++idx2)
    {
       for(size_t idx3 = idx2 + 1;	idx3 < table_cards.size(); ++idx3)
       {
          for(size_t idx4 = 0; idx4 < player_cards.size(); ++idx4)
          {
             for(size_t idx5 = idx4 + 1; idx5 < player_cards.size(); ++idx5)
             {
                tmp_hand[0] = table_cards.at(idx1);
                tmp_hand[1] = table_cards.at(idx2);
                tmp_hand[2] = table_cards.at(idx3);
                tmp_hand[3] = player_cards.at(idx4);
                tmp_hand[4] = player_cards.at(idx5);

                std::sort(tmp_hand.begin(), tmp_hand.end(), sort_greater_card);

                win_combination = std::max(win_combination, best_combination(tmp_hand));
             }
          }
       }
    }
 }
 return win_combination;
}
