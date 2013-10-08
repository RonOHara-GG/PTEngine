#include "..\PTEngine.h"
#include "..\Material.h"
#include "RendererOGL.h"
#include "VertexBufferOGL.h"
#include "IndexBufferOGL.h"
#include "TextureOGL.h"
#include "ShaderProgram.h"

#define ATTRIB_POSITION     0
#define ATTRIB_NORMAL       1
#define ATTRIB_COLOR        2
#define ATTRIB_UV0          3

GLenum sOGLPrimTypes[] = { GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_LINES };

RendererOGL::RendererOGL(void)
{
    mCurrentIndexBuffer = 0;
    mCurrentMaterial = 0;
    mSpriteMaterial = 0;
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

void RendererOGL::SetProjectionMatrix(const Matrix4x4& projection)
{
    mProjectionMatrix = projection;
    float whole = ceilf(mProjectionMatrix.mC.mZ);
    float frac = mProjectionMatrix.mC.mZ - whole;
    mProjectionMatrix.mC.mZ = whole + (frac * 2);
    mProjectionMatrix.mD.mZ *= 2;

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

VertexProfile* RendererOGL::CreateVertexProfile(const VertexBuffer** vertexBuffers, int numVertexBuffers)
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

Texture* RendererOGL::CreateTexture(DDS* textureFile, uint dataSize)
{
    TextureOGL* tex = new TextureOGL();
    if( !tex->Init(textureFile) )
    {
        delete tex;
        tex = 0;
    }

    return tex;
}

Material* RendererOGL::SetMaterial(Material* material, const Matrix4x4& ltw)
{
    Material* old = mCurrentMaterial;

    if( old )
    {
        ShaderProgram* oldProgram = (ShaderProgram*)old->GetProgram();
        if( oldProgram )
        {
            oldProgram->UnBind();
        }
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(ltw);

    Matrix4x4 wvp = ltw * mViewProjectionMatrix;    
    
    if( material )
    {
        ShaderProgram* program = (ShaderProgram*)material->GetProgram();
        if( !program )
        {
            program = new ShaderProgram();
            program->Init(material->GetVertexShader(), material->GetPixelShader());
            material->SetProgram(program);
        }
        program->Bind();

        program->SetWVP(wvp);
        program->SetNormalMatrix(ltw);

        Vector3 lightDir(1, 1, 0);
        lightDir.Normalize();
        int loc = glGetUniformLocation(program->GetGLProgram(), "lightDir");
        if( loc >= 0 )
            glUniform3f(loc, lightDir.mX, lightDir.mY, lightDir.mZ);

        loc = glGetUniformLocation(program->GetGLProgram(), "textureSampler");
        if( loc >= 0 )
            glUniform1i(loc, 0);
    }

    mCurrentMaterial = material;
    return old;
}

Material* RendererOGL::SetSpriteMaterial(Material* material)
{
    Material* old = mSpriteMaterial;
    mSpriteMaterial = material;

    Material* current = mCurrentMaterial;
    Matrix4x4 ltw;
    SetMaterial(mSpriteMaterial, ltw);
    SetMaterial(current, ltw);

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
            GLint location = element.mUsage;
            glEnableVertexAttribArray(location);
            glVertexAttribPointer(location, VertexFormat::GetDataSizeOfType(element.mType) / 4, GL_FLOAT, GL_FALSE, format.GetSize(), (const GLvoid*)offset);
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

void RendererOGL::Draw(int vertexCount, int primitiveCount, ePrimitiveType primitiveType)
{
    if( mCurrentIndexBuffer )
    {
        glDrawElements(sOGLPrimTypes[primitiveType], mCurrentIndexBuffer->GetIndexCount(), mCurrentIndexBuffer->IsSixteenBit() ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, 0);   
    }
    else
    {
        glDrawArrays(sOGLPrimTypes[primitiveType], 0, vertexCount);
    }
}

void RendererOGL::DrawSprites(Texture* texture, int numSprites, VertexBuffer* vb)
{
    // Bind the sprite material
    Matrix4x4 ltw;
    Material* currentMaterial = SetMaterial(mSpriteMaterial, ltw);

    // Bind the vertex buffer
    VertexBuffer* currentVB = SetVertexBuffer(0, vb);

    // Clear the index buffer
    IndexBuffer* currentIB = SetIndexBuffer(0);

    // Bind the texture
    TextureOGL* oglTex = (TextureOGL*)texture;
    oglTex->Bind();
    
    // Draw the sprites
    Draw(numSprites * 6, numSprites * 2, ePT_Triangles);

    // Restore the old material
    SetVertexBuffer(0, currentVB);
    SetIndexBuffer(currentIB);
    SetMaterial(currentMaterial, ltw);
}

void RendererOGL::EnableDepthTest(bool enable)
{
    if( enable )
        glEnable(GL_DEPTH);
    else
        glDisable(GL_DEPTH);
}

void RendererOGL::SetCullMode(eCullMode cullMode)
{    
    if( cullMode == eCM_None )
        glDisable(GL_CULL_FACE);
    else
    {
        glEnable(GL_CULL_FACE);
        glCullFace(cullMode == eCM_Clockwise ? GL_CW : GL_CCW);
    }
}