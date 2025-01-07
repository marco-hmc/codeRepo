#include <cassert>
#include <vector>

#include "macros.h"

class TypeInfo {
  public:
    virtual ~TypeInfo() = default;
    virtual bool isDerivedFrom(const TypeInfo* base) const = 0;
};

template <typename T>
class TypeInfoImpl : public TypeInfo {
  public:
    static TypeInfoImpl instance;

    bool isDerivedFrom(const TypeInfo* base) const override {
        return base == &instance;
    }
};

template <typename T>
TypeInfoImpl<T> TypeInfoImpl<T>::instance;

class RTTIBase {
  public:
    virtual ~RTTIBase() = default;
    virtual const TypeInfo* getTypeInfo() const = 0;
};

#define DECLARE_RTTI                                              \
  public:                                                         \
    const TypeInfo* getTypeInfo() const override {                \
        return &TypeInfoImpl<                                     \
            std::remove_pointer<decltype(this)>::type>::instance; \
    }

#define IS_BLOOD_RELATED(obj, type)                                     \
    ((obj)->getTypeInfo()->isDerivedFrom(&TypeInfoImpl<type>::instance) \
         ? true                                                         \
         : false)

class Grandfather : public RTTIBase {
    DECLARE_RTTI
};

class Father : public Grandfather {
    DECLARE_RTTI
};

class Son : public Father {
    DECLARE_RTTI
};

class LaoWang : public RTTIBase {
    DECLARE_RTTI
};

void correctTest() {
    Grandfather* son = new Son();
    assert(IS_BLOOD_RELATED(son, Father));
    assert(IS_BLOOD_RELATED(son, Grandfather));
    assert(!IS_BLOOD_RELATED(son, LaoWang));
    delete son;
}

#pragma GCC push_options
#pragma GCC optimize("O0")

void testRTTI(int times = 1000000) {
    correctTest();

    std::vector<Grandfather*> objects;
    objects.reserve(times);
    for (int i = 0; i < times; ++i) {
        objects.push_back(new Son());
    }

    for (int i = 0; i < times; ++i) {
        IS_BLOOD_RELATED(objects[i], Father);
        IS_BLOOD_RELATED(objects[i], Grandfather);
        IS_BLOOD_RELATED(objects[i], LaoWang);
    }

    for (auto* obj : objects) {
        delete obj;
    }
}

#pragma GCC pop_options
