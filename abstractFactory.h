#pragma once
#include <iostream>

/*
抽象工厂模式为创建一组对象提供了一种解决方案.
与工厂方法模式相比，抽象工厂模式中的具体工厂不只是创建一种产品，它负责创建一族产品
*/

namespace abstract_fac {

class AbstractProductA;
class AbstractProductB;

// 抽象工厂
class Factory {
public:
    virtual AbstractProductA* createProductA() = 0;
    virtual AbstractProductB* createProductB() = 0;
};

// 具体工厂1, 负责生产 型号1 的产品
class ConcreteFactory1 : public Factory {
public:
    AbstractProductA* createProductA();
    AbstractProductB* createProductB();
};
// 具体工厂2, 负责生产 型号2 的产品
class ConcreteFactory2 : public Factory {
public:
    AbstractProductA* createProductA();
    AbstractProductB* createProductB();
};

// 抽象产品
class AbstractProductA {
public:
    virtual void func() = 0;
};

// 抽象产品
class AbstractProductB {
public:
    virtual void func() = 0;
};

// 具体产品A, 由具体工厂1 生成
class ConcreteProductA1 : public AbstractProductA {
public:
    void func() { std::cout << "Concrete-Product-A-1" << std::endl; }
};

// 具体产品A, 由具体工厂2 生成
class ConcreteProductA2 : public AbstractProductA {
public:
    void func() { std::cout << "Concrete-Product-A-2" << std::endl; }
};

// 具体产品B, 由具体工厂1 生成
class ConcreteProductB1 : public AbstractProductB {
public:
    void func() { std::cout << "Concrete-Product-B-1" << std::endl; }
};

// 具体产品A, 由具体工厂2 生成
class ConcreteProductB2 : public AbstractProductB {
public:
    void func() { std::cout << "Concrete-Product-B-2" << std::endl; }
};

// 工厂1 生产 产品A
AbstractProductA*
ConcreteFactory1::createProductA() {
    return new ConcreteProductA1();
}

AbstractProductB*
ConcreteFactory1::createProductB() {
    return new ConcreteProductB1();
}

// 工厂2 生产 产品A
AbstractProductA*
ConcreteFactory2::createProductA() {
    return new ConcreteProductA2();
}

AbstractProductB*
ConcreteFactory2::createProductB() {
    return new ConcreteProductB2();
}


// Test
void abstractFacTest() {
    // 具体工厂1，只生产 型号1 的产品
    Factory* pFactory = new ConcreteFactory1();
    AbstractProductA* pProductA = pFactory->createProductA();
    pProductA->func();
    AbstractProductB* pProductB = pFactory->createProductB();
    pProductB->func();
    // 具体工厂2，只生产 型号2 的产品
    pFactory = new ConcreteFactory2();
    pProductA = pFactory->createProductA();
    pProductA->func();
    pProductB = pFactory->createProductB();
    pProductB->func();
    //
    delete pFactory;
    delete pProductA;
    delete pProductB;
}

}