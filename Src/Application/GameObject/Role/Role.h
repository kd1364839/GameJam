#pragma once

class Role : public KdGameObject
{
public:
	Role() {}
	~Role() {}

	void Init()override;
	void Update()override;
	void DrawSprite()override;

	POINT GetMousePos();

private:

	KdTexture     m_Role1Tex;
	KdTexture     m_Role2Tex;
	KdTexture     m_Role3Tex;
	Math::Vector3 m_pos;

	int m_roleType = 1;
	bool m_isKey = false;

	//ボタン関係
	KdTexture     m_LButtonTex;
	KdTexture     m_RButtonTex;
	Math::Vector3 m_Lpos;
	Math::Vector3 m_Rpos;
	int           m_buttonRad = 40;
	bool          m_isRButton = true;
	bool          m_isLButton = false;

	bool          m_isCheck   = false;
	
};
