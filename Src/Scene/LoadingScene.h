#pragma once
#include "BaseScene.h"

//���C�������N���X
class LoadingScene : public BaseScene{
public:
	//�R���X�g���N�^
	LoadingScene(ISceneManager* changer, IResourceManager* pResource);
	virtual ~LoadingScene(){}

	void Initialize() override {};
	void Update() override;
	void DrawLoop() override;
	void Finalize() override {};

private:
	int m_nLoadCount = 0;
	int m_nWaitCount = 0;
	const int m_nResourceCount = ResourceImage::IMAGE_UNKNOWN + ResourceSound::SOUND_UNKNOWN;

	void DrawLoadGauge();
};

