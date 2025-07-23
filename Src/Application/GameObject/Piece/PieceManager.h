#pragma once

class BasePiece;

class PieceManager : public KdGameObject {
public:
	PieceManager() {}
	~PieceManager() {}

	void Init()override;

	void Update()override;

	void AddPiece(std::weak_ptr<KdGameObject>_piece) {
		m_piece.push_back(_piece);
	}

	std::vector<std::weak_ptr<KdGameObject>> GetPiece() {
		return m_piece;
	}
private:
	static const int PieceNum = 4;//種類ごとの数

	//牌を持っておく
	std::vector<std::weak_ptr<KdGameObject>>m_piece;
	//std::shared_ptr<BasePiece>m_piece;
};