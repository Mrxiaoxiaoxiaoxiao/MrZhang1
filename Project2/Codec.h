#pragma once

#include "SequenceASN1.h"

class Codec :public SequenceASN1
{
public:
	Codec();
	virtual ~Codec();

	// ���ݱ���
	virtual int msgEncode(char** outData, int &len);
	// ���ݽ���
	virtual void* msgDecode(char *inData, int inLen);
	//�ڴ��ͷ�
	virtual int msgMemFree(void **point);
};

