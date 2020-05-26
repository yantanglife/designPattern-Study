#pragma once
#include <iostream>
/*
* 代理模式和适配器模式：
*
* 适配器模式是因为新旧接口不一致导致出现了客户端无法得到满足的问题，
* 为了使用以前实现旧接口（适配者）的服务，就应该在适配器类中将旧接口包装程新接口
*
* 代理提供的接口和原本的接口是一样的，代理模式的作用是不把实现直接暴露出来，
* 而是通过代理这个层，代理能够做一些处理
*/
namespace proxy {

class Subject {
public:
    virtual void request() = 0;
};


class RealSubject : public Subject {
public:
    void request() { std::cout << "RealSubject::request()." << std::endl; }

};


class Proxy : public Subject {
public:
    Proxy(Subject* subject) : m_subject(subject) {}
    ~Proxy() {}

    void preRequest() { std::cout << "Proxy::preRequest()." << std::endl; }
    void postRequest() { std::cout << "Proxy::posteRequest()." << std::endl; }

    void request();
private:
    Subject* m_subject;
};

void Proxy::request() {
    preRequest();
    m_subject->request();
    postRequest();
}


void proxyTest() {
    Subject* pSubject = new RealSubject();
    Subject* pProxy = new Proxy(pSubject);
    pProxy->request();

    delete pSubject;
    delete pProxy;
}

}