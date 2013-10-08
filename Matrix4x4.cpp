#include "PTEngine.h"
#include "Matrix4x4.h"

#undef malloc
#undef free
#include <math.h>

void Matrix4x4::SetOrthographic(float left, float right, float top, float bottom, float near, float far, bool leftHanded)
{
    mA.Set(2 / (right - left), 0, 0, 0);
    mB.Set(0, 2 / (top - bottom), 0, 0);
    if( leftHanded )
        mC.Set(0, 0, 1 / (far - near), 0);
    else
        mC.Set(0, 0, 1 / (near - far), 0);
    mD.Set((left + right) / (left - right), (top + bottom) / (bottom - top), near / (near - far), 1);
}

void Matrix4x4::SetPerspective(float width, float height, float near, float far, bool leftHanded)
{
    mA.Set((2 * near) / width, 0, 0, 0);
    mB.Set(0, (2 * near) / height, 0, 0);
    if( leftHanded )
        mC.Set(0, 0, far / (far - near), 1.0f);
    else
        mC.Set(0, 0, far / (near - far), -1.0f);
    mD.Set(0, 0, (near * far) / (near - far), 0);
}

void Matrix4x4::SetPerspectiveFov(float fovy, float aspectRatio, float near, float far, bool leftHanded)
{
    float yScale = (1.0f / tan(fovy / 2));
    float xScale = yScale / aspectRatio;

    mA.Set(xScale, 0, 0, 0);
    mB.Set(0, yScale, 0, 0);
    if( leftHanded )
    {
        mC.Set(0, 0, far / (far - near), 1.0f);
        mD.Set(0, 0, (-near * far) / (far - near), 0);
    }
    else
    {
        mC.Set(0, 0, far / (near - far), -1.0f);
        mD.Set(0, 0, (near * far) / (near - far), 0);
    }
}

void Matrix4x4::SetLook(const Vector3& eyePosition, const Vector3& lookAt, const Vector3& upDirection, bool leftHanded)
{
    Vector3 zaxis = leftHanded ? lookAt - eyePosition : eyePosition - lookAt;
    zaxis.Normalize();
    Vector3 xaxis = Vector3::Cross(upDirection, zaxis);
    xaxis.Normalize();
    Vector3 yaxis = Vector3::Cross(zaxis, xaxis);

    mA.Set(xaxis.mX, yaxis.mX, zaxis.mX, 0.0f);
    mB.Set(xaxis.mY, yaxis.mY, zaxis.mY, 0.0f);
    mC.Set(xaxis.mZ, yaxis.mZ, zaxis.mZ, 0.0f);    
    mD.Set(-xaxis.Dot(eyePosition), -yaxis.Dot(eyePosition), -zaxis.Dot(eyePosition), 1.0f);
}

void Matrix4x4::SetRotationY(float angleRadians)
{
    float c = cosf(angleRadians);
    float s = sinf(angleRadians);
    SetIdentity();
    mA.mX = c; 
    mA.mZ = -s;
    mC.mX = s;
    mC.mZ = c;
}