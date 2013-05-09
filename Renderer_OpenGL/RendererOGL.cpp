#include "..\PTEngine.h"
#include "..\Material.h"
#include "RendererOGL.h"
#include "VertexBufferOGL.h"
#include "IndexBufferOGL.h"

#define ATTRIB_POSITION     0
#define ATTRIB_NORMAL       1
#define ATTRIB_COLOR        2
#define ATTRIB_UV0          3

GLenum sOGLPrimTypes[] = { GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_LINES };

RendererOGL::RendererOGL(void)
{
    mCurrentIndexBuffer = 0;
    mCurrentMaterial = 0;
}

RendererOGL::~RendererOGL(void)
{
	PlatformShutdown();
}

bool RendererOGL::Init(void* window, int width, int height, bool fullScreen)
{
    if( !PlatformInit(window, width, height, fullScreen) )
        return false;

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_CW);
	
    return true;
}

void RendererOGL::Shutdown()
{
}

void RendererOGL::BeginFrame()
{
}

void RendererOGL::EndFrame()
{
}

void RendererOGL::FinishFrame()
{
    PlatformFinishFrame();
}

void RendererOGL::SetViewport(const Box& viewSpace)
{
    mCurrentViewport = viewSpace;
    glViewport((GLint)viewSpace.mMin.mX, (GLint)viewSpace.mMin.mY, (GLsizei)viewSpace.mMax.mX, (GLsizei)viewSpace.mMax.mY);
}

const Box& RendererOGL::GetViewport()
{
    return mCurrentViewport;
}

void RendererOGL::SetViewMatrix(const Matrix4x4& view)
{
    mViewMatrix = view;
    UpdateViewProjection();
}

#undef malloc
#undef free
#include <Windows.h>
#include <gl/GLU.h>
#pragma comment (lib, "Glu32.lib")
void RendererOGL::SetProjectionMatrix(const Matrix4x4& projection)
{
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45, 853.0f / 480.0f, 0.01f, 10.0f);
    float mtx[16];
    glGetFloatv(GL_PROJECTION_MATRIX, mtx);

    mProjectionMatrix = projection;
    UpdateViewProjection();
}

void RendererOGL::UpdateViewProjection()
{
    glMatrixMode(GL_PROJECTION);

    mViewProjectionMatrix = mViewMatrix * mProjectionMatrix;
    glLoadMatrixf(mViewProjectionMatrix);
}

void RendererOGL::Clear(bool bClearColor, const RGBA& color, bool bClearDepth, float depthValue, bool bClearStencil, unsigned int stencilValue)
{
	GLbitfield clearBits = bClearColor ? GL_COLOR_BUFFER_BIT : 0;
	clearBits |= bClearDepth ? GL_DEPTH_BUFFER_BIT : 0;

	glClearColor(color.mRed, color.mGreen, color.mBlue, color.mAlpha);
	glClearDepth(depthValue);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool CompileShader(GLhandleARB shader, void* shaderData, uint shaderDataSize)
{
    glShaderSourceARB(shader, 1, (const GLcharARB**)&shaderData, (GLint*)&shaderDataSize);
    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if( status == GL_FALSE )
    {
        char log[16 * 1024];
        GLsizei length;
        glGetShaderInfoLog(shader, sizeof(log), &length, log);

        return false;
    }
    return true;
}

VertexShader* RendererOGL::CreateVertexShader(void* shaderData, uint shaderDataSize)
{
    GLhandleARB vs = glCreateShaderObjectARB(GL_VERTEX_SHADER);
    if( !CompileShader(vs, shaderData, shaderDataSize) )
    {
        glDeleteObjectARB(vs);
        return 0;
    }
    return (VertexShader*)vs;
}

PixelShader* RendererOGL::CreatePixelShader(void* shaderData, uint shaderDataSize)
{
    GLhandleARB ps = glCreateShaderObjectARB(GL_FRAGMENT_SHADER);
    if( !CompileShader(ps, shaderData, shaderDataSize) )
    {
        glDeleteObjectARB(ps);
        return 0;
    }
    return (PixelShader*)ps;
}

VertexProfile* RendererOGL::CreateVertexProfile(const DynamicArray<VertexBuffer*>& vertexBuffers)
{
    return 0;
}

VertexBuffer* RendererOGL::CreateVertexBuffer(int vertexCount, const VertexFormat& format, bool dynamic)
{
    VertexBufferOGL* vb = new VertexBufferOGL(vertexCount, format);
    return vb;
}

IndexBuffer* RendererOGL::CreateIndexBuffer(int indexCount, bool sixteenBit)
{
    IndexBufferOGL* ib = new IndexBufferOGL(indexCount, sixteenBit);
    return ib;
}

Material* RendererOGL::SetMaterial(Material* material, const Matrix4x4& ltw)
{
    Material* old = mCurrentMaterial;
    mCurrentMaterial = material;

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(ltw);

    Matrix4x4 wvp = ltw * mViewProjectionMatrix;

    void* program = material->GetProgram();
    if( !program )
    {
        GLhandleARB prg = glCreateProgramObjectARB();
        glAttachObjectARB(prg, (GLhandleARB)material->GetVertexShader());
        glAttachObjectARB(prg, (GLhandleARB)material->GetPixelShader());
        glLinkProgramARB(prg);
        program = (void*)prg;
        material->SetProgram(program);
    }
    glUseProgramObjectARB((GLhandleARB)program);

    GLint loc = glGetUniformLocation((GLint)program, "WorldViewProjection");
    glUniformMatrix4fv(loc, 1, false, wvp);

    loc = glGetUniformLocation((GLint)program, "normalMatrix");
    float normalMatrix[9] = {ltw.mA.mX, ltw.mA.mY, ltw.mA.mZ,
                             ltw.mB.mX, ltw.mB.mY, ltw.mB.mZ,
                             ltw.mC.mX, ltw.mC.mY, ltw.mC.mZ};
    glUniformMatrix3fv(loc, 1, false, normalMatrix);


    Vector3 lightDir(1, 1, 0);
    lightDir.Normalize();
    loc = glGetUniformLocation((GLint)program, "lightDir");
    glUniform3f(loc, lightDir.mX, lightDir.mY, lightDir.mZ);


    return old;
}

VertexProfile* RendererOGL::SetVertexProfile(VertexProfile* profile)
{
    return 0;
}

VertexBufferOGL* sVB = 0;
VertexBuffer* RendererOGL::SetVertexBuffer(uint index, VertexBuffer* vertexBuffer)
{
    uint bufferName = 0;
    VertexBufferOGL* vb = (VertexBufferOGL*)vertexBuffer;
    if( vb )
        bufferName = vb->GetBufferName();
    sVB = vb;
    
    glBindBuffer(GL_ARRAY_BUFFER, bufferName);
    if( vb )
    {
        int offset = 0;
        const VertexFormat& format = vb->GetVertexFormat();
        for( int i = 0; i < format.GetElementCount(); i++ )
        {
            const VertexFormat::VertexElement& element = format.GetElement(i);
            GLint location = -1;
            switch( element.mUsage )
            {
                case VertexFormat::eVU_Position:
                    location = glGetAttribLocation((GLuint)mCurrentMaterial->GetProgram(), "InPosition");;
                    break;
                case VertexFormat::eVU_Normal:
                    location = glGetAttribLocation((GLuint)mCurrentMaterial->GetProgram(), "InNormal");
                    break;
            }
            if( location >= 0 )
            {
                glEnableVertexAttribArray(location);
                glVertexAttribPointer(location, VertexFormat::GetDataSizeOfType(element.mType) / 4, GL_FLOAT, GL_FALSE, format.GetSize(), (const GLvoid*)offset);   
            }
            offset += VertexFormat::GetDataSizeOfType(element.mType);
        }
    }
    return 0;
}

IndexBuffer* RendererOGL::SetIndexBuffer(IndexBuffer* indexBuffer)
{
    IndexBuffer* current = mCurrentIndexBuffer;

    uint name = 0;
    IndexBufferOGL* ib = (IndexBufferOGL*)indexBuffer;
    if( ib )
        name = ib->GetBufferName();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, name);

    mCurrentIndexBuffer = ib;
    return current;
}

void RendererOGL::Draw(int primitiveCount, ePrimitiveType primitiveType)
{
}

void RendererOGL::DrawIndexed(int vertexCount, int primitiveCount, ePrimitiveType primitiveType)
{
    glDrawElements(sOGLPrimTypes[primitiveType], mCurrentIndexBuffer->GetIndexCount(), mCurrentIndexBuffer->IsSixteenBit() ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, 0);
}