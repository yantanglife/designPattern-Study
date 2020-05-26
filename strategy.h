#pragma once
#include <iostream>

/*
* 策略模式的主要目的是将算法的定义与使用分开，也就是将算法的行为和环境分开，
* 将算法的定义放在专门的策略类中，每一个策略类封装了一种实现算法，
* 使用算法的环境类针对抽象策略类进行编程，符合“依赖倒转原则”.
*/

namespace strategy {

class Strategy;

// 环境类：使用算法
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

// 抽象策略类
class Strategy {
public:
    virtual void algorithm() = 0;
};

// 具体策略类
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