#include "Bomb.h"
#include"../BasePiece.h"

void Bomb::Init()
{
	BasePiece::Init();

	m_spModel->Load("Asset/Models/Piece/Bomb/Bomb.gltf");

	m_type = PieceTypeNo::BOMB;
}

void Bomb::Update()
{

	BasePiece::Update();
}
