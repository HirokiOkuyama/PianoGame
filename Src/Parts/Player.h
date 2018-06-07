#pragma once
#include "../Task.h"
#include "../Common/Animation.h"

class Player : public Task
{
public:
	Player(int nX, int nY, const int& nHandle, const int& nWhiteHandle, const int& nIndex, Animation*& pAnime, const int& nAnimeIndex);
	~Player();

	void Update() override;
	void DrawLoop() override;

	int GetPlayerPositionX() const { return m_pStatusSet->m_nPlayerX; }
	int GetPlayerPositionY() const { return m_pStatusSet->m_nPlayerY; }

	void SetCollision() { m_pStatusSet->m_bCollision = TRUE; }
	int GetCollision() const { return m_pStatusSet->m_bCollision; }
	void ReverseCollision(){ ReverseFlag(m_pStatusSet->m_bCollision); }
	void SetFlash(const int& nIndex){ 
		if(m_pStatusSet->m_bCollision) return;
		if(nIndex == m_pStatusSet->m_nIndex) m_pStatusSet->m_bFlash = TRUE;
		else m_pStatusSet->m_bFlash = FALSE;
	}
	int IsFlash() const { return m_pStatusSet->m_bFlash; }
private:
	struct StructStatus{
		int m_nPlayerX;					//�v���C���[X���W
		int m_nPlayerY;					//�v���C���[Y���W
		int m_nAlphaCount = 0;			//�v���C���[���ߓx�J�E���^
		int m_nFlashCount = 0;			//�v���C���[�_�ŃJ�E���^
		int m_nFlashCycleCount = 8;	//1�t���b�V���ɕK�v�ȃJ�E���g
		int m_bCollision =  FALSE;		//�v���C���[�o�[�̂����蔻��
		int m_nFlashHandle;				//�v���C���[�摜
		int m_nStopHandle;				//�v���C���[�摜2
		int m_nIndex;						//�v���C���[�ԍ�
		int m_bFlash = FALSE;			//�v���C���[�o�[�_��
		int m_nAnimeIndex;				//�A�j���[�V�����v�f�ԍ�
	};

	StructStatus* m_pStatusSet;
	Animation* m_pAnime;
};

