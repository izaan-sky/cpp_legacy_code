#pragma once

#include "Order.hpp"
#include "OrderFetcher.hpp"

class ShippingCalculator {
public:
    ShippingCalculator(OrderFetcher fetcher);
    double calculateShipping(int orderId);

private:
    OrderFetcher fetcher;
};
