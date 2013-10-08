#ifndef _SHADER_PROGRAM_H_
#define _SHADER_PROGRAM_H_

class VertexShader;
class PixelShader;
class Matrix4x4;
class Vector3;

class ShaderProgram
{
public:
    ShaderProgram(void);
    ~ShaderProgram(void);

    void Init(VertexShader* vs, PixelShader* ps);
    void Bind();
    void UnBind();

    void SetWVP(const Matrix4x4& wvp);
    void SetNormalMatrix(const Matrix4x4& wvp);

    uint GetGLProgram() { return mProgram; }

private:
    uint    mProgram;

    int     mWVP;
    int     mNormalMatrix;
};

#endif // _SHADER_PROGRAM_H_