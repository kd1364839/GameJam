#pragma once

#include"../BaseScene/BaseScene.h"
class Title;
class TitleScene : public BaseScene
{
public :

	TitleScene()  { Init(); }
	~TitleScene() {}

private :

	void Event() override;
	void Init()  override;

	std::shared_ptr<Title> m_title;
};
