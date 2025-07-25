#include "Title.h"

void Title::Init()
{
	m_titleTex.Load("Asset/Textures/title.png");
}

void Title::Update()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 || GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		if (!m_isKey)
		{
			m_isKey = true;
		}
		m_isPush = true;
	}
	else m_isKey = false;

	if (m_isPush)
	{
		m_wait++;
		if (m_wait >= 120)
		{
			m_isGameStart = true;
		}
	}

	m_mWorld = Math::Matrix::CreateTranslation(m_pos);
}

void Title::DrawSprite()
{
	if (m_isPush)
	{
		m_Alpha -= 0.013f;
		if (m_Alpha <= 0.0f)m_Alpha = 0.0f;
	}
	DirectX::SimpleMath::Color _color = { 1,1,1,m_Alpha };

	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_titleTex, m_pos.x, m_pos.y, 1280, 720,nullptr,&_color);

}
