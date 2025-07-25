#include "Role.h"
#include "../../main.h"

void Role::Init()
{
	m_Role1Tex.Load("Asset/Textures/Memo1.png");
	m_Role2Tex.Load("Asset/Textures/Memo2.png");
	m_Role3Tex.Load("Asset/Textures/Memo3.png");

	m_LButtonTex.Load("Asset/Textures/LButton.png");
	m_RButtonTex.Load("Asset/Textures/RButton.png");

	m_Lpos = { -590,0,0 };
	m_Rpos = {  590,0,0 };


}

void Role::Update()
{

	if (GetAsyncKeyState('1') & 0x8000)
	{
		m_isCheck = true;
	}
	if (GetAsyncKeyState('2') & 0x8000)
	{
		m_isCheck = false;
	}

	if (m_isCheck)
	{
		if (m_Rpos.x - m_buttonRad <= GetMousePos().x && GetMousePos().x <= m_Rpos.x + m_buttonRad &&
			m_Rpos.y - m_buttonRad <= GetMousePos().y && GetMousePos().y <= m_Rpos.y + m_buttonRad && m_roleType == 1)
		{
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				if (!m_isKey)
				{
					m_isKey = true;
					m_roleType = 2;
				}
			}
		}
		else if (m_Rpos.x - m_buttonRad <= GetMousePos().x && GetMousePos().x <= m_Rpos.x + m_buttonRad &&
			m_Rpos.y - m_buttonRad <= GetMousePos().y && GetMousePos().y <= m_Rpos.y + m_buttonRad && m_roleType == 2)
		{
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				if (!m_isKey)
				{
					m_isKey = true;
					m_roleType = 3;
				}
			}
		}
		else if (m_Lpos.x - m_buttonRad <= GetMousePos().x && GetMousePos().x <= m_Lpos.x + m_buttonRad &&
			m_Lpos.y - m_buttonRad <= GetMousePos().y && GetMousePos().y <= m_Lpos.y + m_buttonRad && m_roleType == 3)
		{
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				if (!m_isKey)
				{
					m_isKey = true;
					m_roleType = 2;
				}
			}
		}
		else if (m_Lpos.x - m_buttonRad <= GetMousePos().x && GetMousePos().x <= m_Lpos.x + m_buttonRad &&
			m_Lpos.y - m_buttonRad <= GetMousePos().y && GetMousePos().y <= m_Lpos.y + m_buttonRad && m_roleType == 2)
		{
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				if (!m_isKey)
				{
					m_isKey = true;
					m_roleType = 1;
				}
			}
		}
		else m_isKey = false;
	}

}

void Role::DrawSprite()
{
	if (m_isCheck)
	{
		switch (m_roleType)
		{
		case 1:
			KdShaderManager::Instance().m_spriteShader.DrawTex(&m_Role1Tex, 0, 0, 1100, 600);
			break;
		case 2:
			KdShaderManager::Instance().m_spriteShader.DrawTex(&m_Role2Tex, 0, 0, 1100, 600);
			break;
		case 3:
			KdShaderManager::Instance().m_spriteShader.DrawTex(&m_Role3Tex, 0, 0, 1100, 600);
			break;
		}
		if (m_roleType != 1)
		{
			KdShaderManager::Instance().m_spriteShader.DrawTex(&m_LButtonTex, m_Lpos.x, m_Lpos.y, 80, 80);
		}
		if (m_roleType != 3)
		{
			KdShaderManager::Instance().m_spriteShader.DrawTex(&m_RButtonTex, m_Rpos.x, m_Rpos.y, 80, 80);
		}
	}


}

POINT Role::GetMousePos()
{
	POINT mousePos;
	GetCursorPos(&mousePos);
	ScreenToClient(Application::Instance().GetWindowHandle(), &mousePos);
	mousePos.x -= 1280 / 2;
	mousePos.y -= 720 / 2;
	mousePos.y *= -1;
	return mousePos;
}
