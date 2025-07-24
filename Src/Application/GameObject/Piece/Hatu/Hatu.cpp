#include "Hatu.h"
#include"../BasePiece.h"

void Hatu::Init()
{
	BasePiece::Init();

	m_spModel->Load("Asset/Models/Piece/Hatu/Hatu.gltf");

	m_type = PieceTypeNo::HATU;

	m_pCollider = std::make_unique<KdCollider>();//生成
	m_pCollider->RegisterCollisionShape(//判定情報を登録
		"Hatu",				//登録名
		m_spModel,			//モデルデータ(拡大も加味される)
		KdCollider::TypeGround);//判定種類
}
