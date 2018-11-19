//
//	UI.cpp
//		Author:HIROMASA IKEDA		DATE:2018/08/28
//===============================================
#include<d3dx9.h>
#include"CUI.h"
#include"input.h"

//===============================================
//	UI クラス
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
UI::UI(Transform2* pTransform2, Texture* pTexture):Sprite(pTransform2, pTexture)
{
}

UI::UI(Transform2* pTransform2, Texture* pTexture, Animation* pAnimation): Sprite(pTransform2, pTexture, pAnimation)
{
	
}

//-------------------------------------
//	Set()
//-------------------------------------
void UI::Set(Transform2* pTransform2)
{
	this->render.pTransform = pTransform2;
}

//-------------------------------------
//	Click()
//-------------------------------------
bool UI::Click()
{
	if (Hover() && Mouse_IsLeftDown())
	{
		return true;
	}
	return false;
}

//-------------------------------------
//	Hover
//-------------------------------------
bool UI::Hover()
{

	if (this->transform.Position.x - this->transform.Scale.x * 0.5f <= Mouse_IsMouseX() && Mouse_IsMouseX() <= this->transform.Position.x + this->transform.Scale.x * 0.5f)
	{
		if (this->transform.Position.y - this->transform.Scale.y * 0.5f <= Mouse_IsMouseY() && Mouse_IsMouseY() <= this->transform.Position.y + this->transform.Scale.x * 0.5f)
		{
			return true;
		}
	}

	return false;
}
