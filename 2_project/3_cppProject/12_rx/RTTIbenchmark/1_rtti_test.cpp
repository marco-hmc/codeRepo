#include <cassert>
#include <iostream>

#include "include/impl1/rtti.hh"

namespace {

#define IS_BLOOD_RELATED(obj, type) (obj->cast<type>() ? true : false)

    class Grandfather : public RTTI::Enable {
        RTTI_DECLARE_TYPEINFO(Grandfather);
    };

    class Father : public Grandfather {
        RTTI_DECLARE_TYPEINFO(Father, Grandfather);
    };

    class Son : public Father {
        RTTI_DECLARE_TYPEINFO(Son, Father);
    };

    class LaoWang : public RTTI::Enable {
        RTTI_DECLARE_TYPEINFO(LaoWang);
    };

    void correctTest() {
        Grandfather* son = new Son();
        assert(IS_BLOOD_RELATED(son, Father));
        assert(IS_BLOOD_RELATED(son, Grandfather));
        assert(!IS_BLOOD_RELATED(son, LaoWang));
        std::cout << "Hello, World! -- test4" << std::endl;
    }

}  // namespace

#pragma GCC push_options
#pragma GCC optimize("O0")

void testRTTI(int times = 1000000) {
    // correctTest();

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