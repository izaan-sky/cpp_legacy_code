#include <gtest/gtest.h>
#include <utility>

#include "OrderFetcher.hpp"
#include "ShippingCalculator.hpp"

class OrderFetcherStub : public IOrderFetcher
{
    public:
    OrderFetcherStub(Order order) {
        m_order = std::move(order);
    }

    Order fetchOrder(const int orderId) override
    {
        return m_order;
    }

    private:
    Order m_order;
};

class OrderFetcherExpressStub : public IOrderFetcher
{
    Order fetchOrder(const int orderId) override
    {
        Order order;
        order.distanceKm = 300;
        order.shippingType = "EXPRESS";
        order.weightKg = 8.5;
        return order;
    }
};

class OrderFetcherOvernightStub : public IOrderFetcher {
    Order fetchOrder(const int orderId) override {
        Order order;
        order.distanceKm = 50;
        order.shippingType = "OVERNIGHT";
        order.weightKg = 2;
        return order;
    }
};

class OrderFetcherInternationalStub : public IOrderFetcher {
    Order fetchOrder(const int orderId) override {
        Order order;
        order.shippingType = "INTERNATIONAL";
        order.weightKg = 20;
        return order;
    }
};

TEST(ShippingCalculatorTest, StandardShippingFor5kgOver120kmIs2Point5)
{
    Order order;
    order.distanceKm = 120;
    order.shippingType = "STANDARD";
    order.weightKg = 5;

    OrderFetcherStub orderFetcherStub(std::move(order));

    ShippingCalculator shippingCalculator(orderFetcherStub);
    const double calculatedCost = shippingCalculator.calculateShipping(1001);
    EXPECT_EQ(2.5, calculatedCost);
}

TEST(ShippingCalculatorTest, ExpressShipping)
{
    Order order;
    order.distanceKm = 300;
    order.shippingType = "EXPRESS";
    order.weightKg = 8.5;

    OrderFetcherStub orderFetcherStub(std::move(order));
    ShippingCalculator shippingCalculator(orderFetcherStub);
    const double calculatedCost = shippingCalculator.calculateShipping(1002);
    EXPECT_EQ(36.8, calculatedCost);
}

TEST(ShippingCalculatorTest, OvernightShipping) {
    Order order;
    order.distanceKm = 50;
    order.shippingType = "OVERNIGHT";
    order.weightKg = 2;

    OrderFetcherStub orderFetcherStub(std::move(order));
    ShippingCalculator shippingCalculator(orderFetcherStub);
    const double calculatedCost = shippingCalculator.calculateShipping(1003);
    EXPECT_EQ(27.4, calculatedCost);
}

TEST(ShippingCalculatorTest, InternationalShipping) {
    Order order;
    order.shippingType = "INTERNATIONAL";
    order.weightKg = 20;

    OrderFetcherStub orderFetcherStub(std::move(order));
    ShippingCalculator shippingCalculator(orderFetcherStub);
    const double calculatedCost = shippingCalculator.calculateShipping(1004);
    EXPECT_EQ(30.0, calculatedCost);
}