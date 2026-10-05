#pragma once

class Order;

class OvernightShipping {
public:
    double calculate(const Order &order) const;
};
