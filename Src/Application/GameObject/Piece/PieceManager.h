#pragma once

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

	//牌を持っておく
	std::vector<std::weak_ptr<BasePiece>>m_piece;

	static const int HandPieceNum = 5;

	int m_playerHandPiece[HandPieceNum] = {};
	int m_enemyHandPiece[HandPieceNum] = {};
};