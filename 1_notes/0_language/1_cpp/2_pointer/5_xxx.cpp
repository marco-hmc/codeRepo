#include <cstdlib>
#include <iostream>

const int X_DIM = 16;
const int Y_DIM = 5;
const int Z_DIM = 3;

int main() {
    char *space =
        static_cast<char *>(std::malloc(X_DIM * Y_DIM * Z_DIM * sizeof(char)));
    char ***Arr3D = static_cast<char ***>(std::malloc(Z_DIM * sizeof(char **)));
    for (int z = 0; z < Z_DIM; z++) {
        Arr3D[z] = static_cast<char **>(std::malloc(Y_DIM * sizeof(char *)));
        for (int y = 0; y < Y_DIM; y++) {
            Arr3D[z][y] = space + (z * (X_DIM * Y_DIM) + y * X_DIM);
        }
    }

    ptrdiff_t diff;
    for (int z = 0; z < Z_DIM; z++) {
        std::cout << "Location of array " << z << " is "
                  << static_cast<void *>(*Arr3D[z]) << std::endl;
        for (int y = 0; y < Y_DIM; y++) {
            std::cout << "  Array " << z << " and Row " << y << " starts at "
                      << static_cast<void *>(Arr3D[z][y]);
            diff = Arr3D[z][y] - space;
            std::cout << "    diff = " << diff << "  ";
            std::cout << " z = " << z << "  y = " << y << std::endl;
        }
    }

    // 释放内存
    for (int z = 0; z < Z_DIM; z++) {
        std::free(Arr3D[z]);
    }
    std::free(Arr3D);
    std::free(space);

    return 0;
}