#include "LoadingScene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="changer"></param>
LoadingScene::LoadingScene(ISceneManager* pChanger, IResourceManager* pResource) : BaseScene(pChanger, pResource){
}

/// <summary>
/// ���t���[���X�V����
/// </summary>
/// <returns>TRUE</returns>
void LoadingScene::Update(){
	if(m_pResource->IsLoadGraphics()) m_nLoadCount++;
	else if(m_pResource->IsLoadSounds()) m_nLoadCount++;
	else{
		if(!m_bFinishScene){
			if(m_pKey->IsKeyPush(KEY_INPUT_Z)) m_bFinishScene = TRUE;
			return;
		}
		//�Q�[�W100������1�b���Ă��玟�̃V�[����
		if(m_nWaitCount >= m_nWaitMaxCount){
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
	int nAlpha = 255 - (255 / m_nWaitMaxCount) * m_nWaitCount;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, nAlpha);
	DrawDescription();
	DrawLoadGauge();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - nAlpha);
	//�t�F�[�h�A�E�g
	DrawGraph(0, 0, m_pResource->GetGraphicsHandle(ResourceImage::IMAGE_PRACTICE_BACKGROUND), FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void LoadingScene::DrawDescription(){
	DrawRotaGraph(WindowCenX, WindowCenY / 2, 1, 0, m_pResource->GetGraphicsHandle(ResourceImage::IMAGE_LOAD_TITLE), TRUE);

	if(m_nLoadCount != m_nResourceCount || m_nWaitCount % 4 / 2 != 0) return;
	DrawRotaGraph(WindowCenX, WindowCenY + 30, 1, 0, m_pResource->GetGraphicsHandle(ResourceImage::IMAGE_LOAD_START), TRUE);
}

void LoadingScene::DrawLoadGauge(){
	float fPi = static_cast<float>(M_PI);
	float fRadian = (2 * fPi / 360) * (GetNowCount() / 2);
	int nAlpha = static_cast<int>(255 - 127 * sinf(fRadian));
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, nAlpha);
	DrawRotaGraph(WindowCenX / 2, 360, 1, 0, m_pResource->GetGraphicsHandle(ResourceImage::IMAGE_LOAD_LOADING), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	int nLength = 50 + static_cast<int>((500.0f / m_nResourceCount) * m_nLoadCount);
	DrawExtendGraph(50, 376, 550, 400, m_pResource->GetGraphicsHandle(ResourceImage::IMAGE_LOAD_GAUGE_EMPTY), TRUE);
	DrawExtendGraph(50, 376, nLength, 400, m_pResource->GetGraphicsHandle(ResourceImage::IMAGE_LOAD_GAUGE_FILL), TRUE);

	float fRatio = (float)m_nLoadCount / (float)m_nResourceCount;
	DrawFormatString(480, 350, GetColor(255, 255, 255), "%.2f%%", fRatio * 100);
}
