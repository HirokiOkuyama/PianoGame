#pragma once
#include "BaseScene.h"

class ConfigScene : public BaseScene
{
public:
	//�R���X�g���N�^
	ConfigScene(ISceneManager* changer);

	void Initialize() override;
	void Update() override;
	void DrawLoop() override;
	void Finalize() override;
};

