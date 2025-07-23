#pragma once

#include"../BaseScene/BaseScene.h"

class PieceManager;

class GameScene : public BaseScene
{
public :

	GameScene()  { Init(); }
	~GameScene() {}

private:

	void Event() override;
	void Init()  override;

	std::shared_ptr<PieceManager>m_pieceManager;

	bool m_keyFlg = false;

};
