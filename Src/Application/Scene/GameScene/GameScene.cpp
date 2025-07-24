#include "GameScene.h"
#include"../SceneManager.h"
//置物
#include"../../GameObject/Desk/Desk.h"

#include"../../GameObject/Piece/PieceManager.h"
#include"../../GameObject/Piece/East/East.h"
#include"../../GameObject/Piece/West/West.h"
#include"../../GameObject/Piece/South/South.h"
#include"../../GameObject/Piece/North/North.h"
#include"../../GameObject/Piece/Haku/Haku.h"
#include"../../GameObject/Piece/Hatu/Hatu.h"
#include"../../GameObject/Piece/Tyun/Tyun.h"
#include"../../GameObject/Piece/Bomb/Bomb.h"
#include"../../GameObject/Piece/Son/Son.h"
#include"../../GameObject/Piece/Stone/Stone.h"
#include"../../GameObject/Piece/Win/Win.h"

void GameScene::Event()
{
	//カメラ
	Math::Vector3 pPos = { 0,110,-90 };
	Math::Vector3 move;
	Math::Vector3 moveDir;
	moveDir.x = pPos.x - m_cameraPos.x;
	moveDir.y = pPos.y - m_cameraPos.y;
	moveDir.z = pPos.z - m_cameraPos.z;

	moveDir.Normalize();

	move.x = pPos.x - m_cameraPos.x;
	move.y = pPos.y - m_cameraPos.y;
	move.z = pPos.z - m_cameraPos.z;

	float dist = sqrt(move.y * move.y + move.x * move.x + move.z * move.z);

	m_cameraPos += moveDir * dist * m_camSpeed;

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_cameraPos);
	Math::Matrix rotMat = Math::Matrix::CreateRotationX(
		DirectX::XMConvertToRadians(25));
	Math::Matrix rotMat2 = Math::Matrix::CreateRotationY(
		DirectX::XMConvertToRadians(dist * 0.1));
	Math::Matrix worldMat = rotMat * rotMat2 * transMat;
	m_camera->SetCameraMatrix(worldMat);


	KdShaderManager::Instance().WorkAmbientController().
		AddPointLight(
			Math::Vector3(10, 10, 10),
			50,
			m_cameraPos + Math::Vector3(0, -20, 0)
		);
}

void GameScene::Init()
{
	//カメラ
	m_camera = std::make_shared<KdCamera>();
	m_cameraPos = { -100,200,-270 };

	KdEffekseerManager::GetInstance().SetCamera(m_camera);

	//机
	std::shared_ptr<Desk>desk;
	desk = std::make_shared<Desk>();
	desk->Init();
	AddObject(desk);

	//牌マネージャー
	m_pieceManager = std::make_shared<PieceManager>();

	std::shared_ptr<East>east;
	for (int i = 0; i < 3; i++) {
		east = std::make_shared<East>();
		east->Init();
		AddObject(east);
		m_pieceManager->AddPiece(east);
	}

	std::shared_ptr<West>west;
	for (int i = 0; i < 3; i++) {
		west = std::make_shared<West>();
		west->Init();
		AddObject(west);
		m_pieceManager->AddPiece(west);
	}

	std::shared_ptr<South>south;
	for (int i = 0; i < 3; i++) {
		south = std::make_shared<South>();
		south->Init();
		AddObject(south);
		m_pieceManager->AddPiece(south);
	}

	std::shared_ptr<North>north;
	for (int i = 0; i < 3; i++) {
		north = std::make_shared<North>();
		north->Init();
		AddObject(north);
		m_pieceManager->AddPiece(north);
	}

	std::shared_ptr<Haku>haku;
	for (int i = 0; i < 3; i++) {
		haku = std::make_shared<Haku>();
		haku->Init();
		AddObject(haku);
		m_pieceManager->AddPiece(haku);
	}

	std::shared_ptr<Hatu>hatu;
	for (int i = 0; i < 20; i++) {
		hatu = std::make_shared<Hatu>();
		hatu->Init();
		AddObject(hatu);
		m_pieceManager->AddPiece(hatu);
	}

	std::shared_ptr<Tyun>tyun;
	for (int i = 0; i < 3; i++) {
		tyun = std::make_shared<Tyun>();
		tyun->Init();
		AddObject(tyun);
		m_pieceManager->AddPiece(tyun);
	}

	std::shared_ptr<Bomb>bomb;
	for (int i = 0; i < 20; i++) {
		bomb = std::make_shared<Bomb>();
		bomb->Init();
		AddObject(bomb);
		m_pieceManager->AddPiece(bomb);
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
