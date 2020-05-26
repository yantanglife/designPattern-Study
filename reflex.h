#pragma once
#include <string>

/*
*C++ ʵ�ַ������
*https://blog.csdn.net/y1196645376/article/details/51455273
*/

#define DECLARE_CLASS(name) \
    protected:  \
        static ClassInfo ms_classInfo;  \
    public: \
        virtual ClassInfo* GetClassInfo() const;    \
        static Object* CreateObject();

#define IMPLEMENT_CLASS_COMMON(name, func)  \
    ClassInfo name::ms_classInfo((#name), (ObjectConstructionFn) func); \
    \
    ClassInfo *name::GetClassInfo() const   \
        { return &name::ms_classInfo; }

#define IMPLEMENT_CLASS(name)   \
    IMPLEMENT_CLASS_COMMON(name, name::CreateObject)    \
    Object* name::CreateObject()    \
        { return new name; }


class ClassInfo;

// ����
class Object {
public:
    Object() {};
    virtual ~Object() {};

    static bool Register(ClassInfo* classInfo);
    static Object* CreateObject(std::string name);
};

// ����ָ�� ---> ��� new ����
typedef Object* (*ObjectConstructionFn)(void);


class ClassInfo {
public:
    // ����Ϊ�����Ͷ�Ӧ�� new ����ָ��
    ClassInfo(const std::string className, ObjectConstructionFn ctor)
        : m_className(className), m_objectConstructor(ctor) {
        // ע��
        Object::Register(this);
    }
    virtual ~ClassInfo() {}

    Object* CreateObject() const { return m_objectConstructor ? (*m_objectConstructor)() : 0; }

    bool IsDynamic() const { return NULL != m_objectConstructor; }

    ObjectConstructionFn GetConstructor() const { return m_objectConstructor; }
    const std::string GetClassName() const { return m_className; }

public:
    std::string m_className;
    ObjectConstructionFn m_objectConstructor;
};
