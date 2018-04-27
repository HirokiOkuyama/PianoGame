#pragma once
#include "ISceneManager.h"
#include "BaseScene.h"

class SceneMgr : public ISceneManager, Task
{
private:
	//�V�[���Ǘ��ϐ�
	BaseScene* m_pScene;
	Animation* m_pAnimeScene;

	//���̃V�[���Ǘ��ϐ�
	Scene m_eNextScene;
	Phase m_eNextPhase;

public:
	SceneMgr();
	~SceneMgr();
	void Initialize() override;
	void Update() override;
	void DrawLoop() override;
	void Finalize() override;

	//����nextScene�ɃV�[����ύX����
	void ChangeScene(Scene eScene) override;

	void SetPhase(Phase ePhase) override;
	int GetPhase() override;
};

