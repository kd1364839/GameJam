﻿#pragma once

enum TurnNo {
	WaitTurn,
	PlayerTurn,
	EnemyTurn,
	TurnNoMax
};

class BasePiece;

class PieceManager : public KdGameObject {
public:
	PieceManager() {}
	~PieceManager() {}

	void Init()override;

	void Update()override;

	void DrawSprite()override;

	void DrawEffect()override;

	void AddPiece(std::weak_ptr<BasePiece>_piece) {
		m_piece.push_back(_piece);
	}

	std::vector<std::weak_ptr<BasePiece>> GetPiece() {
		return m_piece;
	}

	void SetCamera(const std::shared_ptr<KdCamera>& _camera) {
		m_wpCamera = _camera;
	}
private:
	void WaveInit();
	void HandPieceReset();

	std::weak_ptr<KdCamera>m_wpCamera;

	int m_nowWave = 0;
	bool m_waveInitFlg = true;

	int m_turn = TurnNo::WaitTurn;
	int m_nextTurn = TurnNo::WaitTurn;

	bool m_turnInitFlg = true;
	bool m_turnEndFlg = false;

	bool m_winFlg = false;
	int m_winWaitFram = 0;
	bool m_loseFlg = false;

	Math::Vector3 m_fireEffectPos;
	Math::Vector3 m_winEffectPos;
	Math::Vector3 m_loseEffectPos;

	bool m_winEffectFlg = false;
	bool m_loseEffectFlg = false;

	float m_winEffectFrame = 0;
	float m_loseEffectFrame = 0;


	//牌を持っておく
	std::vector<std::weak_ptr<BasePiece>>m_piece;

	static const int HandPieceNum = 5;

	int m_playerHandPiece[HandPieceNum] = {};
	int m_enemyHandPiece[HandPieceNum] = {};

	int m_playerCoin = 0;
	int m_enemyCoin = 0;

	bool m_winCheck = false;
	//bool m_loseCheck = false;必要なかったぽい

	int m_timer = 0;

	bool m_playerWin = false;
	bool m_playerLose = false;

	KdTexture m_winTex;
	KdTexture m_loseTex;


	//大爆発
	bool m_deskExplosionActive = false; //大爆発用フラグ
	int m_deskExplosionTimer = 0;

	bool Once = false;

	struct ExplosionInfo {
		int frame;
		Math::Vector3 pos;
	};

	std::vector<ExplosionInfo> m_explosionSequence;

	void BigExplosion();

	bool m_trigger = false;
};