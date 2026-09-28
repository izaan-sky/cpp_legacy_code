#pragma once

#include "Order.hpp"

class IOrderFetcher
{
public:
    virtual Order fetchOrder(const int orderId) = 0;
};

class OrderFetcher : public IOrderFetcher
{
public:
    Order fetchOrder(const int orderId) override;
};
