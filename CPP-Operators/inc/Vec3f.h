#ifndef VEC3F_H
#define VEC3F_H


#ifndef __FLT_EPSILON__
#define __FLT_EPSILON__ 0.00001f
#endif

#include <iostream>
#include <math.h>

using namespace std;

class Vec3f
{
    // Overloading
    friend ostream& operator<< (ostream& out, const Vec3f& obj)
    {
        return out << "[" << obj.x << "," << obj.y << "," << obj.z << "]";
    }
    
    friend const Vec3f operator* (const float lhs, const Vec3f rhs)
    {
        return Vec3f(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
    }
    
private:
    float x;
    float y;
    float z;
    
public:
    // Constructors
    explicit Vec3f(const float x=0, const float y=0, const float z=0) : x(x), y(y), z(z)
    {}
    
    Vec3f(const float* array)
    {
        x = array[0];
        y = array[1];
        z = array[2];
    }
    
    // Copy Constructor
    Vec3f(const Vec3f& CopySource)
    {
        x = CopySource.x;
        y = CopySource.y;
        z = CopySource.z;
    }
    
    // Destructor
    ~Vec3f()
    {}
    
    /**
     ** OPERATIONS OVERLOADING
     **/
    
    // Unary Operation "-": changes the sign (direction) of the vector
    Vec3f operator- (void)
    {
        return Vec3f(-1 * x, -1 * y, -1 * z);
    }
    
    // Binary Operation "+": adds two vectors
    const Vec3f operator+ (const Vec3f& rhs) const
    {
        return Vec3f(x + rhs.x, y + rhs.y, z + rhs.z);
    }
    
    // Binary Operation "-": subtracts two vectors
    const Vec3f operator- (const Vec3f& rhs) const
    {
        return Vec3f(x - rhs.x, y - rhs.y, z - rhs.z);
    }
    
    // Binary Operation "*": returns the dot product of two vectors
    const float operator* (const Vec3f& rhs)
    {
        return x*rhs.x + y*rhs.y + z*rhs.z;
    }
    
    // Binary Operation "^": return the cross product of two vectors
    const Vec3f operator^ (const Vec3f& rhs) const
    {
        float newX = (y * rhs.z) - (z * rhs.y);
        float newY = (z * rhs.x) - (x * rhs.z);
        float newZ = (x * rhs.y) - (y * rhs.x);
        
        return Vec3f(newX, newY, newZ);
    }
    
    // Binary Operation "=": replaces the vector with a new one
    const Vec3f& operator= (const Vec3f rhs)
    {
        if (*this != rhs)
        {
            x = rhs.x;
            y = rhs.y;
            z = rhs.z;
        }
        
        return *this;
    }
    
    // Binary Operation "/=": divides the vector itself with a value
    const Vec3f& operator/= (const float value)
    {
        x /= value;
        y /= value;
        z /= value;
        
        return *this;
    }
    
    // Binary Operation "==": compares two vectors, returns true if the vectors are equivalent with
    // an error difference of 1E-5 or smaller, which defined by __FLT_EPSILON__, and returns false otherwise
    bool operator== (const Vec3f& rhs)
    {
        float x_diff = fabsf(x-rhs.x);
        float y_diff = fabsf(y-rhs.y);
        float z_diff = fabsf(z-rhs.z);
        
        return x_diff < __FLT_EPSILON__ && y_diff < __FLT_EPSILON__ && z_diff < __FLT_EPSILON__;
    }
    
    // Binary Operation "!=": the contrary function of the function above, returns true if the vectors are not
    // equivalent or false otherwise
    bool operator!= (const Vec3f& rhs)
    {
        return !(*this == rhs);
    }
    
    // Binary Operation "*": scales the vector by "factor"-times
    const Vec3f operator* (const float factor) const
    {
        return Vec3f(factor * x, factor * y, factor * z);
    }
    
    /**
     ** CLASS FUNCTIONS
     **/
    
    // return the length of the vector
    float length()
    {
        return (float) sqrt(x*x + y*y + z*z);
    }
    
    // normalizes the vector itself, the length of a normalized vector is always 1
    const Vec3f& normalize()
    {
        float len = length();
        
        x /= len;
        y /= len;
        z /= len;
        
        return *this;
    }
};

#endif
