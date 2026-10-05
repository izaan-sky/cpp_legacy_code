#pragma once

#include "OrderFetcher.hpp"

class ShippingCalculator {
public:
    ShippingCalculator(IOrderFetcher& fetcher);

    double calculate(Order order);

    double calculateShipping(int orderId);

private:
    IOrderFetcher& fetcher;
};
