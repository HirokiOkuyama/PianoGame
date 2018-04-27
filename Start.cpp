#include "DxLib.h"
#include "SceneMgr.h"

extern int ContinueGame();

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){
	//�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�
	ChangeWindowMode(TRUE);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	//new�錾���Ȃ��̂ŏI����������delete�����
	SceneMgr sceneMgr;
	sceneMgr.Initialize();

	while(ContinueGame() == TRUE && sceneMgr.GetPhase() != PHASE_EXIT){
		sceneMgr.Update();
		sceneMgr.DrawLoop();
	}

	sceneMgr.Finalize();
	DxLib_End();
	return SUCCESS;
}

int ContinueGame(){
	if(ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) return TRUE;
	return FALSE;
}