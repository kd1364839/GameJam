#include"PieceManager.h"
#include"../../main.h"
#include"../../Scene/SceneManager.h"

//牌
#include"BasePiece.h"

void PieceManager::Init()
{
	m_nowWave = 0;
	m_waveInitFlg = true;

	m_playerCoin = 0;
	m_enemyCoin = 0;

	m_winTex.Load("Asset/Textures/Win.png");
	m_loseTex.Load("Asset/Textures/Lose.png");
}

void PieceManager::Update()
{
	for (auto _piece : m_piece) {
		//動いていたら何もしない
		if (_piece.lock()->GetMoveFlg())return;
	}

	if (!m_playerWin && !m_playerLose) {
		if (m_waveInitFlg) {
			HandPieceReset();

			bool _flg = false;
			for (auto _piece : m_piece) {
				//牌が山に戻っていないなら
				if (_piece.lock()->GetPos() !=
					_piece.lock()->GetPieceMountPos())_flg = true;
			}
			if (!_flg) {
				WaveInit();
				m_waveInitFlg = false;
			}
			return;
		}
	}

	std::shared_ptr<BasePiece>piece;

	for (auto _piece : m_piece) {
		_piece.lock()->SetSelectFlg(false);
	}

	if (m_turn == TurnNo::PlayerTurn) {
		if (m_turnInitFlg) {
			m_playerHandPiece[4] = KdRandom::GetInt(0, m_piece.size() - 1);
			while (m_piece[m_playerHandPiece[4]].lock()->GetHandPieceFlg()) {
				m_playerHandPiece[4] = KdRandom::GetInt(0, m_piece.size() - 1);
			}
			piece = m_piece[m_playerHandPiece[4]].lock();
			piece->SetHandPieceFlg(true);
			piece->SetPlayerHandFlg(true);
			piece->SetDestinationPos(Math::Vector3(0, 95, -70));
			m_turnInitFlg = false;

			return;
		}

		//for (auto _piece : m_piece) {
		//	//動いていたら何もしない
		//	if (_piece.lock()->GetMoveFlg())return;
		//}

		//手牌の数
		int handPieceTypeNum[PieceTypeNo::PieceTypeNoNum] = {};
		for (int i = 0; i < HandPieceNum; i++) {
			handPieceTypeNum[m_piece[m_playerHandPiece[i]].lock()->GetPieceType()]++;
		}

		if (!m_winCheck) {
			m_winFlg = false;
			//役判定
			{
				//風牌 or 爆 or 石 *3
				if (handPieceTypeNum[PieceTypeNo::EAST] == 3 ||
					handPieceTypeNum[PieceTypeNo::WEST] == 3 ||
					handPieceTypeNum[PieceTypeNo::SOUTH] == 3 ||
					handPieceTypeNum[PieceTypeNo::NORTH] == 3 ||
					handPieceTypeNum[PieceTypeNo::STONE] == 3) {
					for (int i = 0; i < PieceTypeNo::PieceTypeNoNum; i++) {
						if (handPieceTypeNum[i] == 2) {
							m_winFlg = true;
							m_playerCoin += 1;
							break;
						}
					}
				}

				//三元牌 * 3
				if (handPieceTypeNum[PieceTypeNo::HAKU] == 3 ||
					handPieceTypeNum[PieceTypeNo::HATU] == 3 ||
					handPieceTypeNum[PieceTypeNo::TYUN] == 3) {
					for (int i = 0; i < PieceTypeNo::PieceTypeNoNum; i++) {
						if (handPieceTypeNum[i] == 2) {
							m_winFlg = true;
							m_playerCoin += 2;
							break;
						}
					}
				}

				//三元牌のみ
				if (handPieceTypeNum[PieceTypeNo::HAKU] >= 1 &&
					handPieceTypeNum[PieceTypeNo::HATU] >= 1 &&
					handPieceTypeNum[PieceTypeNo::TYUN] >= 1) {
					bool _flg = true;
					for (int i = 0; i < PieceTypeNo::PieceTypeNoNum; i++) {
						if (handPieceTypeNum[i] > 0) {
							_flg = false;
							break;
						}
					}
					if (_flg) {
						m_winFlg = true;
						m_playerCoin += 3;
					}
				}

				//勝勝勝
				if (handPieceTypeNum[PieceTypeNo::WIN] == 3) {
					for (int i = 0; i < PieceTypeNo::PieceTypeNoNum; i++) {
						if (handPieceTypeNum[i] == 2) {
							m_winFlg = true;
							m_playerCoin += 2;
							break;
						}
					}
				}

				//損損損
				if (handPieceTypeNum[PieceTypeNo::SON] == 3) {
					for (int i = 0; i < PieceTypeNo::PieceTypeNoNum; i++) {
						if (handPieceTypeNum[i] == 2) {
							m_winFlg = true;
							m_playerCoin += 1;
							m_enemyCoin -= 1;
							break;
						}
					}
				}

				//東西南北　free
				if (handPieceTypeNum[PieceTypeNo::EAST] >= 1 &&
					handPieceTypeNum[PieceTypeNo::WEST] >= 1 &&
					handPieceTypeNum[PieceTypeNo::SOUTH] >= 1 &&
					handPieceTypeNum[PieceTypeNo::NORTH] >= 1) {
					m_winFlg = true;
					m_playerCoin += 5;
				}

				//爆爆爆
				if (handPieceTypeNum[PieceTypeNo::BOMB] == 3) {
					//勝勝
					if (handPieceTypeNum[PieceTypeNo::WIN] == 2) {
						m_winFlg = true;
						m_playerCoin += 100; //シーン移動？
						m_nowWave = 3;
					}
					//発発
					else if (handPieceTypeNum[PieceTypeNo::HATU] == 2) {
						m_winFlg = true;
						//大爆発処理
						m_deskExplosionActive = true;
						
					}
					else {
						for (int i = 0; i < PieceTypeNo::PieceTypeNoNum; i++) {
							if (handPieceTypeNum[i] == 2) {
								m_winFlg = true;
								
								m_playerCoin += 2;
								break;
							}
						}
					}
				}

				if (m_winFlg) {
					m_winCheck = true;

				}
			}
		}
		//if (m_nowWave == 0) 
		//{
		//	KdDebugGUI::Instance().AddLog(U8("東,南,西,北,白,発,中,爆,損,石,勝\n"));
		//	for (int i = 0; i < PieceTypeNo::PieceTypeNoNum; i++) {
		//		KdDebugGUI::Instance().AddLog(" %d,", handPieceTypeNum[i]);
		//	}
		//	KdDebugGUI::Instance().AddLog("\n");

		//	for (int i = 0; i < HandPieceNum; i++) {
		//		piece = m_piece[m_playerHandPiece[i]].lock();
		//		KdDebugGUI::Instance().AddLog("%d,", piece->GetPieceType());
		//	}
		//	KdDebugGUI::Instance().AddLog("\n");
		//}
		if (GetAsyncKeyState('W') & 0x8000) {
			m_winFlg = true;
		}

		if (GetAsyncKeyState('O') & 0x8000) {
			m_deskExplosionActive = true;
		}

		if (m_winFlg) {
			//並べ替え
			for (int typeNo = 0; typeNo < PieceTypeNo::PieceTypeNoNum; typeNo++) {
				handPieceTypeNum[typeNo] = 0;
			}
			for (int i = 0; i < HandPieceNum; i++) {
				handPieceTypeNum[m_piece[m_playerHandPiece[i]].lock()->GetPieceType()]++;
			}
			int changeNo = 0;
			for (int typeNo = 0; typeNo < PieceTypeNo::PieceTypeNoNum; typeNo++) {
				if (handPieceTypeNum[typeNo] > 0) {
					for (int i = changeNo; i < HandPieceNum; i++) {
						if (m_piece[m_playerHandPiece[i]].lock()->GetPieceType() == typeNo) {
							int memory = m_playerHandPiece[changeNo];
							m_playerHandPiece[changeNo] = m_playerHandPiece[i];
							m_playerHandPiece[i] = memory;

							changeNo++;
						}
					}
				}
				if (changeNo >= HandPieceNum) {
					break;
				}
			}

			//if (!m_winCheck) {
			static bool once = false;

				for (int i = 0; i < HandPieceNum; i++) {
					piece = m_piece[m_playerHandPiece[i]].lock();
					piece->SetDestinationPos(Math::Vector3(-10 + (i * 5), 90, -70));
					if (!once) {
						piece->SetEffectFlg(true);
					}
				}
				once = true;
			//}

				//for (int i = 0; i < HandPieceNum; i++) {
				//	auto piece = m_piece[m_playerHandPiece[i]].lock();
				//	piece->SetDestinationPos(Math::Vector3(-10 + (i * 5), 90, -70));

				//	if (!m_trigger) {
				//		piece->SetEffectFlg(true); // This is the one-time trigger
				//		m_trigger = true;
				//	}
				//}

				


			m_winWaitFram--;
			if (m_winWaitFram < 0) {
				m_waveInitFlg = true;
				m_nowWave++;
				m_winWaitFram = 60;

				m_winCheck = false;
			}
		}
		else {
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
			for (int i = 0; i < HandPieceNum; i++)
			{
				std::weak_ptr<BasePiece> wpGameObj = m_piece[m_playerHandPiece[i]];
				if (wpGameObj.expired())continue;
				std::shared_ptr<BasePiece> spGameObj = wpGameObj.lock();

				//if (!spGameObj->GetHandPieceFlg())continue;
				//if (!spGameObj->GetPlayerHandFlg())continue;

				//spGameObj->SetSelectFlg(false);

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

					if (_hitObj.lock()->GetPieceType() == PieceTypeNo::STONE) {
						_hitObj.lock()->SetEffectFlg(true);
					}
					else _hitObj.lock()->SetDestinationMountPos();

					m_turnEndFlg = true;
				}
			}
		}
		
		BigExplosion();

		/////////////////////////////////////////
		//レイ判定終わり
		/////////////////////////////////////////

		if (m_turnEndFlg) {
			if (m_piece[m_playerHandPiece[4]]
				.lock()->GetPlayerHandFlg()) {
				for (int i = 0; i < HandPieceNum - 1; i++) {
					if (!m_piece[m_playerHandPiece[i]]
						.lock()->GetHandPieceFlg()) {
						m_playerHandPiece[i] = m_playerHandPiece[4];
						break;
					}
				}

				//並べ替え
				for (int typeNo = 0; typeNo < PieceTypeNo::PieceTypeNoNum; typeNo++) {
					handPieceTypeNum[typeNo] = 0;
				}
				for (int i = 0; i < HandPieceNum - 1; i++) {
					handPieceTypeNum[m_piece[m_playerHandPiece[i]].lock()->GetPieceType()]++;
				}
				int changeNo = 0;
				for (int typeNo = 0; typeNo < PieceTypeNo::PieceTypeNoNum; typeNo++) {
					if (handPieceTypeNum[typeNo] > 0) {
						for (int i = changeNo; i < HandPieceNum - 1; i++) {
							if (m_piece[m_playerHandPiece[i]].lock()->GetPieceType() == typeNo) {
								int memory = m_playerHandPiece[changeNo];
								m_playerHandPiece[changeNo] = m_playerHandPiece[i];
								m_playerHandPiece[i] = memory;

								changeNo++;
							}
						}
					}
					if (changeNo >= HandPieceNum - 1) {
						break;
					}
				}
			}

			for (int i = 0; i < HandPieceNum - 1; i++) {
				piece = m_piece[m_playerHandPiece[i]].lock();
				piece->SetDestinationPos(Math::Vector3(-7.5f + (i * 5), 90, -70));
			}

			m_turn = TurnNo::WaitTurn;
			m_nextTurn = TurnNo::EnemyTurn;

			m_turnEndFlg = false;
		}
	}
	else if(m_turn == TurnNo::EnemyTurn){
		/*if (m_turnInitFlg) {
			m_enemyHandPiece[4] = KdRandom::GetInt(0, m_piece.size() - 1);
			while (m_piece[m_enemyHandPiece[4]].lock()->GetHandPieceFlg()) {
				m_enemyHandPiece[4] = KdRandom::GetInt(0, m_piece.size() - 1);
			}
			piece = m_piece[m_enemyHandPiece[4]].lock();
			piece->SetHandPieceFlg(true);
			piece->SetDestinationPos(Math::Vector3(0, 95, 70));

			m_turnInitFlg = false;

			return;
		}*/


		//int handPieceTypeNum[PieceTypeNo::PieceTypeNoNum] = {};
		//for (int i = 0; i < HandPieceNum; i++) {
		//	handPieceTypeNum[m_piece[m_enemyHandPiece[i]].lock()->GetPieceType()]++;
		//}
		////役判定
		//m_loseFlg = false;
		//{
		//	//風牌 or 爆 or 石 *3
		//	if (handPieceTypeNum[PieceTypeNo::EAST] == 3 ||
		//		handPieceTypeNum[PieceTypeNo::WEST] == 3 ||
		//		handPieceTypeNum[PieceTypeNo::SOUTH] == 3 ||
		//		handPieceTypeNum[PieceTypeNo::NORTH] == 3 ||
		//		handPieceTypeNum[PieceTypeNo::STONE] == 3) {
		//		for (int i = 0; i < PieceTypeNo::PieceTypeNoNum; i++) {
		//			if (handPieceTypeNum[i] == 2) {
		//				m_loseFlg = true;
		//				m_enemyCoin += 1;
		//				break;
		//			}
		//		}
		//	}

		//	//三元牌 * 3
		//	if (handPieceTypeNum[PieceTypeNo::HAKU] == 3 ||
		//		handPieceTypeNum[PieceTypeNo::HATU] == 3 ||
		//		handPieceTypeNum[PieceTypeNo::TYUN] == 3) {
		//		for (int i = 0; i < PieceTypeNo::PieceTypeNoNum; i++) {
		//			if (handPieceTypeNum[i] == 2) {
		//				m_loseFlg = true;
		//				m_enemyCoin += 2;
		//				break;
		//			}
		//		}
		//	}

		//	//三元牌のみ
		//	if (handPieceTypeNum[PieceTypeNo::HAKU] >= 1 &&
		//		handPieceTypeNum[PieceTypeNo::HATU] >= 1 &&
		//		handPieceTypeNum[PieceTypeNo::TYUN] >= 1) {
		//		bool _flg = true;
		//		for (int i = 0; i < PieceTypeNo::PieceTypeNoNum; i++) {
		//			if (handPieceTypeNum[i] > 0) {
		//				_flg = false;
		//				break;
		//			}
		//		}
		//		if (_flg) { 
		//			m_loseFlg = true; 
		//			m_enemyCoin += 3;
		//		}
		//	}

		//	//勝勝勝
		//	if (handPieceTypeNum[PieceTypeNo::WIN] == 3) {
		//		for (int i = 0; i < PieceTypeNo::PieceTypeNoNum; i++) {
		//			if (handPieceTypeNum[i] == 2) {
		//				m_loseFlg = true;
		//				m_enemyCoin += 2;
		//				break;
		//			}
		//		}
		//	}

		//	//損損損
		//	if (handPieceTypeNum[PieceTypeNo::SON] == 3) {
		//		for (int i = 0; i < PieceTypeNo::PieceTypeNoNum; i++) {
		//			if (handPieceTypeNum[i] == 2) {
		//				m_loseFlg = true;
		//				m_enemyCoin += 1;
		//				m_playerCoin -= 1;
		//				break;
		//			}
		//		}
		//	}

		//	//東西南北　free
		//	if (handPieceTypeNum[PieceTypeNo::EAST] >= 1 &&
		//		handPieceTypeNum[PieceTypeNo::WEST] >= 1 &&
		//		handPieceTypeNum[PieceTypeNo::SOUTH] >= 1 &&
		//		handPieceTypeNum[PieceTypeNo::NORTH] >= 1) {
		//		m_loseFlg = true;
		//		m_enemyCoin += 5;
		//	}

		//	//爆爆爆
		//	if (handPieceTypeNum[PieceTypeNo::BOMB] == 3) {
		//		//勝勝
		//		if (handPieceTypeNum[PieceTypeNo::WIN] == 2) {
		//			m_loseFlg = true;
		//			m_enemyCoin += 99;
		//			m_nowWave = 3;

		//		}
		//		//発発
		//		else if (handPieceTypeNum[PieceTypeNo::HATU] == 2) {
		//			m_loseFlg = true;

		//		}
		//		else {
		//			for (int i = 0; i < PieceTypeNo::PieceTypeNoNum; i++) {
		//				if (handPieceTypeNum[i] == 2) {
		//					m_winFlg = true;
		//					m_playerCoin += 2;
		//					break;
		//				}
		//			}
		//		}
		//	}
		//}

		//if (m_loseFlg) {
		//	m_waveInitFlg = true;
		//	m_nowWave++;
		//}
		//else{
		//	bool changeFlg = false;
		//	for (int typeNo = PieceTypeNo::PieceTypeNoNum - 1;
		//		typeNo > PieceTypeNo::NullType; typeNo--) {
		//		if (handPieceTypeNum[typeNo] == 1) {
		//			for (int i = 0; i < HandPieceNum; i++) {
		//				if (m_piece[m_enemyHandPiece[i]].lock()->GetPieceType() == typeNo) {
		//					m_piece[m_enemyHandPiece[i]].lock()->SetHandPieceFlg(false);
		//					m_piece[m_enemyHandPiece[i]].lock()->SetPlayerHandFlg(false);

		//					if (m_piece[m_enemyHandPiece[i]].lock()->GetPieceType() == PieceTypeNo::STONE) {
		//						m_piece[m_enemyHandPiece[i]].lock()->SetEffectFlg(true);
		//					}
		//					else m_piece[m_enemyHandPiece[i]].lock()->SetDestinationMountPos();

		//					changeFlg = true;
		//					break;
		//				}
		//			}
		//		}

		//		if (changeFlg) {
		//			break;
		//		}
		//	}

		//	if (m_piece[m_enemyHandPiece[4]]
		//		.lock()->GetHandPieceFlg()) {
		//		for (int i = 0; i < HandPieceNum - 1; i++) {
		//			if (!m_piece[m_enemyHandPiece[i]]
		//				.lock()->GetHandPieceFlg()) {
		//				m_enemyHandPiece[i] = m_enemyHandPiece[4];
		//				break;
		//			}
		//		}
		//	}

		//	for (int i = 0; i < HandPieceNum - 1; i++) {
		//		piece = m_piece[m_enemyHandPiece[i]].lock();
		//		piece->SetDestinationPos(Math::Vector3(-15 + (i * 10), 90, 70));
		//	}

		//	m_turnEndFlg = true;
		//}

		m_turnEndFlg = true;

		if (m_turnEndFlg) {
			m_turn = TurnNo::WaitTurn;
			m_nextTurn = TurnNo::PlayerTurn;

			m_turnEndFlg = false;
		}
	}
	else if(m_turn == TurnNo::WaitTurn){
		m_turnInitFlg = true;
		m_turnEndFlg = false;
		m_turn = m_nextTurn;
	}


	//3ウェーブ後終了処理
	if (m_nowWave >= 3) 
	{
		m_timer++;

		if ((m_playerCoin > m_enemyCoin) && !m_playerWin) {
			m_playerWin = true;
			{
				//ここ勝利サウンド
				KdAudioManager::Instance().Play("Asset/Data/Sound/Burning.wav", true);
				KdAudioManager::Instance().Play("Asset/Data/Sound/VictoryLaugh.wav", false);
			}
		}
		else if((m_playerCoin < m_enemyCoin) && !m_playerLose){
			m_playerLose = true;
			{
				//ここ敗北サウンド
				KdAudioManager::Instance().Play("Asset/Data/Sound/Burning.wav", true);
				KdAudioManager::Instance().Play("Asset/Data/Sound/DefeatScream.wav", false);
			}
		}

		if (m_timer >= 60 * 5) { //１秒
			SceneManager::Instance().SetNextScene
			(
				SceneManager::SceneType::Title
			);
		}
	}

	/*KdDebugGUI::Instance().AddLog("%d,",m_playerCoin);
	KdDebugGUI::Instance().AddLog("\n");
	KdDebugGUI::Instance().AddLog("%d,", m_enemyCoin);
	KdDebugGUI::Instance().AddLog("\n");*/

	KdDebugGUI::Instance().AddLog("%d\n", m_nowWave);

	if (GetAsyncKeyState('K') & 0x8000) {
		m_playerCoin = 2;
		m_enemyCoin = 0;
		m_nowWave = 3;
	}

}

void PieceManager::DrawSprite()
{
	Math::Rectangle rect = { 0,0,450,450 };
	Math::Color color = { 0,0,0,0.5f };
	if (m_playerWin) {
		KdShaderManager::Instance().m_spriteShader.DrawBox(0, 130, 640, 170, &color);
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_winTex, 0, 100, rect.width, rect.height, &rect);
	}
	if (m_playerLose) {
		KdShaderManager::Instance().m_spriteShader.DrawBox(0, 130, 640, 170, &color);
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_loseTex, 0, 100, rect.width, rect.height, &rect);
	}
}

void PieceManager::WaveInit()
{
	//手牌を決める
	std::shared_ptr<BasePiece>piece;
	for (int i = 0; i < HandPieceNum - 1; i++) {
		//プレイヤー
		m_playerHandPiece[i] = KdRandom::GetInt(0, m_piece.size() - 1);
		while (m_piece[m_playerHandPiece[i]].lock()->GetHandPieceFlg()) {
			m_playerHandPiece[i] = KdRandom::GetInt(0, m_piece.size() - 1);
		}
		piece = m_piece[m_playerHandPiece[i]].lock();
		piece->SetHandPieceFlg(true);
		piece->SetPlayerHandFlg(true);
		piece->SetDestinationPos(Math::Vector3(-7.5f + (i * 5), 90, -70));

		//敵
		m_enemyHandPiece[i] = KdRandom::GetInt(0, m_piece.size() - 1);
		while (m_piece[m_enemyHandPiece[i]].lock()->GetHandPieceFlg()) {
			m_enemyHandPiece[i] = KdRandom::GetInt(0, m_piece.size() - 1);
		}
		piece = m_piece[m_enemyHandPiece[i]].lock();
		piece->SetHandPieceFlg(true);
		piece->SetDestinationPos(Math::Vector3(-15 + (i * 10), 90, 70));
	}

	m_turn = TurnNo::WaitTurn;
	m_nextTurn = TurnNo::PlayerTurn;

	m_winFlg = false;
	m_winWaitFram = 60;

	m_loseFlg = false;
	KdAudioManager::Instance().Play("Asset/Data/Sound/WaveStart.wav", false);//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

}

void PieceManager::HandPieceReset()
{
	for (auto _piece : m_piece) {
		_piece.lock()->SetDestinationMountPos();
		_piece.lock()->SetHandPieceFlg(false);
		_piece.lock()->SetPlayerHandFlg(false);
		_piece.lock()->SetSelectFlg(false);
	}
	for (int i = 0; i < HandPieceNum - 1; i++) {
		m_playerHandPiece[i] = 0;
		m_enemyHandPiece[i] = 0;
	}
}

void PieceManager::BigExplosion()
{
	const int endFrame = 40;

	if (m_deskExplosionActive)
	{
		m_deskExplosionTimer++;
		if (!Once && m_explosionSequence.empty()) {
			m_explosionSequence = {
				{ KdRandom::GetInt(20,40), {  KdRandom::GetFloat(-30,30), 90,  KdRandom::GetFloat(-80,0)}},
				{ KdRandom::GetInt(20,40), {  KdRandom::GetFloat(-30,30), 90,  KdRandom::GetFloat(-80,0)} },
				{ KdRandom::GetInt(20,40), {  KdRandom::GetFloat(-30,30), 90,  KdRandom::GetFloat(-80,0)} },
				{ KdRandom::GetInt(20,40), {  KdRandom::GetFloat(-30,30), 90,  KdRandom::GetFloat(-80,0)} },
				{ KdRandom::GetInt(20,40), {  KdRandom::GetFloat(-30,30), 90,  KdRandom::GetFloat(-80,0)} },
				{ KdRandom::GetInt(20,40), {  KdRandom::GetFloat(-30,30), 90,  KdRandom::GetFloat(-80,0)} },
				{ KdRandom::GetInt(20,40), {  KdRandom::GetFloat(-30,30), 90,  KdRandom::GetFloat(-80,0)} },
				{ KdRandom::GetInt(20,40), {  KdRandom::GetFloat(-30,30), 90,  KdRandom::GetFloat(-80,0)} },
				{ KdRandom::GetInt(20,40), {  KdRandom::GetFloat(-30,30), 90,  KdRandom::GetFloat(-80,0)} },
				{ KdRandom::GetInt(20,40), {  KdRandom::GetFloat(-30,30), 90,  KdRandom::GetFloat(-80,0)} },
				{ KdRandom::GetInt(20,40), {  KdRandom::GetFloat(-30,30), 90,  KdRandom::GetFloat(-80,0)} },
				{ KdRandom::GetInt(20,40), {  KdRandom::GetFloat(-30,30), 90,  KdRandom::GetFloat(-80,0)} },
				{ KdRandom::GetInt(20,40), {  KdRandom::GetFloat(-30,30), 90,  KdRandom::GetFloat(-80,0)} },
				{ KdRandom::GetInt(20,40), {  KdRandom::GetFloat(-30,30), 90,  KdRandom::GetFloat(-80,0)} },
				{ KdRandom::GetInt(20,40), {  KdRandom::GetFloat(-30,30), 90,  KdRandom::GetFloat(-80,0)} },
				{ KdRandom::GetInt(20,40), {  KdRandom::GetFloat(-30,30), 90,  KdRandom::GetFloat(-80,0)} },
			};
			Once = true;
		}

		for (const auto& explosion : m_explosionSequence)
		{
			if (m_deskExplosionTimer == explosion.frame)
			{
				KdAudioManager::Instance().Play("Asset/Data/Sound/BigExplosion.wav", false);//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

				KdEffekseerManager::GetInstance().Play(
					"Explosion.efkefc",
					explosion.pos,
					3.0f,
					0.1f,
					false
				);
			}
		}

		if (m_deskExplosionTimer >= endFrame)
		{
			m_deskExplosionActive = false;
			m_deskExplosionTimer = 0;
			m_explosionSequence.clear();
			m_explosionSequence.shrink_to_fit();
			Once = false;
			m_nowWave = 3;
			m_playerCoin = 300;
		}
	}
}
