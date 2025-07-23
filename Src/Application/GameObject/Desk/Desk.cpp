#include "Desk.h"

void Desk::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/Desk/Stage.gltf");

	Math::Matrix scaleMat = Math::Matrix::CreateScale(2);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(0, 0, 0);
	m_mWorld = scaleMat * transMat;
}

void Desk::DrawLit()
{
	if (!m_spModel)return;
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}
