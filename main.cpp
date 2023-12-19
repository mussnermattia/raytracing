#include <iostream>
#include <vector>

using namespace std;

struct Vector3D {
    double x;
    double y;
    double z;

    Vector3D (double x, double y, double z) : x(x), y(y), z(z) {}
};

struct Sphere {
    Vector3D pos;
    double rad;

    Sphere (double x, double y, double z, double rad) : pos(x, y, z), rad(rad) {}
};

struct Camera {
    Vector3D pos;
    Vector3D dir;

    Camera (double x, double y, double z, double xRot, double yRot, double zRot) : pos(x, y, z), dir(xRot, yRot, zRot) {}
};

int main() {
    cout << "hello world" << endl;
    
    
    Camera m(1, 2, 3, 4, 5, 6);

    cout << m.pos.x << " " << m.pos.y << " " << m.pos.z << " " << m.dir.x << " " << m.dir.y << " " << m.dir.z << endl;

    return 0;
}
