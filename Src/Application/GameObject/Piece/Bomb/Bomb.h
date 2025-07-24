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
};