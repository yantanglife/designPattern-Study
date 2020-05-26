#pragma once
#include <iostream>
#include <list>

namespace observer {

class Observer;

// Ŀ����
class Subject {
public:
    Subject() {}
    virtual ~Subject() {}

    // ע��
    void attach(Observer* observer);
    // ע��
    void detach(Observer* observer);

    void setValue(int value) { m_value = value; }
    int getValue() { return m_value; }

    // ֪ͨ����
    virtual void notify() = 0;

protected:
    // ��Ź۲���
    std::list<Observer*> m_observers;
    int m_value;
};


// ����Ŀ����
class ConcreteSubject : public Subject {
public:
    ConcreteSubject() {}
    ConcreteSubject(int value) { setValue(value); }
    ~ConcreteSubject() {}

    void notify();

};


// �۲���
class Observer {
public:
    Observer() {}
    virtual ~Observer() {}

    virtual void update(Subject*) = 0;
};


// ����۲���
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