#ifndef VECTOR2_HPP_INCLUDED
#define VECTOR2_HPP_INCLUDED

#include <Fantasy2C/Basic.hpp>

namespace F2C{

template<typename T>
class Vector2{
    public:
    T x;
    T y;

    Vector2():
        x(0),
        y(0)
    {}

    Vector2(T x,T y):
        x(x),
        y(y)
    {}

    const Vector2<T>& operator+=(const Vector2<T>& vec){
        *this = *this + vec;
        return *this;
    }
    const Vector2<T>& operator-=(const Vector2<T>& vec){
        *this = *this - vec;
        return *this;
    }
    const Vector2<T>& operator*=(const Vector2<T>& vec){
        *this = *this * vec;
        return *this;
    }
    const Vector2<T>& operator/=(const Vector2<T>& vec){
        *this = *this / vec;
        return *this;
    }

    const Vector2<T>& operator+=(const T& vec){
        *this = *this + vec;
        return *this;
    }
    const Vector2<T>& operator-=(const T& vec){
        *this = *this - vec;
        return *this;
    }
    const Vector2<T>& operator*=(const T& vec){
        *this = *this * vec;
        return *this;
    }
    const Vector2<T>& operator/=(const T& vec){
        *this = *this / vec;
        return *this;
    }

    //length of Vector
    // |v| = sqrt(v.x^2 + v.y^2 + v.z^2)
    T length() const {
        return sqrt(this->x*this->x +
                    this->y*this->y);
    }

    //length of Vector (square)
    // |v|^2 = v.x^2 + v.y^2 + v.z^2
    T lengthSqu() const {
        return this->x*this->x +
                this->y*this->y;
    }

    //Normalize
    //n = v / |v|
    Vector2<T> Normalize() const {
        T len = this->length();
        if(len != 0)
            return *this / len;
        else
            return *this;
    }

    //Dotproduct
    //v1.v2 = |v1| * |v2| * cos(φ)

    //v1
    //|
    //|
    //|alpha----v2
    //v1.v2 = 0: alpha = 90°
    //v1.v2 < 0: alpha > 90°
    //v1.v2 > 0: alpha < 90°
    T dotProduct(const Vector2<T>& vec2) const {
        return acos(this->lengthSqu()+vec2.lengthSqu());
    }

    T Distance(const Vector2<T>& vec2) const{
        T x = vec2.x - this->x;
        T y = vec2.y - this->y;
        return sqrt(x*x + y*y);
    }
};

template<typename T>
inline Vector2<T> operator+(const Vector2<T>& vec1,const Vector2<T>& vec2){
    return Vector2<T> (vec1.x+vec2.x,vec1.y+vec2.y);
}
template<typename T>
inline Vector2<T> operator-(const Vector2<T>& vec1,const Vector2<T>& vec2){
    return Vector2<T> (vec1.x-vec2.x,vec1.y-vec2.y);
}
template<typename T>
inline Vector2<T> operator*(const Vector2<T>& vec1,const Vector2<T>& vec2){
    return Vector2<T> (vec1.x*vec2.x,vec1.y*vec2.y);
}
template<typename T>
inline Vector2<T> operator/(const Vector2<T>& vec1,const Vector2<T>& vec2){
    return Vector2<T> (vec1.x/vec2.x,vec1.y/vec2.y);
}

template<typename T>
inline Vector2<T> operator*(const Vector2<T>& vec1,const T value){
    return Vector2<T> (vec1.x*value,vec1.y*value);
}
template<typename T>
inline Vector2<T> operator/(const Vector2<T>& vec1,const T value){
    return Vector2<T> (vec1.x/value,vec1.y/value);
}

template<typename T>
inline Vector2<T> operator*(const T value,const Vector2<T>& vec1){
    return Vector2<T> (vec1.x*value,vec1.y*value);
}
template<typename T>
inline Vector2<T> operator/(const T value,const Vector2<T>& vec1){
    return Vector2<T> (vec1.x/value,vec1.y/value);
}

template<typename T>
inline bool operator==(const Vector2<T>& vec1,const Vector2<T>& vec2){
    return vec1.x == vec2.x &&
            vec1.y == vec2.y;
}

template<typename T>
inline bool operator!=(const Vector2<T>& vec1,const Vector2<T>& vec2){
    return vec1.x != vec2.x ||
            vec1.y != vec2.y;
}

template<typename T>
inline Vector2<T> max(const Vector2<T>& vec1,const Vector2<T>& vec2){
    return Vector2<T> ( std::max(vec1.x,vec2.x), std::max(vec1.y,vec2.y) );
}
template<typename T>
inline Vector2<T> min(const Vector2<T>& vec1,const Vector2<T>& vec2){
    return Vector2<T> ( std::min(vec1.x,vec2.x), std::min(vec1.y,vec2.y) );
}

template<typename T>
inline Vector2<T> linearInterpolation(const Vector2<T>& vec1,const Vector2<T>& vec2,T s){
    return vec1 + s * (vec2-vec1);
}


}

#endif // VECTOR2_HPP_INCLUDED
