#include "ExpressShipping.hpp"

#include "Order.hpp"

double ExpressShipping::calculate(const Order &order) const
{
    return order.weightKg * 0.8 + order.distanceKm * 0.1;
}
