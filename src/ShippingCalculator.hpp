#pragma once

#include "Order.hpp"
#include "OrderFetcher.hpp"

class ShippingCalculator {
public:
    ShippingCalculator();
    double calculateShipping(int orderId);

private:
    OrderFetcher fetcher;
};
