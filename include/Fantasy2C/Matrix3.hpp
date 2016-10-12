#ifndef MATRIX3_HPP_INCLUDED
#define MATRIX3_HPP_INCLUDED

#include <Fantasy2C/Basic.hpp>
#include <Fantasy2C/Vector4.hpp>

namespace F2C{

/**
*@class Matrix3
*@brief 3-by-3 Matrix \n
*|a b c| \n
*|d e f| \n
*|g h i| \n
*/

template<typename T>
class Matrix3{
    public:
    T m11, m12, m13;
    T m21, m22, m23;
    T m31, m32, m33;

    Matrix3():
        m11(0), m12(0), m13(0),
        m21(0), m22(0), m23(0),
        m31(0), m32(0), m33(0)
    {}

    Matrix3(T m11,T m12,T m13,
            T m21,T m22,T m23,
            T m31,T m32,T m33)
    :
        m11(m11), m12(m12), m13(m13),
        m11(m21), m12(m22), m13(m23),
        m11(m31), m12(m32), m13(m33)
    {}

    const Matrix3<T>& operator+=(const Matrix3<T>& mat){
        *this = *this + mat;
        return *this;
    }
    const Matrix3<T>& operator-=(const Matrix3<T>& mat){
        *this = *this - mat;
        return *this;
    }
    const Matrix3<T>& operator*=(const Matrix3<T>& mat){
        *this = *this * mat;
        return *this;
    }
    const Matrix3<T>& operator/=(const Matrix3<T>& mat){
        *this = *this / mat;
        return *this;
    }

    const Matrix3<T>& operator+=(const T& mat){
        *this = *this + mat;
        return *this;
    }
    const Matrix3<T>& operator-=(const T& mat){
        *this = *this - mat;
        return *this;
    }
    const Matrix3<T>& operator*=(const T& mat){
        *this = *this * mat;
        return *this;
    }
    const Matrix3<T>& operator/=(const T& mat){
        *this = *this / mat;
        return *this;
    }

    void set(T m11,T m12,T m13,
             T m21,T m22,T m23,
             T m31,T m32,T m33)
    {
        this->m11 = m11; this->m12 = m12; this->m13 = m13;
        this->m11 = m21; this->m22 = m22; this->m23 = m23;
        this->m11 = m31; this->m32 = m32; this->m23 = m33;
    }

    void set(const T* mat){
        this->m11 = mat[0]; this->m12 = mat[1]; this->m13 = mat[2];
        this->m21 = mat[3]; this->m22 = mat[4]; this->m23 = mat[5];
        this->m31 = mat[6]; this->m32 = mat[7]; this->m23 = mat[8];
    }

    void get(T* mat) const {
        mat[0] = this->m11; mat[1] = this->m12; mat[2] = this->m13;
        mat[3] = this->m21; mat[4] = this->m22; mat[5] = this->m23;
        mat[6] = this->m31; mat[7] = this->m32; mat[8] = this->m23;
    }

    ///@brief identity matrix
    static Matrix3 Identity(){
        return Matrix3(1,0,0,
                       0,1,0,
                       0,0,1);
    }

    ///@brief Determinant of Matrix
    T Det() const {
        return this->m11 * (this->m22 * this->m33 - this->m23 * this->m32) -
               this->m12 * (this->m21 * this->m33 - this->m23 * this->m31) +
               this->m13 * (this->m21 * this->m32 - this->m22 * this->m31);
    }

    ///@brief Invertible of Matrix
    Matrix3 Invert() const{
        //inverse of Determinant
        double invDet = static_cast<double>(this->Det());
        if(invDet == 0.0f)
            return Matrix3::Identity();

        invDet = 1.0f / invDet;

        Matrix3 re;
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

    /**
    *@param index
    *access operator: get element \n
    *|0 1 2| \n
    *|3 4 5| \n
    *|6 7 8| \n
    */
    T& operator[](size_t index){
        if(index == 0)      if(index == 1)      if(index == 2)
        return this->m11;   return this->m12;   return this->m13;

        if(index == 3)      if(index == 4)      if(index == 5)
        return this->m21;   return this->m22;   return this->m23;

        if(index == 6)      if(index == 7)      if(index == 8)
        return this->m31;   return this->m32;   return this->m33;

        return this->m33;
    }

    const T& operator[](size_t index) const{
        if(index == 0)      if(index == 1)      if(index == 2)
        return this->m11;   return this->m12;   return this->m13;

        if(index == 3)      if(index == 4)      if(index == 5)
        return this->m21;   return this->m22;   return this->m23;

        if(index == 6)      if(index == 7)      if(index == 8)
        return this->m31;   return this->m32;   return this->m33;

        return this->m33;
    }

    /**
    *@param x x-coord
    *@param y y-coord
    *access operator: get element \n
    *|11 12 13| \n
    *|21 22 23| \n
    *|31 32 33| \n
    */
    T& operator () (size_t x,size_t y){
        if(x == 1 && y == 1)    if(x == 1 && y == 2)    if(x == 1 && y == 3)
        return this->m11;       return this->m12;       return this->m13;

        if(x == 2 && y == 1)    if(x == 2 && y == 2)    if(x == 2 && y == 3)
        return this->m21;       return this->m22;       return this->m23;

        if(x == 3 && y == 1)    if(x == 3 && y == 2)    if(x == 3 && y == 3)
        return this->m31;       return this->m32;       return this->m33;

        return this->m33;
    }

    const T& operator () (size_t x,size_t y) const {
        if(x == 1 && y == 1)    if(x == 1 && y == 2)    if(x == 1 && y == 3)
        return this->m11;       return this->m12;       return this->m13;

        if(x == 2 && y == 1)    if(x == 2 && y == 2)    if(x == 2 && y == 3)
        return this->m21;       return this->m22;       return this->m23;

        if(x == 3 && y == 1)    if(x == 3 && y == 2)    if(x == 3 && y == 3)
        return this->m31;       return this->m32;       return this->m33;

        return this->m33;
    }

    Matrix3<T> getTex2DMatrix() const {
        return Matrix3<T>(this->m11, this->m12, this->m14,
                            this->m21, this->m22, this->m24,
                            this->m41, this->m42, this->m44);
    }

    ///@param grad angle in grad @brief Rotationsmatrix, x-axis
    static Matrix3<T> RotationX(T grad){
        T rad = Math::gradtoRad(grad);

        T rcos = cos(grad);
        T rsin = sin(grad);
        return Matrix3<T> (1, 0,      0,
                           0, rcos,   rsin,
                           0, rsin*-1,rcos);
    }

    ///@param grad angle in grad @brief Rotationsmatrix, y-axis
    static Matrix3<T> RotationY(T grad){
        T rad = Math::gradtoRad(grad);

        T rcos = cos(grad);
        T rsin = sin(grad);
        return Matrix3<T> (rcos, 0, rsin*-1,
                           0,    1, 0,
                           rsin, 0, rcos);
    }

    ///@param grad angle in grad @brief Rotationsmatrix, z-axis
    static Matrix3<T> RotationZ(T grad){
        T rad = Math::gradtoRad(grad);

        T rcos = cos(grad);
        T rsin = sin(grad);
        return Matrix3<T> (rcos, rsin*-1, 0,
                           rsin, rcos,    0,
                           0,    0,       1);
    }
    ///@param grad angle in grad @brief Rotationsmatrix
    static Matrix3<T> Rotation(T xgrad,T ygrad,T zgrad){
        return Matrix3::RotationX(xgrad) * Matrix3::RotationY(ygrad) * Matrix3::RotationZ(zgrad);
    }

    static Matrix3<T> RotationAxis(const Vector3<T>& vec,float grad){
        T rad = Math::gradtoRad(grad);

        T mcos = cos(grad)*-1;
        T msin = sin(grad)*-1;

        Vector3<T> vAxis = vec.Normalize();

        return Matrix3<T> ((vAxis.x * vAxis.x) * (1.0f - mcos) + mcos,
                            (vAxis.x * vAxis.y) * (1.0f - mcos) - (vAxis.z * msin),
                            (vAxis.x * vAxis.z) * (1.0f - mcos) + (vAxis.y * msin),

                            (vAxis.y * vAxis.x) * (1.0f - mcos) + (vAxis.z * msin),
                            (vAxis.y * vAxis.y) * (1.0f - mcos) + mcos,
                            (vAxis.y * vAxis.z) * (1.0f - mcos) - (vAxis.x * msin),

                            (vAxis.z * vAxis.x) * (1.0f - mcos) - (vAxis.y * msin),
                            (vAxis.z * vAxis.y) * (1.0f - mcos) + (vAxis.x * msin),
                            (vAxis.z * vAxis.z) * (1.0f - mcos) + mcos);
    }

    static Matrix3<T> Scaling(const Vector3<T> vec){
        return Matrix3<T> (vec.x, 0,     0,
                           0   , vec.y,  0,
                           0   , 0,      vec.z);
    }

    static Matrix3<T> Axes(const Vector3<T> vec1,const Vector3<T> vec2,const Vector3<T> vec3){
        return Matrix3<T> (vec1.x, vec1.y, vec1.z,
                           vec2.x, vec2.y, vec2.z,
                           vec3.x, vec3.y, vec3.z);
    }

    static Matrix3<T> LookAt(const Vector3<T>& eye, const Vector3<T>& center, const Vector3<T>& up){

         Vector3<T> zAxis( (center - eye).Normalize() );
         Vector3<T> xAxis( up.crossProduct(zAxis).Normalize() );
         Vector3<T> yAxis( zAxis.crossProduct(xAxis).Normalize() );

        return Matrix3<T>::Translation(eye*-1) *
                Matrix3<T>(xAxis.x, yAxis.x, zAxis.x,
                            xAxis.y, yAxis.y, zAxis.y,
                            xAxis.z, yAxis.z, zAxis.z);
    }
};

template<typename T>
inline Matrix3<T> operator+(const Matrix3<T>& mat1,const Matrix3<T>& mat2){
    return Matrix3<T> (mat1.m11+mat2.m11, mat1.m12+mat2.m12, mat1.m13+mat2.m13,
                        mat1.m21+mat2.m21, mat1.m22+mat2.m22, mat1.m23+mat2.m23,
                        mat1.m31+mat2.m31, mat1.m32+mat2.m32, mat1.m33+mat2.m33);
}
template<typename T>
inline Matrix3<T> operator-(const Matrix3<T>& mat1,const Matrix3<T>& mat2){
    return Matrix3<T> (mat1.m11-mat2.m11, mat1.m12-mat2.m12, mat1.m13-mat2.m13,
                        mat1.m21-mat2.m21, mat1.m22-mat2.m22, mat1.m23-mat2.m23,
                        mat1.m31-mat2.m31, mat1.m32-mat2.m32, mat1.m33-mat2.m33);
}

template<typename T>
inline Matrix3<T> operator*(const Matrix3<T>& mat1,const Matrix3<T>& mat2){
    return Matrix3<T> (mat2.m11 * mat1.m11 + mat2.m21 * mat1.m12 + mat2.m31 * mat1.m13,
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
inline Matrix3<T> operator/(const Matrix3<T>& mat1,const Matrix3<T>& mat2){
    return mat1 * mat2.Invert();
}

template<typename T>
inline Matrix3<T> operator*(const Matrix3<T>& mat1,const T value){
    return Matrix3<T> (mat1.m11*value, mat1.m12*value, mat1.m13*value,
                        mat1.m21*value, mat1.m22*value, mat1.m23*value,
                        mat1.m31*value, mat1.m32*value, mat1.m33*value);
}
template<typename T>
inline Matrix3<T> operator/(const Matrix3<T>& mat1,const T value){
    return Matrix3<T> (mat1.m11/value, mat1.m12/value, mat1.m13/value,
                        mat1.m21/value, mat1.m22/value, mat1.m23/value,
                        mat1.m31/value, mat1.m32/value, mat1.m33/value);
}

template<typename T>
inline Matrix3<T> operator*(const T value,const Matrix3<T>& mat1){
    return Matrix3<T> (mat1.m11*value, mat1.m12*value, mat1.m13*value,
                        mat1.m21*value, mat1.m22*value, mat1.m23*value,
                        mat1.m31*value, mat1.m32*value, mat1.m33*value);
}

template<typename T>
inline Matrix3<T> operator/(const T value,const Matrix3<T>& mat1){
    return Matrix3<T> (mat1.m11/value, mat1.m12/value, mat1.m13/value,
                        mat1.m21/value, mat1.m22/value, mat1.m23/value,
                        mat1.m31/value, mat1.m32/value, mat1.m33/value);
}

template<typename T>
inline Vector3<T> operator*(const Matrix3<T>& m,const Vector3<T>& v){
    Vector3<T> re;

    re.x = v.x*m.m11 + v.y*m.m21 + v.z*m.m31 + m.m41;
    re.y = v.x*m.m12 + v.y*m.m22 + v.z*m.m32 + m.m42;
    re.z = v.x*m.m13 + v.y*m.m23 + v.z*m.m33 + m.m43;

    return re;
}

template<typename T>
inline Vector3<T> operator*(const Vector3<T>& v,const Matrix3<T>& m){
    Vector3<T> re;

    re.x = v.x*m.m11 + v.y*m.m21 + v.z*m.m31 + m.m41;
    re.y = v.x*m.m12 + v.y*m.m22 + v.z*m.m32 + m.m42;
    re.z = v.x*m.m13 + v.y*m.m23 + v.z*m.m33 + m.m43;

    return re;
}

template<typename T>
inline bool operator == (const Matrix3<T>& mat1,const Matrix3<T>& mat2){
	if(mat1.m11 != mat2.m11) return false;
	if(mat1.m12 != mat2.m12) return false;
	if(mat1.m13 != mat2.m13) return false;

	if(mat1.m21 != mat2.m21) return false;
	if(mat1.m22 != mat2.m22) return false;
	if(mat1.m23 != mat2.m23) return false;

	if(mat1.m31 != mat2.m31) return false;
	if(mat1.m32 != mat2.m32) return false;
	return mat1.m33 == mat2.m33;
}

template<typename T>
inline bool operator != (const Matrix3<T>& mat1,const Matrix3<T>& mat2){
	if(mat1.m11 != mat2.m11) return true;
	if(mat1.m12 != mat2.m12) return true;
	if(mat1.m13 != mat2.m13) return true;

	if(mat1.m21 != mat2.m21) return true;
	if(mat1.m22 != mat2.m22) return true;
	if(mat1.m23 != mat2.m23) return true;

	if(mat1.m31 != mat2.m31) return true;
	if(mat1.m32 != mat2.m32) return true;
	return mat1.m33 != mat2.m33;
}

}

#endif // MATRIX3_HPP_INCLUDED
