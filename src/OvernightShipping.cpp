#include "OvernightShipping.hpp"

#include "Order.hpp"

double OvernightShipping::calculate(const Order &order) const {
    return order.weightKg * 1.2 + 25;
}
