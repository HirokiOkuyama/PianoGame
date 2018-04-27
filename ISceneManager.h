#pragma once

enum Scene{
	SCENE_LOAD,
	SCENE_MENU,
	SCENE_PRACTICE,
	SCENE_BATTLE,
	SCENE_REPLAY,
	SCENE_CONFIG,
	SCENE_EXIT,

	SCENE_UNKNOWN
};

enum Phase{
	PHASE_LOAD = -1,		//���[�h��
	PHASE_TITLE = 0,		//���j���[�I��
	PHASE_PRACTICE = 1,	//�ȑI��
	PHASE_LEVEL = 2,		//���x���I��
	PHASE_REPLAY = 3,		//���v���C�I��
	PHASE_CONFIG = 4,		//�R���t�B�O�I��
	PHASE_EXIT = 5,		//�Q�[���I��
	PHASE_GAMEPLAY = 6,	//�Q�[���J�n
	PHASE_PAUSE = 7,		//�ꎞ��~
	PHASE_STORAGE = 8,	//�ۑ�

	PHASE_UNKNOWN = 99
};

class ISceneManager
{
public:
	ISceneManager();
	virtual ~ISceneManager() = 0;
	virtual void ChangeScene(Scene eScene) = 0;	//�w��V�[���ɕύX����
	virtual void SetPhase(Phase ePhase) = 0;	//�w��t�F�[�Y�ɕύX����
	virtual int GetPhase() = 0;
};

