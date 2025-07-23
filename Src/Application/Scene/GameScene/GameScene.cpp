#include "GameScene.h"
#include"../SceneManager.h"
//置物
#include"../../GameObject/Desk/Desk.h"

#include"../../GameObject/Piece/PieceManager.h"
#include"../../GameObject/Piece/Bomb/Bomb.h"
#include"../../GameObject/Piece/Haku/Haku.h"

void GameScene::Event()
{
	//カメラ
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_cameraPos);
	Math::Matrix rotMat = Math::Matrix::CreateRotationX(
		DirectX::XMConvertToRadians(25));
	Math::Matrix worldMat = rotMat * transMat;
	m_camera->SetCameraMatrix(worldMat);
}

void GameScene::Init()
{
	//カメラ
	m_camera = std::make_unique<KdCamera>();
	m_cameraPos = { 0,100,-70 };

	//机
	std::shared_ptr<Desk>desk;
	desk = std::make_shared<Desk>();
	desk->Init();
	AddObject(desk);

	//牌マネージャー
	m_pieceManager = std::make_shared<PieceManager>();
	m_pieceManager->Init();
	AddObject(m_pieceManager);

	std::shared_ptr<Bomb>bomb;
	for (int i = 0; i < 4; i++) {
		bomb = std::make_shared<Bomb>();
		bomb->Init();
		bomb->SetPos(Math::Vector3(-10 + (i * 5), 90, 0));
		AddObject(bomb);
		m_pieceManager->AddPiece(bomb);
	}

	std::shared_ptr<Haku>haku;
	for (int i = 0; i < 4; i++) {
		haku = std::make_shared<Haku>();
		haku->Init();
		haku->SetPos(Math::Vector3(-10 + (i * 5), 100, 0));
		AddObject(haku);
		m_pieceManager->AddPiece(haku);
	}
	std::vector<std::weak_ptr<KdGameObject>> a = m_pieceManager->GetPiece();
}
