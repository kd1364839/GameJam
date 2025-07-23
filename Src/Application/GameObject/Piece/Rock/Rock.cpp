#include "Rock.h"
#include"../BasePiece.h"

void Rock::Init()
{
	BasePiece::Init();

	m_spModel->Load("Asset/Models/Piece/Haku/Haku.gltf");

	m_type = PieceTypeNo::ROCK;

	m_velocity = { 0.0f, 0.0f, 4.0f }; 

	KdEffekseerManager::GetInstance().Create(1280,720);

	KdEffekseerManager::GetInstance().Play(
		"RockTrail2.efkefc",
		m_pos,
		1.0f,
		1.0f,
		false);

}

void Rock::Update()
{

	if (m_pos.y < 0)m_isExpired = true;

	// Accelerate slowly
	//const float acceleration = 0.01f; // Tune this for desired acceleration
	//m_speed += acceleration;

	//// Move forward in world Z+ direction
	//m_pos.z += m_speed;

	// Apply gravity to vertical (Y) velocity
	m_velocity.y += m_gravity;

	// Apply velocity to position
	m_pos += m_velocity;

	KdEffekseerManager::GetInstance().SetPos(0,m_pos);

	Math::Matrix rotateMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(90));
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = rotateMat * transMat;

	KdEffekseerManager::GetInstance().Update();
}

void Rock::DrawEffect()
{
	KdEffekseerManager::GetInstance().Draw();
}
