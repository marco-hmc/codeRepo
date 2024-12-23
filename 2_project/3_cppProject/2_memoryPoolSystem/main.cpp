#include <iostream>

#include "../include/mps.h"

struct Data {
    int dataValue;
};

int main() {
    MemPool *mp = new MemPool(2 * GB + 1000 * MB + 1000 * KB,
                              1 * GB + 500 * MB + 500 * KB);
    struct Data *data = (struct Data *)mp->MemoryPoolAlloc(sizeof(struct Data));
    data->dataValue = 2333;
    std::cout << data->dataValue << std::endl;
    mp->MemoryPoolFree(data);
    mp->MemoryPoolClear();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}