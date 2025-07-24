#include"PieceManager.h"
#include"../../main.h"
#include"../../Scene/SceneManager.h"

//牌
#include"BasePiece.h"

void PieceManager::Init()
{
	//手牌を決める
	std::shared_ptr<BasePiece>piece;
	for (int i = 0; i < HandPieceNum; i++) {
		//プレイヤー
		m_playerHandPiece[i] = KdRandom::GetInt(0, m_piece.size() - 1);
		while (m_piece[m_playerHandPiece[i]].lock()->GetHandPieceFlg()) {
			m_playerHandPiece[i] = KdRandom::GetInt(0, m_piece.size() - 1);
		}
		piece = m_piece[m_playerHandPiece[i]].lock();
		piece->SetHandPieceFlg(true);
		piece->SetPlayerHandFlg(true);
		piece->SetDestinationPos(Math::Vector3(-10 + (i * 5), 90, -70));

		//敵
		m_enemyHandPiece[i] = KdRandom::GetInt(0, m_piece.size() - 1);
		while (m_piece[m_enemyHandPiece[i]].lock()->GetHandPieceFlg()) {
			m_enemyHandPiece[i] = KdRandom::GetInt(0, m_piece.size() - 1);
		}
		piece = m_piece[m_enemyHandPiece[i]].lock();
		piece->SetHandPieceFlg(true);
		piece->SetDestinationPos(Math::Vector3(-20 + (i * 10), 90, 70));
	}

	m_turn = TurnNo::WaitTurn;
	m_nextTurn = TurnNo::PlayerTurn;
}

void PieceManager::Update()
{
	std::shared_ptr<BasePiece>piece;
	if (m_turn == TurnNo::PlayerTurn) {
		if (m_turnInitFlg) {
			m_playerHandPiece[5] = KdRandom::GetInt(0, m_piece.size() - 1);
			while (m_piece[m_playerHandPiece[5]].lock()->GetHandPieceFlg()) {
				m_playerHandPiece[5] = KdRandom::GetInt(0, m_piece.size() - 1);
			}
			piece = m_piece[m_playerHandPiece[5]].lock();
			piece->SetHandPieceFlg(true);
			piece->SetPlayerHandFlg(true);
			piece->SetDestinationPos(Math::Vector3(0, 95, -70));
			m_turnInitFlg = false;
		}

		//カメラ取得
		if (m_wpCamera.expired())return;
		std::shared_ptr<KdCamera>_camera;
		_camera = m_wpCamera.lock();

		/////////////////////////////////////////
		//レイ判定はじめ
		/////////////////////////////////////////

		//マウス座標を取得
		POINT _mousePos;
		GetCursorPos(&_mousePos);
		ScreenToClient(Application::Instance().GetWindowHandle(), &_mousePos);

		//2D座標を3D座標に
		Math::Vector3	_rayPos = _camera->GetCameraMatrix().Translation();
		Math::Vector3	_rayDir = Math::Vector3::Zero;
		float			_range = 100.0f;
		_camera->GenerateRayInfoFromClientPos(
			_mousePos, _rayPos, _rayDir, _range);

		//レイ判定
		KdCollider::RayInfo rayInfo;
		rayInfo.m_pos = _rayPos;
		rayInfo.m_dir = _rayDir;
		rayInfo.m_range = _range;
		rayInfo.m_type = KdCollider::TypeGround;

		bool hit = false;
		float maxOverLap = 0;
		Math::Vector3 hitPos = {};
		std::weak_ptr<BasePiece>_hitObj;

		std::list<KdCollider::CollisionResult> retRayList;
		//for (std::weak_ptr<BasePiece> wpGameObj : m_piece)
		for (int i = 0; i < HandPieceNum + 1; i++)
		{
			std::weak_ptr<BasePiece> wpGameObj = m_piece[m_playerHandPiece[i]];
			if (wpGameObj.expired())continue;
			std::shared_ptr<BasePiece> spGameObj = wpGameObj.lock();

			//if (!spGameObj->GetHandPieceFlg())continue;
			//if (!spGameObj->GetPlayerHandFlg())continue;

			spGameObj->SetSelectFlg(false);

			if (!(spGameObj->Intersects(rayInfo, &retRayList)))continue;

			for (auto& ret : retRayList) {
				if (maxOverLap < ret.m_overlapDistance) {
					maxOverLap = ret.m_overlapDistance;
					hitPos = ret.m_hitPos;
					hit = true;
					_hitObj = spGameObj;
				}
			}
		}

		if (hit) {
			_hitObj.lock()->SetSelectFlg(true);

			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
				_hitObj.lock()->SetHandPieceFlg(false);
				_hitObj.lock()->SetPlayerHandFlg(false);
				_hitObj.lock()->SetDestinationMountPos();

				m_turnEndFlg = true;
			}
		}

		/////////////////////////////////////////
		//レイ判定終わり
		/////////////////////////////////////////

		if (m_turnEndFlg) {
			if (m_piece[m_playerHandPiece[5]]
				.lock()->GetPlayerHandFlg()) {
				for (int i = 0; i < HandPieceNum; i++) {
					if (!m_piece[m_playerHandPiece[i]]
						.lock()->GetHandPieceFlg()) {
						m_playerHandPiece[i] = m_playerHandPiece[5];
						break;
					}
				}
			}

			for (int i = 0; i < HandPieceNum; i++) {
				piece = m_piece[m_playerHandPiece[i]].lock();
				piece->SetDestinationPos(Math::Vector3(-10 + (i * 5), 90, -70));
			}

			m_turn = TurnNo::WaitTurn;
			m_nextTurn = TurnNo::EnemyTurn;

			m_turnEndFlg = false;
		}
	}
	else if(m_turn == TurnNo::EnemyTurn){
		//if (m_turnInitFlg) {
		//	m_enemyHandPiece[5] = KdRandom::GetInt(0, m_piece.size() - 1);
		//	while (m_piece[m_enemyHandPiece[5]].lock()->GetHandPieceFlg()) {
		//		m_enemyHandPiece[5] = KdRandom::GetInt(0, m_piece.size() - 1);
		//	}
		//	piece = m_piece[m_enemyHandPiece[5]].lock();
		//	piece->SetHandPieceFlg(true);
		//	piece->SetPlayerHandFlg(true);
		//	piece->SetDestinationPos(Math::Vector3(0, 95, 70));

		//	m_turnInitFlg = false;
		//}

		m_turnEndFlg = true;

		if (m_turnEndFlg) {
			m_turn = TurnNo::WaitTurn;
			m_nextTurn = TurnNo::PlayerTurn;

			m_turnEndFlg = false;
		}
	}
	else if(m_turn == TurnNo::WaitTurn){
		for (auto _piece : m_piece) {
			//動いていたら何もしない
			if (_piece.lock()->GetMoveFlg())return;
		}
		m_turnInitFlg = true;
		m_turnEndFlg = false;
		m_turn = m_nextTurn;
	}

	KdDebugGUI::Instance().AddLog("%d\n", m_turn);
}
