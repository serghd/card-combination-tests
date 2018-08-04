#ifndef COMMON_H
#define	COMMON_H

#include <boost/cstdint.hpp>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <string>
#include <stdexcept>

#include <QString>
#include <QDebug>

static const int CARD_WIDTH = 38;
static const int CARD_HEIGHT = 56;

enum e_game_type
{
	texas_holdem = 1,
	omaha = 2
};

namespace cards_info
{
inline QString get_str_game_type(e_game_type game_type)
{
	QString str_game_type = "-";

	switch(game_type)
	{
	case texas_holdem:
		str_game_type = "Texas Holdem";
		break;
	case omaha:
		str_game_type = "Omaha";
		break;
	}

	return str_game_type;
}

inline QString get_card(int card)
{
	QString suit;
	QString rating;

	switch (card / 13)
	{
	case 0: // Clubs
		suit = QChar(0x2663);
		break;
	case 1: // Spades
		suit = QChar(0x2660);
		break;
	case 2: // Diamonds
		suit = QChar(0x2662);
		break;
	case 3: // Hearts
		suit = QChar(0x2661);
		break;
	default:
		suit = QChar('-');
		break;
	}

	switch (card % 13)
	{
	case 0:
		rating = QString("2");
		break;
	case 1:
		rating = QString("3");
		break;
	case 2:
		rating = QString("4");
		break;
	case 3:
		rating = QString("5");
		break;
	case 4:
		rating = QString("6");
		break;
	case 5:
		rating = QString("7");
		break;
	case 6:
		rating = QString("8");
		break;
	case 7:
		rating = QString("9");
		break;
	case 8:
		rating = QString("10");
		break;
	case 9:
		rating = QString("J");
		break;
	case 10:
		rating = QString("Q");
		break;
	case 11:
		rating = QString("K");
		break;
	case 12:
		rating = QString("A");
		break;
	default:
		rating = QString("-");
		break;
	}
	return rating + suit;
}
} // namespace cards_info

/****** for combination tests *******/

namespace ns_api
{
namespace ns_table
{
typedef int8_t card;
typedef std::vector<card> cards;

enum class e_cards_combination: char
{
	hight_card,
	pair,
	doper,
	set,
    // когда в стрите туз - наименьшая карта
	wheel,
	straight,
	flush,
	full_house,
	four,
    // флеш-стрит с наименьшим тузом
    steel_wheel,
	straight_flush,
	royal_flush
};

struct cards_combination_t
{
	cards_combination_t(e_cards_combination comb, cards c):
		// комбинация по умолчанию, не удалять!
		_combination(comb),
		_cards(c)
	{}

	cards_combination_t():
		// комбинация по умолчанию, не удалять!
		_combination(e_cards_combination::hight_card),
		_cards(5, -1)
	{}

	bool operator ==(const cards_combination_t & cc) const
	{
		return (compare(cc) == 0);
	}
	bool operator>(const cards_combination_t & cc) const
	{
		return (compare(cc) > 0);
	}
	bool operator<(const cards_combination_t & cc) const
	{
		return (compare(cc) < 0);
	}

	// сравнение двух комбинаций
	int compare(const cards_combination_t & cc) const
	{
		if (_combination < cc._combination)
			return -1;
		if (_combination > cc._combination)
			return 1;

		//если выигрышные комбинации равны, то сравниваем по картам
		for (std::size_t i = 0; i < _cards.size(); ++i)
		{
			if (_cards[i] % 13 < cc._cards[i] % 13)
			{
				return -1;
			}
			if (_cards[i] % 13 > cc._cards[i] % 13)
			{
				return 1;
			}
		}
		return 0;
	}

	e_cards_combination _combination;
	cards _cards;
};
} // namespace ns_table
} // namespace ns_api

inline std::string get_suit_sign(int8_t suit)
{
	std::string suit_sign = "";

	switch (suit)
	{
	case 0:
		suit_sign = "c"; // clubs, "креста"
		break;
	case 1:
		suit_sign = "s"; // spades, "пика"
		break;
	case 2:
		suit_sign = "d"; // diamonds, "бубна"
		break;
	case 3:
		suit_sign = "h"; // hearts, "чирва"
		break;
	}
	return suit_sign;
}

inline std::string get_rating_sign(int8_t rating)
{
	char sign[5];

	switch (rating)
	{
	case 9:
		return std::string("J");
		break;
	case 10:
		return std::string("Q");
		break;
	case 11:
		return std::string("K");
		break;
	case 12:
		return std::string("A");
		break;
	default:
		sprintf(sign, "%d", rating + 2);
		std::string s(sign);
		return s;
		break;
	}

	return "<invalid rating sign>";
}

inline void print_hand(const std::string& msg, const ns_api::ns_table::cards& crds)
{
	std::string message = msg;
	for (ns_api::ns_table::card a: crds)
	{
		message += get_rating_sign(a % 13);
		message += get_suit_sign(a / 13) + " ";
	}

	std::cout << std::endl << message << std::flush;
}

inline void print_hand(const std::string& msg, const ns_api::ns_table::cards& crds, const ns_api::ns_table::cards& crds2)
{
	std::string message = msg;

	for (ns_api::ns_table::card a: crds)
	{
		message += get_rating_sign(a % 13);
		message += get_suit_sign(a / 13) + " ";
	}

	for (ns_api::ns_table::card a: crds2)
	{
		message += get_rating_sign(a % 13);
		message += get_suit_sign(a / 13) + " ";
	}

	std::cout << std::endl << message << std::flush;
}

inline bool sort_greater_card(const int& i1, const int& i2)
{
	int k1 = i1 % 13;
	int k2 = i2 % 13;

	if (k1 != k2)
	{
		return (k1) > (k2);
	}
	else
		return (i1 / 13) > (i2 / 13);
}

namespace cards_info
{
inline QString get_str_win_combination(ns_api::ns_table::e_cards_combination comb)
{
	using namespace ns_api::ns_table;

	QString str_combination = "";

	switch(comb)
	{
	case e_cards_combination::hight_card:
		str_combination += "hight card";
		break;
	case e_cards_combination::pair:
		str_combination += "pair";
		break;
	case e_cards_combination::doper:
		str_combination += "doper";
		break;
	case e_cards_combination::set:
		str_combination += "set";
		break;
	case e_cards_combination::wheel:
		str_combination += "wheel";
		break;
	case e_cards_combination::straight:
		str_combination += "straight";
		break;
	case e_cards_combination::steel_wheel:
		str_combination += "steel_wheel";
		break;
	case e_cards_combination::flush:
		str_combination += "flush";
		break;
	case e_cards_combination::full_house:
		str_combination += "full house";
		break;
	case e_cards_combination::four:
		str_combination += "four";
		break;
	case e_cards_combination::straight_flush:
		str_combination += "straight flush";
		break;
	case e_cards_combination::royal_flush:
		str_combination += "royal flush";
		break;
	}

	return str_combination;
}
} // namespace cards_info

inline ns_api::ns_table::cards_combination_t best_combination(const ns_api::ns_table::cards& cards) {
	if(cards.size() != 5)
		throw std::runtime_error("Wrong hand size");

	std::map<int, ns_api::ns_table::cards> table;

	std::vector<ns_api::ns_table::e_cards_combination> combinations;
	combinations.push_back(ns_api::ns_table::e_cards_combination::hight_card);

	/** Get the count table */
	for(size_t idx = 0; idx < cards.size(); ++idx) {
		int currentRating = cards.at(idx) % 13;
		int count = std::count_if(cards.begin(), cards.end(), [&](ns_api::ns_table::card card){ return card % 13 == currentRating; });
		table[count].push_back(cards.at(idx));
	}

	/** Check for Flush */
	auto it = cards.begin();
	int suit = *it / 13;
	bool flush_suit = ( 4 == std::count_if(++it, cards.end(), [&] (ns_api::ns_table::card card) { return (card / 13 == suit); } ) );
	if(flush_suit) {
		combinations.push_back(ns_api::ns_table::e_cards_combination::flush);
	}

	/** Straight */
	bool straight = true;
	for(std::size_t idx = 1; idx < cards.size(); ++idx) {
		if(cards.at(idx) % 13 + static_cast<ns_api::ns_table::card>(idx) != cards.at(0) % 13) {
			straight = false;
			break;
		}
	}
	if(cards.at(0) % 13 == 12 && cards.at(1) % 13 == 3 && cards.at(2) % 13 == 2 && cards.at(3) % 13 == 1 && cards.at(4) % 13 == 0) {
		if(flush_suit) {
			combinations.push_back(ns_api::ns_table::e_cards_combination::steel_wheel);
		} else {
			combinations.push_back(ns_api::ns_table::e_cards_combination::wheel);
		}
	}

	if(straight) {
		/** Straight flush */
		if(flush_suit) {
			if(cards.at(0) % 13 == 12 && cards.at(1) % 13 == 11)
				combinations.push_back(ns_api::ns_table::e_cards_combination::royal_flush);
			else
				combinations.push_back(ns_api::ns_table::e_cards_combination::straight_flush);
		} else {
			combinations.push_back(ns_api::ns_table::e_cards_combination::straight);
		}
	}


	ns_api::ns_table::cards result;
	for(size_t count = 4; count > 0; --count) {
		ns_api::ns_table::cards& sub = table[count];
		if(sub.empty())
			continue;

		std::sort(sub.begin(), sub.end(), [](ns_api::ns_table::card c1, ns_api::ns_table::card c2) { return c1 % 13 > c2 % 13; } );
		std::copy(sub.begin(), sub.end(), std::back_inserter(result));

		switch(count) {
			case 0:
			case 1:
				// Do nothing
				break;
			case 2: // Pair
				if(sub.size() == count) /** Pair */ {
					combinations.push_back(ns_api::ns_table::e_cards_combination::pair);
				} else if(sub.size() == 4) /** Doper */ {
					combinations.push_back(ns_api::ns_table::e_cards_combination::doper);
				} else {
					throw std::runtime_error("Wrong poker-eval algorithm");
				}
				break;
			case 3:
				if(sub.size() == count) {
					if(!table[2].empty()) /** FullHouse */ {
						combinations.push_back(ns_api::ns_table::e_cards_combination::full_house);
					} else /** Trips */ {
						combinations.push_back(ns_api::ns_table::e_cards_combination::set);
					}
				} else {
					throw std::runtime_error("Wrong poker-eval algorithm");
				}
				break;
			case 4: // Quads
				if(sub.size() == count) {
					combinations.push_back(ns_api::ns_table::e_cards_combination::four);
				} else {
					throw std::runtime_error("Wrong poker-eval algorithm");
				}
				break;
			default: // Smth going wrong, should be another value
				throw std::runtime_error("Wrong poker-eval algorithm");
		}
	}

	std::sort(combinations.begin(), combinations.end(), std::greater<ns_api::ns_table::e_cards_combination>());

#ifdef DEBUG
	print_hand(cards_info::get_str_win_combination(combinations.front()).toStdString() + " ", result);
#endif

	return ns_api::ns_table::cards_combination_t(combinations.front(), result);
}


#endif	/* COMMON_H */

