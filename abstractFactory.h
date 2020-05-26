#pragma once
#include <iostream>

/*
���󹤳�ģʽΪ����һ������ṩ��һ�ֽ������.
�빤������ģʽ��ȣ����󹤳�ģʽ�еľ��幤����ֻ�Ǵ���һ�ֲ�Ʒ�������𴴽�һ���Ʒ
*/

namespace abstract_fac {

class AbstractProductA;
class AbstractProductB;

// ���󹤳�
class Factory {
public:
    virtual AbstractProductA* createProductA() = 0;
    virtual AbstractProductB* createProductB() = 0;
};

// ���幤��1, �������� �ͺ�1 �Ĳ�Ʒ
class ConcreteFactory1 : public Factory {
public:
    AbstractProductA* createProductA();
    AbstractProductB* createProductB();
};
// ���幤��2, �������� �ͺ�2 �Ĳ�Ʒ
class ConcreteFactory2 : public Factory {
public:
    AbstractProductA* createProductA();
    AbstractProductB* createProductB();
};

// �����Ʒ
class AbstractProductA {
public:
    virtual void func() = 0;
};

// �����Ʒ
class AbstractProductB {
public:
    virtual void func() = 0;
};

// �����ƷA, �ɾ��幤��1 ����
class ConcreteProductA1 : public AbstractProductA {
public:
    void func() { std::cout << "Concrete-Product-A-1" << std::endl; }
};

// �����ƷA, �ɾ��幤��2 ����
class ConcreteProductA2 : public AbstractProductA {
public:
    void func() { std::cout << "Concrete-Product-A-2" << std::endl; }
};

// �����ƷB, �ɾ��幤��1 ����
class ConcreteProductB1 : public AbstractProductB {
public:
    void func() { std::cout << "Concrete-Product-B-1" << std::endl; }
};

// �����ƷA, �ɾ��幤��2 ����
class ConcreteProductB2 : public AbstractProductB {
public:
    void func() { std::cout << "Concrete-Product-B-2" << std::endl; }
};

// ����1 ���� ��ƷA
AbstractProductA*
ConcreteFactory1::createProductA() {
    return new ConcreteProductA1();
}

AbstractProductB*
ConcreteFactory1::createProductB() {
    return new ConcreteProductB1();
}

// ����2 ���� ��ƷA
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
    // ���幤��1��ֻ���� �ͺ�1 �Ĳ�Ʒ
    Factory* pFactory = new ConcreteFactory1();
    AbstractProductA* pProductA = pFactory->createProductA();
    pProductA->func();
    AbstractProductB* pProductB = pFactory->createProductB();
    pProductB->func();
    // ���幤��2��ֻ���� �ͺ�2 �Ĳ�Ʒ
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