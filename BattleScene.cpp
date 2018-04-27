#include "BattleScene.h"
#include "DxLib.h"


BattleScene::BattleScene(ISceneManager* changer) : BaseScene(changer)
{
}

/// <summary>
/// ����������
/// </summary>
/// <returns>TRUE</returns>
void BattleScene::Initialize(){
}

/// <summary>
/// ���t���[���X�V����
/// </summary>
/// <returns>TRUE</returns>
void BattleScene::Update(){
	if(CheckHitKey(KEY_INPUT_DOWN) == TRUE){
		m_pSceneChanger->ChangeScene(SCENE_REPLAY);	//�V�[���ړ�
	}
}

/// <summary>
/// ���t���[���`�揈��
/// </summary>
/// <returns>TRUE</returns>
void BattleScene::DrawLoop(){
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Battle");
}

/// <summary>
/// �I��������
/// </summary>
/// <returns>TRUE</returns>
void BattleScene::Finalize(){
}
