#include "Matrix.h"

using namespace AEOIAF_Utilities;

Matrix::Matrix()
{
    m11 = 0.0f; m12 = 0.0f; m13 = 0.0f; m14 = 0.0f;
    m21 = 0.0f; m22 = 0.0f; m23 = 0.0f; m24 = 0.0f;
    m31 = 0.0f; m32 = 0.0f; m33 = 0.0f; m34 = 0.0f;
    m41 = 0.0f; m42 = 0.0f; m43 = 0.0f; m44 = 0.0f;
}

Matrix::Matrix(const Matrix& matrix)
{
    Copy(matrix);
}

Matrix& Matrix::operator=(const Matrix& m)
{
    Copy(m);
    return *this;
}

Matrix Matrix::operator*(const Matrix& m)
{
    return Multiply(*this, m);
}

void Matrix::Copy(const Matrix& matrix)
{
    m11 = matrix.m11; m12 = matrix.m12; m13 = matrix.m13; m14 = matrix.m14;
    m21 = matrix.m21; m22 = matrix.m22; m23 = matrix.m23; m24 = matrix.m24;
    m31 = matrix.m31; m32 = matrix.m32; m33 = matrix.m33; m34 = matrix.m34;
    m41 = matrix.m41; m42 = matrix.m42; m43 = matrix.m43; m44 = matrix.m44;
}

Matrix Matrix::GetIdentity()
{
    return Matrix (1.0f, 0.0f, 0.0f, 0.0f,
                   0.0f, 1.0f, 0.0f, 0.0f,
                   0.0f, 0.0f, 1.0f, 0.0f,
                   0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix Matrix::CreateTranslation(const Vector& xy, const float& zPos)
{
    Matrix m = GetIdentity();
    m.m41 = xy.GetX();
    m.m42 = xy.GetY();
    m.m43 = zPos;

    return m;
}

Matrix Matrix::CreateRotation(float angle)
{
    Matrix m = GetIdentity();

	//We calculate these so we can save
	//partially on cosine and sine calculations
	float cosVal, sinVal;

	cosVal = (float)cos(angle);
	sinVal = (float)sin(angle);

    m.m11 =  cosVal;
    m.m12 = -sinVal;
    m.m21 =  sinVal;
    m.m22 =  cosVal;

    return m;
}

Matrix Matrix::CreateScale(float scale)
{
    Matrix m = GetIdentity();
    m.m11 = scale;
    m.m22 = scale;
    m.m33 = scale;

    return m;
}

Matrix Matrix::Multiply(const Matrix& matrix1, const Matrix& matrix2)
{
    Matrix m;

    //Now comes death
    m.m11 = matrix1.m11 * matrix2.m11 + matrix1.m12 * matrix2.m21 + matrix1.m13 * matrix2.m31 + matrix1.m14 * matrix2.m41;
    m.m12 = matrix1.m11 * matrix2.m12 + matrix1.m12 * matrix2.m22 + matrix1.m13 * matrix2.m32 + matrix1.m14 * matrix2.m42;
    m.m13 = matrix1.m11 * matrix2.m13 + matrix1.m12 * matrix2.m23 + matrix1.m13 * matrix2.m33 + matrix1.m14 * matrix2.m43;
    m.m14 = matrix1.m11 * matrix2.m14 + matrix1.m12 * matrix2.m24 + matrix1.m13 * matrix2.m34 + matrix1.m14 * matrix2.m44;

    m.m21 = matrix1.m21 * matrix2.m11 + matrix1.m22 * matrix2.m21 + matrix1.m23 * matrix2.m31 + matrix1.m24 * matrix2.m41;
    m.m22 = matrix1.m21 * matrix2.m12 + matrix1.m22 * matrix2.m22 + matrix1.m23 * matrix2.m32 + matrix1.m24 * matrix2.m42;
    m.m23 = matrix1.m21 * matrix2.m13 + matrix1.m22 * matrix2.m23 + matrix1.m23 * matrix2.m33 + matrix1.m24 * matrix2.m43;
    m.m24 = matrix1.m21 * matrix2.m14 + matrix1.m22 * matrix2.m24 + matrix1.m23 * matrix2.m34 + matrix1.m24 * matrix2.m44;

    m.m31 = matrix1.m31 * matrix2.m11 + matrix1.m32 * matrix2.m21 + matrix1.m33 * matrix2.m31 + matrix1.m34 * matrix2.m41;
    m.m32 = matrix1.m31 * matrix2.m12 + matrix1.m32 * matrix2.m22 + matrix1.m33 * matrix2.m32 + matrix1.m34 * matrix2.m42;
    m.m33 = matrix1.m31 * matrix2.m13 + matrix1.m32 * matrix2.m23 + matrix1.m33 * matrix2.m33 + matrix1.m34 * matrix2.m43;
    m.m34 = matrix1.m31 * matrix2.m14 + matrix1.m32 * matrix2.m24 + matrix1.m33 * matrix2.m34 + matrix1.m34 * matrix2.m44;

    m.m41 = matrix1.m41 * matrix2.m11 + matrix1.m42 * matrix2.m21 + matrix1.m43 * matrix2.m31 + matrix1.m44 * matrix2.m41;
    m.m42 = matrix1.m41 * matrix2.m12 + matrix1.m42 * matrix2.m22 + matrix1.m43 * matrix2.m32 + matrix1.m44 * matrix2.m42;
    m.m43 = matrix1.m41 * matrix2.m13 + matrix1.m42 * matrix2.m23 + matrix1.m43 * matrix2.m33 + matrix1.m44 * matrix2.m43;
    m.m44 = matrix1.m41 * matrix2.m14 + matrix1.m42 * matrix2.m24 + matrix1.m43 * matrix2.m34 + matrix1.m44 * matrix2.m44;

    return m;
}

Matrix Matrix::Inverse(const Matrix& m)
{
    Matrix cMatrix = CalculateCofactor(m);
    Matrix transpose = Transpose(cMatrix);

    float invDtr = 1 / CalculateDeterminant(m);
    Matrix inverseMatrix = Matrix(transpose.m11 * invDtr, transpose.m12 * invDtr, transpose.m13 * invDtr, transpose.m14 * invDtr,
                                  transpose.m21 * invDtr, transpose.m22 * invDtr, transpose.m23 * invDtr, transpose.m24 * invDtr,
                                  transpose.m31 * invDtr, transpose.m32 * invDtr, transpose.m33 * invDtr, transpose.m34 * invDtr,
                                  transpose.m41 * invDtr, transpose.m42 * invDtr, transpose.m43 * invDtr, transpose.m44 * invDtr);

    return inverseMatrix;
}

Matrix Matrix::CalculateCofactor(const Matrix& m)
{
    Matrix cofactor;

    cofactor.m11 = CalculateDeterminant(m.m22, m.m23, m.m24, m.m32, m.m33, m.m34, m.m42, m.m43, m.m44);
    cofactor.m12 = CalculateDeterminant(m.m21, m.m23, m.m24, m.m31, m.m33, m.m34, m.m41, m.m43, m.m44);
    cofactor.m13 = CalculateDeterminant(m.m21, m.m22, m.m24, m.m31, m.m32, m.m34, m.m41, m.m42, m.m44);
    cofactor.m14 = CalculateDeterminant(m.m21, m.m22, m.m23, m.m31, m.m32, m.m33, m.m41, m.m42, m.m43);

    cofactor.m21 = CalculateDeterminant(m.m12, m.m13, m.m14, m.m32, m.m33, m.m34, m.m42, m.m43, m.m44);
    cofactor.m22 = CalculateDeterminant(m.m11, m.m13, m.m14, m.m31, m.m33, m.m34, m.m41, m.m43, m.m44);
    cofactor.m23 = CalculateDeterminant(m.m11, m.m12, m.m14, m.m31, m.m32, m.m34, m.m41, m.m42, m.m44);
    cofactor.m24 = CalculateDeterminant(m.m11, m.m12, m.m13, m.m31, m.m32, m.m33, m.m41, m.m42, m.m43);

    cofactor.m31 = CalculateDeterminant(m.m12, m.m13, m.m14, m.m22, m.m23, m.m24, m.m42, m.m43, m.m44);
    cofactor.m32 = CalculateDeterminant(m.m11, m.m13, m.m14, m.m21, m.m23, m.m24, m.m41, m.m43, m.m44);
    cofactor.m33 = CalculateDeterminant(m.m11, m.m12, m.m14, m.m21, m.m22, m.m24, m.m41, m.m42, m.m44);
    cofactor.m34 = CalculateDeterminant(m.m11, m.m12, m.m13, m.m21, m.m22, m.m23, m.m41, m.m42, m.m43);

    cofactor.m41 = CalculateDeterminant(m.m12, m.m13, m.m14, m.m22, m.m23, m.m24, m.m32, m.m33, m.m34);
    cofactor.m42 = CalculateDeterminant(m.m11, m.m13, m.m14, m.m21, m.m23, m.m24, m.m31, m.m33, m.m34);
    cofactor.m43 = CalculateDeterminant(m.m11, m.m12, m.m14, m.m21, m.m22, m.m24, m.m31, m.m32, m.m34);
    cofactor.m44 = CalculateDeterminant(m.m11, m.m12, m.m13, m.m21, m.m22, m.m23, m.m31, m.m32, m.m33);

    return ApplyCheckerboard(cofactor);
}

Matrix Matrix::ApplyCheckerboard(const Matrix& m)
{
    return Matrix( m.m11, -m.m12,  m.m13, -m.m14,
                  -m.m21,  m.m22, -m.m23,  m.m24,
                   m.m31, -m.m32,  m.m33, -m.m34,
                  -m.m41,  m.m42, -m.m43,  m.m44);
}

Matrix Matrix::Transpose(const Matrix& m)
{
    return Matrix(m.m11, m.m21, m.m31, m.m41,
                  m.m12, m.m22, m.m32, m.m42,
                  m.m13, m.m23, m.m33, m.m43,
                  m.m14, m.m24, m.m34, m.m44);
}

float Matrix::CalculateDeterminant(const float& nw, const float& n, const float& ne, const float& w, const float& c,
                                   const float& e, const float& sw, const float& s, const float& se)
{
    return (nw * c * se) + (n * e * sw) + (ne * w * s) -
           (ne * c * sw) - (nw * e * s) - (n * w * se);
}

float Matrix::CalculateDeterminant(const Matrix& m)
{
    float val1 = (-1.0f) * m.m21 * CalculateDeterminant(m.m12, m.m13, m.m14, m.m32, m.m33, m.m34, m.m42, m.m43, m.m44);
    float val2 =           m.m22 * CalculateDeterminant(m.m11, m.m13, m.m14, m.m31, m.m33, m.m34, m.m41, m.m43, m.m44);
    float val3 = (-1.0f) * m.m23 * CalculateDeterminant(m.m11, m.m12, m.m14, m.m31, m.m32, m.m34, m.m41, m.m42, m.m44);
    float val4 =           m.m24 * CalculateDeterminant(m.m11, m.m12, m.m13, m.m31, m.m32, m.m33, m.m41, m.m42, m.m43);

    return val1 + val2 + val3 + val4;
}

Vector Matrix::Transform(const Vector& toTransform, const Matrix& matrix)
{
	float x, y; //Store toTransform's components after single call to get them
    Vector result; //What we will return

	x = toTransform.GetX();
	y = toTransform.GetY();
    
	result.SetX((x * matrix.m11) + (y * matrix.m21) + matrix.m41);
    result.SetY((x * matrix.m12) + (y * matrix.m22) + matrix.m42);

    return result;
}
