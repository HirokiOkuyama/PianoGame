#include "DxLib.h"
#include "Scene/SceneMgr.h"

extern int IsContinueGame();

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){
	//�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�
	ChangeWindowMode(TRUE);
	SetGraphMode(WindowMaxX, WindowMaxY, 32);

	//���d�N���֎~
	SetDoubleStartValidFlag(FALSE);
	if(DxLib_Init() == Invalid) return Invalid;

	SetDrawScreen(DX_SCREEN_BACK);

	//new�錾���Ȃ��̂ŏI����������delete�����
	SceneMgr m_pManager;
	m_pManager.Initialize();
	while(IsContinueGame() && m_pManager.GetPhase() != PHASE_EXIT){
		m_pManager.Update();
		m_pManager.DrawLoop();
	}
	m_pManager.Finalize();
	DxLib_End();
	return Success;
}

int IsContinueGame(){
	if(ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) return TRUE;
	return FALSE;
}