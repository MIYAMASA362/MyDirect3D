//
//	Collision.cpp
//		USER:HIROMASA IKEDA		DATE:2018/07/03
//===============================================
#include"common.h"
#include"Debug_Circle.h"
#include"Collision.h"

//===============================================
//	Collsiion ÉNÉâÉX
//===============================================
Collision::Collision()
{
	trigger = false;
}

//===============================================
//	Physics	ÉNÉâÉX
//===============================================

//-------------------------------------
//	Physics()
//-------------------------------------
Physics::Physics()
{
	Force = {0,0};
	velocity = {0,0};
}

//-------------------------------------
//	Update()
//-------------------------------------
void Physics::Update(float Speed)
{
	D3DXVec2Normalize(&Force,&Force);

	pTransform2->Position += Force * Speed;

	Force = {0,0};
}

//-------------------------------------
//	Update(D3DXVECTOR Speed)
//-------------------------------------
void Physics::Update(D3DXVECTOR2 Speed)
{
	D3DXVec2Normalize(&Force, &Force);

	pTransform2->Position.x += Force.x * Speed.x;
	pTransform2->Position.y += Force.y * Speed.y;

	Force = { 0,0 };
}

//-------------------------------------
//	Collision_Hit(const Collision* pCollision)
//-------------------------------------
HIT_PORTION Physics::Collision_Hit(const Collision* pCollision)
{
	D3DXVECTOR2 Diffrence(0, 0);
	HIT_PORTION Hit = NONE;

	for (int i = 0; i < (int)this->pCollision->BoxIndex.size(); i++)
	{
		Box pBox_A = *this->pCollision->BoxIndex.at(i);
		pBox_A.Scale.height *= 0.5f;
		pBox_A.Scale.width *= 0.5f;

		for (int j = 0; j < (int)pCollision->BoxIndex.size(); j++)
		{
			Box pBox_B = *pCollision->BoxIndex.at(j);
			pBox_B.Scale.height *= 0.5f;
			pBox_B.Scale.width *= 0.5f;

			//Xé≤
			if (pBox_A.Center.x + pBox_A.Scale.width >= pBox_B.Center.x - pBox_B.Scale.width && pBox_A.Center.x - pBox_A.Scale.width <= pBox_B.Center.x + pBox_B.Scale.width)
			{
				//Yé≤
				if (pBox_A.Center.y + pBox_A.Scale.height >= pBox_B.Center.y - pBox_B.Scale.height && pBox_A.Center.y - pBox_A.Scale.height <= pBox_B.Center.y + pBox_B.Scale.height)
				{
					//PhysicsîªíËÇµÇ»Ç¢
					if (pCollision->trigger || this->pCollision->trigger)
					{
						Hit = HIT;
					}
					//PhysicsîªíËÇ∑ÇÈ
					else
					{

						//â∫Ç…Player
						if (pBox_A.Center.y + pBox_A.Scale.height > pBox_B.Center.y + pBox_B.Scale.height)
						{
							Diffrence.y -= (pBox_A.Center.y - pBox_A.Scale.height) - (pBox_B.Center.y + pBox_B.Scale.height);
							Hit = BOTTOM;
						}
						//è„Ç…Player
						else if (pBox_A.Center.y - pBox_A.Scale.height < pBox_B.Center.y - pBox_B.Scale.height)
						{
							Diffrence.y -= (pBox_A.Center.y + pBox_A.Scale.height) - (pBox_B.Center.y - pBox_B.Scale.height);
							Hit = TOP;
							UseGravity = false;
						}
						else
						{
							//ç∂Ç…Player
							if (pBox_A.Center.x - pBox_A.Scale.width < pBox_B.Center.x - pBox_B.Scale.width)
							{
								Diffrence.x -= (pBox_A.Center.x + pBox_A.Scale.width) - (pBox_B.Center.x - pBox_B.Scale.width);
								Hit = LEFT;
							}
							//âEÇ…Player
							else if (pBox_A.Center.x + pBox_A.Scale.width > pBox_B.Center.x + pBox_B.Scale.width)
							{
								Diffrence.x -= (pBox_A.Center.x - pBox_A.Scale.width) - (pBox_B.Center.x + pBox_B.Scale.width);
								Hit = RIGHT;
							}
						}
					}
					
				}
			}
		}
	}

	pTransform2->Position += Diffrence;

	return Hit;
}

//***********************************************
//	Ç†ÇΩÇËîªíËÅ@â~
//***********************************************
bool Collision_Hit(const Circle *pCircle_A,const Circle *pCircle_B) 
{
	float Hit_distance = pCircle_A->radius + pCircle_B->radius;

	float Glodal_distance =
		(pCircle_A->Center.x - pCircle_B->Center.x) *
		(pCircle_A->Center.x - pCircle_B->Center.x) +
		(pCircle_A->Center.y - pCircle_B->Center.y) *
		(pCircle_A->Center.y - pCircle_B->Center.y);

	return Glodal_distance < (Hit_distance * Hit_distance);
}	

//***********************************************
//	Ç†ÇΩÇËîªíËÅ@â~Å~éläp
//***********************************************
bool Collision_Hit(const Circle *pCircle_A, const Box *pBox_B)
{
	//â°Ç≈ÇÃìñÇΩÇËãóó£
	float Hit_distanceX = pCircle_A->radius + pBox_B->Scale.width * 0.5f;
	Hit_distanceX = Hit_distanceX * Hit_distanceX;

	//ècÇ≈ÇÃìñÇΩÇËãóó£
	float Hit_distanceY = pCircle_A->radius + pBox_B->Scale.height*0.5f;
	Hit_distanceY = Hit_distanceY * Hit_distanceY;

	float Global_distanceX = (pCircle_A->Center.x - pBox_B->Center.x) * (pCircle_A->Center.x - pBox_B->Center.x);
	float Global_distanceY = (pCircle_A->Center.y - pBox_B->Center.y) * (pCircle_A->Center.y - pBox_B->Center.y);

	if (Global_distanceX <= Hit_distanceX && Global_distanceY <= Hit_distanceY) return true;
	return false;
}

//***********************************************
//	Ç†ÇΩÇËîªíËÅ@éläpÅ~éläp
//***********************************************
bool Collision_Hit(const Box *pBox_A, const Box *pBox_B)
{
	float Hit_distanceX = pBox_A->Scale.width + pBox_B->Scale.width*0.5f;
	float Hit_distanceY = pBox_A->Scale.height + pBox_B->Scale.height*0.5f;

	float Global_distanceX = (pBox_A->Center.x - pBox_B->Center.x) * (pBox_A->Center.x - pBox_B->Center.x);
	float Global_distanceY = (pBox_A->Center.y - pBox_B->Center.y) * (pBox_A->Center.y - pBox_B->Center.y);

	if (Global_distanceX < Hit_distanceX * Hit_distanceX && Global_distanceY < Hit_distanceY * Hit_distanceY)
	{
		return true;
	}
	
	return false;
}

//===============================================
//	Ç†ÇΩÇËîªíË3D
//===============================================
