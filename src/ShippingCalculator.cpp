#include "ShippingCalculator.hpp"

#include "OrderFetcher.hpp"
#include "Order.hpp"

#include <boost/asio/connect.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/asio/ssl/stream_base.hpp>

#include <boost/beast/core/flat_buffer.hpp>
#include <boost/beast/core/tcp_stream.hpp>
#include <boost/beast/http/empty_body.hpp>
#include <boost/beast/http/field.hpp>
#include <boost/beast/http/read.hpp>
#include <boost/beast/http/string_body.hpp>
#include <boost/beast/http/verb.hpp>
#include <boost/beast/http/write.hpp>
#include <boost/beast/ssl/ssl_stream.hpp>

#include <boost/json/parse.hpp>
#include <boost/json/value.hpp>

#include <openssl/ssl.h>

#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

namespace asio = boost::asio;

using tcp = asio::ip::tcp;

ShippingCalculator::ShippingCalculator(OrderFetcher fetcher) {
    this->fetcher = fetcher;
}

double ShippingCalculator::calculateShipping(int orderId) {
    try {
        const Order order = fetcher.fetchOrder(orderId);

        if (order.shippingType == "STANDARD") {
            return order.weightKg * 0.5;
        }

        if (order.shippingType == "EXPRESS") {
            return order.weightKg * 0.8
                 + order.distanceKm * 0.1;
        }

        if (order.shippingType == "OVERNIGHT") {
            return order.weightKg * 1.2 + 25;
        }

        throw std::runtime_error(
            "Unknown shipping type: " + order.shippingType
        );

    } catch (const std::exception& e) {
        std::cout << e.what() << '\n';
        return -1;
    }
}
