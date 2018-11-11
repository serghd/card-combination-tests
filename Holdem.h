#pragma once

#include "common.h"

namespace Holdem {

ns_api::ns_table::cards_combination_t get_best_combination(const ns_api::ns_table::cards& table_cards, const ns_api::ns_table::cards& player_cards);


} // namespace Holdem
