#ifndef CPP_LEGACY_CODE_STANDARDSHIPPING_H
#define CPP_LEGACY_CODE_STANDARDSHIPPING_H

class Order;

class StandardShipping {
public:
    double calculate(const Order &order) const;
};

#endif //CPP_LEGACY_CODE_STANDARDSHIPPING_H
