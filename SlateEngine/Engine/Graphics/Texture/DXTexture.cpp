#include <SlateEngine/Engine/Graphics/Texture/DXTexture.h>
#include <SlateEngine/Engine/Graphics/DXApplication.h>
#include <DirectXTex.h>
#include <DDSTextureLoader11.h>
#include <WICTextureLoader11.h>
#include <sstream>

DXTexture::DXTexture()
{
}

DXTexture::~DXTexture()
{
}

void DXTexture::Load(const wchar_t* filename)
{
	CreateDDSTextureFromFile(DXApplication::Instance->GetDXDevice().Get(), filename, nullptr, mSRV.GetAddressOf());

    ID3D11Resource* res = nullptr;
    mSRV.Get()->GetResource(&res);

    ID3D11Texture2D* texture2d = nullptr;
    HRESULT hr = res->QueryInterface(&texture2d);

    if (SUCCEEDED(hr))
    {
        D3D11_TEXTURE2D_DESC desc;
        texture2d->GetDesc(&desc);
        Width = desc.Width;
        Height = desc.Height;
    }

    SAFE_RELEASE(texture2d);
    SAFE_RELEASE(res);
}

void DXTexture::Bind(UINT slot)
{
	this->slot = slot;
	DXApplication::Instance->GetDXContext().Get()->PSSetShaderResources(slot, 1, mSRV.GetAddressOf());
}

void DXTexture::UnBind()
{
	ID3D11ShaderResourceView* clearView = nullptr;
	DXApplication::Instance->GetDXContext().Get()->PSSetShaderResources(slot, 1, &clearView);
}