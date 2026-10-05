#pragma once

class Order;

class ExpressShipping {
public:
    double calculate(const Order &order) const;
};