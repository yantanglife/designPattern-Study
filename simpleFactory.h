#pragma once
#include <iostream>
#include <string>


namespace simple_fac {

class Product {
public:
    void sameFunc() { std::cout << "Product::sameFunc()." << std::endl; }

    virtual void diffFunc() = 0;
};

class ConcreteProductA : public Product {
public:
    void diffFunc(){ std::cout << "ConcreteProductA::diffFunc()." << std::endl; }
};

class ConcreteProductB : public Product {
public:
    void diffFunc() { std::cout << "ConcreteProductB::diffFunc()." << std::endl; }
};


class Factory {
public:
    static Product* getProduct(std::string productName);
};


Product* Factory::getProduct(std::string productName) {
    Product* product = NULL;
    if (productName == "A") {
        product = new ConcreteProductA();
    }
    else if (productName == "B") {
        product = new ConcreteProductB();
    }
    return product;
}


// Test
void simpleFactoryTest() {
    Factory* pFactory = new Factory();
    Product* pProduct = pFactory->getProduct("A");
    pProduct->sameFunc();
    pProduct->diffFunc();
    delete pProduct;
    delete pFactory;
}

}