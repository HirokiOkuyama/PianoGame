#include "ReplayScene.h"
#include "DxLib.h"


ReplayScene::ReplayScene(ISceneManager* changer) : BaseScene(changer)
{
}

/// <summary>
/// ����������
/// </summary>
/// <returns>TRUE</returns>
void ReplayScene::Initialize(){
}

/// <summary>
/// ���t���[���X�V����
/// </summary>
/// <returns>TRUE</returns>
void ReplayScene::Update(){
	if(CheckHitKey(KEY_INPUT_LEFT) == TRUE){
		m_pSceneChanger->ChangeScene(SCENE_CONFIG);	//�V�[���ړ�
	}
}

/// <summary>
/// ���t���[���`�揈��
/// </summary>
/// <returns>TRUE</returns>
void ReplayScene::DrawLoop(){
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Replay");
}

/// <summary>
/// �I��������
/// </summary>
/// <returns>TRUE</returns>
void ReplayScene::Finalize(){
}
