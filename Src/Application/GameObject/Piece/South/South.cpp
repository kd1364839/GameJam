#include "South.h"
#include"../BasePiece.h"

void South::Init()
{
	BasePiece::Init();

	m_spModel->Load("Asset/Models/Piece/South/South.gltf");

	m_type = PieceTypeNo::SOUTH;

	m_pCollider = std::make_unique<KdCollider>();//生成
	m_pCollider->RegisterCollisionShape(//判定情報を登録
		"South",				//登録名
		m_spModel,			//モデルデータ(拡大も加味される)
		KdCollider::TypeGround);//判定種類
}
