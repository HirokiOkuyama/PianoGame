#pragma once
#include "../Task.h"
#include "../Common/Animation.h"

class Block : public Task
{
public:
	Block(int nDrawX, int nDrawY, int nSpeed, int nHeight, int nWidth, int nHandle, Animation*& pAnime);
	~Block();

	void Update() override;
	void DrawLoop() override;
	
	int GetBlockPositionMinX() const { return m_pStatusSet->m_nBlockX - m_pStatusSet->m_nBlockWidth / 2; };
	int GetBlockPositionMinY() const { return m_pStatusSet->m_nBlockY - m_pStatusSet->m_nBlockHeight / 2; };
	int GetBlockPositionCenX() const { return m_pStatusSet->m_nBlockX; }
	int GetBlockPositionCenY() const { return m_pStatusSet->m_nBlockY; }
	int GetBlockPositionMaxX() const { return m_pStatusSet->m_nBlockX + m_pStatusSet->m_nBlockWidth / 2; };
	int GetBlockPositionMaxY() const { return m_pStatusSet->m_nBlockY + m_pStatusSet->m_nBlockHeight / 2; };
	void SetCollision() { m_pStatusSet->m_bBlockCollision = TRUE; };
	int GetCollision() const { return m_pStatusSet->m_bBlockCollision; };
private:
	struct StructStatus{
		int m_nBlockX;						//�u���b�NX���W
		int m_nBlockY;						//�u���b�NY���W
		int m_nBlockSpeed;				//�u���b�N����
		int m_nBlockHeight;				//�u���b�N�摜����
		int m_nBlockWidth;				//�u���b�N�摜��
		int m_nAlphaCount;				//�u���b�N���ߓx�J�E���^
		int m_bBlockCollision;			//�u���b�N�����蔻��
		int m_nBlockGraphHandle;		//�u���b�N�摜
	};

	StructStatus* m_pStatusSet;
	Animation* m_pAnime;
};

