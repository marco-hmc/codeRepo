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

#include <stdio.h>

#include <cassert>

namespace addressTable {
    void example1() {
        int tab[2][3] = {{1, 2, 3}, {4, 5, 5}};
        assert(tab == &tab[0]);
        assert(*tab == &tab[0][0]);

        assert(tab + 1 == &tab[1]);
        assert(*(tab + 1) == &tab[1][0]);

        assert(tab[1][2] == *(tab[0] + 5));
    }

}  // namespace addressTable

int main() {
    int tab[2][2] = {{1, 2}, {3, 4}};

    // 输出*tab, **tab, *(tab + 1), **(tab + 1)的值
    printf("tab = %p\n", tab);
    printf("*tab = %p\n", *tab);
    printf("**tab = %d\n", **tab);

    return 0;
}