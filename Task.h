#pragma once

#ifndef DEF_EXTENSION_H

#define DEF_EXTENSION_H
#define SUCCESS 0
#define INVALID -1

#endif // !DEF_EXTENSION_H

//���N���X
class Task
{
public:
	virtual ~Task(){}

	//=0�ƂȂ��Ă�����̂͌p����Ŏ������Ȃ���΂����Ȃ�
	//{}�ƂȂ��Ă�����̂͌p����Ŏ������Ȃ��Ă��悢
	virtual void Initialize(){}
	virtual void Update() = 0;
	virtual void DrawLoop() = 0;
	virtual void Finalize(){}
};

