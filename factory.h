#pragma once
#include <iostream>

/*
* �ڼ򵥹���ģʽ��ֻ�ṩһ�������࣬�ù����ദ�ڶԲ�Ʒ�����ʵ����������λ�ã�
* ����Ҫ֪��ÿһ����Ʒ����Ĵ���ϸ�ڣ���������ʱʵ������һ����Ʒ��.
*
* �򵥹���ģʽ����ȱ���ǵ����²�ƷҪ���뵽ϵͳ��ʱ�������޸Ĺ����࣬
* ��Ҫ�����м����Ҫ��ҵ���߼�����Υ���ˡ�����ԭ��.
*
* �ڹ�������ģʽ�У������ṩһ��ͳһ�Ĺ��������������еĲ�Ʒ����
* ������Բ�ͬ�Ĳ�Ʒ�ṩ��ͬ�Ĺ�����ϵͳ�ṩһ�����Ʒ�ȼ��ṹ��Ӧ�Ĺ����ȼ��ṹ.
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