#include <iostream>

#include "reflex.h"

/*
*1.继承 Object 类
*2.重载一个 CreatObject() 函数，里面 return new 自身类
*3.拥有一个 classInfo 的成员并且用类名和 CreatObject 初始化
*/
class B : public Object {
    
    DECLARE_CLASS(B);

public:
    B() { std::cout << _HEX << (long)this << "B constructor." << std::endl; }
    ~B() { std::cout << _HEX << (long)this << "B desstructor." << std::endl; }

    /*
    virtual ClassInfo* GetClassInfo() const { return &ms_classInfo; }

    static Object* CreateObject() { return new B; }

protected:
    static ClassInfo ms_classInfo;
    */
};

// ClassInfo B::ms_classInfo("B", B::CreateObject);
IMPLEMENT_CLASS(B);

/*
int main() {
    Object *obj = Object::CreateObject("A");
    delete obj;
    return 0;
}
*/