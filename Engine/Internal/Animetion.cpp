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
#include"Animetion.h"
#include"CAnimetion.h"

//==============================================
//	グローバル変数宣言
//==============================================
static int g_FrameCounter;	//・フレームカウンタ

//===============================================
//	フレーム設定
//===============================================
void Animetion_Initialize()
{
	g_FrameCounter = 0;
}

//===============================================
//	フレーム取得	
//===============================================
int Animetion_GetFrame()
{
	return g_FrameCounter;
}

//===============================================
//	フレーム更新
//===============================================
void Animetion_Update()
{
	g_FrameCounter++;
}

//===============================================
//	アニメーション NOLOOP
//===============================================
bool Animetion_NoLoop(Transform2* pTransform,Texture* pTexture,Animetion* pAnimetion)
{
	float width  = (float)pTexture->GetWidth();
	float height = (float)pTexture->GetHeight();

	pAnimetion->AnimePatern  = min((g_FrameCounter / pAnimetion->Waitframe),pAnimetion->MaxPatern);

	Texture Tex = *pTexture;
	Tex.TexCoord = { pTexture->TexScale.width * (pAnimetion->AnimePatern % pAnimetion->YMaxPatern),pTexture->TexScale.height * (pAnimetion->AnimePatern / pAnimetion->YMaxPatern) };
	Render2D_Texture_Clip(pTransform,&Tex);

	return pAnimetion->AnimePatern >= pAnimetion->MaxPatern;
}

//===============================================
//	アニメーション LOOP
//===============================================
void Animetion_Loop(Transform2* pTransform,Texture* pTexture,Animetion* pAnimetion)
{
	float width  = (float)pTexture->GetWidth();
	float height = (float)pTexture->GetHeight();

	pAnimetion->AnimePatern = (g_FrameCounter / pAnimetion->Waitframe) % pAnimetion->MaxPatern;

	Texture Tex = *pTexture;
	Tex.TexCoord = { pTexture->TexScale.width * (pAnimetion->AnimePatern % pAnimetion->YMaxPatern),pTexture->TexScale.height * (pAnimetion->AnimePatern / pAnimetion->YMaxPatern) };
	Render2D_Texture_Clip(pTransform,&Tex);
}

//===============================================
//	回転アニメーション
//===============================================
void Animetion_Loop_Rotate(Transform2* pTransform,Texture* pTexture,Animetion* pAnimetion)
{
	float width  = (float)pTexture->GetWidth();
	float height = (float)pTexture->GetHeight();

	pAnimetion->AnimePatern = (g_FrameCounter / pAnimetion->Waitframe) % pAnimetion->MaxPatern;

	Texture Tex = *pTexture;
	Tex.TexCoord = { pTexture->TexScale.width * (pAnimetion->AnimePatern % pAnimetion->YMaxPatern),pTexture->TexScale.height * (pAnimetion->AnimePatern / pAnimetion->YMaxPatern) };
	Render2D_Sprite_Rotate(pTransform,&Tex);
}

//===============================================
//	スコアアニメーション
//===============================================
void Animetion_Score(Transform2* pTransform,Texture* pTexture,Animetion* pAnimetion, int Score, bool bLeft, bool bZero, int digitNum)
{
	int digit = 0, MaxScore = 1;
	TEXCOORD AnimeTex = {};

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
			Texture AnimeTex = *pTexture;

			int AnimePatern = Score % 10;
			AnimeTex.TexCoord = { pTexture->TexScale.width * (AnimePatern % pAnimetion->YMaxPatern), pTexture->TexScale.height *(AnimePatern / pAnimetion->YMaxPatern) };
			transform2.Position = { position.x - (pTransform->Scale.x * 0.5f),position.y };
			Render2D_Sprite(&transform2,&AnimeTex);
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
			Texture AnimeTex = *pTexture;
			
			int AnimePatern = Score % 10;
			AnimeTex.TexCoord = { pTexture->TexScale.width * (AnimePatern % pAnimetion->YMaxPatern),pTexture->TexScale.height *(AnimePatern / pAnimetion->YMaxPatern) };
			transform2.Position = { position.x - (pTransform->Scale.x * 0.75f),position.y };
			Render2D_Sprite(&transform2,&AnimeTex);
			Score /= 10;
			digit--;
		}
	}
}
