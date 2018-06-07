#pragma once
#include "../Task.h"
#include "../Common/Animation.h"

class Block : public Task
{
public:
	Block(int nX, int nY, int nSpeed, int nPos, int nHandle, Animation*& pAnime, const int& nIndex);
	~Block();

	void Update() override;
	void DrawLoop() override;
	
	int GetBlockPositionX() const { return m_pStatusSet->m_nBlockX; }
	int GetBlockPositionY() const { return m_pStatusSet->m_nBlockY; }
	void SetBlockHandle(const int& nHandle) { m_pStatusSet->m_nHandle = nHandle; }
	int GetBlockHandle() const { return m_pStatusSet->m_nHandle; }
	void SetCollision() { m_pStatusSet->m_bCollision = TRUE; }
	int GetCollision() const { return m_pStatusSet->m_bCollision; }
	int GetBlockIndex() const { return m_pStatusSet->m_nPos; }
private:
	struct StructStatus{
		int m_nBlockX;			//�u���b�NX���W
		int m_nBlockY;			//�u���b�NY���W
		int m_nPos;				//�u���b�N�v�f�ԍ�
		int m_nSpeed;			//�u���b�N����
		int m_nAlphaCount;	//�u���b�N���ߓx�J�E���^
		int m_bCollision;		//�u���b�N�����蔻��
		int m_nHandle;			//�u���b�N�摜
		int m_nIndex;			//�u���b�N�A�j���[�V��������v�f
	};

	StructStatus* m_pStatusSet;
	Animation* m_pAnime;
};

