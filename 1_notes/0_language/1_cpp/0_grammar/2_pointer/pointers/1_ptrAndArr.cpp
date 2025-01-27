#include <cassert>
#include <iostream>

namespace ArrAddressTable {
    /*
                tab + 0        tab + 1
    Address  0x7ffc5c78b530  0x7ffc5c78b538  0x7ffc5c78b530  0x7ffc5c78b534  0x7ffc5c78b538  0x7ffc5c78b53c
        Value  0x7ffc5c78b530  0x7ffc5c78b538  1  				2  				3  				4
                    [0]           [1]         [0][0]          [0][1]          [1][0]          [1][1]

    tab = table[0] = table[0][0] = 0x7ffc5c78b530
    *tab = 0x7ffc5c78b530
    **tab = table[0][0] = 1

    tab + 1 = table[1] = table[1][0] = 0x7ffc5c78b538
    *(tab + 1) = 0x7ffc5c78b538
    **(tab + 1) = table[1][0] = 3

    */

    void example1() {
        int tab[2][3] = {{1, 2, 3}, {4, 5, 5}};
        assert(tab == &tab[0]);
        assert(*tab == &tab[0][0]);

        assert(tab + 1 == &tab[1]);
        assert(*(tab + 1) == &tab[1][0]);

        assert(tab[1][2] == *(tab[0] + 5));
    }

}  // namespace ArrAddressTable

namespace differenceBetweenPntAndArray {
    void example1() {
        int myArray[5] = {1, 2, 3, 4, 5};
        static_assert(sizeof(myArray) == 20);
        // myArray = nullptr;  // error: array type 'int [5]' is not assignable

        int *p = myArray;
        static_assert(sizeof(p) == 8);
        p = nullptr;

        assert(myArray[1] == *myArray + 1);    // true
        assert(myArray[1] == *(myArray + 1));  // true
    }
}  // namespace differenceBetweenPntAndArray

int main() {
    ArrAddressTable::example1();
    differenceBetweenPntAndArray::example1();
    return 0;
}