#pragma once

#include"../BasePiece.h"

class Rock : public BasePiece {
public:
	Rock(){}
	~Rock()override{}

	void Init()override;

	void Update()override;

	void DrawEffect()override;
private:
	float m_speed = 0;
	Math::Vector3 m_velocity;  // Velocity vector
	float m_gravity = -0.01f;  // Gravity power (adjust as needed)

};