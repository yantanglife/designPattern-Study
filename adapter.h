#pragma once
#include <iostream>

namespace adapter {

// 适配者
class Adaptee {
public:
    Adaptee() {}
    ~Adaptee() {}

    void specificRequest() { std::cout << "Adaptee::specificRequest()." << std::endl; }
};


// 目标抽象类
class Target {
public:
    Target() {}
    virtual ~Target() {}

    virtual void request() = 0;
};


// 适配器类
class Adaptor : public Target {
public:
    Adaptor(Adaptee* adaptee) : mp_adaptee(adaptee) {}
    ~Adaptor() {}

    void request() { mp_adaptee->specificRequest(); }

private:
    Adaptee* mp_adaptee;
};


// Test 
void adapterTest() {
    Adaptee* pAdaptee = new Adaptee();
    Target* pTarget = new Adaptor(pAdaptee);
    pTarget->request();
    delete pAdaptee;
    delete pTarget;
}

}