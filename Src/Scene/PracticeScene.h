#pragma once
#include "BaseScene.h"
#include "../Parts/Block.h"
#include "../Parts/Player.h"

class PracticeScene : public BaseScene
{
public:
	//�R���X�g���N�^
	PracticeScene(ISceneManager* pChanger, IResourceManager* pResource);
	virtual ~PracticeScene();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void DrawLoop() override;
	virtual void Finalize() override;

private:
	enum BlockPosition{
		BLOCK_POSITION_C,
		BLOCK_POSITION_D,
		BLOCK_POSITION_E,
		BLOCK_POSITION_F,
		BLOCK_POSITION_G,
		BLOCK_POSITION_A,
		BLOCK_POSITION_B
	};

	struct StructIndex{
		int m_nAnimeIndex = Invalid;		//�X�e�[�W�̌����Ԃ��J�E���g
		int m_nFinishStageIndex = Invalid;	//�Q�[���i�s���~�܂�܂ł̃J�E���g
		int m_nMoveSceneIndex = Invalid;	//��ʈړ������܂ł̎��Ԃ��J�E���g
		int m_nFadeoutIndex = Invalid;	//�t�F�[�h�A�E�g�����܂ł��J�E���g
	};

	struct StructFlag{
		int m_bStageClear = FALSE;	//�X�e�[�W�I���t���O
		int m_bGameOver = FALSE;	//�Q�[���I�[�o�[�t���O
		int m_bContinue = FALSE;	//�R���e�B�j���[�t���O
		int m_bFadeout = FALSE;		//�t�F�[�h�A�E�g�t���O
		int m_bReserve = TRUE;		//���ʕۑ��t���O
	};

	struct StructStage{
		const int m_nStandMaxCount = 300;												//�Q�[���ҋ@����
		const int m_nFinishStageCount = 60;												//�Q�[���I���܂ł̎���
		const int m_nFadeoutMaxCount = 180;												//�t�F�[�h�A�E�g����
		int m_nLevel = Level::LEVEL_STANDARD;											//�Q�[�����x��
		int m_nGameScore = 0;																//�Q�[���X�R�A
		int m_nGameHiScore = 0;																//�Q�[���n�C�X�R�A
		int m_nGameMaxCount = 0;															//�X�e�[�W�I���܂ł̎���
		std::string m_sGameRank = "D";													//�Q�[�������N
		std::string m_sGameHiRank = "";													//�Q�[���n�C�X�R�A���̃����N
		const int m_anRankingRate[4] = { 100000, 300000, 600000, 1000000 };	//�����N�グ���l�ꗗ
		int m_nAddRate = 100;																//1F���ɑ�����X�R�A�l
		int m_nRateIndex = 0;																//�����N�グ�v�f�ԍ�
		const int m_nRateMaxIndex = 4;													//�����N�グ�v�f�ő�ԍ�
		const int m_nFieldMinX = (WindowMaxX / 2) - 140;							//�ړ��\�̈捶�[X���W
		const int m_nFieldMaxX = (WindowMaxX / 2) + 140;							//�ړ��\�̈�E�[X���W
		const int m_nFieldUpY = WindowCenY;												//�ړ��\�̈��Y���W
		const int m_nFieldDownY = (int)(WindowCenY * 1.5);							//�ړ��\�̈扺Y���W
	};

	struct StructBlock{
		int m_nBlockCount = Invalid;			//�΂�\�������
		int m_nBlockSpeed = 6;					//�u���b�N�������x
		const int m_nBlockDefaultSpeed = 6;	//�u���b�N�����������x
		const int m_nBlockHeight = 10;		//�u���b�N�\���̍���
		const int m_nBlockWidth = 40;			//�u���b�N�\���̕�
	};

	struct StructPlayer{
		const int m_nHeight = 10;			//�v���C���[�\���̍���
		const int m_nWidth = 40;			//�v���C���[�\���̕�
		int m_nBarIndex = 3;					//�v���C���[���ݒn
		const int m_nBarCount = 7;			//�v���C���[�̃o�[�̐�
	};

	StructIndex* m_pIndexSet;
	StructFlag* m_pFlagSet;
	StructStage* m_pStageSet;
	StructBlock* m_pBlockSet;
	StructPlayer* m_pPlayerSet;

	void InitializeSceneStatus();
	void InitializeBlocks();
	void InitializeBlockList();
	void CreateStageBlocks(int& nGameCount, int& nTimes);

	float CreateOneBeat(const float& fBpm){ return 60.0f * nFps / fBpm; }
	void InitializePlayer();
	int GetPlayerBar();
	void UpdateStageClearProcess();
	void UpdateGameOverProcess();
	void UpdateFadeOutProcess();
	void UpdateGamePlayProcess();
	void UpdateRank(std::string& sRank);
	void UpdateBlocks();
	void UpdatePlayers();
	void UpdateCollisionPlayers(const int& nIndex);
	void UpdateCollisionMovePlayers(const int& nIndex);
	void UpdateBarMovePlayers();
	void DrawLoopBlocks();
	void DrawLoopPlayers();
	int GetDrawMagicHandle();
	void FinalizeBlocks();
	void FinalizePlayers();

	int IsProcess(const int& nKey){ return m_pKey->IsKeyPush(nKey); }
	int IsFixedProcess(const int& nKey){ return m_pKey->IsKeyFixedPush(nKey, 15); }

	std::vector<Block*> m_apBlock;
	std::vector<Player*> m_apPlayer;
	std::vector<int> m_anBlocksXList;
	std::vector<int> m_anBlocksYList;

	int m_nSoundHandle;			//���y�n���h��
};