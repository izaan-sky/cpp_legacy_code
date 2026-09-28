#include <gtest/gtest.h>

#include "OrderFetcher.hpp"
#include "ShippingCalculator.hpp"

class OrderFetcherStandardStub : public IOrderFetcher
{
    Order fetchOrder(const int orderId) override
    {
        Order order;
        order.distanceKm = 120;
        order.shippingType = "STANDARD";
        order.weightKg = 5;
        return order;
    }
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

TEST(ShippingCalculatorTest, StandardShippingFor5kgOver120kmIs2Point5)
{
    OrderFetcherStandardStub orderFetcherStub;
    ShippingCalculator shippingCalculator(orderFetcherStub);
    const double calculatedCost = shippingCalculator.calculateShipping(1001);
    EXPECT_EQ(2.5, calculatedCost);
}

TEST(ShippingCalculatorTest, ExpressShipping)
{
    OrderFetcherExpressStub orderFetcherExpressStub;
    ShippingCalculator shippingCalculator(orderFetcherExpressStub);
    const double calculatedCost = shippingCalculator.calculateShipping(1002);
    EXPECT_EQ(36.8, calculatedCost);
}