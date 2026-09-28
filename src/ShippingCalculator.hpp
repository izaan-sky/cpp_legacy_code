#pragma once

#include "Order.hpp"
#include "OrderFetcher.hpp"

class ShippingCalculator {
public:
    Order fetchOrder(const int orderId);
    double calculateShipping(int orderId);

private:
    OrderFetcher fetcher;
};
