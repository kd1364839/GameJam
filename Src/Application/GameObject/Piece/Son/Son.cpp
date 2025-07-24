#include "Son.h"
#include"../BasePiece.h"

void Son::Init()
{
	BasePiece::Init();

	m_spModel->Load("Asset/Models/Piece/Son/Son.gltf");

	m_type = PieceTypeNo::SON;

	m_pCollider = std::make_unique<KdCollider>();//生成
	m_pCollider->RegisterCollisionShape(//判定情報を登録
		"Son",				//登録名
		m_spModel,			//モデルデータ(拡大も加味される)
		KdCollider::TypeGround);//判定種類
}
