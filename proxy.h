#pragma once
#include <iostream>
/*
* ����ģʽ��������ģʽ��
*
* ������ģʽ����Ϊ�¾ɽӿڲ�һ�µ��³����˿ͻ����޷��õ���������⣬
* Ϊ��ʹ����ǰʵ�־ɽӿڣ������ߣ��ķ��񣬾�Ӧ�������������н��ɽӿڰ�װ���½ӿ�
*
* �����ṩ�Ľӿں�ԭ���Ľӿ���һ���ģ�����ģʽ�������ǲ���ʵ��ֱ�ӱ�¶������
* ����ͨ����������㣬�����ܹ���һЩ����
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