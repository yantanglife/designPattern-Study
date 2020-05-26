#include <map>

#include "reflex.h"


// �洢����Ϣ
static std::map<std::string, ClassInfo*> *classInfoMap = NULL;

//Object

// ע��ĳһ����Ϣ
bool Object::Register(ClassInfo* classInfo) {
    if (!classInfoMap) {
        classInfoMap = new std::map<std::string, ClassInfo*>();
    }
    if (classInfo) {
        if (classInfoMap->find(classInfo->m_className) == classInfoMap->end()) {
            classInfoMap->insert(std::map<std::string, ClassInfo*>::value_type(classInfo->m_className, classInfo));
        }
    }
    return true;
}

// ���������ƣ����ø���� new ����
Object* Object::CreateObject(std::string name) {
    const auto iter = classInfoMap->find(name);
    if (iter != classInfoMap->end()) {
        return iter->second->CreateObject();
    }
    return NULL;
}