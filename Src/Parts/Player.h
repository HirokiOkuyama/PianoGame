#pragma once
#include "../Task.h"
#include "../Common/Animation.h"

class Player : public Task
{
public:
	Player(int nPlayerX, int nPlayerY, int nHeight, int nWidth, int nHandle, int nWhiteHandle, int nIndex, Animation*& pAnime);
	~Player();

	void Update() override;
	void DrawLoop() override;

	int GetPlayerPositionMinX() const { return m_pStatusSet->m_nPlayerX - m_pStatusSet->m_nPlayerWidth / 2; }
	int GetPlayerPositionMinY() const { return m_pStatusSet->m_nPlayerY - m_pStatusSet->m_nPlayerHeight / 2; }
	int GetPlayerPositionCenX() const { return m_pStatusSet->m_nPlayerX; }
	int GetPlayerPositionCenY() const { return m_pStatusSet->m_nPlayerY; }
	int GetPlayerPositionMaxX() const { return m_pStatusSet->m_nPlayerX + m_pStatusSet->m_nPlayerWidth / 2; }
	int GetPlayerPositionMaxY() const { return m_pStatusSet->m_nPlayerY + m_pStatusSet->m_nPlayerHeight / 2; }

	void SetCollision() { m_pStatusSet->m_bPlayerCollision = TRUE; }
	int GetCollision() const { return m_pStatusSet->m_bPlayerCollision; }
	void SetFlash(const int& nIndex){ 
		if(m_pStatusSet->m_bPlayerCollision) return;

		if(nIndex == m_pStatusSet->m_nPlayerIndex) m_pStatusSet->m_bPlayerFlash = TRUE;
		else m_pStatusSet->m_bPlayerFlash = FALSE;
	}
	int IsFlash() const { return m_pStatusSet->m_bPlayerFlash; }
private:
	struct StructStatus{
		int m_nPlayerX;							//�v���C���[X���W
		int m_nPlayerY;							//�v���C���[Y���W
		int m_nPlayerHeight;						//�v���C���[�摜����
		int m_nPlayerWidth;						//�v���C���[�摜��
		int m_nPlayerAlphaCount = 0;			//�v���C���[���ߓx�J�E���^
		int m_nPlayerFlashCount = 0;			//�v���C���[�_�ŃJ�E���^
		int m_nPlayerFlashCycleCount = 8;	//1�t���b�V���ɕK�v�ȃJ�E���g
		int m_bPlayerCollision =  FALSE;		//�v���C���[�o�[�̂����蔻��
		int m_nPlayerFlashHandle;				//�v���C���[�摜
		int m_nPlayerStopHandle;				//�v���C���[�摜2
		int m_nPlayerIndex;						//�v���C���[�ԍ�
		int m_bPlayerFlash = FALSE;			//�v���C���[�o�[�_��
	};

	StructStatus* m_pStatusSet;
	Animation* m_pAnime;
};

