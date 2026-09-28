#pragma once

#include "Order.hpp"

class OrderFetcher
{
public:
    Order fetchOrder(const int orderId);
};
