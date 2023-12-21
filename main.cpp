#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

struct Vector3D {
    double x, y, z;

    Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

    double magnitude() {
        return sqrt(x * x + y * y + z * z);
    }

    void normalize() {
        double m = magnitude();
        x /= m;
        y /= m;
        z /= m;
    }


    void setMagnitude(double a) {
        double m = magnitude();
        x = x*a/m;
        y = y*a/m;
        z = z*a/m;
    }

    Vector3D operator+(const Vector3D &other) const {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }

    Vector3D operator*(double factor) const {
        return Vector3D(x * factor, y * factor, z * factor);
    }

    Vector3D& operator*=(double factor) {
        x *= factor;
        y *= factor;
        z *= factor;
        return *this; // Return a reference to the modified object
    }
};

struct Ray {
    Vector3D pos, dir;
    Ray(Vector3D pos, Vector3D dir) : pos(pos), dir(dir) {}

    Ray operator+(const Vector3D &other) const {
        return Ray(pos, Vector3D(dir.x + other.x, dir.y + other.y, dir.z + other.z));
    }
};

struct Color {
    double r, g, b;

    Color(double r, double g, double b) : r(r), g(g), b(b) {}
};

struct Sphere {
    Vector3D pos;
    double rad;
    Color col;

    Sphere(double x, double y, double z, double rad, Color col) : pos(x, y, z), rad(rad), col(col) {}
};

struct Camera {
    Vector3D pos, dir;

    Camera(double xPos, double yPos, double zPos, double xDir, double yDir, double zDir) : pos(xPos, yPos, zPos), dir(xDir, yDir, zDir) {}
};

const int MAXBOUNCES = 4;
const int HEIGHT = 8;
const int WIDTH = 10;

Vector3D crossProduct(const Vector3D &v1, const Vector3D &v2);
void getRaysVectors(Camera camera, double distBetwenPixels);
void printVector(Vector3D v);
Color calcColor(Ray ray);
void printRay(Ray r);

int main() {
    cout << "hello world" << endl;

    Camera m(7, 3, 4, -2, 1, 0.5);
    vector<Sphere> spheres;
    spheres.push_back(Sphere(10, -2, 0, 1, Color(1, 0, 0)));
    spheres.push_back(Sphere(9, -4, 2, .5, Color(1, 0, 0)));

    // cout << spheres[1].pos.magnitude() << endl;
    // spheres[1].pos.normalize();
    // cout << spheres[1].pos.x << " " << spheres[1].pos.y << " " << spheres[1].pos.z << endl;

    // cout << endl;
    // cout << endl;
    // cout << endl;
    // cout << endl;

    getRaysVectors(m, .1);

    return 0;
}

void getRaysVectors(Camera camera, double distBetweenPixels) {

    Ray middleRay = Ray(camera.pos, camera.dir);
    Vector3D rightVector = Vector3D(camera.dir.y, -camera.dir.x, 0);
    Vector3D upVector = Vector3D(middleRay.dir.y*rightVector.z-middleRay.dir.z*rightVector.y, middleRay.dir.z*rightVector.x-middleRay.dir.x*rightVector.z, middleRay.dir.x*rightVector.y-middleRay.dir.y*rightVector.x);
    rightVector.setMagnitude(distBetweenPixels);
    upVector.setMagnitude(distBetweenPixels);

    double theta = 5./180*M_PI;

    // print middle ray
    // printRay(Ray(middleRay.pos, middleRay.dir*2));

    // loop through each pixel
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            // calc new vector which goes from camera in the direction of the pixel on the "screen"

            int actualX = x-WIDTH/2;
            int actualY = y-HEIGHT/2;

            printRay(Ray(middleRay.pos, middleRay.dir+rightVector*actualX+upVector*actualY));
            
            // colors[y][x] = calcColor(currRay);
        }
    }
}

Color calcColor(Ray ray) {

    Color rayColor = Color(0, 0, 0);

    for (int i = 0; i < MAXBOUNCES; i++) {

    }

    return rayColor;
}

void printRay(Ray r) {
    cout << "vector(("<<r.pos.x<<", "<<r.pos.y<<", "<<r.pos.z<<"), ("<<r.dir.x+r.pos.x<<", "<<r.dir.y+r.pos.y<<", "<<r.dir.z+r.pos.z<<"))"<<endl;
}

void printVector(Vector3D v) {
    cout << "x: " << v.x << ", y: " << v.y << ", z: " << v.z << endl;
}

Vector3D crossProduct(const Vector3D &v1, const Vector3D &v2) {
    double w1 = v1.y * v2.z - v1.z * v2.y;
    double w2 = v1.z * v2.x - v1.x * v2.z;
    double w3 = v1.x * v2.y - v1.y * v2.x;

    return Vector3D(w1, w2, w3);
}
