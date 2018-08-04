#ifndef TEST_H
#define	TEST_H

#include "common.h"

namespace Omaha {

ns_api::ns_table::cards_combination_t 
choose_best_combination(const std::vector<ns_api::ns_table::cards>& v_hand_cards, const ns_api::ns_table::cards& tablecards);
 
ns_api::ns_table::cards_combination_t 
get_best_combination(const ns_api::ns_table::cards& table_cards, const ns_api::ns_table::cards& player_cards);

} // namespace Omaha

#endif	/* TEST_H */

