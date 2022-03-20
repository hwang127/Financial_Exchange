#include "Order.h"
Order::Order(time_t time_, long id_, bool is_buy_, int quantity_, long price_, std::string symbol_) :
	time(time_),
	id(id_),
	is_buy(is_buy_),
	quantity(quantity_),
	price(Price4(price_)),
	neg_price(Price4(-price_)),
	symbol(symbol_) {}

long Order::get_id() {
	return id;
}
bool Order::get_is_buy() {
	return is_buy;
}
void Order::set_quantity(int new_q)
{ 
	quantity = new_q;
}
Price4 Order::get_price() {
	return price;
}
Price4 Order::get_neg_price() {
	return neg_price;
}
int Order::get_quantity(){
	return quantity;
}
