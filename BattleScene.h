#pragma once
#include "BaseScene.h"

class BattleScene : public BaseScene
{
public:
	//�R���X�g���N�^
	BattleScene(ISceneManager* changer);

	void Initialize() override;
	void Update() override;
	void DrawLoop() override;
	void Finalize() override;
};

