#include "LoadingScene.h"
#include "DxLib.h"

//string maFileList = {
//	"Picture/001.jpg",
//	"Picture/002.jpg"
//};

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="changer"></param>
LoadingScene::LoadingScene(ISceneManager* pChanger) : BaseScene(pChanger){
}

/// <summary>
/// ����������
/// </summary>
/// <returns>TRUE</returns>
void LoadingScene::Initialize(){
	m_nLoadCount = 0;
	m_nWaitCount = 0;
	//���[�h���
	m_pAnime->SetAnimationCount(450);
	m_anImageHandle.resize(m_nImageHandleCount);

}

/// <summary>
/// ���t���[���X�V����
/// </summary>
/// <returns>TRUE</returns>
void LoadingScene::Update(){
	if(m_nLoadCount < m_nImageHandleCount){
		//�Ƃ肠���������摜�ǂݍ��݂Ŏ��Ԃ�������悤�Ɍ�����
		m_anImageHandle.at(m_nLoadCount) = LoadGraph("Picture/001.jpg");
		m_nLoadCount++;
	}
	else{
		//�Q�[�W100������1�b���Ă��玟�̃V�[����
		if(m_nWaitCount >= 60){
			m_pSceneChanger->ChangeScene(SCENE_MENU);
			SetPhase(PHASE_TITLE);
		}
		m_nWaitCount++;
	}
}

/// <summary>
/// ���t���[���`�揈��
/// </summary>
/// <returns>TRUE</returns>
void LoadingScene::DrawLoop(){
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Load");
	DrawLoadGauge();
}

/// <summary>
/// �I��������
/// </summary>
/// <returns>TRUE</returns>
void LoadingScene::Finalize(){
	m_nLoadCount = 0;
}

void LoadingScene::DrawLoadGauge(){
	//5F����Loading�̌�Ɂu.�v��\�� or ��\��
	std::string loadWord = "Now Loading ";
	int addDotCount = ((m_nLoadCount + m_nWaitCount) % 20) / 5;
	for(int i = 0; i < addDotCount; i++) loadWord.append(".");

	DrawString(0, 350, loadWord.c_str(), GetColor(255, 255, 255));
	DrawFormatString(280, 350, GetColor(255, 255, 255), "%.2f%%", (m_nLoadCount / (float)(m_nImageHandleCount)) * 100.0f);
	DrawBox(0, 382, 300, 406, GetColor(255, 255, 255), TRUE);
	DrawBox(0, 382, m_nLoadCount * 300 / m_nImageHandleCount, 406, GetColor(255, 128, 255), TRUE);
}
