#include "StandardShipping.hpp"

#include "Order.hpp"

double StandardShipping::calculate(const Order &order) const {
    return order.weightKg * 0.5;
}