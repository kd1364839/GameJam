#pragma once

class Title : public KdGameObject
{
public:
	Title() {}
	~Title() {}

	void Init()override;
	void Update()override;
	void DrawSprite()override;

	int GameStart() { return m_isGameStart; }

private:

	KdTexture     m_titleTex;
	Math::Vector3 m_pos;

	float         m_wait        = 0.0f;
	bool          m_isKey       = false;
	bool          m_isPush      = false;
	bool          m_isGameStart = false;

	float         m_Alpha       = 1.5f;
	bool          m_isAlphaMax  = false;
};