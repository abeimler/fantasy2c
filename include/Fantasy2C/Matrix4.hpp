#ifndef MATRIX4_HPP_INCLUDED
#define MATRIX4_HPP_INCLUDED

#include <Fantasy2C/Basic.hpp>
#include <Fantasy2C/Vector4.hpp>

namespace F2C{

template<typename T>
class Matrix4{
    public:
    T m11, m12, m13, m14;
    T m21, m22, m23, m24;
    T m31, m32, m33, m34;
    T m41, m42, m43, m44;

    Matrix4():
        m11(0), m12(0), m13(0),m14(0),
        m21(0), m22(0), m23(0),m24(0),
        m31(0), m32(0), m33(0),m34(0),
        m41(0), m42(0), m43(0),m44(0)
    {}

    Matrix4(T m11,T m12,T m13,T m14,
            T m21,T m22,T m23,T m24,
            T m31,T m32,T m33,T m34,
            T m41,T m42,T m43,T m44)
    :
        m11(m11), m12(m12), m13(m13),m14(m14),
        m21(m21), m22(m22), m23(m23),m24(m24),
        m31(m31), m32(m32), m33(m33),m34(m34),
        m41(m41), m42(m42), m43(m43),m44(m44)
    {}

    const Matrix4<T>& operator+=(const Matrix4<T>& mat){
        *this = *this + mat;
        return *this;
    }
    const Matrix4<T>& operator-=(const Matrix4<T>& mat){
        *this = *this - mat;
        return *this;
    }
    const Matrix4<T>& operator*=(const Matrix4<T>& mat){
        *this = *this * mat;
        return *this;
    }
    const Matrix4<T>& operator/=(const Matrix4<T>& mat){
        *this = *this / mat;
        return *this;
    }

    const Matrix4<T>& operator+=(const T& mat){
        *this = *this + mat;
        return *this;
    }
    const Matrix4<T>& operator-=(const T& mat){
        *this = *this - mat;
        return *this;
    }
    const Matrix4<T>& operator*=(const T& mat){
        *this = *this * mat;
        return *this;
    }
    const Matrix4<T>& operator/=(const T& mat){
        *this = *this / mat;
        return *this;
    }

    void set(T m11,T m12,T m13,T m14,
                T m21,T m22,T m23,T m24,
                T m31,T m32,T m33,T m34,
                T m41,T m42,T m43,T m44)
    {
        this->m11 = m11; this->m12 = m12; this->m13 = m13; this->m14 = m14;
        this->m21 = m21; this->m22 = m22; this->m23 = m23; this->m24 = m24;
        this->m31 = m31; this->m23 = m32; this->m33 = m33; this->m34 = m34;
        this->m41 = m41; this->m24 = m42; this->m43 = m34; this->m44 = m44;
    }

    void set(const T* mat){
        this->m11 = mat[0]; this->m12 = mat[1]; this->m13 = mat[2]; this->m14 = mat[3];
        this->m21 = mat[4]; this->m22 = mat[5]; this->m23 = mat[6]; this->m24 = mat[7];
        this->m31 = mat[8]; this->m32 = mat[9]; this->m23 = mat[10]; this->m34 = mat[11];
        this->m41 = mat[12]; this->m42 = mat[13]; this->m43 = mat[14]; this->m44 = mat[15];
    }

    void get(T* mat) const {
        mat[0] = this->m11; mat[1] = this->m12; mat[2] = this->m13; mat[3] = this->m14;
        mat[4] = this->m21; mat[5] = this->m22; mat[6] = this->m23; mat[7] = this->m24;
        mat[8] = this->m31; mat[9] = this->m32; mat[10] = this->m23; mat[11] = this->m34;
        mat[12] = this->m41; mat[13] = this->m42; mat[14] = this->m43; mat[15] = this->m44;
    }

    //identity matrix
    static Matrix4<T> Identity(){
        return Matrix4<T>(1,0,0,0,
                            0,1,0,0,
                            0,0,1,0,
                            0,0,0,1);
    }

    //Determinant of Matrix
    T Det() const {
        return this->m11 * (this->m22 * this->m33 - this->m23 * this->m32) -
               this->m12 * (this->m21 * this->m33 - this->m23 * this->m31) +
               this->m13 * (this->m21 * this->m32 - this->m22 * this->m31);
    }

    //Invertible of Matrix
    Matrix4 Invert() const{
        //inverse of Determinant
        double invDet = static_cast<double>(this->Det());
        if(invDet == 0.0f)
            return Matrix4::Identity();

        invDet = 1.0f / invDet;

        Matrix4 re;
        re.m11 =  invDet * (this->m22 * this->m33 - this->m23 * this->m32);
        re.m12 = -invDet * (this->m12 * this->m33 - this->m13 * this->m32);
        re.m13 =  invDet * (this->m12 * this->m23 - this->m13 * this->m22);

        re.m21 =  invDet * (this->m21 * this->m33 - this->m23 * this->m31)*-1;
        re.m22 =  invDet * (this->m11 * this->m33 - this->m13 * this->m31);
        re.m23 =  invDet * (this->m11 * this->m23 - this->m13 * this->m21)*-1;

        re.m31 =  invDet * (this->m21 * this->m32 - this->m22 * this->m31);
        re.m32 =  invDet * (this->m11 * this->m32 - this->m12 * this->m31)*-1;
        re.m33 =  invDet * (this->m11 * this->m22 - this->m12 * this->m21);

        return re;
    }

    //access operator
    T& operator[](size_t index){

        if(index == 0)      if(index == 1)      if(index == 2)      if(index == 3)
        return this->m11;   return this->m12;   return this->m13;   return this->m14;

        if(index == 4)      if(index == 5)      if(index == 6)      if(index == 7)
        return this->m21;   return this->m22;   return this->m23;   return this->m24;

        if(index == 8)      if(index == 9)      if(index == 10)     if(index == 11)
        return this->m31;   return this->m32;   return this->m33;   return this->m34;

        if(index == 12)     if(index == 13)     if(index == 14)     if(index == 15)
        return this->m41;   return this->m42;   return this->m43;   return this->m44;

        return this->m44;
    }

    const T& operator[](size_t index) const{
        if(index == 0)      if(index == 1)      if(index == 2)      if(index == 3)
        return this->m11;   return this->m12;   return this->m13;   return this->m14;

        if(index == 4)      if(index == 5)      if(index == 6)      if(index == 7)
        return this->m21;   return this->m22;   return this->m23;   return this->m24;

        if(index == 8)      if(index == 9)      if(index == 10)     if(index == 11)
        return this->m31;   return this->m32;   return this->m33;   return this->m34;

        if(index == 12)     if(index == 13)     if(index == 14)     if(index == 15)
        return this->m41;   return this->m42;   return this->m43;   return this->m44;

        return this->m44;
    }

    T& operator () (size_t x,size_t y){
        if(x == 1 && y == 1)    if(x == 1 && y == 2)    if(x == 1 && y == 3)    if(x == 1 && y == 4)
        return this->m11;       return this->m12;       return this->m13;       return this->m14;

        if(x == 2 && y == 1)    if(x == 2 && y == 2)    if(x == 2 && y == 3)    if(x == 2 && y == 4)
        return this->m21;       return this->m22;       return this->m23;       return this->m24;

        if(x == 3 && y == 1)    if(x == 3 && y == 2)    if(x == 3 && y == 3)    if(x == 3 && y == 4)
        return this->m31;       return this->m32;       return this->m33;       return this->m34;

        if(x == 4 && y == 1)    if(x == 4 && y == 2)    if(x == 4 && y == 3)    if(x == 4 && y == 4)
        return this->m41;       return this->m42;       return this->m43;       return this->m44;

        return this->m44;
    }

    const T& operator () (size_t x,size_t y) const {
        if(x == 1 && y == 1)    if(x == 1 && y == 2)    if(x == 1 && y == 3)    if(x == 1 && y == 4)
        return this->m11;       return this->m12;       return this->m13;       return this->m14;

        if(x == 2 && y == 1)    if(x == 2 && y == 2)    if(x == 2 && y == 3)    if(x == 2 && y == 4)
        return this->m21;       return this->m22;       return this->m23;       return this->m24;

        if(x == 3 && y == 1)    if(x == 3 && y == 2)    if(x == 3 && y == 3)    if(x == 3 && y == 4)
        return this->m31;       return this->m32;       return this->m33;       return this->m34;

        if(x == 4 && y == 1)    if(x == 4 && y == 2)    if(x == 4 && y == 3)    if(x == 4 && y == 4)
        return this->m41;       return this->m42;       return this->m43;       return this->m44;

        return this->m44;
    }

    Matrix4<T> getTex2DMatrix() const {
        return Matrix4<T>(this->m11, this->m12, this->m14, 0,
                            this->m21, this->m22, this->m24, 0,
                            this->m41, this->m42, this->m44, 0,
                            0,  0,  0,  1);
    }

    //translationsmatrix
    static Matrix4<T> Translation(const Vector3<T> vec) {
        return Matrix4<T>(1, 0, 0, 0,
                            0, 1, 0, 0,
                            0, 0, 1, 0,
                            vec.x, vec.y, vec.z, 1);
    }

    //Rotationsmatrix, x-axis
    static Matrix4<T> RotationX(T grad){
        T rad = Math::gradtoRad(grad);

        T rcos = cos(grad);
        T rsin = sin(grad);
        return Matrix4<T> (1, 0,      0,      0,
                           0, rcos,   rsin,   0,
                           0, rsin*-1,rcos,   0,
                           0, 0,      0,      0 );
    }

    //Rotationsmatrix, y-axis
    static Matrix4<T> RotationY(T grad){
        T rad = Math::gradtoRad(grad);

        T rcos = cos(grad);
        T rsin = sin(grad);
        return Matrix4<T> (rcos, 0, rsin*-1, 0,
                           0,    1, 0,       0,
                           rsin, 0, rcos,    0,
                           0,    0, 0,       1);
    }

    //Rotationsmatrix, z-axis
    static Matrix4<T> RotationZ(T grad){
        T rad = Math::gradtoRad(grad);

        T rcos = cos(grad);
        T rsin = sin(grad);
        return Matrix4<T> (rcos, rsin*-1, 0, 0,
                           rsin, rcos,    0, 0,
                           0,    0,       1, 0,
                           0,    0,       0, 1);
    }

    static Matrix4<T> Rotation(T xgrad,T ygrad,T zgrad){
        return Matrix4::RotationX(xgrad) * Matrix4::RotationY(ygrad) * Matrix4::RotationZ(zgrad);
    }

    static Matrix4<T> RotationAxis(const Vector3<T>& vec,float grad){
        T rad = Math::gradtoRad(grad);

        T mcos = cos(grad)*-1;
        T msin = sin(grad)*-1;

        Vector3<T> vAxis = vec.Normalize();

        return Matrix4<T> ((vAxis.x * vAxis.x) * (1.0f - mcos) + mcos,
                            (vAxis.x * vAxis.y) * (1.0f - mcos) - (vAxis.z * msin),
                            (vAxis.x * vAxis.z) * (1.0f - mcos) + (vAxis.y * msin),
                            0.0f,

                            (vAxis.y * vAxis.x) * (1.0f - mcos) + (vAxis.z * msin),
                            (vAxis.y * vAxis.y) * (1.0f - mcos) + mcos,
                            (vAxis.y * vAxis.z) * (1.0f - mcos) - (vAxis.x * msin),
                            0.0f,

                            (vAxis.z * vAxis.x) * (1.0f - mcos) - (vAxis.y * msin),
                            (vAxis.z * vAxis.y) * (1.0f - mcos) + (vAxis.x * msin),
                            (vAxis.z * vAxis.z) * (1.0f - mcos) + mcos,
                            0.0f,

                            0.0f,
                            0.0f,
                            0.0f,
                            1.0f);
    }

    static Matrix4<T> Scaling(const Vector3<T> vec){
        return Matrix4<T> (vec.x, 0,     0,     0,
                           0   , vec.y,  0,     0,
                           0   , 0,      vec.z, 0,
                           0   , 0,      0,     1);
    }

    static Matrix4<T> Axes(const Vector3<T> vec1,const Vector3<T> vec2,const Vector3<T> vec3){
        return Matrix4<T> (vec1.x, vec1.y, vec1.z, 0,
                           vec2.x, vec2.y, vec2.z, 0,
                           vec3.x, vec3.y, vec3.z, 0,
                           0, 0, 0, 1);
    }

    static Matrix4<T> ProjectionPerspective(T fovy,T aspect,T nearPlane,T farPlane){
        T F = cos(fovy) / sin(fovy);

        return Matrix4<T> (F/aspect, 0, 0, 0,
                           0, F, 0, 0,
                           0, 0, (nearPlane+farPlane) / (nearPlane-farPlane), (2.0f*farPlane*nearPlane)/(nearPlane-farPlane),
                           0, 0, -1, 0);
    }

    static Matrix4<T> ProjectionOrthographic(T left,T right,T top,T bottom,T nearPlane,T farPlane){
        return Matrix4<T> (2.0f / (left-right), 0, 0, (right+left)/(right-left),
                           0, 2.0f / (top-bottom), 0, (top+bottom)/(top-bottom),
                           0, 0, 2.0f / (nearPlane-farPlane), (farPlane+nearPlane)/(farPlane-nearPlane),
                           0, 0, 0, 1);
    }

    static Matrix4<T> LookAt(const Vector3<T>& eye, const Vector3<T>& center, const Vector3<T>& up){

         Vector3<T> zAxis( (center - eye).Normalize() );
         Vector3<T> xAxis( up.crossProduct(zAxis).Normalize() );
         Vector3<T> yAxis( zAxis.crossProduct(xAxis).Normalize() );

        return Matrix4<T>::Translation(eye*-1) *
                Matrix4<T>(xAxis.x, yAxis.x, zAxis.x, 0,
                            xAxis.y, yAxis.y, zAxis.y, 0,
                            xAxis.z, yAxis.z, zAxis.z, 0,
                            0,     0,     0,     1);
    }
};

template<typename T>
inline Matrix4<T> operator+(const Matrix4<T>& mat1,const Matrix4<T>& mat2){
    return Matrix4<T> (mat1.m11+mat2.m11, mat1.m12+mat2.m12, mat1.m13+mat2.m13, mat1.m14+mat2.m14,
                        mat1.m21+mat2.m21, mat1.m22+mat2.m22, mat1.m23+mat2.m23, mat1.m24+mat2.m24,
                        mat1.m31+mat2.m31, mat1.m32+mat2.m32, mat1.m33+mat2.m33, mat1.m34+mat2.m34,
                        mat1.m41+mat2.m41, mat1.m42+mat2.m42, mat1.m43+mat2.m43, mat1.m44+mat2.m44);
}
template<typename T>
inline Matrix4<T> operator-(const Matrix4<T>& mat1,const Matrix4<T>& mat2){
    return Matrix4<T> (mat1.m11-mat2.m11, mat1.m12-mat2.m12, mat1.m13-mat2.m13, mat1.m14-mat2.m14,
                        mat1.m21-mat2.m21, mat1.m22-mat2.m22, mat1.m23-mat2.m23, mat1.m24-mat2.m24,
                        mat1.m31-mat2.m31, mat1.m32-mat2.m32, mat1.m33-mat2.m33, mat1.m34-mat2.m34,
                        mat1.m41-mat2.m41, mat1.m42-mat2.m42, mat1.m43-mat2.m43, mat1.m44-mat2.m44);
}

template<typename T>
inline Matrix4<T> operator*(const Matrix4<T>& mat1,const Matrix4<T>& mat2){
    return Matrix4<T> (mat2.m11 * mat1.m11 + mat2.m21 * mat1.m12 + mat2.m31 * mat1.m13,
                        mat2.m12 * mat1.m11 + mat2.m22 * mat1.m12 + mat2.m32 * mat1.m13,
                        mat2.m13 * mat1.m11 + mat2.m23 * mat1.m12 + mat2.m33 * mat1.m13,

                        mat2.m11 * mat1.m21 + mat2.m21 * mat1.m22 + mat2.m31 * mat1.m23,
                        mat2.m12 * mat1.m21 + mat2.m22 * mat1.m22 + mat2.m32 * mat1.m23,
                        mat2.m13 * mat1.m21 + mat2.m23 * mat1.m22 + mat2.m33 * mat1.m23,

                        mat2.m11 * mat1.m31 + mat2.m21 * mat1.m32 + mat2.m31 * mat1.m33,
                        mat2.m12 * mat1.m31 + mat2.m22 * mat1.m32 + mat2.m32 * mat1.m33,
                        mat2.m13 * mat1.m31 + mat2.m23 * mat1.m32 + mat2.m33 * mat1.m33);
}
template<typename T>
inline Matrix4<T> operator/(const Matrix4<T>& mat1,const Matrix4<T>& mat2){
    return mat1 * mat2.Invert();
}

template<typename T>
inline Matrix4<T> operator*(const Matrix4<T>& mat1,const T value){
    return Matrix4<T> (mat1.m11*value, mat1.m12*value, mat1.m13*value, mat1.m14*value,
                        mat1.m21*value, mat1.m22*value, mat1.m23*value, mat1.m24*value,
                        mat1.m31*value, mat1.m32*value, mat1.m33*value, mat1.m34*value,
                        mat1.m41*value, mat1.m42*value, mat1.m43*value, mat1.m44*value);
}
template<typename T>
inline Matrix4<T> operator/(const Matrix4<T>& mat1,const T value){
    return Matrix4<T> (mat1.m11/value, mat1.m12/value, mat1.m13/value, mat1.m14/value,
                        mat1.m21/value, mat1.m22/value, mat1.m23/value, mat1.m24/value,
                        mat1.m31/value, mat1.m32/value, mat1.m33/value, mat1.m34/value,
                        mat1.m41/value, mat1.m42/value, mat1.m43/value, mat1.m44/value);
}

template<typename T>
inline Matrix4<T> operator*(const T value,const Matrix4<T>& mat1){
    return Matrix4<T> (mat1.m11*value, mat1.m12*value, mat1.m13*value, mat1.m14*value,
                        mat1.m21*value, mat1.m22*value, mat1.m23*value, mat1.m24*value,
                        mat1.m31*value, mat1.m32*value, mat1.m33*value, mat1.m34*value,
                        mat1.m41*value, mat1.m42*value, mat1.m43*value, mat1.m44*value);
}

template<typename T>
inline Matrix4<T> operator/(const T value,const Matrix4<T>& mat1){
    return Matrix4<T> (mat1.m11/value, mat1.m12/value, mat1.m13/value, mat1.m14/value,
                        mat1.m21/value, mat1.m22/value, mat1.m23/value, mat1.m24/value,
                        mat1.m31/value, mat1.m32/value, mat1.m33/value, mat1.m34/value,
                        mat1.m41/value, mat1.m42/value, mat1.m43/value, mat1.m44/value);
}

template<typename T>
inline Vector4<T> operator*(const Matrix4<T>& m,const Vector4<T>& v){
    Vector4<T> re;

    re.x = v.x*m.m11 + v.y*m.m21 + v.z*m.m31 + v.w*m.m41;
    re.y = v.x*m.m12 + v.y*m.m22 + v.z*m.m32 + v.w*m.m42;
    re.z = v.x*m.m13 + v.y*m.m23 + v.z*m.m33 + v.w*m.m43;
    re.w = v.x*m.m14 + v.y*m.m24 + v.z*m.m34 + v.w*m.m44;

    return re;
}

template<typename T>
inline Vector4<T> operator*(const Vector4<T>& v,const Matrix4<T>& m){
    Vector4<T> re;

    re.x = v.x*m.m11 + v.y*m.m21 + v.z*m.m31 + v.w*m.m41;
    re.y = v.x*m.m12 + v.y*m.m22 + v.z*m.m32 + v.w*m.m42;
    re.z = v.x*m.m13 + v.y*m.m23 + v.z*m.m33 + v.w*m.m43;
    re.w = v.x*m.m14 + v.y*m.m24 + v.z*m.m34 + v.w*m.m44;

    return re;
}

template<typename T>
inline bool operator == (const Matrix4<T>& mat1,const Matrix4<T>& mat2){
	if(mat1.m11 != mat2.m11) return false;
	if(mat1.m12 != mat2.m12) return false;
	if(mat1.m13 != mat2.m13) return false;
	if(mat1.m14 != mat2.m14) return false;

	if(mat1.m21 != mat2.m21) return false;
	if(mat1.m22 != mat2.m22) return false;
	if(mat1.m23 != mat2.m23) return false;
	if(mat1.m24 != mat2.m24) return false;

	if(mat1.m31 != mat2.m31) return false;
	if(mat1.m32 != mat2.m32) return false;
	if(mat1.m33 != mat2.m33) return false;
	if(mat1.m34 != mat2.m34) return false;

	if(mat1.m41 != mat2.m41) return false;
	if(mat1.m42 != mat2.m42) return false;
	if(mat1.m43 != mat2.m43) return false;
	return mat1.m44 == mat2.m44;
}

template<typename T>
inline bool operator != (const Matrix4<T>& mat1,const Matrix4<T>& mat2){
	if(mat1.m11 != mat2.m11) return true;
	if(mat1.m12 != mat2.m12) return true;
	if(mat1.m13 != mat2.m13) return true;
	if(mat1.m14 != mat2.m14) return true;

	if(mat1.m21 != mat2.m21) return true;
	if(mat1.m22 != mat2.m22) return true;
	if(mat1.m23 != mat2.m23) return true;
	if(mat1.m24 != mat2.m24) return true;

	if(mat1.m31 != mat2.m31) return true;
	if(mat1.m32 != mat2.m32) return true;
	if(mat1.m33 != mat2.m33) return true;
	if(mat1.m34 != mat2.m34) return true;

	if(mat1.m41 != mat2.m41) return true;
	if(mat1.m42 != mat2.m42) return true;
	if(mat1.m43 != mat2.m43) return true;
	return mat1.m44 != mat2.m44;
}

}
#endif // MATRIX4_HPP_INCLUDED
