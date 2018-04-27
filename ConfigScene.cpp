#include "ConfigScene.h"
#include "DxLib.h"

ConfigScene::ConfigScene(ISceneManager* changer) : BaseScene(changer)
{
}

/// <summary>
/// ����������
/// </summary>
/// <returns>TRUE</returns>
void ConfigScene::Initialize(){
}

/// <summary>
/// ���t���[���X�V����
/// </summary>
/// <returns>TRUE</returns>
void ConfigScene::Update(){
	if(CheckHitKey(KEY_INPUT_RIGHT) == TRUE){
		m_pSceneChanger->ChangeScene(SCENE_MENU);	//�V�[���ړ�
	}
}

/// <summary>
/// ���t���[���`�揈��
/// </summary>
/// <returns>TRUE</returns>
void ConfigScene::DrawLoop(){
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Result");
}

/// <summary>
/// �I��������
/// </summary>
/// <returns>TRUE</returns>
void ConfigScene::Finalize(){
}
