#pragma once
#include <map>
#include <unordered_map>
#include "Order.h"
#include <list>
#include <tuple>
#include <memory>
typedef std::list<Order*> order_list;
typedef std::shared_ptr<order_list> list_p;
typedef std::map<Price4, list_p> book;
class Order_book
{
	long order_number = 0;
	book sell_side;
	book buy_side;
	std::unordered_map<long, 
std::pair<order_list::iterator, list_p>> all_orders;

public:
	Order_book() = default;
	void check_valid(Order& order);
	void add_order(Order* order);
	void cancel_order(long order_id);
	void match(Order* order);
	void trade(Order* buy_order, Order* sell_order);
	void trade_list(Order* order, list_p price_list,
		book::iterator book_iter, book& book);
	void trade_list(Order* order, list_p price_list,
		book::reverse_iterator book_iter, book& book);
};

