#ifndef MATRIX_H
#define MATRIX_H

#include <SDL2/SDL.h>
#include <math.h>
#include "../Utility_Components/Vector.h"

namespace AEOIAF_Utilities
{
    class Matrix
    {
        public:
            Matrix();
            Matrix(float nm11, float nm12, float nm13, float nm14,
                   float nm21, float nm22, float nm23, float nm24,
                   float nm31, float nm32, float nm33, float nm34,
                   float nm41, float nm42, float nm43, float nm44)
                   : m11(nm11), m12(nm12), m13(nm13), m14(nm14),
                     m21(nm21), m22(nm22), m23(nm23), m24(nm24),
                     m31(nm31), m32(nm32), m33(nm33), m34(nm34),
                     m41(nm41), m42(nm42), m43(nm43), m44(nm44) {}
            Matrix(const Matrix& matrix);

            Matrix& operator= (const Matrix& m);
            Matrix operator* (const Matrix& m);

            void Copy(const Matrix& matrix);

            static Matrix GetIdentity();
            static Matrix CreateTranslation(const Vector& xy, const float& zPos);
            static Matrix CreateRotation(float angle);
            static Matrix CreateScale(float scale);

            static Matrix Multiply(const Matrix& matrix1, const Matrix& matrix2);
            static Matrix Inverse(const Matrix& matrix);
            static Matrix CalculateCofactor(const Matrix& m);
            static Matrix ApplyCheckerboard(const Matrix& m);
            static Matrix Transpose(const Matrix& m);

            static float CalculateDeterminant(const float& nw, const float& n, const float& ne, const float& w, const float& c,
                                              const float& e, const float& sw, const float& s, const float& se);
            static float CalculateDeterminant(const Matrix& m);

            static Vector Transform(const Vector& toTransform, const Matrix& matrix);

            float m11, m12, m13, m14;
            float m21, m22, m23, m24;
            float m31, m32, m33, m34;
            float m41, m42, m43, m44;
    };
}

#endif // MATRIX_H
