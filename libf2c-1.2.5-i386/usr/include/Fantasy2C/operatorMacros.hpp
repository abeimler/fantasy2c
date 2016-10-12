#ifndef OPERATORMACROS_HPP_INCLUDED
#define OPERATORMACROS_HPP_INCLUDED

#define DEF_ASS_OPERATOR(classname)\
const classname& operator+=(const classname& param);\
const classname& operator-=(const classname& param);\
const classname& operator*=(const classname& param);\
const classname& operator/=(const classname& param);

#define DEF_ASS_OPERATOR_T(classname,paramtype)\
const classname& operator+=(const paramtype& param);\
const classname& operator-=(const paramtype& param);\
const classname& operator*=(const paramtype& param);\
const classname& operator/=(const paramtype& param);

#define DEFDLL_G_OPERATOR(classname)\
classname DLL operator+(const classname& param1,const classname& param2);\
classname DLL operator-(const classname& param1,const classname& param2);\
classname DLL operator*(const classname& param1,const classname& param2);\
classname DLL operator/(const classname& param1,const classname& param2);

#define DEFDLL_G_OPERATOR_T(classname,param2type)\
classname DLL operator+(const classname& param1,const param2type param2);\
classname DLL operator-(const classname& param1,const param2type param2);\
classname DLL operator*(const classname& param1,const param2type param2);\
classname DLL operator/(const classname& param1,const param2type param2);\
\
classname DLL operator+(const param2type param2,const classname& param1);\
classname DLL operator-(const param2type param2,const classname& param1);\
classname DLL operator*(const param2type param2,const classname& param1);\
classname DLL operator/(const param2type param2,const classname& param1);

//-----------

#define ASS_OPERATOR(classname)\
const classname& classname::operator+=(const classname& param){\
    *this = *this + param;\
    return *this;\
}\
const classname& classname::operator-=(const classname& param){\
    *this = *this - param;\
    return *this;\
}\
const classname& classname::operator*=(const classname& param){\
    *this = *this * param;\
    return *this;\
}\
const classname& classname::operator/=(const classname& param){\
    *this = *this / param;\
    return *this;\
}\

#define ASS_OPERATOR_T(classname,paramtype)\
const classname& classname::operator+=(const paramtype& param){\
    *this = *this + param;\
    return *this;\
}\
const classname& classname::operator-=(const paramtype& param){\
    *this = *this - param;\
    return *this;\
}\
const classname& classname::operator*=(const paramtype& param){\
    *this = *this * param;\
    return *this;\
}\
const classname& classname::operator/=(const paramtype& param){\
    *this = *this / param;\
    return *this;\
}

#define G_OPERATOR3(classname,x,y,z)\
classname operator+(const classname& param1,const classname& param2){\
    return classname (param1.x+param2.x,param1.y+param2.y,param1.z+param2.z);\
}\
classname operator-(const classname& param1,const classname& param2){\
    return classname (param1.x-param2.x,param1.y-param2.y,param1.z-param2.z);\
}\
classname operator*(const classname& param1,const classname& param2){\
    return classname (param1.x*param2.x,param1.y*param2.y,param1.z*param2.z);\
}\
classname operator/(const classname& param1,const classname& param2){\
    return classname (param1.x/param2.x,param1.y/param2.y,param1.z/param2.z);\
}

#define G_OPERATOR_T3(classname,param2type,x,y,z)\
classname operator+(const classname& param1,const param2type param2){\
    return classname (param1.x+param2,param1.y+param2,param1.z+param2);\
}\
classname operator-(const classname& param1,const param2type param2){\
    return classname (param1.x-param2,param1.y-param2,param1.z-param2);\
}\
classname operator*(const classname& param1,const param2type param2){\
    return classname (param1.x*param2,param1.y*param2,param1.z*param2);\
}\
classname operator/(const classname& param1,const param2type param2){\
    return classname (param1.x/param2,param1.y/param2,param1.z/param2);\
}\
\
classname operator+(const param2type param2,const classname& param1){\
    return classname (param1.x+param2,param1.y+param2,param1.z+param2);\
}\
classname operator-(const param2type param2,const classname& param1){\
    return classname (param1.x-param2,param1.y-param2,param1.z-param2);\
}\
classname operator*(const param2type param2,const classname& param1){\
    return classname (param1.x*param2,param1.y*param2,param1.z*param2);\
}\
classname operator/(const param2type param2,const classname& param1){\
    return classname (param1.x/param2,param1.y/param2,param1.z/param2);\
}

#define G_OPERATOR4(classname,x,y,z,w)\
classname operator+(const classname& param1,const classname& param2){\
    return classname (param1.x+param2.x,param1.y+param2.y,param1.z+param2.z,param1.w+param2.w);\
}\
classname operator-(const classname& param1,const classname& param2){\
    return classname (param1.x-param2.x,param1.y-param2.y,param1.z-param2.z,param1.w-param2.w);\
}\
classname operator*(const classname& param1,const classname& param2){\
    return classname (param1.x*param2.x,param1.y*param2.y,param1.z*param2.z,param1.w*param2.w);\
}\
classname operator/(const classname& param1,const classname& param2){\
    return classname (param1.x/param2.x,param1.y/param2.y,param1.z/param2.z,param1.w/param2.w);\
}

#define G_OPERATOR_T4(classname,param2type,x,y,z,w)\
classname operator+(const classname& param1,const param2type param2){\
    return classname (param1.x+param2,param1.y+param2,param1.z+param2,param1.w+param2);\
}\
classname operator-(const classname& param1,const param2type param2){\
    return classname (param1.x-param2,param1.y-param2,param1.z-param2,param1.w-param2);\
}\
classname operator*(const classname& param1,const param2type param2){\
    return classname (param1.x*param2,param1.y*param2,param1.z*param2,param1.w*param2);\
}\
classname operator/(const classname& param1,const param2type param2){\
    return classname (param1.x/param2,param1.y/param2,param1.z/param2,param1.w/param2);\
}\
\
classname operator+(const param2type param2,const classname& param1){\
    return classname (param1.x+param2,param1.y+param2,param1.z+param2,param1.w+param2);\
}\
classname operator-(const param2type param2,const classname& param1){\
    return classname (param1.x-param2,param1.y-param2,param1.z-param2,param1.w-param2);\
}\
classname operator*(const param2type param2,const classname& param1){\
    return classname (param1.x*param2,param1.y*param2,param1.z*param2,param1.w*param2);\
}\
classname operator/(const param2type param2,const classname& param1){\
    return classname (param1.x/param2,param1.y/param2,param1.z/param2,param1.w/param2);\
}

#endif // OPERATORMACROS_HPP_INCLUDED
