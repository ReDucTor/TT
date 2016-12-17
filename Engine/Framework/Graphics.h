/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Graphics.h																			  *
*	Copyright 2016 PlanetChili <http://www.planetchili.net>								  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#pragma once

#include "TextSurface.h"
#include <d3d11.h>
#include <wrl.h>
#include "ChiliException.h"
#include "Colors.h"

#define CHILI_GFX_EXCEPTION( hr,note ) Graphics::Exception( hr,note,_CRT_WIDE(__FILE__),__LINE__ )

class Graphics
{
public:
	class Exception : public ChiliException
	{
	public:
		Exception(HRESULT hr, const std::wstring& note, const wchar_t* file, unsigned int line);
		std::wstring GetErrorName() const;
		std::wstring GetErrorDescription() const;
		virtual std::wstring GetFullMessage() const override;
		virtual std::wstring GetExceptionType() const override;
	private:
		HRESULT hr;
	};
private:
	// vertex format for the framebuffer fullscreen textured quad
	struct FSQVertex
	{
		float x, y, z;		// position
		float u, v;			// texcoords
	};
public:
	Graphics(class HWNDKey& key, unsigned int width, unsigned int height);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	void EndFrame();
	void BeginFrame();
	void PutPixel(int x, int y, int r, int g, int b)
	{
		PutPixel(x, y, { unsigned char(r),unsigned char(g),unsigned char(b) });
	}
	void PutPixel(int x, int y, Color c)
	{
		sysBuffer.PutPixel(x, y, c);
	}
	void DrawSprite(int dstX, int dstY, const Surface& surf);
	void DrawSpriteAlfa(int dstX, int dstY, const Surface& surf);
	void DrawText(const std::wstring& string, const Vec2& pt, const TextSurface::Font& font, Color c)
	{
		sysBuffer.DrawString(string, pt, font, c);
	}
	void DrawClipText(const std::wstring& string, const RectF& pt, const TextSurface::Font& font, Color c)
	{
		sysBuffer.DrawClipString(string, pt, font, c);
	}
	void DrawText(const std::string& string, const Vec2& pt, const TextSurface::Font& font, Color c)
	{
		std::wstring str(string.begin(), string.end());
		sysBuffer.DrawString(str, pt, font, c);
	}
	void DrawClipText(const std::string& string, const RectF& pt, const TextSurface::Font& font, Color c)
	{
		std::wstring str(string.begin(), string.end());
		sysBuffer.DrawClipString(str, pt, font, c);
	}
	RectF MeasureString(const std::string& str, int length, const TextSurface::Font& font, const RectF rect) {
		std::wstring string(str.begin(), str.end());
		return sysBuffer.MeasureString(string, length, font, rect);
	}
	RectF MeasureString(const std::wstring& str, int length, const TextSurface::Font& font, const RectF rect) {
		return sysBuffer.MeasureString(str, length, font, rect);
	}
	~Graphics();
private:
	unsigned int ScreenWidth;
	unsigned int ScreenHeight;
private:
	Microsoft::WRL::ComPtr<IDXGISwapChain>				pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11Device>				pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>			pImmediateContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		pRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				pSysBufferTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	pSysBufferTextureView;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>			pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				pVertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11SamplerState>			pSamplerState;
	D3D11_MAPPED_SUBRESOURCE							mappedSysBufferTexture;
	TextSurface                                         sysBuffer;
};
