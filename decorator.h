#pragma once
#include <iostream>
#include <string>

namespace decorator {

// ���󹹼���
class Component {
public:
    Component() {}
    virtual ~Component() {}
    virtual void display() = 0;
};


// ���幹����
class Window : public Component {
public:
    Window(std::string name) : m_name(name) {}
    ~Window() {}
    void display() { std::cout << m_name << std::endl; }
private:
    std::string m_name;
};


// ����װ����
class ComponentDecortor {
public:
    ComponentDecortor(Component* component) : m_component(component) {}
    ~ComponentDecortor() {}

    virtual void display() { m_component->display(); }

private:
    Component* m_component;
};

// ����װ����
class ScrollDecortor : public ComponentDecortor {
public:
    ScrollDecortor(Component* component) : ComponentDecortor(component) {}
    ~ScrollDecortor() {}
    void display() { ComponentDecortor::display(); setScroll(); }
private:
    void setScroll() { std::cout << "setScroll." << std::endl; }
};


// Test
void decoratorTest() {
    Component* com = new Window("window");
    ComponentDecortor* comDec = new ScrollDecortor(com);
    comDec->display();
    delete comDec;
    delete com;
}

}