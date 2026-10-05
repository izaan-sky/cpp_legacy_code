#include "ShippingCalculator.hpp"

#include "OrderFetcher.hpp"
#include "Order.hpp"

#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

#include "StandardShipping.hpp"

ShippingCalculator::ShippingCalculator(IOrderFetcher& fetcher) : fetcher(fetcher) {}

double ShippingCalculator::calculateShipping(int orderId) {
    try {
        const Order order = fetcher.fetchOrder(orderId);

        if (order.shippingType == "STANDARD") {
            return StandardShipping().calculate(order);
        }

        if (order.shippingType == "EXPRESS") {
            return calculate(order);
        }

        if (order.shippingType == "OVERNIGHT") {
            return order.weightKg * 1.2 + 25;
        }

        if (order.shippingType == "INTERNATIONAL") {
            return order.weightKg * 1.5;
        }

        throw std::runtime_error(
            "Unknown shipping type: " + order.shippingType
        );

    } catch (const std::exception& e) {
        std::cout << e.what() << '\n';
        return -1;
    }
}

double ShippingCalculator::calculate(const Order &order)
{
    return order.weightKg * 0.8 + order.distanceKm * 0.1;
}
