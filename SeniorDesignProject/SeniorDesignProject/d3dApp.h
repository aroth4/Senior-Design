#ifndef D3DAPP_H
#define D3DAPP_H

#pragma comment (lib, "D3D10_1.lib")
#pragma comment (lib, "DXGI.lib")
#pragma comment (lib, "D2D1.lib")
#pragma comment (lib, "dwrite.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <xnamath.h>
#include <D3D10_1.h>
#include <DXGI.h>
#include <D2D1.h>
#include <sstream>
#include <dwrite.h>
#include <dinput.h>
#include <vector>
#include "Stats.h"
#include "Weapon.h"
#include "Biped.h"
#include "Sounds.h"
#include <string>

#include "Struct.h"

class D3DApp
{
protected:
	//Player Init
	Stats Player1;
	Weapon PlayerWep;
	Biped thePlayer;
	Biped enemies[20];
	bool reloadBro = false;
	Settings* _settings;

	Position playerLoc;
	LPCWSTR WndClassName;	//Define our window class name
	HWND hwnd;	//Sets our windows handle to NULL
	HRESULT hr;

	int Width;	//window width
	int Height;	//window height

	DIMOUSESTATE mouseLastState;
	LPDIRECTINPUT8 DirectInput;

	float rotx;
	float rotz;
	float scaleX;
	float scaleY;

	Struct::cbPerObject cbPerObj;
	Struct::Light light;
	Struct::cbPerFrame constbuffPerFrame;
	std::vector<Struct::SurfaceMaterial> material;

	double countsPerSecond = 0.0;
	__int64 CounterStart = 0;

	int frameCount = 0;
	int fps = 0;

	__int64 frameTimeOld = 0;
	double frameTime;

	UINT numElements;

	///////////////**************new**************////////////////////
	bool isShoot;

	int ClientWidth;
	int ClientHeight;

	int score;
	float pickedDist;
	float pickedDist2;
	float pickedDist3;
	float pickedDist4;
	float pickedDist5;
	float pickedDist6;
	float pickedDist7;
	float pickedDist8;
	float pickedDist9;
	float pickedDist10;
	
	///////////////**************new**************////////////////////

	D3D11_VIEWPORT mScreenViewport;
	HINSTANCE		mhAppInst;

	IDXGISwapChain* SwapChain;
	ID3D11Device* d3d11Device;
	ID3D11DeviceContext* d3d11DevCon;
	ID3D11RenderTargetView* renderTargetView;
	ID3D11Buffer* squareIndexBuffer;
	ID3D11DepthStencilView* depthStencilView;
	ID3D11Texture2D* depthStencilBuffer;
	ID3D11Buffer* squareVertBuffer;
	ID3D11VertexShader* VS;
	ID3D11PixelShader* PS;
	ID3D11PixelShader* D2D_PS;
	ID3D10Blob* D2D_PS_Buffer;
	ID3D10Blob* VS_Buffer;
	ID3D10Blob* PS_Buffer;
	ID3D11InputLayout* vertLayout;
	ID3D11Buffer* cbPerObjectBuffer;
	ID3D11BlendState* d2dTransparency;
	ID3D11RasterizerState* CCWcullMode;
	ID3D11RasterizerState* CWcullMode;
	ID3D11ShaderResourceView* CubesTexture;
	ID3D11SamplerState* CubesTexSamplerState;
	ID3D11Buffer* cbPerFrameBuffer;

	ID3D10Device1 *d3d101Device;
	IDXGIKeyedMutex *keyedMutex11;
	IDXGIKeyedMutex *keyedMutex10;
	ID2D1RenderTarget *D2DRenderTarget;
	ID2D1SolidColorBrush *Brush;
	ID3D11Texture2D *BackBuffer11;
	ID3D11Texture2D *sharedTex11;
	ID3D11Buffer *d2dVertBuffer;
	ID3D11Buffer *d2dIndexBuffer;
	ID3D11ShaderResourceView *d2dTexture;
	IDWriteFactory *DWriteFactory;
	IDWriteTextFormat *TextFormat;

	IDirectInputDevice8* DIKeyboard;
	IDirectInputDevice8* DIMouse;

	//Sounds 

	ID3D11DepthStencilState* DSLessEqual;
	ID3D11RasterizerState* RSCullNone;

	ID3D11BlendState* Transparency;

	std::wstring printText;

public:
	D3DApp(HINSTANCE hInstance);
	virtual ~D3DApp();

	virtual LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//Initialize our window
	bool InitializeWindow();

	//Main part of the program
	int messageloop();

	bool InitDirectInput(HINSTANCE hInstance);
	virtual void DetectInput(double time) = 0;

	//Main windows function
	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);

	bool InitializeDirect3d11App(HINSTANCE hInstance);
	virtual bool InitScene() = 0;
	virtual void UpdateScene(double time) = 0;
	virtual void DrawScene() = 0;
	virtual void RenderText(std::wstring text, int inInt) = 0;

	bool InitD2D_D3D101_DWrite(IDXGIAdapter1 *Adapter);
	void InitD2DScreenTexture();

	void StartTimer();
	double GetTime();
	double GetFrameTime();
};

#endif // D3DAPP_H