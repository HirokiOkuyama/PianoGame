#include "DxLib.h"
#include "Animation.h"

Animation::Animation()
{
	m_anAnimationMaxCount.resize(m_nMaxIndex, INVALID);
	m_anAnimationNowCount.resize(m_nMaxIndex, 0);
	m_abAnimation.resize(m_nMaxIndex, INVALID);
	m_anIndexList.reserve(m_nMaxIndex);
}

Animation::~Animation()
{
	m_anAnimationMaxCount.clear();
	m_anAnimationNowCount.clear();
	m_abAnimation.clear();
	m_anIndexList.clear();
}

/// <summary>
/// �������������s���܂��B
/// </summary>
void Animation::Initialize(){
}

/// <summary>
/// ���t���[���`��ȊO�̏������s���܂��B
/// </summary>
void Animation::Update(){
	UpdateAnimation();
}

/// <summary>
/// ���t���[���`�揈�����s���܂��B
/// </summary>
void Animation::DrawLoop(){
	//�f�o�b�O�p�ɕ\�����Ă���
	int a = 0;
	for(unsigned int i = 0; i < 128; i++){
		if(m_anAnimationMaxCount.at(i) != INVALID){
			DrawString(200 + 40 * i, 0, "A", GetColor(0, 255, 255));
			DrawFormatString(200 + 40 * i, 70, GetColor(0, 255, 255), "%d", m_anAnimationMaxCount.at(i));
			DrawFormatString(200 + 40 * i, 50, GetColor(0, 255, 255), "%d", m_anAnimationNowCount.at(i));
			a++;
		}
	}
	DrawFormatString(200, 100, GetColor(0, 255, 192), "%d", a);
}

/// <summary>
/// �I���������s���܂��B
/// </summary>
void Animation::Finalize(){
}

/// <summary>
/// �A�j���[�V������ݒ肵�܂��B
/// </summary>
/// <param name="count">�A�j���[�V�������鎞��</param>
/// <returns>�ݒ肵���z��v�f�ԍ�</returns>
int Animation::SetAnimationCount(int nCount){
	if(nCount < 0) return INVALID;

	auto itrBegin = m_anAnimationMaxCount.begin();
	auto itrEnd = m_anAnimationMaxCount.end();
	auto itrFactor = std::find(itrBegin, itrEnd, INVALID);
	//�v�f�ԍ����擾
	int nIndex = std::distance(itrBegin, itrFactor);

	if(nIndex == m_nMaxIndex) return INVALID;

	m_anAnimationNowCount.at(nIndex) = 0;
	m_anAnimationMaxCount.at(nIndex) = nCount;
	m_abAnimation.at(nIndex) = TRUE;
	m_anIndexList.push_back(nIndex);
	return nIndex;
}

/// <summary>
/// �w��J�E���^���擾���܂��B
/// </summary>
/// <param name="nIndex">�w��v�f�ԍ�</param>
/// <returns>�J�E���^</returns>
int Animation::GetAnimationCount(int nIndex){
	if(nIndex < 0 || nIndex >= m_nMaxIndex || m_anAnimationMaxCount.at(nIndex) == INVALID) return INVALID;
	else return m_anAnimationNowCount.at(nIndex);
}

/// <summary>
/// �w��J�E���^���~���܂��B
/// </summary>
/// <param name="nIndex">�w��v�f�ԍ�</param>
/// <returns></returns>
int Animation::StopAnimation(int nIndex){
	if(nIndex < 0 || nIndex >= m_nMaxIndex || m_anAnimationMaxCount.at(nIndex) == INVALID) return INVALID;

	m_abAnimation.at(nIndex) = FALSE;
	return TRUE;
}

/// <summary>
/// �w��J�E���^���ăJ�E���g���܂��B
/// </summary>
/// <param name="nIndex">�w��v�f�ԍ�</param>
/// <returns></returns>
int Animation::RestartAnimation(int nIndex){
	if(nIndex < 0 || nIndex >= m_nMaxIndex || m_anAnimationMaxCount.at(nIndex) == INVALID) return INVALID;

	m_abAnimation.at(nIndex) = TRUE;
	return TRUE;
}

/// <summary>
/// �o�^�ς݂̃J�E���^��S�Ē�~���܂��B
/// </summary>
/// <returns></returns>
int Animation::StopAllAnimation(){
	int size = m_anIndexList.size();
	for(int i = 0; i < size; i++){
		int index = m_anIndexList.at(i);
		if(m_abAnimation.at(index) != INVALID) m_abAnimation.at(index) = FALSE;
	}
	return TRUE;
}

/// <summary>
/// �o�^�ς݂̃J�E���^��S�čăJ�E���g���܂��B
/// </summary>
/// <returns></returns>
int Animation::RestartAllAnimation(){
	int size = (int)m_anIndexList.size();
	for(int i = 0; i < size; i++){
		int index = m_anIndexList.at(i);
		if(m_abAnimation.at(index) != INVALID) m_abAnimation.at(index) = TRUE;
	}
	return TRUE;
}

/// <summary>
/// ���t���[���J�E���^���Ď����A�I���l�ɒB�����J�E���^���폜���܂��B
/// </summary>
/// <returns></returns>
int Animation::UpdateAnimation(){
	int nIndexSize = (int)m_anIndexList.size();
	if(nIndexSize <= 0) return FALSE;

	std::vector<int> anAnimeDeleteList;
	anAnimeDeleteList.reserve(nIndexSize);

	for(int i = 0; i < nIndexSize; i++){
		int nIndex = m_anIndexList.at(i);

		if(m_anAnimationMaxCount.at(nIndex) == INVALID || m_abAnimation.at(nIndex) == FALSE) continue;

		if(m_anAnimationNowCount.at(nIndex) >= m_anAnimationMaxCount.at(nIndex)){
			m_anAnimationNowCount.at(nIndex) = INVALID;
			m_anAnimationMaxCount.at(nIndex) = INVALID;
			anAnimeDeleteList.push_back(nIndex);
		}
		else m_anAnimationNowCount.at(nIndex)++;
	}

	int nDeleteSize = (int)anAnimeDeleteList.size();
	//�A�j���[�V�������I���������̂�����΍폜
	if(nDeleteSize > 0){
		for(int i = 0; i < nDeleteSize; i++){
			int nIndex = anAnimeDeleteList.at(i);
			auto itrFactor = std::find(m_anIndexList.begin(), m_anIndexList.end(), nIndex);
			int nFindIndex = std::distance(m_anIndexList.begin(), itrFactor);
			m_anIndexList.erase(m_anIndexList.begin() + nFindIndex);
		}
	}

	return TRUE;
}

/// <summary>
/// �����ω��̓����J�E���^�ł��B
/// </summary>
/// <param name="nIndex">�v�f�ԍ�</param>
/// <param name="fStart">nNow = 0�̊J�n�l</param>
/// <param name="fEnd">nNow = nMax�̏I���l</param>
/// <returns>���ݎ��Ԃɑ�������l</returns>
float Animation::GetAnimationSmooth(int nIndex, float fStart, float fEnd){
	if(nIndex < 0 || nIndex >= m_nMaxIndex) return INVALID;
	else if(fStart == fEnd) return fEnd;

	float fNow = (float)m_anAnimationNowCount.at(nIndex);
	float fMax = (float)m_anAnimationMaxCount.at(nIndex);

	float fValue = fStart + (fEnd - fStart) * (fNow / fMax);
	return fValue;
}

/// <summary>
/// �����ω��̓����J�E���^�ł��B
/// </summary>
/// <param name="nIndex">�v�f�ԍ�</param>
/// <param name="fStart">nNow = 0�̊J�n�l</param>
/// <param name="fEnd">nNow = nMax�̏I���l</param>
/// <returns>���ݎ��Ԃɑ�������l</returns>
float Animation::GetAnimationAccelerate(int nIndex, float fStart, float fEnd){
	if(nIndex < 0 || nIndex >= m_nMaxIndex) return INVALID;
	else if(fStart == fEnd) return fEnd;
	
	float fNow = (float)m_anAnimationNowCount.at(nIndex);
	float fMax = (float)m_anAnimationMaxCount.at(nIndex);

	float fValue = fStart + (fEnd - fStart) * std::powf(fNow / fMax, 2.0f);
	return fValue;
}

/// <summary>
/// �����ω��̓����J�E���^�ł��B
/// </summary>
/// <param name="nIndex">�v�f�ԍ�</param>
/// <param name="fStart">nNow = 0�̊J�n�l</param>
/// <param name="fEnd">nNow = nMax�̏I���l</param>
/// <returns>���ݎ��Ԃɑ�������l</returns>
float Animation::GetAnimationSlowDown(int nIndex, float fStart, float fEnd){
	if(nIndex < 0 || nIndex >= m_nMaxIndex) return INVALID;
	else if(fStart == fEnd) return fEnd;
	
	float fNow = (float)m_anAnimationNowCount.at(nIndex);
	float fMax = (float)m_anAnimationMaxCount.at(nIndex);

	float fValue = fStart + (fEnd - fStart) * (1.0f - std::powf(1.0f - (fNow / fMax), 2.0f));
	return fValue;
}

/// <summary>
/// ���������ω��̓����J�E���^�ł��B
/// </summary>
/// <param name="nIndex">�v�f�ԍ�</param>
/// <param name="fStart">nNow = 0�̊J�n�l</param>
/// <param name="fCenter">nNow = nMax / 2�̒��Ԓl</param>
/// <param name="fEnd">nNow = nMax�̏I���l</param>
/// <returns></returns>
float Animation::GetAnimationSmoothLaps(int nIndex, float fStart, float fCenter, float fEnd){
	if(nIndex < 0 || nIndex >= m_nMaxIndex) return INVALID;

	float fNow = (float)m_anAnimationNowCount.at(nIndex);
	float fMiddle = (float)(m_anAnimationMaxCount.at(nIndex) / 2);

	float fValue;
	if(fNow < fMiddle){
		if(fStart == fCenter) return fCenter;
		fValue = fStart + (fCenter - fStart) * (fNow / fMiddle);
	}
	else{
		if(fCenter == fEnd) return fEnd;

		fNow -= fMiddle;
		fValue = fCenter + (fEnd - fCenter) * (fNow / fMiddle);
	}

	return fValue;
}


float Animation::GetAnimationAccelerateLaps(int nIndex, float fStart, float fCenter, float fEnd){
	if(nIndex < 0 || nIndex >= m_nMaxIndex) return INVALID;

	float fNow = (float)m_anAnimationNowCount.at(nIndex);
	float fMiddle = (float)(m_anAnimationMaxCount.at(nIndex) / 2);

	float fValue;
	if(fNow < fMiddle){
		if(fStart == fCenter) return fCenter;
		fValue = fStart + (fCenter - fStart) * std::powf(fNow / fMiddle, 2.0f);
	}
	else{
		if(fCenter == fEnd) return fEnd;

		fNow -= fMiddle;
		fValue = fCenter + (fEnd - fCenter) * std::powf(fNow / fMiddle, 2.0f);
	}

	return fValue;
}


float Animation::GetAnimationSlowDownLaps(int nIndex, float fStart, float fCenter, float fEnd){
	if(nIndex < 0 || nIndex >= m_nMaxIndex) return INVALID;

	float fNow = (float)m_anAnimationNowCount.at(nIndex);
	float fMiddle = (float)(m_anAnimationMaxCount.at(nIndex) / 2);

	float fValue;
	if(fNow < fMiddle){
		if(fStart == fCenter) return fCenter;
		fValue = fStart + (fCenter - fStart) * (1.0f - std::powf(1.0f - (fNow / fMiddle), 2.0f));
	}
	else{
		if(fCenter == fEnd) return fEnd;

		fNow -= fMiddle;
		fValue = fCenter + (fEnd - fCenter) * (1.0f - std::powf(1.0f - (fNow / fMiddle), 2.0f));
	}

	return fValue;
}

float Animation::GetAnimationGravityLaps(int nIndex, float fStart, float fCenter, float fEnd){
	if(nIndex < 0 || nIndex >= m_nMaxIndex) return INVALID;

	float fNow = (float)m_anAnimationNowCount.at(nIndex);
	float fMiddle = (float)(m_anAnimationMaxCount.at(nIndex) / 2);

	if(fNow < fMiddle) return GetAnimationSlowDownLaps(nIndex, fStart, fCenter, fEnd);
	else return GetAnimationAccelerateLaps(nIndex, fStart, fCenter, fEnd);
}