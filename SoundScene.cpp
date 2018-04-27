#include "SoundScene.h"
#include "DxLib.h"

SoundScene::SoundScene(ISceneManager* changer) : BaseScene(changer)
{
}

/// <summary>
/// ����������
/// </summary>
/// <returns>TRUE</returns>
void SoundScene::Initialize(){
}

/// <summary>
/// ���t���[���X�V����
/// </summary>
/// <returns>TRUE</returns>
void SoundScene::Update(){
	if(CheckHitKey(KEY_INPUT_LEFT) == TRUE){
		m_pSceneChanger->ChangeScene(SCENE_LOAD);	//�V�[���ړ�
	}
}

/// <summary>
/// ���t���[���`�揈��
/// </summary>
/// <returns>TRUE</returns>
void SoundScene::DrawLoop(){
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Sound");
}

/// <summary>
/// �I��������
/// </summary>
/// <returns>TRUE</returns>
void SoundScene::Finalize(){
}
