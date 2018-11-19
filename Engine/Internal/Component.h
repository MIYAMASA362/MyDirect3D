//
//	Component.h
//		Author:HIROMASA IKEDA	DATE:2018/09/26
//===============================================
//
//	今後使うかも
//
//-----------------------------------------------
#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include<d3dx9.h>
#include<vector>

using namespace std;

//===============================================
//	Component 部品クラス
//===============================================
class Component 
{
private:
	
public:
	static vector<Component*> g_Index;	//インデックス

	Component();

protected:

};

#endif // !COMPONENT_H

