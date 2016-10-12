#ifndef VECTOR4_HPP_INCLUDED
#define VECTOR4_HPP_INCLUDED

#include <Fantasy2C/Basic.hpp>
#include <Fantasy2C/Vector2.hpp>
#include <Fantasy2C/Vector3.hpp>

namespace F2C{

template<typename T>
class Vector4{
    public:
    T x;
    T y;
    T z;
    T w;

    Vector4():
        x(0),
        y(0),
        z(0),
        w(1)
    {}

    Vector4(T x,T y,T z,T w):
        x(x),
        y(y),
        z(z),
        w(w)
    {}

    Vector4(const Vector2<T>& vec):
        x(vec.x),
        y(vec.y),
        z(0),
        w(1)
    {}

    Vector4(const Vector3<T>& vec):
        x(vec.x),
        y(vec.y),
        z(vec.z),
        w(1)
    {}

    const Vector4<T>& operator+=(const Vector4<T>& vec){
        *this = *this + vec;
        return *this;
    }
    const Vector4<T>& operator-=(const Vector4<T>& vec){
        *this = *this - vec;
        return *this;
    }
    const Vector4<T>& operator*=(const Vector4<T>& vec){
        *this = *this * vec;
        return *this;
    }
    const Vector4<T>& operator/=(const Vector4<T>& vec){
        *this = *this / vec;
        return *this;
    }

    const Vector4<T>& operator+=(const T& vec){
        *this = *this + vec;
        return *this;
    }
    const Vector4<T>& operator-=(const T& vec){
        *this = *this - vec;
        return *this;
    }
    const Vector4<T>& operator*=(const T& vec){
        *this = *this * vec;
        return *this;
    }
    const Vector4<T>& operator/=(const T& vec){
        *this = *this / vec;
        return *this;
    }

    //length of Vector
    // |v| = sqrt(v.x^2 + v.y^2 + v.z^2)
    T length() const {
        return sqrt(this->x*this->x +
                    this->y*this->y +
                    this->z*this->z +
                    this->w*this->w);
    }

    //length of Vector (square)
    // |v|^2 = v.x^2 + v.y^2 + v.z^2
    T lengthSqu() const {
        return this->x*this->x +
                this->y*this->y +
                this->z*this->z +
                this->w*this->w;
    }

    //Normalize
    //n = v / |v|
    Vector4<T> Normalize() const {
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
    T dotProduct(const Vector4<T>& vec2) const {
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
    Vector4<T> crossProduct(const Vector4<T>& vec2) const {
        return Vector4<T> (this->y*vec2.z - this->z*vec2.y,
                            this->z*vec2.x - this->x*vec2.z,
                            this->x*vec2.y - this->y*vec2.x,
                            this->w);
    }

    T Distance(const Vector4<T>& vec2) const{
        T x = vec2.x - this->x;
        T y = vec2.y - this->y;
        T z = vec2.z - this->z;
        T w = vec2.w - this->w;
        return sqrt(x*x + y*y + z*z + w*w);
    }
};

template<typename T>
inline Vector4<T> operator+(const Vector4<T>& vec1,const Vector4<T>& vec2){
    return Vector4<T> (vec1.x+vec2.x,vec1.y+vec2.y,vec1.z+vec2.z,vec1.w+vec2.w);
}
template<typename T>
inline Vector4<T> operator-(const Vector4<T>& vec1,const Vector4<T>& vec2){
    return Vector4<T> (vec1.x-vec2.x,vec1.y-vec2.y,vec1.z-vec2.z,vec1.w-vec2.w);
}
template<typename T>
inline Vector4<T> operator*(const Vector4<T>& vec1,const Vector4<T>& vec2){
    return Vector4<T> (vec1.x*vec2.x,vec1.y*vec2.y,vec1.z*vec2.z,vec1.w*vec2.w);
}
template<typename T>
inline Vector4<T> operator/(const Vector4<T>& vec1,const Vector4<T>& vec2){
    return Vector4<T> (vec1.x/vec2.x,vec1.y/vec2.y,vec1.z/vec2.z,vec1.w/vec2.w);
}

template<typename T>
inline Vector4<T> operator*(const Vector4<T>& vec1,const T value){
    return Vector4<T> (vec1.x*value,vec1.y*value,vec1.z*value,vec1.w*value);
}
template<typename T>
inline Vector4<T> operator/(const Vector4<T>& vec1,const T value){
    return Vector4<T> (vec1.x/value,vec1.y/value,vec1.z/value,vec1.w/value);
}

template<typename T>
inline Vector4<T> operator*(const T value,const Vector4<T>& vec1){
    return Vector4<T> (vec1.x*value,vec1.y*value,vec1.z*value,vec1.w*value);
}
template<typename T>
inline Vector4<T> operator/(const T value,const Vector4<T>& vec1){
    return Vector4<T> (vec1.x/value,vec1.y/value,vec1.z/value,vec1.w/value);
}

template<typename T>
inline bool operator==(const Vector4<T>& vec1,const Vector4<T>& vec2){
    return vec1.x == vec2.x &&
            vec1.y == vec2.y &&
            vec1.z == vec2.z &&
            vec1.w == vec2.z;
}

template<typename T>
inline bool operator!=(const Vector4<T>& vec1,const Vector4<T>& vec2){
    return vec1.x != vec2.x ||
            vec1.y != vec2.y ||
            vec1.z != vec2.z ||
            vec1.w != vec2.w;
}

template<typename T>
inline Vector3<T> max(const Vector4<T>& vec1,const Vector4<T>& vec2){
    return Vector4<T> ( std::max(vec1.x,vec2.x), std::max(vec1.y,vec2.y), std::max(vec1.z,vec2.z), std::max(vec1.w,vec2.w));
}
template<typename T>
inline Vector4<T> min(const Vector4<T>& vec1,const Vector4<T>& vec2){
    return Vector4<T> ( std::min(vec1.x,vec2.x), std::min(vec1.y,vec2.y), std::min(vec1.z,vec2.z), std::min(vec1.w,vec2.w) );
}

template<typename T>
inline Vector4<T> linearInterpolation(const Vector4<T>& vec1,const Vector4<T>& vec2,T s){
    return vec1 + s * (vec2-vec1);
}


}


#endif // VECTOR4_HPP_INCLUDED
