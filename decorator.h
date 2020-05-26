#pragma once
#include <iostream>
#include <string>

namespace decorator {

// 抽象构件类
class Component {
public:
    Component() {}
    virtual ~Component() {}
    virtual void display() = 0;
};


// 具体构件类
class Window : public Component {
public:
    Window(std::string name) : m_name(name) {}
    ~Window() {}
    void display() { std::cout << m_name << std::endl; }
private:
    std::string m_name;
};


// 抽象装饰类
class ComponentDecortor {
public:
    ComponentDecortor(Component* component) : m_component(component) {}
    ~ComponentDecortor() {}

    virtual void display() { m_component->display(); }

private:
    Component* m_component;
};

// 具体装饰类
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