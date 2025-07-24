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
}

void Bomb::Update()
{
	BasePiece::Update();

	if (!m_isExpired) {
		if (GetAsyncKeyState('P') & 0x8000) {
			if (!m_keyFlg) {
				KdEffekseerManager::GetInstance().Play(
					"Explosion.efkefc",
					m_pos,
					1.0f,
					1.0f,
					false);
				m_keyFlg = true;
				m_deskExplosionActive = true;
			}
		}
		else {
			m_keyFlg = false;
		}

		//const int ExplosionTriggerFrame = 60;
		const int endFrame = 150;

		if (m_deskExplosionActive)
		{
			m_deskExplosionTimer++;
			bool Once = false;
			if (!Once) {
				m_explosionSequence = {
		{ KdRandom::GetInt(60,120), {KdRandom::GetFloat(-30,30), 90,  KdRandom::GetFloat(-60,0)}},
		{ KdRandom::GetInt(60,120), {KdRandom::GetFloat(-30,30), 90,  KdRandom::GetFloat(-60,0)} },
		{ KdRandom::GetInt(60,120), { KdRandom::GetFloat(-30,30), 90,  KdRandom::GetFloat(-60,0)} },
		{ KdRandom::GetInt(60,120), {   KdRandom::GetFloat(-30,30), 90,  KdRandom::GetFloat(-60,0)} },
		{ KdRandom::GetInt(60,120), {  KdRandom::GetFloat(-30,30), 90,  KdRandom::GetFloat(-60,0)} },
		{ KdRandom::GetInt(60,120), {  KdRandom::GetFloat(-30,30), 90,  KdRandom::GetFloat(-60,0)} },
		{ KdRandom::GetInt(60,120), {  KdRandom::GetFloat(-30,30), 90,  KdRandom::GetFloat(-60,0)} },
		{ KdRandom::GetInt(60,120), {  KdRandom::GetFloat(-30,30), 90,  KdRandom::GetFloat(-60,0)} },
		{ KdRandom::GetInt(60,120), {  KdRandom::GetFloat(-30,30), 90,  KdRandom::GetFloat(-60,0)} },
		{ KdRandom::GetInt(60,120), {  KdRandom::GetFloat(-30,30), 90,  KdRandom::GetFloat(-60,0)} },
		{ KdRandom::GetInt(60,120), {  KdRandom::GetFloat(-30,30), 90,  KdRandom::GetFloat(-60,0)} },
				};
				Once = true;
			}

			for (const auto& explosion : m_explosionSequence)
			{
				if (m_deskExplosionTimer == explosion.frame)
				{
					KdEffekseerManager::GetInstance().Play(
						"Explosion.efkefc",
						explosion.pos,
						3.0f,
						0.1f,
						false
					);
				}
			}

			if (m_deskExplosionTimer >= 130) {

			}

			if (m_deskExplosionTimer >= endFrame)
			{
				m_deskExplosionActive = false;
				m_deskExplosionTimer = 0;


			}
		}
	}

	//if (GetAsyncKeyState('O') & 0x8000) {
	//	if (!m_keyFlg1) {
	//		
	//		m_keyFlg1 = true;
	//	}
	//}
	//else {
	//	m_keyFlg1 = false;
	//}

	KdEffekseerManager::GetInstance().Update();

}

void Bomb::DrawEffect()
{
	KdEffekseerManager::GetInstance().Draw();
}
