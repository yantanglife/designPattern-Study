#pragma once
#include <iostream>
#include <string>

namespace bridge {

class AbstractionImp;

// 抽象类
class Abstraction {
public:
    virtual void operation() = 0;
    virtual ~Abstraction() {}
    Abstraction() {}
};


// 扩充抽象类
class RefinedAbstractionA : public Abstraction {
public:
    RefinedAbstractionA(AbstractionImp* imp) : m_imp(imp) {}
    ~RefinedAbstractionA() {}

    void operation();

private:
    // 实现接口类的对象
    AbstractionImp* m_imp;
};


class RefinedAbstractionB : public Abstraction {
public:
    RefinedAbstractionB(AbstractionImp* imp) : m_imp(imp) {}
    ~RefinedAbstractionB() {}

    void operation();

private:
    AbstractionImp* m_imp;
};


// 实现类接口
class AbstractionImp {
public:
    AbstractionImp() {}
    virtual ~AbstractionImp() {}

    virtual void operation() = 0;
};

// 具体实现类
class ConcreteImpA : public AbstractionImp {
public:
    ConcreteImpA() {}
    ~ConcreteImpA() {}

    void operation() { std::cout << "ConcreteImpA::operation()." << std::endl; }
};


// imp RefinedAbstraction::operation()

void RefinedAbstractionA::operation() {
    std::cout << "RefinedAbstractionA::operation()." << std::endl;
    m_imp->operation();
}

void RefinedAbstractionB::operation() {
    std::cout << "RefinedAbstractionB::operation()." << std::endl;
    m_imp->operation();
}


// Test
void bridgeTest() {
    AbstractionImp* pImp = new ConcreteImpA();
    Abstraction* pAbs = new RefinedAbstractionA(pImp);
    pAbs->operation();
    
    delete pImp;
    delete pAbs;
}

}
