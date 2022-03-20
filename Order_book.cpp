#include "Order_book.h"
#include <list>
#include <iostream>
#include <memory>
void Order_book::add_order(Order* order) {
	//Order order(std::move(order_));
	order_list::iterator order_iter;
	list_p list_ptr;
	book* book_p;
	if (order->get_is_buy()){
		book_p = &buy_side;
	}
	else {
		book_p = &sell_side;
	}
	auto it = book_p->find(order->get_price());
	if (it == book_p->end()) {  // if price list does not exist;
		list_ptr = std::make_shared<order_list>();
		auto begin = list_ptr->begin();
		order_iter = list_ptr->insert(begin, order);
		if (order->get_is_buy())book_p->emplace(order->get_neg_price(), list_ptr);
		else book_p->emplace(order->get_price(), list_ptr);
	}
	else {       // if list exists;
		list_ptr = it->second;
		auto end = list_ptr->end();
		order_iter = list_ptr->insert(end, order);
	}
	// add (order_iter, list_ptr) to hashmap with id as key.
	std::pair<order_list::iterator, list_p> order_pair(order_iter, 
		list_ptr);
	std::pair<long, std::pair<order_list::iterator, 
		list_p>> pair(order->get_id(), order_pair);
	all_orders.insert(pair);
}

void Order_book::cancel_order(long order_id) {
	auto got = all_orders.find(order_id);
	if (got == all_orders.end())
		std::cout << "order not found" << std::endl;
	else {	
		auto pair = got->second;
		auto order_iter = pair.first;   // pair.first is order iterator
		pair.second->erase(order_iter); // pair.second is list_ptr
		all_orders.erase(got);
		std::cout << "order canceled" << std::endl;
	}
}

void Order_book::match(Order* order) {
	//Order order(std::move(order_));
	if (order->get_is_buy()) {
		if (sell_side.empty()) {
			add_order(order);
			return;
		}
		else{
			//while order not finished and has counter party.
			while ((order->get_quantity() > 0) &
				(order->get_price() >= sell_side.begin()->first)) {
				trade_list(order, sell_side.begin()->second, 
					sell_side.begin(), sell_side);
			}
		}
	}
	else {
		if (buy_side.empty()) {
			add_order(order);
			return;
		}
		else {
			//while order not finished and has counter party.
			while ((order->get_quantity() > 0) &
				(order->get_neg_price() >= buy_side.begin()->first)) {
				trade_list(order, buy_side.begin()->second, 
					buy_side.begin(), buy_side);
			}
		}
	}
	// add any remaing part of order.
	if (order->get_quantity() > 0) {
		add_order(order);
	}
}


void Order_book::trade_list(Order* order, list_p price_list, 
	book::iterator book_iter, book& book){
	order_list::iterator it = price_list->begin();
	while (it != price_list->end()){
		trade(order, *it);
		long id = (**it).get_id();
		int quantity = (**it).get_quantity();
		
		if (quantity == 0) {
			cancel_order(id); 
			if (price_list->empty()) {
				book.erase(book_iter);
				break;
			}
		}
		
		if (order->get_quantity() == 0) {
			return;
		}
		++it;
	}
}



void Order_book::trade(Order* order1, Order* order2) {
	int traded = std::min(order1->get_quantity(), order2->get_quantity());
	order1->set_quantity(order1->get_quantity() - traded);
	order2->set_quantity(order2->get_quantity() - traded);
}

