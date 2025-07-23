#include "Haku.h"
#include"../BasePiece.h"

void Haku::Init()
{
	BasePiece::Init();

	m_spModel->Load("Asset/Models/Piece/Haku/Haku.gltf");

	m_type = PieceTypeNo::HAKU;
}

void Haku::Update()
{

	BasePiece::Update();
}
