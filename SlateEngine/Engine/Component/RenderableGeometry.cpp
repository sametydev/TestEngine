#include <SlateEngine/Engine/Component/RenderableGeometry.h>

RenderableGeometry::RenderableGeometry()
{

}

RenderableGeometry::~RenderableGeometry()
{
}
void RenderableGeometry::OnInternalInit()
{

    //Create our Vertex Buffer
    m_vertexBuffer = new DXVertexBuffer();

    //Create our Index Buffer
    m_indexBuffer = new DXIndexBuffer();

    SetBuffer(BuiltInMesh::CreateBox<VertexPNT>());


    m_objectConstantBuffer = new DXConstantBuffer();

    ObjectConstantBufferObject.world = mat4x4();
    ObjectConstantBufferObject.worldInverseTranspose = mat4x4();

    ObjectConstantBufferObject.material.ambient = vec4f(0.5f, 0.5f, 0.5f, 1.0f);
    ObjectConstantBufferObject.material.diffuse = vec4f(1.0f, 1.0f, 1.0f, 1.0f);
    ObjectConstantBufferObject.material.specular = vec4f(0.1f, 0.1f, 0.1f, 5.0f);

    //Create Vertex Shader 3D
    vertexShader3D = new DXVertexShader();
    vertexShader3D->Compile(L"Shaders\\TexturedLit\\Lit3DVS.cso", L"Shaders\\TexturedLit\\Lit3DVS.hlsl", "main");
    vertexShader3D->CreateInputLayout(VertexPNT::inputLayout, ARRAYSIZE(VertexPNT::inputLayout));

    //Create Pixel Shader 3D
    pixelShader3D = new DXPixelShader();
    pixelShader3D->Compile(L"Shaders\\TexturedLit\\Lit3DPS.cso", L"Shaders\\TexturedLit\\Lit3DPS.hlsl", "main");

    ConstantBufferDesc cbd{};
    cbd.cbSize = sizeof(ObjectConstantBuffer);
    m_objectConstantBuffer->Create(cbd);

    m_objectConstantBuffer->BindVS(0);
    m_objectConstantBuffer->BindPS(0);

    vertexShader3D->Bind();
    pixelShader3D->Bind();


    //Calling Update once
    OnUpdate(0);
}

void RenderableGeometry::SetTexture(DXTexture* texture)
{
    texture->Bind(0);
}


void RenderableGeometry::OnUpdate(float deltaTime)
{
    ObjectConstantBufferObject.world = connectedEntity->GetComponent<Transform>().GetGlobal();
    ObjectConstantBufferObject.worldInverseTranspose = connectedEntity->GetComponent<Transform>().GetGlobal();

    m_objectConstantBuffer->Map(sizeof(ObjectConstantBuffer), &ObjectConstantBufferObject);
    m_objectConstantBuffer->UnMap();
}

void RenderableGeometry::OnRender()
{
    m_vertexBuffer->BindPipeline(0);
    m_indexBuffer->BindPipeline(0);
    vertexShader3D->Bind();
    vertexShader3D->UpdateInputLayout();
    pixelShader3D->Bind();
    m_objectConstantBuffer->BindVS(0);
    m_objectConstantBuffer->BindPS(0);

    DXApplication::Instance->GetDXContext().Get()->DrawIndexed(m_indices, 0, 0);
}