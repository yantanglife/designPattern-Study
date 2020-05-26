#include <map>

#include "reflex.h"


// 存储类信息
static std::map<std::string, ClassInfo*> *classInfoMap = NULL;

//Object

// 注册某一类信息
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

// 根据类名称，调用该类的 new 方法
Object* Object::CreateObject(std::string name) {
    const auto iter = classInfoMap->find(name);
    if (iter != classInfoMap->end()) {
        return iter->second->CreateObject();
    }
    return NULL;
}