#pragma once

#include "RequestCodec.h"
#include "RespondCodec.h"

//����ģʽ����  ������
class FactoryCodec
{
public:
	FactoryCodec();
	~FactoryCodec();

	//�������д������󷽷�  ��������
	virtual Codec *createCodec(void *arg = NULL);
};

