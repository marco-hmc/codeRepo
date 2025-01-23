#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

struct Pnt {
    double x, y, z;
};

struct Axis {
    Pnt pt;
    Pnt dir;
    double len;
};

typedef double Matrix3[4][4];

struct CSYS {
    Pnt origin_pnt;
    Axis x_axis;
    Axis y_axis;
    Axis z_axis;
    Matrix3 xoy;
    Matrix3 yoz;
    Matrix3 xoz;
};

int main() {
    Matrix3 xoy = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
    Matrix3 yoz = {{0, 0, 1, 0}, {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 1}};
    Matrix3 xoz = {{1, 0, 0, 0}, {0, 0, -1, 0}, {0, 1, 0, 0}, {0, 0, 0, 1}};
    CSYS c{{0, 0, 0},
           {{0, 0, 0}, {1, 0, 0}, 1},
           {{0, 0, 0}, {0, 1, 0}, 1},
           {{0, 0, 0}, {0, 0, 1}, 1},
           {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}},
           {{0, 0, 1, 0}, {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 1}},
           {{1, 0, 0, 0}, {0, 0, -1, 0}, {0, 1, 0, 0}, {0, 0, 0, 1}}};
}
