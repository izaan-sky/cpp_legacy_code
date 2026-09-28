#pragma once

#include "Order.hpp"
#include "OrderFetcher.hpp"

class ShippingCalculator {
public:
    ShippingCalculator(IOrderFetcher& fetcher);
    double calculateShipping(int orderId);

private:
    IOrderFetcher& fetcher;
};
