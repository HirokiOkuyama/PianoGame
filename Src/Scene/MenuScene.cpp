#define _USE_MATH_DEFINES
#include "MenuScene.h"
#include <math.h>

MenuScene::MenuScene(ISceneManager* pChanger, IResourceManager* pResource) : BaseScene(pChanger, pResource)
{
	for(int i = 0; i < (int)Level::LEVEL_UNKNOWN; i++){
		if(m_apData[i] == nullptr) m_apData[i] = new StructReplayData();
	}
	if(m_pCursor == nullptr) m_pCursor = new StructCursor();
}

MenuScene::~MenuScene(){
	for(int i = 0; i < (int)Level::LEVEL_UNKNOWN; i++){
		if(m_apData[i] != nullptr) delete m_apData[i];
	}
	if(m_pCursor != nullptr) delete m_pCursor;
}

/// <summary>
/// ����������
/// </summary>
/// <returns>TRUE</returns>
void MenuScene::Initialize(){
	m_pCursor->m_nConfigBGMCursorPos = GetGameDataVolumeBGM() / 5;
	m_pCursor->m_nConfigSECursorPos = GetGameDataVolumeSE() / 5;
	for(int i = 0; i < (int)Level::LEVEL_UNKNOWN; i++){
		m_apData[i]->m_sDateTime = GetGameDataDateTime(i);
		m_apData[i]->m_nScore = GetGameDataScore(i);
		m_apData[i]->m_sRank = GetGameDataRank(i);
	}
}

/// <summary>
/// ���t���[���X�V����
/// </summary>
/// <returns>TRUE</returns>
void MenuScene::Update(){
	UpdateAlphaCount();
	UpdateMoveCursorAction();
	UpdateGoKeyAction();
	UpdateCancelKeyAction();
}

void MenuScene::UpdateAlphaCount(){
	if(m_nLoopAlphaNowCount == 0) m_nAnimeLoopIndex = m_pAnime->SetAnimationCount(m_nLoopAlphaMaxCount);
	m_nLoopAlphaNowCount = (m_nLoopAlphaNowCount + 1) % m_nLoopAlphaMaxCount;
}

/// <summary>
/// �I��������
/// </summary>
/// <returns>TRUE</returns>
void MenuScene::Finalize(){
	SetGameDataVolumeBGM(m_pCursor->m_nConfigBGMCursorPos * 5);
	SetGameDataVolumeSE(m_pCursor->m_nConfigSECursorPos * 5);
}

/// <summary>
/// �J�[�\���ړ��������̏������s���܂��B
/// </summary>
void MenuScene::UpdateMoveCursorAction(){
	if(m_bOKKeyPush || m_bCancelKeyPush || GetPhase() == (int)Phase::PHASE_RESULT) return;

	if(!m_bLeftKeyPush && !m_bRightKeyPush && !m_bUpKeyPush && !m_bDownKeyPush) MoveCursorKeyPushCheck();
	else{
		//��]�ړ��̃t�F�[�Y���Ɏg�p
		if(GetPhase() == PHASE_TITLE){
			int nMove = (m_bLeftKeyPush ? -1 : 1);
			float fDivAngle = 360.0f / m_pCursor->m_nMainCursorMaxPos;
			float fFromAngle = fDivAngle * m_pCursor->m_nMainCursorPos;
			float fToAngle = fDivAngle * (m_pCursor->m_nMainCursorPos + nMove);
			m_nDrawMenuNowAngle = m_pAnime->GetAnimationSlowDown(m_nAnimeIndex, fFromAngle, fToAngle);
		}

		if(!m_pAnime->IsMatchedAnimationCount(m_nAnimeIndex, m_nMoveCursorCount)) return;
		MoveCursorProcess();
	}
}

void MenuScene::MoveCursorKeyPushCheck(){
	int bConfigExit = (m_pCursor->m_nConfigCursorPos == (int)ConfigCursor::CURSOR_CONFIG_EXIT);
	if(CheckHitKey(KEY_INPUT_LEFT)){
		if(GetPhase() == (int)Phase::PHASE_CONFIG && bConfigExit) return;
		m_bLeftKeyPush = TRUE;
		m_nAnimeIndex = m_pAnime->SetAnimationCount(m_nMoveCursorCount);
		SetGameDataVolumeBGM(m_pCursor->m_nConfigBGMCursorPos * 5);
		SetGameDataVolumeSE(m_pCursor->m_nConfigSECursorPos * 5);
	}
	else if(CheckHitKey(KEY_INPUT_RIGHT)){
		if(GetPhase() == (int)Phase::PHASE_CONFIG && bConfigExit) return;
		m_bRightKeyPush = TRUE;
		m_nAnimeIndex = m_pAnime->SetAnimationCount(m_nMoveCursorCount);
		SetGameDataVolumeBGM(m_pCursor->m_nConfigBGMCursorPos * 5);
		SetGameDataVolumeSE(m_pCursor->m_nConfigSECursorPos * 5);
	}
	else if(CheckHitKey(KEY_INPUT_UP)){
		if(GetPhase() == (int)Phase::PHASE_TITLE) return;
		m_bUpKeyPush = TRUE;
		m_nAnimeIndex = m_pAnime->SetAnimationCount(m_nMoveCursorCount);
	}
	else if(CheckHitKey(KEY_INPUT_DOWN)){
		if(GetPhase() == (int)Phase::PHASE_TITLE) return;
		m_bDownKeyPush = TRUE;
		m_nAnimeIndex = m_pAnime->SetAnimationCount(m_nMoveCursorCount);
	}
}

void MenuScene::MoveCursorProcess(){
	int nPhase = GetPhase();
	int& nCursorPos = GetCursorPos();
	const int& nCursorMaxPos = GetCursorMaxPos();
	int& nConfigCursorPos = GetVolumeCursorPos();
	const int& nConfigCursorMaxPos = GetVolumeCursorMaxPos();

	if(m_bLeftKeyPush){
		m_bLeftKeyPush = FALSE;
		if(GetPhase() != (int)PHASE_CONFIG) nCursorPos = (nCursorPos + (nCursorMaxPos - 1)) % nCursorMaxPos;
		else if(nConfigCursorPos > 0) nConfigCursorPos--;
	}
	else if(m_bRightKeyPush){
		m_bRightKeyPush = FALSE;
		if(GetPhase() != (int)PHASE_CONFIG) nCursorPos = (nCursorPos + 1) % nCursorMaxPos;
		else if(nConfigCursorPos < nConfigCursorMaxPos) nConfigCursorPos++;
	}
	else if(m_bUpKeyPush){
		m_bUpKeyPush = FALSE;
		nCursorPos = (nCursorPos + (nCursorMaxPos - 1)) % nCursorMaxPos;
	}
	else if(m_bDownKeyPush){
		m_bDownKeyPush = FALSE;
		nCursorPos = (nCursorPos + 1) % nCursorMaxPos;
	}
}

int& MenuScene::GetCursorPos(){
	switch(GetPhase()){
	case (int)Phase::PHASE_TITLE:
		return m_pCursor->m_nMainCursorPos;
	case (int)Phase::PHASE_LEVEL:
		return m_pCursor->m_nLevelCursorPos;
	default:
		return m_pCursor->m_nConfigCursorPos;
	}
}

const int& MenuScene::GetCursorMaxPos(){
	switch(GetPhase()){
	case (int)Phase::PHASE_TITLE:
		return m_pCursor->m_nMainCursorMaxPos;
	case (int)Phase::PHASE_LEVEL:
		return m_pCursor->m_nLevelCursorMaxPos;
	default:
		return m_pCursor->m_nConfigCursorMaxPos;
	}
}

int& MenuScene::GetVolumeCursorPos(){
	switch(m_pCursor->m_nConfigCursorPos){
	case (int)ConfigCursor::CURSOR_CONFIG_VOLUME_BGM:
		return m_pCursor->m_nConfigBGMCursorPos;
	case (int)ConfigCursor::CURSOR_CONFIG_VOLUME_SE:
		return m_pCursor->m_nConfigSECursorPos;
	default:
		return m_pCursor->m_nConfigCursorPos;
	}
}

const int& MenuScene::GetVolumeCursorMaxPos(){
	switch(m_pCursor->m_nConfigCursorPos){
	case (int)ConfigCursor::CURSOR_CONFIG_VOLUME_BGM:
		return m_pCursor->m_nConfigBGMCursorMaxPos;
	case (int)ConfigCursor::CURSOR_CONFIG_VOLUME_SE:
		return m_pCursor->m_nConfigSECursorMaxPos;
	default:
		return m_pCursor->m_nConfigCursorPos;
	}
}

/// <summary>
/// ����L�[���������Ƃ��̏������s���܂��B
/// </summary>
void MenuScene::UpdateGoKeyAction(){
	if(m_bLeftKeyPush || m_bRightKeyPush || m_bCancelKeyPush) return;

	const int& nPhase = GetPhase();
	if(!m_bOKKeyPush){
		if(!CheckHitKey(KEY_INPUT_Z)) return;
		if(nPhase == (int)Phase::PHASE_CONFIG && m_pCursor->m_nConfigCursorPos == (int)ConfigCursor::CURSOR_CONFIG_EXIT){
			m_bCancelKeyPush = TRUE;
			SetPhase(PHASE_TITLE);
		}
		else m_bOKKeyPush = TRUE;
		m_nAnimeIndex = m_pAnime->SetAnimationCount(m_nMovePhaseCount);
	}
	else{
		if(!m_pAnime->IsMatchedAnimationCount(m_nAnimeIndex, m_nMovePhaseCount)) return;
		m_bOKKeyPush = FALSE;

		switch(nPhase){
		case (int)Phase::PHASE_TITLE:
			//CursorPos-> 0:Level, 1:Result, 2:Config, 3:Exit
			SetPhase((Phase)(m_pCursor->m_nMainCursorPos + 1));
			break;
		case (int)Phase::PHASE_LEVEL:
			SetPhase(PHASE_GAMEPLAY);
			SetLevel((Level)m_pCursor->m_nLevelCursorPos);
			m_pSceneChanger->ChangeScene(SCENE_PRACTICE);
			break;
		default:
			break;
		}
	}
}

/// <summary>
/// �߂�L�[���������Ƃ��̏������s���܂��B
/// </summary>
void MenuScene::UpdateCancelKeyAction(){
	if(m_bLeftKeyPush || m_bRightKeyPush || m_bOKKeyPush) return;
	if(!m_bCancelKeyPush){
		if(!CheckHitKey(KEY_INPUT_X) || GetPhase() == (int)Phase::PHASE_TITLE) return;
		m_bCancelKeyPush = TRUE;
		m_nAnimeIndex = m_pAnime->SetAnimationCount(m_nMovePhaseCount);
		SetPhase(PHASE_TITLE);
	}
	else{
		if(!m_pAnime->IsMatchedAnimationCount(m_nAnimeIndex, m_nMovePhaseCount)) return;
		m_bCancelKeyPush = FALSE;
	}
}

/// <summary>
/// ���t���[���`�揈��
/// </summary>
/// <returns>TRUE</returns>
void MenuScene::DrawLoop(){
	const int& nPhase = GetPhase();
	if(nPhase >= PHASE_EXIT) return;
	int nTitleX = 280;
	int nTitleY = 50;
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Menu");

	switch(nPhase){
	case (int)Phase::PHASE_TITLE:
		DrawString(nTitleX, nTitleY, "Title", GetColor(255, 0, 255));
		DrawPhaseTitle();
		break;
	case (int)Phase::PHASE_LEVEL:
		DrawString(nTitleX, nTitleY, "Level Select", GetColor(255, 0, 255));
		DrawPhaseLevel();
		break;
	case (int)Phase::PHASE_RESULT:
		DrawString(nTitleX, nTitleY, "Result", GetColor(255, 0, 255));
		DrawPhaseResult();
		break;
	case (int)Phase::PHASE_CONFIG:
		DrawString(nTitleX, nTitleY, "Config", GetColor(255, 0, 255));
		DrawPhaseConfig();
		break;
	default:
		break;
	}
}

void MenuScene::DrawPhaseTitle(){
	int& nCursorPos = m_pCursor->m_nMainCursorPos;
	//�I�𒆂̃J�[�\�����~��̉����ɂ��邽�߂�pi/2�������炷
	float fPi = (float)M_PI;
	float fCycle = (2 * fPi) / 360;
	float fAngle = fCycle * m_nDrawMenuNowAngle + fPi / 2;
	std::string asDisplayWord[4] = { "Practice Mode", "Result Mode", "Config", "Exit" };

	float fMoveX = 0.0f;
	if(m_bOKKeyPush) fMoveX = m_pAnime->GetAnimationSmooth(m_nAnimeIndex, 0.0f, 500.0f);
	else if(m_bCancelKeyPush) fMoveX = m_pAnime->GetAnimationSmooth(m_nAnimeIndex, 500.0f, 0.0f);
	DrawStringF(320.0f + fMoveX, 250.0f, "��", GetColor(255, 64, 255));

	for(int i = 0; i < m_pCursor->m_nMainCursorMaxPos; i++){
		float fX = 280.0f + 10 * i + 200.0f * cosf(fAngle - fPi / 2 * i);
		float fY = 240.0f + 30.0f * sinf(fAngle - fPi / 2 * i);
		const char* sData = asDisplayWord[i].c_str();

		float fAlpha = 1.0f;
		if(m_bOKKeyPush){
			if(i == nCursorPos) fAlpha = m_pAnime->GetAnimationSlowDownLaps(m_nAnimeLoopIndex, 0.0f, 1.0f, 0.0f);
			else fAlpha = m_pAnime->GetAnimationSlowDown(m_nAnimeIndex, 1.0f, 0.0f);
		}
		else if(m_bCancelKeyPush) fAlpha = m_pAnime->GetAnimationAccelerate(m_nAnimeIndex, 0.0f, 1.0f);
		unsigned int nColor = GetColor((int)(255 * fAlpha), (int)(64 * fAlpha), (int)(255 * fAlpha));
		DrawStringF(fX, fY, sData, nColor);
	}
	DrawStringF(320.0f - fMoveX, 290.0f, "��", GetColor(255, 64, 255));
}

void MenuScene::DrawPhaseLevel(){
	const char* asLevel[3] = { "Beginner", "Standard", "Hard" };
	int& nCursorPos = m_pCursor->m_nLevelCursorPos;
	const int& nCursorMaxPos = m_pCursor->m_nLevelCursorMaxPos;
	int nHalfPos = (nCursorMaxPos - 1) / 2;	//nMaxPos�������̎��͐؂�̂�nMaxPos=4 => nHalfPos=1)
	float fDiffX = 15.0f;
	float fDiffY = 20.0f;
	float fMoveX = (m_bLeftKeyPush ? fDiffX : (m_bRightKeyPush ? -fDiffX : 0.0f));
	float fMoveY = (m_bLeftKeyPush ? fDiffY : (m_bRightKeyPush ? -fDiffY : 0.0f));

	//nCursorPos>0�Ƃ��邽�߂ɁA0<=i<nMaxPos�ł͂Ȃ��AnMaxPos<=i<2*nMaxPos�Ƃ���
	for(int i = nCursorMaxPos; i < 2 * nCursorMaxPos; i++){
		//�����`��͏ォ�珇��nHalfPos,nHalfPos+1,�c,nMaxPos,0,1,�c,nHalfPos-1,nHalfPos�ƕ\��
		int nDrawCursorPos = (i + nHalfPos - nCursorPos) % nCursorMaxPos;

		float fStartX = 200.0f + fDiffX * nDrawCursorPos;
		float fStartY = 200.0f + fDiffY * nDrawCursorPos;
		float fEndX = fStartX + fMoveX;
		float fEndY = fStartY + fMoveY;
		float fFlash = m_pAnime->GetAnimationSlowDownLaps(m_nAnimeLoopIndex, 0.0f, 1.0f, 0.0f);
		float fAlpha = (nCursorPos == (i % nCursorMaxPos) ? fFlash : 1.0f);
		float fAnimeX = m_pAnime->GetAnimationSlowDown(m_nAnimeIndex, fStartX, fEndX);
		float fAnimeY = m_pAnime->GetAnimationSlowDown(m_nAnimeIndex, fStartY, fEndY);

		int bFadeOut = (m_bLeftKeyPush && nDrawCursorPos == nCursorMaxPos - 1) || (m_bRightKeyPush && nDrawCursorPos == 0);
		if(bFadeOut){
			fAlpha = m_pAnime->GetAnimationSlowDown(m_nAnimeIndex, 1.0f, 0.0f);

			//�����ɓ�������(�摜)����or������t�F�[�h�C��
			float fNewStartX = (m_bLeftKeyPush ? 200.0f - fDiffX : 200.0f + nCursorMaxPos * fDiffX);
			float fNewStartY = (m_bLeftKeyPush ? 200.0f - fDiffY : 200.0f + nCursorMaxPos * fDiffY);
			float fNewEndX = fNewStartX + fMoveX;
			float fNewEndY = fNewStartY + fMoveY;
			float fNewAlpha = 1.0f - fAlpha;
			float fNewAnimeX = m_pAnime->GetAnimationSlowDown(m_nAnimeIndex, fNewStartX, fNewEndX);
			float fNewAnimeY = m_pAnime->GetAnimationSlowDown(m_nAnimeIndex, fNewStartY, fNewEndY);
			unsigned int nNewColor = GetColor((int)(255 * fNewAlpha), (int)(255 * fNewAlpha), (int)(255 * fNewAlpha));
			DrawStringF(fNewAnimeX, fNewAnimeY, asLevel[i % nCursorMaxPos], nNewColor);
		}

		unsigned int nColor = GetColor((int)(255 * fAlpha), (int)(255 * fAlpha), (int)(255 * fAlpha));
		DrawStringF(fAnimeX, fAnimeY, asLevel[i % nCursorMaxPos], nColor);
	}
}

void MenuScene::DrawPhaseResult(){
	std::string asLevel[3] = { "Begginer", "Standard", "Hard" };
	unsigned int nColor = GetColor(255, 255, 255);
	int nBaseX = 100;
	int nBaseY = 200;
	DrawString(nBaseX, nBaseY - 40, "Level", nColor);
	DrawString(nBaseX + 80, nBaseY - 40, "�V�L�^�X�V���t", nColor);
	DrawString(nBaseX + 290, nBaseY - 40, "�X�R�A", nColor);
	DrawString(nBaseX + 350, nBaseY - 40, "�����N", nColor);
	for(int i = 0; i < (int)Level::LEVEL_UNKNOWN; i++){
		int nX = nBaseX;
		int nY = nBaseY + 50 * i;
		DrawString(nX, nY, asLevel[i].c_str(), nColor);
		DrawString(nX + 80, nY, GetGameDataDateTime(i).c_str(), nColor);
		DrawFormatString(nX + 290, nY, nColor, "%d", GetGameDataScore(i));
		DrawString(nX + 350, nY, GetGameDataRank(i).c_str(), nColor);
	}
}

void MenuScene::DrawPhaseConfig(){
	DrawString(180, 180 + 30 * m_pCursor->m_nConfigCursorPos, "->", GetColor(255, 255, 255));

	int nGaugeMinX = 200;
	int nGaugeMaxX = 350;
	int nColor = GetColor(255, 255, 255);
	float fBGMPercent = (float)m_pCursor->m_nConfigBGMCursorPos / (float)m_pCursor->m_nConfigBGMCursorMaxPos;
	float fSEPercent = (float)m_pCursor->m_nConfigSECursorPos / (float)m_pCursor->m_nConfigSECursorMaxPos;
	float afPercent[2] = { fBGMPercent, fSEPercent };
	int nBGMGaugeX = nGaugeMinX + (int)((nGaugeMaxX - nGaugeMinX) * fBGMPercent);
	int nSEGaugeX = nGaugeMinX + (int)((nGaugeMaxX - nGaugeMinX) * fSEPercent);
	int anGaugeX[2] = { nBGMGaugeX, nSEGaugeX };
	for(int i = 0; i < m_pCursor->m_nConfigCursorMaxPos - 1; i++){
		int nDiffY = 30 * i;
		DrawString(50, 180 + nDiffY, "Volume BGM", nColor);
		DrawBox(200, 180 + nDiffY, 350, 200 + nDiffY, nColor, FALSE);
		DrawBox(200, 180 + nDiffY, anGaugeX[i], 200 + nDiffY, nColor, TRUE);
		DrawFormatString(370, 180 + nDiffY, nColor, "%.2f%%", afPercent[i] * 100);
	}
	DrawString(200, 240, "Back", nColor);
}

void MenuScene::DrawFixMenu(const char* asList[]){
	int nCursorPos = m_pCursor->m_nMainCursorPos;
	int nCursorMaxPos = m_pCursor->m_nMainCursorMaxPos;

}

