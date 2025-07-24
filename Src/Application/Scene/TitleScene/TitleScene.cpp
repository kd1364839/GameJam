#include "TitleScene.h"
#include "../SceneManager.h"
#include"../../GameObject/Desk/Desk.h"

void TitleScene::Event()
{
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Game
		);
	}

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

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_cameraPos);
	Math::Matrix rotMat = Math::Matrix::CreateRotationX(
		DirectX::XMConvertToRadians(25));
	Math::Matrix rotMat2 = Math::Matrix::CreateRotationY(
		DirectX::XMConvertToRadians(dist * 0.1));
	Math::Matrix worldMat = rotMat * rotMat2 * transMat;
	m_camera->SetCameraMatrix(worldMat);
}

void TitleScene::Init()
{
	//カメラ
	m_camera = std::make_shared<KdCamera>();
	m_cameraPos = { -100,200,-270 };

	//机
	std::shared_ptr<Desk>desk;
	desk = std::make_shared<Desk>();
	desk->Init();
	AddObject(desk);
}
