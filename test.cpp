#include <iostream>

#include "reflex.h"

/*
*1.�̳� Object ��
*2.����һ�� CreatObject() ���������� return new ������
*3.ӵ��һ�� classInfo �ĳ�Ա������������ CreatObject ��ʼ��
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