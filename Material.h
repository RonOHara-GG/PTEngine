#ifndef _MATERIAL_H_
#define _MATERIAL_H_

class VertexShader;
class PixelShader;

class Material : public OwnedObject
{
public:
    Material(void);
    ~Material(void);

    VertexShader* SetVertexShader(VertexShader* shader);
    VertexShader* GetVertexShader()                         { return mVertexShader; }

    PixelShader* SetPixelShader(PixelShader* shader);
    PixelShader* GetPixelShader()                           { return mPixelShader; }

protected:
    VertexShader* mVertexShader;
    PixelShader* mPixelShader;
};

#endif // _MATERIAL_H_

