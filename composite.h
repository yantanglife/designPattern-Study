#pragma once
#include <iostream>
#include <list>
#include <string>


namespace composite {

class Component {
public:
    virtual void operation() = 0;
    virtual void add(Component*) = 0;
    virtual void remove(Component*) = 0;
    virtual Component* getChild(int) = 0;
};

class Leaf : public Component {
public:
    Leaf(std::string name) : m_name(name) {}
    void operation();

    void add(Component*);
    void remove(Component*);
    Component* getChild(int);

    std::string getName() { return m_name; }
private:
    std::string m_name;
};

class Composite : public Component {
public:
    Composite(std::string name) : m_name(name) {}
    void add(Component*);
    void remove(Component*);
    Component* getChild(int);
    std::string getName() { return m_name; }
    void operation();
private:
    std::list<Component*> m_list;
    std::string m_name;
};


// Leaf
void Leaf::add(Component*) {
    std::cout << "NO add(). I'm Leaf-" << getName() << std::endl;
}
void Leaf::remove(Component*) {
    std::cout << "NO remove(). I'm Leaf-" << getName() << std::endl;
}
Component* Leaf::getChild(int i) {
    std::cout << "NO getChild(). I'm Leaf-" << getName() << std::endl;
    return NULL;
}
void Leaf::operation() {
    std::cout << "operation(). I'm Leaf-" << getName() << std::endl;
}

// Composite
void Composite::add(Component* c) {
    m_list.push_back(c);
}
void Composite::remove(Component* c) {
    //auto it = std::find()
    for (auto it = m_list.begin(); it != m_list.end(); ++it) {
        if (*it == c) {
            m_list.remove(*it);
            break;
        }
    }
}
Component* Composite::getChild(int i) {
    if (i > m_list.size() || i <= 0) {
        std::cout << getName() << "-" << i << std::endl;
        return NULL;
    }
    auto it = m_list.begin();
    while (--i) {
        it++;
    }
    return *it;
}

void Composite::operation() {
    // std::cout << getName() << "-operation()." << std::endl;
    for (auto it : m_list) {
        it->operation();
    }
}

// Test
void compositeTest() {
    Component* pComponentM = new Composite("M");
    Component* pComponent1 = new Composite("C1");
    Component* pComponent2 = new Composite("C2");
    Component* pComponent3 = new Composite("C3");
    Component* pLeaf1 = new Leaf("leaf-1");
    Component* pLeaf2 = new Leaf("leaf-2");
    Component* pLeaf3 = new Leaf("leaf-3");
    Component* pLeaf4 = new Leaf("leaf-4");
    Component* pLeaf5 = new Leaf("leaf-5");
    //
    pComponentM->add(pComponent1);
    pComponentM->add(pLeaf1);
    pComponentM->add(pLeaf2);
    //
    pComponent1->add(pComponent2);
    pComponent1->add(pComponent3);
    pComponent1->add(pLeaf3);
    //
    pComponent2->add(pLeaf4);
    pComponent2->add(pLeaf5);
    //
    pComponentM->operation();
    //
    pComponent2->operation();
    //
    //auto p1 = pComponentM->getChild(1);
    //auto p2 = pComponentM->getChild(2);
    // auto p3 = pComponentM->getChild(3);
    //auto p4 = pComponentM->getChild(4);
    
    delete pComponentM;
    delete pComponent1;
    delete pComponent2;
    delete pComponent3;
    delete pLeaf1;
    delete pLeaf2;
    delete pLeaf3;
    delete pLeaf4;
    delete pLeaf5;
        
}

}


namespace composite_imp {
/*
* 界面控件库，界面控件分为两大类，
* 一类是单元控件，例如按钮、文本框等，
* 一类是容器控件，例如窗体、中间面板等，试用组合模式设计该界面控件库.
*/

// 在抽象控件类下加入两个抽象子类：单元抽象控件类和容器抽象控件类
// 具体的单元控件和容器控件各自继承其对应的抽象类

class Component {
public:
    Component(std::string name) : m_name(name) {}

    virtual void show() = 0;

    std::string getName() { return m_name; }
private:
    std::string m_name;
};

class Unit : public Component {
public:
    Unit(std::string name) : Component(name) {}
    virtual void show() = 0;
    
};

class Container : public Component {
public:
    Container(std::string name) : Component(name) {}
    void show();
    bool add(Component*);
    bool remove(Component*);
private:
    std::list<Component*> m_list;
};

class Button : public Unit {
public:
    Button(std::string name) : Unit(name) { }
    void show();
};

class TextBox : public Unit {
public:
    TextBox(std::string name) : Unit(name) {}
    void show();
};

class Window : public Container {
public:
    Window(std::string name) : Container(name) {}
};

class CenterPanel : public Container {
public:
    CenterPanel(std::string name) : Container(name) {}
};

void Button::show() {
    std::cout << "Button-" << getName() << std::endl;
}
void TextBox::show() {
    std::cout << "TextBox-" << getName() << std::endl;
}

void Container::show() {
    std::cout << "Container-" << getName() << "-has:" << std::endl;
    if (m_list.size() > 0) {
        for (auto it : m_list) {
            std::cout << it->getName() << " ";
        }
    }
    std::cout << std::endl;
    for (auto it : m_list) {
        it->show();
    }
}
bool Container::add(Component* c) {
    if (c) {
        m_list.push_back(c);
        return true;
    }
    return false;
}
bool Container::remove(Component* c) {
    if (c) {
        for (auto it = m_list.begin(); it != m_list.end(); ++it) {
            if (*it == c) {
                m_list.remove(*it);
                return true;
            }
        }
        return false;
    }
    return false;
}


// Test
void compositeImpTest() {
    Container* pW = new Window("window");
    Container* pC = new CenterPanel("panel");
    Unit* pB1 = new Button("button-1");
    pW->add(pC);
    pW->add(pB1);

    Container* pC1 = new CenterPanel("panel-1");
    Unit* pB2 = new Button("button-2");
    Unit* pT1 = new TextBox("textbox-1");
    pC->add(pC1);
    pC->add(pB2);
    pC->add(pT1);

    pW->show();

    pW->remove(pC);
    pW->show();
    //
    delete pW;
    delete pC;
    delete pC1;
    delete pB1;
    delete pB2;
    delete pT1;

}

}