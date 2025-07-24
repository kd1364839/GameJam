#include "Stone.h"
#include"../BasePiece.h"

void Stone::Init()
{
	BasePiece::Init();

	m_spModel->Load("Asset/Models/Piece/Haku/Haku.gltf");

	m_type = PieceTypeNo::STONE;

	KdEffekseerManager::GetInstance().Create(1280, 720);
}

void Stone::Update()
{

	if (m_pos.y < 0)m_isExpired = true;

	m_rotateX += m_spinSpeed.x;
	m_rotateY += m_spinSpeed.y;
	m_rotateZ += m_spinSpeed.z;

	if (m_rotateX > 360) m_rotateX -= 360;
	if (m_rotateY > 360) m_rotateY -= 360;
	if (m_rotateZ > 360) m_rotateZ -= 360;

	if (GetAsyncKeyState('Q') & 0x8000) {
		if (!m_keyFlg) {
			//m_velocity = { 0.0f, 0.0f, 4.0f }; 
			m_velocity.x = KdRandom::GetFloat(-0.2f, 0.2f);
			m_velocity.y = KdRandom::GetFloat(0.0f, 0.2f);

			m_velocity.z = 5.0f;
			m_gravity -= 0.02f;

			KdEffekseerManager::GetInstance().Play(
				"RockTrail2.efkefc",
				m_pos,
				1.0f,
				1.0f,
				false);

			//m_rotateX = static_cast<float>(rand() % 360);
			m_rotateX = KdRandom::GetFloat(0, 360);
			m_rotateY = KdRandom::GetFloat(0, 360);
			m_rotateZ = KdRandom::GetFloat(0, 360);

			m_spinSpeed = {
			KdRandom::GetFloat(-30.0f, 30.0f), // -25 to +25
			KdRandom::GetFloat(-30.0f, 30.0f),
			KdRandom::GetFloat(-30.0f, 30.0f)
			};
			m_keyFlg = true;
		}
	}
	else {
		m_keyFlg = false;
	}

	m_velocity.y += m_gravity;

	m_pos += m_velocity;

	KdEffekseerManager::GetInstance().SetPos(0, m_pos);

	//Math::Matrix rotateXMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(90));
	Math::Matrix rotateXMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_rotateX));
	Math::Matrix rotateYMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rotateY));
	Math::Matrix rotateZMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_rotateZ));
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = rotateZMat * rotateXMat * rotateYMat * transMat;

	KdEffekseerManager::GetInstance().Update();
}

void Stone::DrawEffect()
{
	KdEffekseerManager::GetInstance().Draw();
}
