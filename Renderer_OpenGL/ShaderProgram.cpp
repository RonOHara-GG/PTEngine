#include "..\PTEngine.h"
#include "..\VertexFormat.h"
#include "..\Matrix4x4.h"
#include "ShaderProgram.h"
#include "gl.h"


ShaderProgram::ShaderProgram(void)
{
    mProgram = 0;

}

ShaderProgram::~ShaderProgram(void)
{
    if( mProgram )
        glDeleteObjectARB(mProgram);
    mProgram = 0;
}

void ShaderProgram::Init(VertexShader* vs, PixelShader* ps)
{
    mProgram = glCreateProgramObjectARB();
    glAttachObjectARB(mProgram, (GLhandleARB)vs);
    glAttachObjectARB(mProgram, (GLhandleARB)ps);
    glLinkProgramARB(mProgram);



    mWVP = glGetUniformLocation(mProgram, "WorldViewProjection");
    mNormalMatrix = glGetUniformLocation(mProgram, "NormalMatrix");
}

void ShaderProgram::Bind()
{
    glUseProgramObjectARB(mProgram);
}

void ShaderProgram::UnBind()
{
    // Unbind the shader program
    glUseProgramObjectARB(0);

    // Clear all used vertex inputs
    for( int i = 0; i < VertexFormat::eVU_Last; i++ )
    {
        glDisableVertexAttribArray(i);
    }
}

void ShaderProgram::SetWVP(const Matrix4x4& wvp)
{
    if( mWVP >= 0 )
        glUniformMatrix4fv(mWVP, 1, false, wvp);
}

void ShaderProgram::SetNormalMatrix(const Matrix4x4& nmtx)
{
    if( mNormalMatrix >= 0 )
    {
        float normalMatrix[9] = {nmtx.mA.mX, nmtx.mA.mY, nmtx.mA.mZ,
                                 nmtx.mB.mX, nmtx.mB.mY, nmtx.mB.mZ,
                                 nmtx.mC.mX, nmtx.mC.mY, nmtx.mC.mZ};
        glUniformMatrix3fv(mNormalMatrix, 1, false, normalMatrix);
    }
}