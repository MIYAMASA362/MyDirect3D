//
//	DebuCircle.cpp
//		Author:YU NISHIMAKI		DATE:2018/10/18
//===============================================
#include<d3dx9.h>
#include"System.h"
#include"Debug_Sphere.h"


//===============================================
//	マクロ定義
//===============================================
#define CIRCLE_VERTEX_COUNT		(16)
#define CIRCLE_DRAW_MAX			(2048)


//===============================================
//	構造体
//===============================================
#define FVF_DEBUG_VERTEX	(D3DFVF_XYZ | D3DFVF_DIFFUSE)

//===============================================
//	グローバル変数
//===============================================

DebugBufferManager* DebugBufferManager::pInstance = NULL;


 LPDIRECT3DVERTEXBUFFER9 DebugBufferManager::pVertexBuffer;		// 頂点バッファ
 LPDIRECT3DINDEXBUFFER9 DebugBufferManager::pIndexBuffer;		// インデックスバッファ

 int DebugBufferManager::CircleCount = 0;
 DebugVertex* DebugBufferManager::pDebugCircleVertex;
 WORD* DebugBufferManager::pDebugCircleVertexIndex;
/* 
 * デストラクタ
 */
DebugBufferManager::~DebugBufferManager()
{
#if defined(_DEBUG) || defined(DEBUG)

	if( pIndexBuffer )
	{
		pIndexBuffer->Release();
		pIndexBuffer = NULL;
	}


	if( pVertexBuffer )
	{
		pVertexBuffer->Release();
		pVertexBuffer = NULL;
	}

#endif // _DEBUG || DEBUG
}

/*
 * 関数
 */
void DebugBufferManager::Init( void )
{
#if defined(_DEBUG) || defined(DEBUG)

	pInstance = new DebugBufferManager;
	LPDIRECT3DDEVICE9 pDevice = System_GetDevice();

	pDevice->CreateVertexBuffer( sizeof( DebugVertex ) * CIRCLE_VERTEX_COUNT * CIRCLE_DRAW_MAX, D3DUSAGE_WRITEONLY, FVF_DEBUG_VERTEX, D3DPOOL_MANAGED, &pVertexBuffer, NULL );

	pDevice->CreateIndexBuffer( sizeof( WORD ) * ( CIRCLE_VERTEX_COUNT * 2 ) * CIRCLE_DRAW_MAX, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pIndexBuffer, NULL );

	CircleCount = 0;

#endif // _DEBUG || DEBUG
}
void DebugBufferManager::Finalize( void )
{
	if( pIndexBuffer )
	{
		pIndexBuffer->Release();
		pIndexBuffer = NULL;
	}


	if( pVertexBuffer )
	{
		pVertexBuffer->Release();
		pVertexBuffer = NULL;
	}
	MessageBox( NULL, "DELETE", "ok ", MB_OK );
	delete pInstance;
	
}

//-------------------------------------
//	Sphere
//-------------------------------------
/*
 * 描画開始 : 終了
 */
void DebugBufferManager::Sphere_BatchBegin( void )
{
#if defined(_DEBUG) || defined(DEBUG)

	CircleCount = 0;

	pVertexBuffer->Lock( 0, 0, (void**) &pDebugCircleVertex, 0 );
	pIndexBuffer->Lock( 0, 0, (void**) &pDebugCircleVertexIndex, 0 );

#endif // _DEBUG || DEBUG
}

void DebugBufferManager::Sphere_BatchRun( void )
{
#if defined(_DEBUG) || defined(DEBUG)

	LPDIRECT3DDEVICE9 pDevice = System_GetDevice();

	D3DXMATRIX mtxTransform;
	D3DXMatrixIdentity( &mtxTransform );
	pDevice->SetTransform( D3DTS_WORLD, &mtxTransform );

	pVertexBuffer->Unlock();
	pIndexBuffer->Unlock();

	pDevice->SetTexture( 0, NULL );
	pDevice->SetFVF( FVF_DEBUG_VERTEX );
	pDevice->SetStreamSource( 0, pVertexBuffer, 0, sizeof( DebugVertex ) );
	pDevice->SetIndices( pIndexBuffer );
	pDevice->DrawIndexedPrimitive( D3DPT_LINELIST, 0, 0, CIRCLE_VERTEX_COUNT * CIRCLE_DRAW_MAX, 0, CircleCount * CIRCLE_VERTEX_COUNT * 3 );
#endif // _DEBUG || DEBUG
}


/*
 * Bufferへの座標登録関数
 */
void DebugBufferManager::BatchDrawSphere( const ShapeSphere *Sphere )
{
#if defined(_DEBUG) || defined(DEBUG)

	int n = CircleCount * CIRCLE_VERTEX_COUNT;

	const float s = D3DX_PI * 2 / CIRCLE_VERTEX_COUNT;

	for( int i = 0; i < CIRCLE_VERTEX_COUNT; i++ )
	{
		pDebugCircleVertex[ n + i ].position.x = (float) cos( i * s ) * Sphere->Radius + Sphere->Pos.x;
		pDebugCircleVertex[ n + i ].position.y = (float) sin( i * s ) * Sphere->Radius + Sphere->Pos.y;
		pDebugCircleVertex[ n + i ].position.z = Sphere->Pos.z;
		pDebugCircleVertex[ n + i ].color = D3DCOLOR_RGBA( 0, 255, 0, 255 );

		pDebugCircleVertexIndex[ n * 2 + i * 2 ] = (WORD) ( n + i );
		pDebugCircleVertexIndex[ n * 2 + i * 2 + 1 ] = (WORD) ( n + ( i + 1 ) % CIRCLE_VERTEX_COUNT );
	}

	CircleCount++;
	n += CIRCLE_VERTEX_COUNT;
	for( int i = 0; i < CIRCLE_VERTEX_COUNT; i++ )
	{
		pDebugCircleVertex[ n + i ].position.x = Sphere->Pos.x;
		pDebugCircleVertex[ n + i ].position.y = (float) cos( i * s ) * Sphere->Radius + Sphere->Pos.y;
		pDebugCircleVertex[ n + i ].position.z = (float) sin( i * s ) * Sphere->Radius + Sphere->Pos.z;
		pDebugCircleVertex[ n + i ].color = D3DCOLOR_RGBA( 0, 255, 0, 255 );

		pDebugCircleVertexIndex[ n * 2 + i * 2 ] = (WORD) ( n + i );
		pDebugCircleVertexIndex[ n * 2 + i * 2 + 1 ] = (WORD) ( n + ( i + 1 ) % CIRCLE_VERTEX_COUNT );
	}
	CircleCount++;
	n += CIRCLE_VERTEX_COUNT;
	for( int i = 0; i < CIRCLE_VERTEX_COUNT; i++ )
	{
		pDebugCircleVertex[ n + i ].position.x = (float) sin( i * s ) * Sphere->Radius + Sphere->Pos.x;
		pDebugCircleVertex[ n + i ].position.y = Sphere->Pos.y;
		pDebugCircleVertex[ n + i ].position.z = (float) cos( i * s ) * Sphere->Radius + Sphere->Pos.z;
		pDebugCircleVertex[ n + i ].color = D3DCOLOR_RGBA( 0, 255, 0, 255 );

		pDebugCircleVertexIndex[ n * 2 + i * 2 ] = (WORD) ( n + i );
		pDebugCircleVertexIndex[ n * 2 + i * 2 + 1 ] = (WORD) ( n + ( i + 1 ) % CIRCLE_VERTEX_COUNT );
	}

	CircleCount++;

#endif // _DEBUG || DEBUG
}
/*
//-------------------------------------
//	Cuboid
//-------------------------------------
void DebugBufferManager::Cuboid_BatchBegin( void )
{
#if defined(_DEBUG) || defined(DEBUG)

CuboidCount = 0;

pVertexBuffer->Lock( 0, 0, (void**) &pDebugCuboidVertex, 0 );
pIndexBuffer->Lock( 0, 0, (void**) &pDebugCuboidVertexIndex, 0 );

#endif // _DEBUG || DEBUG
}
void DebugBufferManager::Cuboid_BatchRun( void )

{
#if defined(_DEBUG) || defined(DEBUG)

LPDIRECT3DDEVICE9 pDevice = System_GetDevice();

D3DXMATRIX mtxTransform;
D3DXMatrixIdentity( &mtxTransform );
pDevice->SetTransform( D3DTS_WORLD, &mtxTransform );

pVertexBuffer->Unlock();
pIndexBuffer->Unlock();

pDevice->SetTexture( 0, NULL );
pDevice->SetFVF( FVF_DEBUG_VERTEX );
pDevice->SetStreamSource( 0, pVertexBuffer, 0, sizeof( DebugVertex ) );
pDevice->SetIndices( pIndexBuffer );
pDevice->DrawIndexedPrimitive( D3DPT_LINELIST, 0, 0, CIRCLE_VERTEX_COUNT * CIRCLE_DRAW_MAX, 0, CircleCount * CIRCLE_VERTEX_COUNT * 3 );


#endif // _DEBUG || DEBUG
}

///*
// * Bufferへの座標登録関数
    /
void DebugBufferManager::BatchDrawCuboid( const ShapeCuboid* Sphere )
{
#if defined(_DEBUG) || defined(DEBUG)
	// 未実装 --------------------------------------------------------------------------------------------------------------------------------------- NOT YET!>
#endif // _DEBUG || DEBUG 
}


*/