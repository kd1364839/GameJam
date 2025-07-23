#include "BasePiece.h"
#include"PieceManager.h"

void BasePiece::Init()
{
	m_spModel = std::make_shared<KdModelData>();

	m_pos = PieceMountPos;
}

void BasePiece::Update()
{
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = transMat;
}

void BasePiece::DrawLit()
{
	if (!m_spModel)return;
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}
