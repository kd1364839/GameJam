#include "BasePiece.h"
#include"PieceManager.h"

void BasePiece::Init()
{
	m_spModel = std::make_shared<KdModelData>();

	m_pos = PieceMountPos;

	m_destinationPos = m_pos;
}

void BasePiece::Update()
{
	m_scale = 1.0f;
	if (m_selectFlg)m_scale = 1.5f;

	m_moveFlg = false;
	if (m_pos != m_destinationPos) {
		m_moveFlg = true;

		Math::Vector3 moveDir = m_destinationPos - m_pos;

		if (moveDir.Length() <= m_speed) {
			m_pos = m_destinationPos;
			if (m_pos.y <= PieceMountPos.y)//戻った先が山かどうか
			{
				KdAudioManager::Instance().Play("Asset/Data/Sound/MahjongMoundHit.wav", false);//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			}
		}
		else {
			moveDir.Normalize();
			moveDir *= m_speed;
			m_pos += moveDir;
		}
	}

	int _rot = 0;
	if (m_handPieceFlg && !m_playerHandFlg)_rot = 180;

	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_scale);
	Math::Matrix rotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(_rot));
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = scaleMat * rotMat * transMat;
}

void BasePiece::DrawLit()
{
	if (!m_spModel)return;
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}
