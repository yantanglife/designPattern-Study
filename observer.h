#pragma once
#include <iostream>
#include <list>

namespace observer {

class Observer;

// 目标类
class Subject {
public:
    Subject() {}
    virtual ~Subject() {}

    // 注册
    void attach(Observer* observer);
    // 注销
    void detach(Observer* observer);

    void setValue(int value) { m_value = value; }
    int getValue() { return m_value; }

    // 通知方法
    virtual void notify() = 0;

protected:
    // 存放观察者
    std::list<Observer*> m_observers;
    int m_value;
};


// 具体目标类
class ConcreteSubject : public Subject {
public:
    ConcreteSubject() {}
    ConcreteSubject(int value) { setValue(value); }
    ~ConcreteSubject() {}

    void notify();

};


// 观察者
class Observer {
public:
    Observer() {}
    virtual ~Observer() {}

    virtual void update(Subject*) = 0;
};


// 具体观察者
class ConcreObserverA : public Observer {
public:
    ConcreObserverA() {}
    // ConcreObserverA(Subject* subject) : m_subject(subject) {}
    ~ConcreObserverA() {}

    void update(Subject*);
private:
    // Subject* m_subject;
    int m_state;
};

class ConcreObserverB : public Observer {
public:
    ConcreObserverB() {}
    // ConcreObserverB(Subject* subject) : m_subject(subject) {}
    ~ConcreObserverB() {}

    void update(Subject*);
private:
    // Subject* m_subject;
};


// Subject

void Subject::attach(Observer* observer) {
    m_observers.push_back(observer);
}

void Subject::detach(Observer* observer) {
    // auto obs = find(m_observers.begin(), m_observers.end(), observer);
    m_observers.remove(observer);
}


// ConcreteSubject
void ConcreteSubject::notify() {
    for (auto obs : m_observers) {
        obs->update(this);
    }
}


// void ConcreObserver

void ConcreObserverA::update(Subject* sub) {

    std::cout << "ConcreObserverA::update()." << sub->getValue() << std::endl;
}

void ConcreObserverB::update(Subject* sub) {
    std::cout << "ConcreObserverB::update()." << sub->getValue() << std::endl;
}


void observerTest() {
    Subject* pSubject = new ConcreteSubject(5);
    Observer* pObserverA = new ConcreObserverA();
    Observer* pObserverB = new ConcreObserverB();
    // Register the observer
    pSubject->attach(pObserverA);
    pSubject->attach(pObserverB);
    pSubject->notify();

    pSubject->setValue(10);
    pSubject->notify();
    // Unregister the observer
    pSubject->detach(pObserverA);
    pSubject->notify();

    delete pSubject;
    delete pObserverA;
    delete pObserverB;

}

}