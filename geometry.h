#pragma once

class Vec3f {
    public: 
    float x, y, z;
    
    Vec3f() {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }

    Vec3f(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vec3f add(Vec3f vec3){
        return Vec3f(x + vec3.x, y + vec3.y, z + vec3.z);
    }

    Vec3f subtract(Vec3f vec3){
        return Vec3f(x - vec3.x, y - vec3.y, z - vec3.z);
    }

    Vec3f multiply(float scalar){
        return Vec3f(x * scalar, y * scalar, z * scalar);
    }

    float dot(Vec3f vec3){
        return (x * vec3.x + y * vec3.y + z * vec3.z);
    }

    Vec3f normalize() {
        return this->multiply(1 / sqrtf(this->dot(*this)));
    }

    void operator= (Vec3f vec3){
        this->x = vec3.x;
        this->y = vec3.y;
        this->z = vec3.z;
    }

    float operator[] (int index){
        switch(index) {
            case 0: return x; break;
            case 1: return y; break;
            case 2: return z; break;
            default: return 0;
        }
    }

    Vec3f operator- (Vec3f vec3){
        return this->subtract(vec3);
    }

    float operator* (Vec3f vec3){
        return this->dot(vec3);
    }
};

typedef struct Pixel{
    uint8_t r, g, b;
    Pixel(): r(0), g(0), b(0) {}
    Pixel(const Vec3f& vec3) {
        r = vec3.x;
        g = vec3.y;
        b = vec3.z;
    }
} Pixel;

struct Sphere {
    Vec3f center;
    const float radius;

    Sphere(const Vec3f& c, const float& r) : center(c), radius(r) {}

    bool ray_intersect(const Vec3f& origin, const Vec3f& dir, float& t0){
        Vec3f L = center - origin;
        float tca = L*dir;
        float d2 = L*L - tca*tca;
        if(d2 > radius*radius) return false;
        float thc = sqrtf(radius*radius - d2);
        t0 = tca - thc;
        float t1 = tca + thc;
        if(t0 < 0) {
            t0 = t1;
            return false;
        }
        return true;

    }
};