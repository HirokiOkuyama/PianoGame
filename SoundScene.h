#pragma once
#include "BaseScene.h"

class SoundScene : public BaseScene
{
public:
	//�R���X�g���N�^
	SoundScene(ISceneManager* changer);

	void Initialize() override;
	void Update() override;
	void DrawLoop() override;
	void Finalize() override;
};

