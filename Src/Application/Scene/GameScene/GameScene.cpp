#include "GameScene.h"
#include"../SceneManager.h"
//置物
#include"../../GameObject/Desk/Desk.h"

#include"../../GameObject/Piece/PieceManager.h"
#include"../../GameObject/Piece/Bomb/Bomb.h"
#include"../../GameObject/Piece/Haku/Haku.h"
#include"../../GameObject/Piece/Son/Son.h"
#include"../../GameObject/Piece/Stone/Stone.h"
#include"../../GameObject/Piece/Win/Win.h"

void GameScene::Event()
{
	//カメラ
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_cameraPos);
	Math::Matrix rotMat = Math::Matrix::CreateRotationX(
		DirectX::XMConvertToRadians(25));
	Math::Matrix worldMat = rotMat * transMat;
	m_camera->SetCameraMatrix(worldMat);

	//KdShaderManager::Instance().WorkAmbientController().
	//	AddPointLight(
	//		Math::Vector3(10, 10, 10),
	//		10,
	//		m_cameraPos //+ Math::Vector3(0, -1.0f, 0)
	//	);
}

void GameScene::Init()
{
	//カメラ
	m_camera = std::make_shared<KdCamera>();
	m_cameraPos = { 0,110,-90 };

	//机
	std::shared_ptr<Desk>desk;
	desk = std::make_shared<Desk>();
	desk->Init();
	AddObject(desk);

	//牌マネージャー
	m_pieceManager = std::make_shared<PieceManager>();

	std::shared_ptr<Bomb>bomb;
	for (int i = 0; i < 3; i++) {
		bomb = std::make_shared<Bomb>();
		bomb->Init();
		AddObject(bomb);
		m_pieceManager->AddPiece(bomb);
	}

	std::shared_ptr<Haku>haku;
	for (int i = 0; i < 3; i++) {
		haku = std::make_shared<Haku>();
		haku->Init();
		AddObject(haku);
		m_pieceManager->AddPiece(haku);
	}

	std::shared_ptr<Son>son;
	for (int i = 0; i < 3; i++) {
		son = std::make_shared<Son>();
		son->Init();
		AddObject(son);
		m_pieceManager->AddPiece(son);
	}

	std::shared_ptr<Stone>stone;
	for (int i = 0; i < 3; i++) {
		stone = std::make_shared<Stone>();
		stone->Init();
		AddObject(stone);
		m_pieceManager->AddPiece(stone);
	}

	std::shared_ptr<Win>win;
	for (int i = 0; i < 3; i++) {
		win = std::make_shared<Win>();
		win->Init();
		AddObject(win);
		m_pieceManager->AddPiece(win);
	}

	m_pieceManager->Init();
	m_pieceManager->SetCamera(m_camera);
	AddObject(m_pieceManager);
}
