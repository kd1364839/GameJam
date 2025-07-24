#pragma once

#include"../BasePiece.h"

class Bomb : public BasePiece {
public:
	Bomb() {}
	~Bomb()override {}

	void Init()override;

	void Update()override;

	void DrawEffect()override;
private:
	bool m_keyFlg = false;
	bool m_keyFlg1 = false;
	bool m_deskExplosionActive = false;
	int m_deskExplosionTimer = 0;

	struct ExplosionInfo {
		int frame;
		Math::Vector3 pos;
	};

	std::vector<ExplosionInfo> m_explosionSequence;
};