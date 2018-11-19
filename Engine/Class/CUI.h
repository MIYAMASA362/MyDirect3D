//
//	UI.h
//		Author:HIROMASA IKEDA	DATE:2018/08/28
//===============================================
#pragma once

#ifndef UI_H
#define UI_H

#include<d3dx9.h>
#include"CTransform.h"
#include"CSprite.h"

//===============================================
//	UI クラス
//===============================================
class UI : public Sprite
{
private:
	
public:

	//コンストラクタ
	UI(Transform2* pTransform2, Texture* pTexture);
	UI(Transform2* pTransform2, Texture* pTexture, Animation* pAnimation);

	void Set(Transform2* pTransform2);
	bool Click();	//クリック時
	bool Hover();	//ホバー時
};

#endif // !UI_H
