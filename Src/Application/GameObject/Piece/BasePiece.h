#pragma once

enum PieceTypeNo {
	NullType = -1,
	BOMB,
	HAKU,
	SON,
	STONE,
	WIN,
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

	void SetPos(const Math::Vector3& pos)override { m_pos = pos; }
	Math::Vector3 GetPos() const override { return m_pos; }
	void SetDestinationPos(const Math::Vector3& pos){ m_destinationPos = pos; }
	void SetDestinationMountPos() { m_destinationPos = PieceMountPos; }
	void SetSelectFlg(bool flg) { m_selectFlg = flg; }

	void SetHandPieceFlg(bool flg) { m_handPieceFlg = flg; }
	void SetPlayerHandFlg(bool flg) { m_playerHandFlg = flg; }
	bool GetHandPieceFlg() { return m_handPieceFlg; }
	bool GetPlayerHandFlg() { return m_playerHandFlg; }
	bool GetMoveFlg() { return m_moveFlg; }
protected:
	Math::Vector3 PieceMountPos = { 0,70,0 };

	std::shared_ptr<KdModelData>m_spModel = nullptr;

	int m_type = 0;

	bool m_handPieceFlg = false;
	bool m_playerHandFlg = false;

	bool m_selectFlg = false;
	
	Math::Vector3		m_pos;
	Math::Vector3 m_destinationPos;
	float m_scale;

	float m_speed = 2;

	bool m_moveFlg = false;
};