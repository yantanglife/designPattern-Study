#pragma once
#include <iostream>
#include <string>

namespace bridge {

class AbstractionImp;

// ������
class Abstraction {
public:
    virtual void operation() = 0;
    virtual ~Abstraction() {}
    Abstraction() {}
};


// ���������
class RefinedAbstractionA : public Abstraction {
public:
    RefinedAbstractionA(AbstractionImp* imp) : m_imp(imp) {}
    ~RefinedAbstractionA() {}

    void operation();

private:
    // ʵ�ֽӿ���Ķ���
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


// ʵ����ӿ�
class AbstractionImp {
public:
    AbstractionImp() {}
    virtual ~AbstractionImp() {}

    virtual void operation() = 0;
};

// ����ʵ����
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
