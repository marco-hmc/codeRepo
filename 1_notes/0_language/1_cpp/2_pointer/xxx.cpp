#include <cstdlib>
#include <iostream>

const int X_DIM = 16;
const int Y_DIM = 3;
const int Z_DIM = 6;

int main() {
    char *space =
        static_cast<char *>(std::malloc(X_DIM * Y_DIM * Z_DIM * sizeof(char)));
    char ***Arr3D = static_cast<char ***>(std::malloc(Y_DIM * sizeof(char **)));
    for (int y = 0; y < Y_DIM; y++) {
        Arr3D[y] = static_cast<char **>(std::malloc(Z_DIM * sizeof(char *)));
        for (int z = 0; z < Z_DIM; z++) {
            Arr3D[y][z] = space + (y * (X_DIM * Z_DIM) + z * X_DIM);
        }
    }

    ptrdiff_t diff;
    for (int y = 0; y < Y_DIM; y++) {
        std::cout << "Location of array " << y << " is "
                  << static_cast<void *>(*Arr3D[y]) << std::endl;
        for (int z = 0; z < Z_DIM; z++) {
            std::cout << "  Array " << y << " and Row " << z << " starts at "
                      << static_cast<void *>(Arr3D[y][z]);
            diff = Arr3D[y][z] - space;
            std::cout << "    diff = " << diff << "  ";
            std::cout << " y = " << y << "  z = " << z << std::endl;
        }
    }

    // // 释放内存
    // for (int z = 0; z < Z_DIM; z++) {
    //     std::free(Arr3D[z]);
    // }
    // std::free(Arr3D);
    // std::free(space);

    return 0;
}