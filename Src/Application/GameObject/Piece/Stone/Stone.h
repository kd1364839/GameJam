#pragma once

#include"../BasePiece.h"

class Stone : public BasePiece {
public:
	Stone() {}
	~Stone()override {}

	void Init()override;

	void Update()override;

	void DrawEffect()override;

	void DrawBright() override;
private:
	Math::Vector3 m_velocity;
	float m_gravity = 0;

	float m_rotateX = 0;
	float m_rotateY = 0;

	Math::Vector3 m_spinSpeed = { 10.0f, 30.0f, 25.0f };

	KdTrailPolygon m_tPolygon;

};