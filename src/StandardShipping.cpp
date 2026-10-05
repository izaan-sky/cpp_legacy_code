#include "StandardShipping.hpp"

#include "Order.hpp"

double StandardShipping::calculate(const Order order) {
    return order.weightKg * 0.5;
}