#include <gtest/gtest.h>

#include "OrderFetcher.hpp"
#include "ShippingCalculator.hpp"

class OrderFetcherStub : public IOrderFetcher
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

TEST(ShippingCalculatorTest, StandardShippingFor5kgOver120kmIs2Point5)
{
    OrderFetcherStub orderFetcherStub;
    ShippingCalculator shippingCalculator(orderFetcherStub);
    const double calculatedCost = shippingCalculator.calculateShipping(1001);
    EXPECT_EQ(2.5, calculatedCost);
}
