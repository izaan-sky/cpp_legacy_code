#include "ShippingCalculator.hpp"

#include "OrderFetcher.hpp"
#include "Order.hpp"

#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

#include "StandardShipping.hpp"
#include "ExpressShipping.hpp"

ShippingCalculator::ShippingCalculator(IOrderFetcher& fetcher) : fetcher(fetcher) {}

double ShippingCalculator::calculateShipping(int orderId) {
    try {
        const Order order = fetcher.fetchOrder(orderId);

        if (order.shippingType == "STANDARD") {
            return StandardShipping().calculate(order);
        }

        if (order.shippingType == "EXPRESS") {
            return ExpressShipping().calculate(order);
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
