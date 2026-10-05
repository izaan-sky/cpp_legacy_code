#pragma once

#include "OrderFetcher.hpp"

class ShippingCalculator {
public:
    ShippingCalculator(IOrderFetcher& fetcher);

    double calculateShipping(int orderId);

    double calculate(const Order &order);

private:
    IOrderFetcher& fetcher;
};
