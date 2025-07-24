#include "North.h"
#include"../BasePiece.h"

void North::Init()
{
	BasePiece::Init();

	m_spModel->Load("Asset/Models/Piece/North/North.gltf");

	m_type = PieceTypeNo::NORTH;

	m_pCollider = std::make_unique<KdCollider>();//生成
	m_pCollider->RegisterCollisionShape(//判定情報を登録
		"North",				//登録名
		m_spModel,			//モデルデータ(拡大も加味される)
		KdCollider::TypeGround);//判定種類
}
