#pragma once
#include "BaseScene.h"

class ReplayScene : public BaseScene
{
public:
	//�R���X�g���N�^
	ReplayScene(ISceneManager* changer);

	void Initialize() override;
	void Update() override;
	void DrawLoop() override;
	void Finalize() override;
};

