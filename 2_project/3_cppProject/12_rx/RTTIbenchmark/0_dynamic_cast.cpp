#include <cassert>
#include <iostream>
#include <typeinfo>
#include <vector>

#include "macros.h"

class Grandfather {
  public:
    virtual ~Grandfather(){};

    template <typename T>
    bool isDerivedFrom(T* obj) {
        return dynamic_cast<Grandfather*>(obj) != nullptr;
    }
};

class Father : public Grandfather {};

class Son : public Father {};

class LaoWang {};

#define IS_BLOOD_RELATED(obj, type) (dynamic_cast<type*>(obj) ? true : false)

void correctTest() {
    Grandfather* son = new Son();
    assert(IS_BLOOD_RELATED(son, Father));
    assert(IS_BLOOD_RELATED(son, Grandfather));
    assert(IS_BLOOD_RELATED(son, LaoWang));
    delete son;
}

#pragma GCC push_options
#pragma GCC optimize("O0")

void testDynamicCast(int times = 1000000) {
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