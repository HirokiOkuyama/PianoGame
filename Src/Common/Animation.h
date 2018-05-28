#pragma once
#include "../Task.h"
#include <vector>
#include <math.h>

class Animation : public Task
{
public:
	Animation();
	~Animation();

	void Update() override;
	void UpdateCount(const int& nIndexSize, std::vector<int>& anAnimeDeleteList);
	void DrawLoop() override;

	/// <summary>
	/// �A�j���[�V������ݒ肵�܂��B
	/// </summary>
	/// <param name="count">�A�j���[�V�������鎞��</param>
	/// <returns>�ݒ肵���z��v�f�ԍ�</returns>
	int SetAnimationCount(const int& nCount){
		if(nCount < 0) return Invalid;

		auto itrBegin = m_anAnimationMaxCount.begin();
		auto itrEnd = m_anAnimationMaxCount.end();
		auto itrFactor = std::find(itrBegin, itrEnd, Invalid);
		//�v�f�ԍ����擾
		int nIndex = std::distance(itrBegin, itrFactor);

		if(nIndex == m_nMaxIndex) return Invalid;

		m_anAnimationNowCount.at(nIndex) = 0;
		m_anAnimationMaxCount.at(nIndex) = nCount;
		m_abAnimation.at(nIndex) = TRUE;
		m_anIndexList.push_back(nIndex);
		return nIndex;
	};
	/// <summary>
	/// �w��̎��ԕ��x����A�A�j���[�V������ݒ肵�܂��B
	/// </summary>
	/// <param name="nCount">�A�j���[�V�������鎞��</param>
	/// <param name="nDelayCount">�A�j���[�V�����O�̒x�����鎞��</param>
	/// <returns>�ݒ肵���z��v�f�ԍ�</returns>
	int SetAnimationDelayCount(const int& nCount, const int& nDelayCount){
		if(nDelayCount < 0 || nDelayCount >= INT_MAX) return Invalid;

		int nIndex = SetAnimationCount(nCount);
		if(nIndex == Invalid) return Invalid;

		m_anAnimationDelayNowCount.at(nIndex) = 0;
		m_anAnimationDelayMaxCount.at(nIndex) = nDelayCount;
		return nIndex;
	};
	/// <summary>
	/// �A�j���[�V�����̑��x�����A�A�j���[�V������ݒ肵�܂��B
	/// </summary>
	/// <param name="nCount">�A�j���[�V�������鎞��</param>
	/// <param name="nSpeedCount">�A�j���[�V�������鑬�x</param>
	/// <returns></returns>
	int SetAnimationSpeed(const int& nCount, const int& nSpeedCount){
		if(nSpeedCount < 0 || nSpeedCount >= INT_MAX) return Invalid;

		int nIndex = SetAnimationCount(nCount);
		if(nIndex == Invalid) return Invalid;

		m_anAnimationSpeed.at(nIndex) = nSpeedCount;
		return nIndex;
	}
	/// <summary>
	/// �w��J�E���^���擾���܂��B
	/// </summary>
	/// <param name="nIndex">�w��v�f�ԍ�</param>
	/// <returns>�J�E���^</returns>
	int GetAnimationCount(const int& nIndex) const{
		if(nIndex < 0 || nIndex >= m_nMaxIndex || m_anAnimationMaxCount.at(nIndex) == Invalid) return Invalid;
		return m_anAnimationNowCount.at(nIndex);
	}
	/// <summary>
	/// �w��J�E���^�I���l���擾���܂��B
	/// </summary>
	/// <param name="nIndex">�w��v�f�ԍ�</param>
	/// <returns>�J�E���^</returns>
	int GetAnimationMaxCount(const int& nIndex) const{
		if(nIndex < 0 || nIndex >= m_nMaxIndex || m_anAnimationMaxCount.at(nIndex) == Invalid) return Invalid;
		return m_anAnimationMaxCount.at(nIndex);
	}
	/// <summary>
	/// �w��x���J�E���^���擾���܂��B
	/// </summary>
	/// <param name="nIndex">�w��v�f�ԍ�</param>
	/// <returns>�J�E���^</returns>
	int GetAnimationDelayCount(const int& nIndex) const{
		if(nIndex < 0 || nIndex >= m_nMaxIndex || m_anAnimationDelayMaxCount.at(nIndex) == Invalid) return Invalid;
		return m_anAnimationDelayNowCount.at(nIndex);
	}
	/// <summary>
	/// �w��x���J�E���^�I���l���擾���܂��B
	/// </summary>
	/// <param name="nIndex">�w��v�f�ԍ�</param>
	/// <returns>�J�E���^</returns>
	int GetAnimationDelayMaxCount(const int& nIndex) const {
		if(nIndex < 0 || nIndex >= m_nMaxIndex || m_anAnimationDelayMaxCount.at(nIndex) == Invalid) return Invalid;
		return m_anAnimationDelayMaxCount.at(nIndex);
	}
	/// <summary>
	/// �w��J�E���^�̑��x���擾���܂��B
	/// </summary>
	/// <param name="nIndex">�w��v�f�ԍ�</param>
	/// <returns>�J�E���^</returns>
	int GetAnimationSpeed(const int& nIndex) const{
		if(nIndex < 0 || nIndex >= m_nMaxIndex || m_anAnimationMaxCount.at(nIndex) == Invalid) return Invalid;
		return m_anAnimationSpeed.at(nIndex);
	}
	/// <summary>
	/// �w��J�E���g�ɓ��B�������`�F�b�N���܂��B
	/// </summary>
	/// <param name="nIndex">�w��v�f�ԍ�</param>
	/// <param name="nMatchCount">�w��J�E���g</param>
	/// <returns>TRUE�F�w��J�E���^�ɂȂ����@�AFALSE�F�w��J�E���^�ɂȂ��Ă��Ȃ�</returns>
	int IsMatchedAnimationCount(const int& nIndex, const int& nMatchCount) const{
		if(nIndex < 0 || nIndex >= m_nMaxIndex || m_anAnimationMaxCount.at(nIndex) == Invalid) return Invalid;
		if(nMatchCount < 0 || nMatchCount > m_anAnimationMaxCount.at(nIndex)) return Invalid;

		int bMatch = FALSE;
		if(m_anAnimationNowCount.at(nIndex) == nMatchCount) bMatch = TRUE;
		return bMatch;
	}
	/// <summary>
	/// �w��J�E���^���J�E���g���I�������`�F�b�N���܂��B
	/// </summary>
	/// <param name="nIndex">�w��v�f�ԍ�</param>
	/// <returns>TRUE: �J�E���g���I�����A FALSE�F �J�E���g���I���Ă��Ȃ�</returns>
	int IsFinishedAnimationCount(const int& nIndex) const{
		if(nIndex < 0 || nIndex >= m_nMaxIndex || m_anAnimationNowCount.at(nIndex) == Invalid) return Invalid;

		int bFinish = FALSE;
		if(m_anAnimationNowCount.at(nIndex) == m_anAnimationMaxCount.at(nIndex)) bFinish = TRUE;
		return bFinish;
	}
	/// <summary>
	/// �w��J�E���g�ɓ��B�������`�F�b�N���܂��B
	/// </summary>
	/// <param name="nIndex">�w��v�f�ԍ�</param>
	/// <param name="nMatchCount">�w��J�E���g</param>
	/// <returns>TRUE�F�w��J�E���^�ɂȂ����@�AFALSE�F�w��J�E���^�ɂȂ��Ă��Ȃ�</returns>
	int IsMatchedAnimationDelayCount(const int& nIndex, const int& nMatchCount) const{
		if(nIndex < 0 || nIndex >= m_nMaxIndex || m_anAnimationDelayMaxCount.at(nIndex) == Invalid) return Invalid;
		if(nMatchCount < 0 || nMatchCount > m_anAnimationDelayMaxCount.at(nIndex)) return Invalid;

		int bMatch = FALSE;
		if(m_anAnimationDelayNowCount.at(nIndex) == nMatchCount) bMatch = TRUE;
		return bMatch;
	}
	/// <summary>
	/// �w��x���J�E���^���J�E���g���I�������`�F�b�N���܂��B
	/// </summary>
	/// <param name="nIndex">�w��v�f�ԍ�</param>
	/// <returns>TRUE: �J�E���g���I�����A FALSE�F �J�E���g���I���Ă��Ȃ�</returns>
	int IsFinishedAnimationDelayCount(const int& nIndex) const{
		if(nIndex < 0 || nIndex >= m_nMaxIndex || m_anAnimationDelayNowCount.at(nIndex) == Invalid) return Invalid;

		int bFinish = FALSE;
		if(m_anAnimationDelayNowCount.at(nIndex) == m_anAnimationDelayMaxCount.at(nIndex)) bFinish = TRUE;
		return bFinish;
	}
	/// <summary>
	/// �w��J�E���^���~���܂��B
	/// </summary>
	/// <param name="nIndex">�w��v�f�ԍ�</param>
	/// <returns></returns>
	int StopAnimation(const int& nIndex){
		if(nIndex < 0 || nIndex >= m_nMaxIndex || m_anAnimationMaxCount.at(nIndex) == Invalid) return Invalid;

		m_abAnimation.at(nIndex) = FALSE;
		return TRUE;
	}
	/// <summary>
	/// �w��J�E���^���ăJ�E���g���܂��B
	/// </summary>
	/// <param name="nIndex">�w��v�f�ԍ�</param>
	/// <returns></returns>
	int RestartAnimation(const int& nIndex){
		if(nIndex < 0 || nIndex >= m_nMaxIndex || m_anAnimationMaxCount.at(nIndex) == Invalid) return Invalid;

		m_abAnimation.at(nIndex) = TRUE;
		return TRUE;
	}
	/// /// <summary>
	/// �o�^�ς݂̃J�E���^��S�Ē�~���܂��B
	/// </summary>
	/// <returns></returns>
	int StopAllAnimation(){
		int nSize = (int)m_anIndexList.size();
		for(int i = 0; i < nSize; i++){
			int nIndex = m_anIndexList.at(i);
			if(m_abAnimation.at(nIndex) != Invalid) m_abAnimation.at(nIndex) = FALSE;
		}
		return TRUE;
	}
	/// <summary>
	/// �o�^�ς݂̃J�E���^��S�čăJ�E���g���܂��B
	/// </summary>
	/// <returns></returns>
	int RestartAllAnimation(){
		int nSize = (int)m_anIndexList.size();
		for(int i = 0; i < nSize; i++){
			int nIndex = m_anIndexList.at(i);
			if(m_abAnimation.at(nIndex) != Invalid) m_abAnimation.at(nIndex) = TRUE;
		}
		return TRUE;
	}
	/// <summary>
	/// �w��J�E���^����~���Ă��邩�`�F�b�N���܂��B
	/// </summary>
	/// <param name="nIndex">�w��v�f�ԍ�</param>
	/// <returns></returns>
	int IsStoppedAnimation(const int& nIndex) const{
		if(nIndex < 0 || nIndex >= m_nMaxIndex || m_anAnimationMaxCount.at(nIndex) == Invalid) return Invalid;
		return m_abAnimation.at(nIndex);
	}
	/// <summary>
	/// �o�^�ς݂̃J�E���^���S�Ē�~���Ă��邩�`�F�b�N���܂��B
	/// </summary>
	/// <returns></returns>
	int IsAllStoppedAnimation() const{
		int nSize = (int)m_anIndexList.size();
		int nCount = 0;
		for(int i = 0; i < nSize; i++){
			int nIndex = m_anIndexList.at(i);
			if(m_abAnimation.at(nIndex)) break;
			nCount++;
		}
		int bAllStop = (nCount == nSize);
		return bAllStop;
	}
	/// <summary>
	/// �����ω��̓����J�E���^�ł��B
	/// </summary>
	/// <param name="nIndex">�v�f�ԍ�</param>
	/// <param name="tStart">nNow = 0�̊J�n�l</param>
	/// <param name="tEnd">nNow = nMax�̏I���l</param>
	/// <returns>���ݎ��Ԃɑ�������l</returns>
	template <typename T> T GetAnimationSmooth(const int& nIndex, const T& tStart, const T& tEnd) const{
		if(nIndex < 0 || nIndex >= m_nMaxIndex) return (T)Invalid;
		else if(tStart == tEnd) return tEnd;

		T tNow = (T)m_anAnimationNowCount.at(nIndex);
		T tMax = (T)m_anAnimationMaxCount.at(nIndex);

		T tRatio = tNow / tMax;
		T tValue = tStart + (tEnd - tStart) * tRatio;
		return tValue;
	}
	/// <summary>
	/// �����ω��̓����J�E���^�ł��B
	/// </summary>
	/// <param name="nIndex">�v�f�ԍ�</param>
	/// <param name="tStart">nNow = 0�̊J�n�l</param>
	/// <param name="tEnd">nNow = nMax�̏I���l</param>
	/// <returns>���ݎ��Ԃɑ�������l</returns>
	template <typename T> T GetAnimationAccelerate(const int& nIndex, const T& tStart, const T& tEnd) const{
		if(nIndex < 0 || nIndex >= m_nMaxIndex) return (T)Invalid;
		else if(tStart == tEnd) return tEnd;

		T tNow = (T)m_anAnimationNowCount.at(nIndex);
		T tMax = (T)m_anAnimationMaxCount.at(nIndex);
		T tRatio = (tNow / tMax) * (tNow / tMax);
		T tValue = tStart + (tEnd - tStart) * tRatio;
		return tValue;
	};
	/// <summary>
	/// �����ω��̓����J�E���^�ł��B
	/// </summary>
	/// <param name="nIndex">�v�f�ԍ�</param>
	/// <param name="tStart">nNow = 0�̊J�n�l</param>
	/// <param name="tEnd">nNow = nMax�̏I���l</param>
	/// <returns>���ݎ��Ԃɑ�������l</returns>
	template <typename T> T GetAnimationSlowDown(const int& nIndex, const T& tStart, const T& tEnd) const{
		if(nIndex < 0 || nIndex >= m_nMaxIndex) return (T)Invalid;
		else if(tStart == tEnd) return tEnd;

		T tNow = (T)m_anAnimationNowCount.at(nIndex);
		T tMax = (T)m_anAnimationMaxCount.at(nIndex);
		T tRatio = 1 - (1 - (tNow / tMax)) * (1 - (tNow / tMax));
		T tValue = tStart + (tEnd - tStart) * tRatio;
		return tValue;
	};
	/// <summary>
	/// ���������ω��̓����J�E���^�ł��B
	/// </summary>
	/// <param name="nIndex">�v�f�ԍ�</param>
	/// <param name="tStart">nNow = 0�̊J�n�l</param>
	/// <param name="tCenter">nNow = nMax / 2�̒��Ԓl</param>
	/// <param name="tEnd">nNow = nMax�̏I���l</param>
	/// <returns></returns>
	template <typename T> T GetAnimationSmoothLaps(const int& nIndex, const T& tStart, const T& tCenter, const T& tEnd) const{
		if(nIndex < 0 || nIndex >= m_nMaxIndex) return (T)Invalid;

		T tNow = (T)m_anAnimationNowCount.at(nIndex);
		T tMiddle = (T)(m_anAnimationMaxCount.at(nIndex) / (T)2);
		T tValue;
		if(tNow < tMiddle){
			if(tStart == tCenter) return tCenter;
			T tRatio = tNow / tMiddle;
			tValue = tStart + (tCenter - tStart) * tRatio;
		}
		else{
			if(tCenter == tEnd) return tEnd;
			tNow -= tMiddle;
			T tRatio = tNow / tMiddle;
			tValue = tCenter + (tEnd - tCenter) * tRatio;
		}
		return tValue;
	};
	/// <summary>
	/// �J�n�l�`���Ԓl�A���Ԓl���I���l�܂ł��ꂼ����������ω��̓����J�E���^�ł��B
	/// </summary>
	/// <param name="nIndex">�v�f�ԍ�</param>
	/// <param name="tStart">nNow = 0�̊J�n�l</param>
	/// <param name="tCenter">nNow = nMax / 2�̒��Ԓl</param>
	/// <param name="tEnd">nNow = nMax�̏I���l</param>
	/// <returns></returns>
	template <typename T> T GetAnimationAccelerateLaps(const int& nIndex, const T& tStart, const T& tCenter, const T& tEnd) const{
		if(nIndex < 0 || nIndex >= m_nMaxIndex) return (T)Invalid;

		T tNow = (T)m_anAnimationNowCount.at(nIndex);
		T tMiddle = (T)(m_anAnimationMaxCount.at(nIndex) / (T)2);
		T tValue;
		if(tNow < tMiddle){
			if(tStart == tCenter) return tCenter;
			T tRatio = (tNow / tMiddle) * (tNow / tMiddle);
			tValue = tStart + (tCenter - tStart) * tRatio;
		}
		else{
			if(tCenter == tEnd) return tEnd;
			tNow -= tMiddle;
			T tRatio = (tNow / tMiddle) * (tNow / tMiddle);
			tValue = tCenter + (tEnd - tCenter) * tRatio;
		}
		return tValue;
	};
	/// <summary>
	/// �J�n�l�`���Ԓl�A���Ԓl���I���l�܂ł��ꂼ�ꌸ�������ω��̓����J�E���^�ł��B
	/// </summary>
	/// <param name="nIndex">�v�f�ԍ�</param>
	/// <param name="tStart">nNow = 0�̊J�n�l</param>
	/// <param name="tCenter">nNow = nMax / 2�̒��Ԓl</param>
	/// <param name="tEnd">nNow = nMax�̏I���l</param>
	/// <returns></returns>
	template <typename T> T GetAnimationSlowDownLaps(const int& nIndex, const T& tStart, const T& tCenter, const T& tEnd) const{
		if(nIndex < 0 || nIndex >= m_nMaxIndex) return (T)Invalid;

		T tNow = (T)m_anAnimationNowCount.at(nIndex);
		T tMiddle = (T)(m_anAnimationMaxCount.at(nIndex) / (T)2);

		T tValue;
		if(tNow < tMiddle){
			if(tStart == tCenter) return tCenter;
			T tRatio = 1 - (1 - (tNow / tMiddle)) * (1 - (tNow / tMiddle));
			tValue = tStart + (tCenter - tStart) * tRatio;
		}
		else{
			if(tCenter == tEnd) return tEnd;
			tNow -= tMiddle;
			T tRatio = 1 - (1 - (tNow / tMiddle)) * (1 - (tNow / tMiddle));
			tValue = tCenter + (tEnd - tCenter) * tRatio;
		}
		return tValue;
	};
	/// <summary>
	/// �J�n�l�`���Ԓl�܂Ō����A���Ԓl���I���l�܂ŉ����̉����ω��̓����J�E���^�ł��B
	/// </summary>
	/// <param name="nIndex">�v�f�ԍ�</param>
	/// <param name="tStart">nNow = 0�̊J�n�l</param>
	/// <param name="tCenter">nNow = nMax / 2�̒��Ԓl</param>
	/// <param name="tEnd">nNow = nMax�̏I���l</param>
	/// <returns></returns>
	template <typename T> T GetAnimationGravityLaps(const int& nIndex, const T& tStart, const T& tCenter, const T& tEnd) const{
		if(nIndex < 0 || nIndex >= m_nMaxIndex) return (T)Invalid;

		T tNow = (T)m_anAnimationNowCount.at(nIndex);
		T tMiddle = (T)(m_anAnimationMaxCount.at(nIndex) / (T)2);
		if(tNow < tMiddle) return GetAnimationSlowDownLaps(nIndex, tStart, tCenter, tEnd);
		else return GetAnimationAccelerateLaps(nIndex, tStart, tCenter, tEnd);
	};

	//��nIndex�̃A�j���[�V����������l���擾����p

	/// <summary>
	/// �����ω��̓����J�E���^�ł��B
	/// (�A�j���[�V�����J�E���^��p�����ɒl���o���������p)
	/// </summary>
	/// <param name="tStart">nNow = 0�̊J�n�l</param>
	/// <param name="tEnd">nNow = nMax�̏I���l</param>
	/// <param name="nNow">���ݎ���</param>
	/// <param name="nMax">nNow�̍ő�l</param>
	/// <returns>���ݎ��Ԃɑ�������l</returns>
	template <typename T> T GetMomentSmooth(const T& tStart, const T& tEnd, const int nNow, const int nMax){
		if(tNow <= 0) return tStart;
		if(tStart == tEnd || tNow >= tMax || tMax <= 0) return tEnd;

		T tRatio = (T)nNow / (T)nMax;
		T tValue = tStart + (tEnd - tStart) * tRatio;
		return tValue;
	};
	/// <summary>
	/// �����ω��̓����J�E���^�ł��B
	/// (�A�j���[�V�����J�E���^��p�����ɒl���o���������p)
	/// </summary>
	/// <param name="tStart">nNow = 0�̊J�n�l</param>
	/// <param name="tEnd">nNow = nMax�̏I���l</param>
	/// <param name="nNow">���ݎ���</param>
	/// <param name="nMax">nNow�̍ő�l</param>
	/// <returns>���ݎ��Ԃɑ�������l</returns>
	template <typename T> T GetMomentAccelerate(const T& tStart, const T& tEnd, const int nNow, const int nMax){
		if(tNow <= 0) return tStart;
		if(tStart == tEnd || tNow >= tMax || tMax <= 0) return tEnd;

		T tRatio = ((T)nNow / (T)nMax) * ((T)nNow / (T)nMax);
		T tValue = tStart + (tEnd - tStart) * tRatio;
		return tValue;
	};
	/// <summary>
	/// �����ω��̓����J�E���^�ł��B
	/// (�A�j���[�V�����J�E���^��p�����ɒl���o���������p)
	/// </summary>
	/// <param name="tStart">nNow = 0�̊J�n�l</param>
	/// <param name="tEnd">nNow = nMax�̏I���l</param>
	/// <param name="nNow">���ݎ���</param>
	/// <param name="nMax">nNow�̍ő�l</param>
	/// <returns>���ݎ��Ԃɑ�������l</returns>
	template <typename T> T GetMomentSlowDown(const T& tStart, const T& tEnd, const int nNow, const int nMax){
		if(tNow <= 0) return tStart;
		if(tStart == tEnd || tNow >= tMax || tMax <= 0) return tEnd;

		T tRatio = 1 - (1 - ((T)nNow / (T)nMax)) * (1 - ((T)nNow / (T)nMax));
		T fValue = fStart + (fEnd - fStart) * tRatio;
		return fValue;
	};
private:
	const int m_nMaxIndex = 128;

	std::vector<int> m_anAnimationMaxCount;
	std::vector<int> m_anAnimationNowCount;
	std::vector<int> m_anAnimationDelayNowCount;
	std::vector<int> m_anAnimationDelayMaxCount;
	std::vector<int> m_anAnimationSpeed;
	std::vector<int> m_abAnimation;
	std::vector<int> m_anIndexList;
};

