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

	Math::Vector3 pPos = { 0,100,-70 };
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

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{	
		m_cameraPos += moveDir* dist* m_camSpeed;
	}



	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_cameraPos);
	Math::Matrix rotMat = Math::Matrix::CreateRotationX(
		DirectX::XMConvertToRadians(25));
	Math::Matrix rotMat2 = Math::Matrix::CreateRotationY(
		DirectX::XMConvertToRadians(dist*0.1));
	Math::Matrix worldMat = rotMat * rotMat2 * transMat;
	m_camera->SetCameraMatrix(worldMat);

}

void GameScene::Init()
{
	//カメラ
	m_camera = std::make_unique<KdCamera>();
	//m_cameraPos = { 0,100,-70 };
	m_cameraPos = { -100,200,-270 };

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
