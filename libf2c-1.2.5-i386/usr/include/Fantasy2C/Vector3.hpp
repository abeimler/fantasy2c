#ifndef VECTOR3_HPP_INCLUDED
#define VECTOR3_HPP_INCLUDED

#include <Fantasy2C/Basic.hpp>
#include <Fantasy2C/Vector2.hpp>

namespace F2C{

template<typename T>
class Vector3{
    public:
    T x;
    T y;
    T z;

    Vector3():
        x(0),
        y(0),
        z(0)
    {}

    Vector3(T x,T y,T z):
        x(x),
        y(y),
        z(z)
    {}

    Vector3(const Vector2<T>& vec):
        x(vec.x),
        y(vec.y),
        z(0)
    {}

    const Vector3<T>& operator+=(const Vector3<T>& vec){
        *this = *this + vec;
        return *this;
    }
    const Vector3<T>& operator-=(const Vector3<T>& vec){
        *this = *this - vec;
        return *this;
    }
    const Vector3<T>& operator*=(const Vector3<T>& vec){
        *this = *this * vec;
        return *this;
    }
    const Vector3<T>& operator/=(const Vector3<T>& vec){
        *this = *this / vec;
        return *this;
    }

    const Vector3<T>& operator+=(const T& vec){
        *this = *this + vec;
        return *this;
    }
    const Vector3<T>& operator-=(const T& vec){
        *this = *this - vec;
        return *this;
    }
    const Vector3<T>& operator*=(const T& vec){
        *this = *this * vec;
        return *this;
    }
    const Vector3<T>& operator/=(const T& vec){
        *this = *this / vec;
        return *this;
    }

    //length of Vector
    // |v| = sqrt(v.x^2 + v.y^2 + v.z^2)
    T length() const {
        return sqrt(this->x*this->x +
                    this->y*this->y +
                    this->z*this->z);
    }

    //length of Vector (square)
    // |v|^2 = v.x^2 + v.y^2 + v.z^2
    T lengthSqu() const {
        return this->x*this->x +
                this->y*this->y +
                this->z*this->z;
    }

    //Normalize
    //n = v / |v|
    Vector3<T> Normalize() const {
        T len = this->length();
        if(len != 0)
            return *this / len;
        else
            return *this;
    }

    //Dotproduct
    //v1.v2 = |v1| * |v2| * cos(φ)
    //this->v2 = 0: alpha = 90°
    //this->v2 < 0: alpha > 90°
    //this->v2 > 0: alpha < 90°

    // x
    //
    // v1
    // |
    // |
    // |alpha
    // *---------v2    y
    T dotProduct(const Vector3<T>& vec2) const {
        return acos(this->lengthSqu()+vec2.lengthSqu());
    }

    //Crossproduct
    //v1 x v2 = (v1.y*v2.z - v1.z*v2.y,
    //              v1.z*v2.x - v1.x*v2.z,
    //              v1.x*v2.y - v1.y*v2.x)

    //       y
    //
    //       v1
    //       |
    //       |
    //       *-----v2   x
    //      /
    //     /
    // (v1 x v2)
    //
    //z
    Vector3<T> crossProduct(const Vector3<T>& vec2) const {
        return Vector3<T> (this->y*vec2.z - this->z*vec2.y, this->z*vec2.x - this->x*vec2.z, this->x*vec2.y - this->y*vec2.x);
    }

    T Distance(const Vector3<T>& vec2) const{
        T x = vec2.x - this->x;
        T y = vec2.y - this->y;
        T z = vec2.z - this->z;
        return sqrt(x*x + y*y + z*z);
    }
};

template<typename T>
inline Vector3<T> operator+(const Vector3<T>& vec1,const Vector3<T>& vec2){
    return Vector3<T> (vec1.x+vec2.x,vec1.y+vec2.y,vec1.z+vec2.z);
}
template<typename T>
inline Vector3<T> operator-(const Vector3<T>& vec1,const Vector3<T>& vec2){
    return Vector3<T> (vec1.x-vec2.x,vec1.y-vec2.y,vec1.z-vec2.z);
}
template<typename T>
inline Vector3<T> operator*(const Vector3<T>& vec1,const Vector3<T>& vec2){
    return Vector3<T> (vec1.x*vec2.x,vec1.y*vec2.y,vec1.z*vec2.z);
}
template<typename T>
inline Vector3<T> operator/(const Vector3<T>& vec1,const Vector3<T>& vec2){
    return Vector3<T> (vec1.x/vec2.x,vec1.y/vec2.y,vec1.z/vec2.z);
}

template<typename T>
inline Vector3<T> operator*(const Vector3<T>& vec1,const T value){
    return Vector3<T> (vec1.x*value,vec1.y*value,vec1.z*value);
}
template<typename T>
inline Vector3<T> operator/(const Vector3<T>& vec1,const T value){
    return Vector3<T> (vec1.x/value,vec1.y/value,vec1.z/value);
}

template<typename T>
inline Vector3<T> operator*(const T value,const Vector3<T>& vec1){
    return Vector3<T> (vec1.x*value,vec1.y*value,vec1.z*value);
}
template<typename T>
inline Vector3<T> operator/(const T value,const Vector3<T>& vec1){
    return Vector3<T> (vec1.x/value,vec1.y/value,vec1.z/value);
}

template<typename T>
inline bool operator==(const Vector3<T>& vec1,const Vector3<T>& vec2){
    return vec1.x == vec2.x &&
            vec1.y == vec2.y &&
            vec1.z == vec2.z;
}

template<typename T>
inline bool operator!=(const Vector3<T>& vec1,const Vector3<T>& vec2){
    return vec1.x != vec2.x ||
            vec1.y != vec2.y ||
            vec1.z != vec2.z;
}


template<typename T>
inline Vector3<T> max(const Vector3<T>& vec1,const Vector3<T>& vec2){
    return Vector3<T> ( std::max(vec1.x,vec2.x), std::max(vec1.y,vec2.y), std::max(vec1.z,vec2.z) );
}

template<typename T>
inline Vector3<T> min(const Vector3<T>& vec1,const Vector3<T>& vec2){
    return Vector3<T> ( std::min(vec1.x,vec2.x), std::min(vec1.y,vec2.y), std::min(vec1.z,vec2.z) );
}

template<typename T>
inline Vector3<T> linearInterpolation(const Vector3<T>& vec1,const Vector3<T>& vec2,T s){
    return vec1 + s * (vec2-vec1);
}


}

#endif // VECTOR3_HPP_INCLUDED
