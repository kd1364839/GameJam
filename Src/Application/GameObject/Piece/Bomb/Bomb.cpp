#include "Bomb.h"
#include"../BasePiece.h"

void Bomb::Init()
{
	BasePiece::Init();

	m_spModel->Load("Asset/Models/Piece/Bomb/Bomb.gltf");

	m_type = PieceTypeNo::BOMB;

	KdEffekseerManager::GetInstance().Create(1280, 720);

	m_pCollider = std::make_unique<KdCollider>();//生成
	m_pCollider->RegisterCollisionShape(//判定情報を登録
		"Bomb",				//登録名
		m_spModel,			//モデルデータ(拡大も加味される)
		KdCollider::TypeGround);//判定種類

	m_keyFlg = false;
}

void Bomb::Update()
{
	KdEffekseerManager::GetInstance().Update();

	if (m_effectFlg) {
		
			KdEffekseerManager::GetInstance().Play(
				"Explosion.efkefc",
				m_pos,
				1.0f,
				0.3f,
				false);
			m_effectFlg = false;

			KdAudioManager::Instance().Play("Asset/Data/Sound/Explosion.wav", false);//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	}

	

	BasePiece::Update();
}

void Bomb::DrawEffect()
{
	KdEffekseerManager::GetInstance().Draw();
}
