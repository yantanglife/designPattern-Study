#pragma once
#include <iostream>

/*
* ����ģʽ����ҪĿ���ǽ��㷨�Ķ�����ʹ�÷ֿ���Ҳ���ǽ��㷨����Ϊ�ͻ����ֿ���
* ���㷨�Ķ������ר�ŵĲ������У�ÿһ���������װ��һ��ʵ���㷨��
* ʹ���㷨�Ļ�������Գ����������б�̣����ϡ�������תԭ��.
*/

namespace strategy {

class Strategy;

// �����ࣺʹ���㷨
class Context {
public:
    Context() {}
    Context(Strategy* strategy) : m_strategy(strategy) {}
    ~Context() {}

    void setStrategy(Strategy* strategy) { m_strategy = strategy; }

    void algorithm();
private:
    Strategy* m_strategy;
};

// ���������
class Strategy {
public:
    virtual void algorithm() = 0;
};

// ���������
class ConcreteStrategyA : public Strategy {
public:
    void algorithm();
};

class ConcreteStrategyB : public Strategy {
public:
    void algorithm();
};


// 
void Context::algorithm() {
    m_strategy->algorithm();
}

void ConcreteStrategyA::algorithm() {
    std::cout << "ConcreteStrategyA::algorithm()." << std::endl;
}

void ConcreteStrategyB::algorithm() {
    std::cout << "ConcreteStrategyB::algorithm()." << std::endl;
}


// Test
void strategyTest() {
    Context* pContext = new Context();
    Strategy* pStrategy = new ConcreteStrategyA();
    pContext->setStrategy(pStrategy);
    pContext->algorithm();
    pStrategy = new ConcreteStrategyB();
    pContext->setStrategy(pStrategy);
    pContext->algorithm();
    delete pContext;
    delete pStrategy;
}

}