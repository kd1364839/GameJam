#include "Stone.h"
#include"../BasePiece.h"

void Stone::Init()
{
	BasePiece::Init();

	m_spModel->Load("Asset/Models/Piece/Stone/Stone.gltf");

	m_type = PieceTypeNo::STONE;

	KdEffekseerManager::GetInstance().Create(1280, 720);

	m_pCollider = std::make_unique<KdCollider>();//生成
	m_pCollider->RegisterCollisionShape(//判定情報を登録
		"Stone",				//登録名
		m_spModel,			//モデルデータ(拡大も加味される)
		KdCollider::TypeGround);//判定種類
}

void Stone::Update()
{
	if (m_effectFlg) {
		if (m_pos.y < 0)
		{
			m_pos = PieceMountPos;
			m_destinationPos = m_pos;

			m_effectFlg = false;
		}

		if (m_effectInitFlg) {
			KdEffekseerManager::GetInstance().Play(
				"RockTrail2.efkefc",
				m_pos,
				1.0f,
				1.0f,
				false);

			m_effectInitFlg = false;
		}

		m_rotateX += m_spinSpeed.x;
		m_rotateY += m_spinSpeed.y;

		if (m_rotateX > 360) m_rotateX -= 360;
		if (m_rotateY > 360) m_rotateY -= 360;

		//m_velocity = { 0.0f, 0.0f, 4.0f }; 
		m_velocity.x = KdRandom::GetFloat(-0.2f, 0.2f);
		m_velocity.y = KdRandom::GetFloat(0.0f, 0.2f);

		m_velocity.z = 5.0f;
		m_gravity -= 0.02f;

		//m_rotateX = static_cast<float>(rand() % 360);
		m_rotateX = KdRandom::GetFloat(0, 360);
		m_rotateY = KdRandom::GetFloat(0, 360);

		m_spinSpeed = {
		KdRandom::GetFloat(-30.0f, 30.0f), // -25 to +25
		KdRandom::GetFloat(-30.0f, 30.0f),
		KdRandom::GetFloat(-30.0f, 30.0f)
		};

		m_velocity.y += m_gravity;

		m_pos += m_velocity;

		KdEffekseerManager::GetInstance().SetPos(0, m_pos);
	}
	else {
		BasePiece::Update();

		m_rotateX = 0;
		m_rotateY = 0;
	}

	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	Math::Matrix rotateXMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_rotateX));
	Math::Matrix rotateYMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rotateY));
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = scaleMat * rotateXMat * rotateYMat * transMat;

	KdEffekseerManager::GetInstance().Update();
}

void Stone::DrawEffect()
{
	KdEffekseerManager::GetInstance().Draw();
}
