#include "Stone.h"
#include"../BasePiece.h"

void Stone::Init()
{
	BasePiece::Init();

	m_spModel->Load("Asset/Models/Piece/Stone/Stone.gltf");

	m_type = PieceTypeNo::STONE;

	//KdEffekseerManager::GetInstance().Create(1280, 720);

	m_pCollider = std::make_unique<KdCollider>();//生成
	m_pCollider->RegisterCollisionShape(//判定情報を登録
		"Stone",				//登録名
		m_spModel,			//モデルデータ(拡大も加味される)
		KdCollider::TypeGround);//判定種類

	m_tPolygon.SetMaterial("Asset/Textures/jet.png");
}

void Stone::Update()
{
	// When effect mode is active
	if (m_effectFlg) {

		// Spin
		m_rotateX += m_spinSpeed.x;
		m_rotateY += m_spinSpeed.y;

		// Keep angles in 0–360 range
		if (m_rotateX > 360) m_rotateX -= 360;
		if (m_rotateY > 360) m_rotateY -= 360;

		// Movement forward with gravity
		m_velocity.z = 10.0f;
		m_gravity -= 0.02f;
		m_velocity.y += m_gravity;

		m_pos += m_velocity;

		// World matrix
		Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
		Math::Matrix rotateXMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_rotateX));
		Math::Matrix rotateYMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rotateY));
		Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
		m_mWorld = scaleMat * rotateXMat * rotateYMat * transMat;

		m_tPolygon.AddPoint(m_mWorld);

		// When past a certain Z, reset
		if (m_pos.z > 200)
		{
			m_pos = PieceMountPos;
			m_destinationPos = m_pos;

			m_effectFlg = false;

			// Reset rotation and movement
			m_rotateX = 0;
			m_rotateY = 0;
			m_velocity = {};
			m_gravity = 0;
		}
	}
	else {
		// If not in effect mode, do base behavior
		BasePiece::Update();

		// Reset world matrix (BasePiece does it too but ok to be safe)
		Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
		Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
		m_mWorld = scaleMat * transMat;
	}
}

void Stone::DrawEffect()
{
	KdEffekseerManager::GetInstance().Draw();
}

void Stone::DrawBright()
{
	if (m_effectFlg) {
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_tPolygon);
	}
}
