// Financial_Exchange.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
#include "Price4.h"
#include "Order.h"
#include "Order_book.h"
#include <chrono>
#include <string>
// for convenience
using json = nlohmann::json;
time_t time_since_epoch()
{
    auto now = std::chrono::system_clock::now();
    return std::chrono::system_clock::to_time_t(now);
}
int main(int argc, char* argv[])
{
    /*Price4 p = Price4(100100);
    json j;
    j["type"] = "NEW";
    j["price"] = p.to_str();
    j["quantity"] = "100";
    j["time"] = time_since_epoch();
    j["id"] = 0;
    j["is_buy"] = true;
    std::cout << j<<std::endl;

    time_t time_ = time_since_epoch(); 
    long id_ = 0;
    bool is_buy_ = true;
    int quantity_ = 100;
    long price_ = 23456700;
    std::string symbol_ = "AAPL";
    Order order(time_, id_, is_buy_, quantity_, price_, symbol_);
    
    Order_book book; // create order book
    book.add_order(order);
    book.cancel_order(id_);
    std::cout << order.get_id() << std::endl;*/

    std::ifstream file;
    for (int i = 1; i < argc; i++) {
        std::string s(argv[i]);
        if (s.rfind("-input ", 0) == 0) {
            file = std::ifstream(s.substr(std::string("-input ").length()));
            if (file.good()) std::cout << s.substr(std::string("-input ").length())
                << " Input file exists" << std::endl;
            else std::cout << s.substr(std::string("-input ").length())
                << " Input file not found" << std::endl;
        }
        else {
            std::cout << "Unknown: " << s << std::endl;
        }
    }
    if (file.is_open())
    {
        Order_book book; // create order book
        std::string line;
        while (std::getline(file, line))
        {
            json j = json::parse(line);
            std::cout << j << std::endl;
            if (j["type"] == "NEW") {
                auto *order = new Order(j["time"], j["order_id"], (j["side"] == "BUY"),
                    j["quantity"], j["limit_price"], j["symbol"]);
                std::cout << "add order, id = " << j["order_id"] << std::endl;
                book.match(order);
            }
            else {
                book.cancel_order(j["order_id"]);
            }
        }
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
