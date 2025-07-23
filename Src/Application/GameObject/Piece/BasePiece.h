#pragma once

enum PieceTypeNo {
	NullType = -1,
	BOMB,
	HAKU,
	PieceTypeNoMax
};

class BasePiece :public KdGameObject {
public:
	BasePiece(){}
	~BasePiece()override{}

	void Init()override;

	void Update()override;

	void DrawLit()override;

	int GetPieceType() { return m_type; }

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }
protected:
	Math::Vector3 PieceMountPos = { 0,25,-20 };

	std::shared_ptr<KdModelData>m_spModel = nullptr;

	int m_type = 0;

	Math::Vector3		m_pos;
};