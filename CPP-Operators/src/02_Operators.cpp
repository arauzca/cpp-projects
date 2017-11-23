#include "../inc/Vec3f.h"

int main()
{
                                        cout << "3 points in the xz-plane:"               << endl;
    Vec3f A(0,0,0);                     cout << "Vec3f A(0,0);               A = " << A   << endl;
    float b[3]={2,0,0};                 cout << "float b[3]={2,0,0};"                     << endl;
    Vec3f B(b);                         cout << "Vec3f B(b);                 B = " << B   << endl;
    Vec3f C(Vec3f(0,0,-2));             cout << "Vec3f C(Vec3f(0,0,-1));     C = " << C   << endl;
                                        cout                                              << endl;
                                        cout << "2 edges of a triangle:"                  << endl;
    Vec3f E1 = B-A;                     cout << "Vec3f E1 = B-A;            E1 = " << E1  << endl;
          E1 = B+-A;                    cout << "      E1 = B+-A;           E1 = " << E1  << endl;
    Vec3f E2 = C-A;                     cout << "Vec3f E2 = C-A;            E2 = " << E2  << endl;
                                        cout                                              << endl;
                                        cout << "N is the triangles normal:"              << endl;
    Vec3f N = E1^E2;                    cout << "Vec3f N = E1^E2;            N = " << N   << endl;
    N.normalize();                      cout << "N.normalize();              N = " << N   << endl;
                                        cout                                              << endl;
                                        cout << "I is an incident ray:"                   << endl;
    Vec3f I(1,-1);                      cout << "Vec3f I(1,-1);              I = " << I   << endl;
    float len = I.length();             cout << "float len = I.length();   len = " << len << endl;
    I /= len;                           cout << "I /= len;                   I = " << I   << endl;
    int eq=I==Vec3f(1,-1).normalize();  cout << "I == Vec3f(1,-1).normalize()  = " << eq  << endl;
                                        cout                                              << endl;
    const float PI = 3.141592653f;      cout << "Angle between I and N:"                  << endl;
    float deg = acos(-I*N)*180.0f/PI;   cout << "deg=acos(-I*N)*180.0f/PI; deg = " << deg << endl;
                                        cout                                              << endl;
                                        cout << "R is the reflected ray of I:"            << endl;
    Vec3f R = I-2*(I*N)*N;              cout << "Vec3f R = I-2*(I*N)*N;      R = " << R   << endl;
                                        cout                                              << endl;
    
	return 0;
}

