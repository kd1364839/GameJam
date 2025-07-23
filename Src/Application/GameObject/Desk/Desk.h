#pragma once

class Desk :public KdGameObject {
public:
	Desk(){}
	~Desk()override {}

	void Init()override;

	void DrawLit()override;

private:
	std::shared_ptr<KdModelData>m_spModel = nullptr;
};