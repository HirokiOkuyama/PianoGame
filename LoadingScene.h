#pragma once
#include "BaseScene.h"
#include <vector>
#include <string>


//���C�������N���X
class LoadingScene : public BaseScene{
public:
	//�R���X�g���N�^
	LoadingScene(ISceneManager* changer);

	void Initialize() override;
	void Update() override;
	void DrawLoop() override;
	void Finalize() override;

private:
	int m_nLoadCount;
	int m_nWaitCount;

	void DrawLoadGauge();
};

