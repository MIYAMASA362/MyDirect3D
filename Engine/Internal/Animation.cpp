//
//	Animetion.cpp
//		Author:HIROMASA IKEDA	DATE:2018/09/28
//===============================================
#include<d3dx9.h>
#include<math.h>

#include"Texture.h"
#include"CTexture.h"
#include"CTransform.h"
#include"Sprite.h"
#include"Animation.h"
#include"CAnimation.h"

//==============================================
//	グローバル変数宣言
//==============================================
static int g_FrameCounter;	//・フレームカウンタ

//===============================================
//	フレーム設定
//===============================================
void Animation_Initialize()
{
	g_FrameCounter = 0;
}

//===============================================
//	フレーム取得	
//===============================================
int Animation_GetFrame()
{
	return g_FrameCounter;
}

//===============================================
//	フレーム更新
//===============================================
void Animation_Update()
{
	g_FrameCounter++;
}

//===============================================
//	アニメーション NOLOOP
//===============================================
bool Animation_NoLoop(Transform2* pTransform,Texture* pTexture,Animation* pAnimetion)
{
	float width  = (float)pTexture->GetWidth();
	float height = (float)pTexture->GetHeight();

	pAnimetion->AnimaPatern  = min((g_FrameCounter / pAnimetion->Waitframe),pAnimetion->MaxPatern);

	Texture Tex = *pTexture;
	Tex.TexCoord = { pTexture->TexScale.width * (pAnimetion->AnimaPatern % pAnimetion->YMaxPatern),pTexture->TexScale.height * (pAnimetion->AnimaPatern / pAnimetion->YMaxPatern) };
	Render2D_Texture_Clip(pTransform,&Tex);

	return pAnimetion->AnimaPatern >= pAnimetion->MaxPatern;
}

//===============================================
//	アニメーション LOOP
//===============================================
void Animation_Loop(Transform2* pTransform,Texture* pTexture,Animation* pAnimetion)
{
	float width  = (float)pTexture->GetWidth();
	float height = (float)pTexture->GetHeight();

	pAnimetion->AnimaPatern = (g_FrameCounter / pAnimetion->Waitframe) % pAnimetion->MaxPatern;

	Texture Tex = *pTexture;
	Tex.TexCoord = { pTexture->TexScale.width * (pAnimetion->AnimaPatern % pAnimetion->YMaxPatern),pTexture->TexScale.height * (pAnimetion->AnimaPatern / pAnimetion->YMaxPatern) };
	Render2D_Texture_Clip(pTransform,&Tex);
}

//===============================================
//	回転アニメーション
//===============================================
void Animation_Loop_Rotate(Transform2* pTransform,Texture* pTexture,Animation* pAnimetion)
{
	float width  = (float)pTexture->GetWidth();
	float height = (float)pTexture->GetHeight();

	pAnimetion->AnimaPatern = (g_FrameCounter / pAnimetion->Waitframe) % pAnimetion->MaxPatern;

	Texture Tex = *pTexture;
	Tex.TexCoord = { pTexture->TexScale.width * (pAnimetion->AnimaPatern % pAnimetion->YMaxPatern),pTexture->TexScale.height * (pAnimetion->AnimaPatern / pAnimetion->YMaxPatern) };
	Render2D_Sprite_Rotate(pTransform,&Tex);
}

//===============================================
//	スコアアニメーション
//===============================================
void Animation_Score(Transform2* pTransform,Texture* pTexture,Animation* pAnimetion, int Score, bool bLeft, bool bZero, int digitNum)
{
	int digit = 0, MaxScore = 1;
	TEXCOORD AnimaTex = {};

	//桁取得
	for (digit = 0; digit < digitNum; digit++)
	{
		MaxScore *= 10;
	}

	//カウントオーバー
	if (Score >= MaxScore)
	{
		Score = MaxScore - 1;
	}

	//左詰め
	if (bLeft)
	{
		//桁数取得
		digit = 0;
		for (int score = Score; score > 0; digit++)
		{
			score /= 10;
		}

		//左詰め
		D3DXVECTOR2 position = { pTransform->Position.x + (pTransform->Scale.x * 0.5f) * digit,pTransform->Position.y };
		while (digit > 0)
		{
			Transform2 transform2 = *pTransform;
			Texture AnimaTex = *pTexture;

			int AnimePatern = Score % 10;
			AnimaTex.TexCoord = { pTexture->TexScale.width * (AnimePatern % pAnimetion->YMaxPatern), pTexture->TexScale.height *(AnimePatern / pAnimetion->YMaxPatern) };
			transform2.Position = { position.x - (pTransform->Scale.x * 0.5f),position.y };
			Render2D_Sprite(&transform2,&AnimaTex);
			Score /= 10;
			digit--;
		}
	}
	//右詰め
	else
	{
		//位置決め
		D3DXVECTOR2 position( (pTransform->Scale.x * 0.7f) * digit,pTransform->Position.y );

		//0埋め
		if (!bZero)
		{
			digit = 0;
			int score = Score;
			do
			{
				score /= 10;
				digit++;
			} while (score > 0);
		}
		//右詰め
		while (digit > 0)
		{
			Transform2 transform2 = *pTransform;
			Texture AnimaTex = *pTexture;
			
			int AnimaPatern = Score % 10;
			AnimaTex.TexCoord = { pTexture->TexScale.width * (AnimaPatern % pAnimetion->YMaxPatern),pTexture->TexScale.height *(AnimaPatern / pAnimetion->YMaxPatern) };
			transform2.Position = { position.x - (pTransform->Scale.x * 0.75f),position.y };
			Render2D_Sprite(&transform2,&AnimaTex);
			Score /= 10;
			digit--;
		}
	}
}
