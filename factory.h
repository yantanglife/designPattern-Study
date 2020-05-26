#pragma once
#include <iostream>

/*
* 在简单工厂模式中只提供一个工厂类，该工厂类处于对产品类进行实例化的中心位置，
* 它需要知道每一个产品对象的创建细节，并决定何时实例化哪一个产品类.
*
* 简单工厂模式最大的缺点是当有新产品要加入到系统中时，必须修改工厂类，
* 需要在其中加入必要的业务逻辑，这违背了“开闭原则”.
*
* 在工厂方法模式中，不再提供一个统一的工厂类来创建所有的产品对象，
* 而是针对不同的产品提供不同的工厂，系统提供一个与产品等级结构对应的工厂等级结构.
*/

namespace factory {

class Product {
public:
    Product() {}
    virtual ~Product() {}
};

class ConcreteProduct : public Product {
public:
    ConcreteProduct(std::string name) : m_name(name) {}
    ~ConcreteProduct() {}
    void func() { std::cout << "ConcreteProduct::func()." << std::endl; }
    std::string getName() { return m_name; }
private:
    std::string m_name;
};

class Factory {
public:
    virtual Product* factoryFunc() = 0;
};

class ConcreteFactory : public Factory {
public:
    Product* factoryFunc();
};

Product* ConcreteFactory::factoryFunc() {
    return new ConcreteProduct("ConcreteProductA");
}


// Test
void factoryTest() {
    Factory* pFactory = new ConcreteFactory();
    Product* pProduct = pFactory->factoryFunc();
    auto pConProduct = static_cast<ConcreteProduct*>(pProduct);
    pConProduct->func();
    std::cout << pConProduct->getName() << std::endl;

    delete pFactory;
    delete pProduct;
    delete pConProduct;
}

}