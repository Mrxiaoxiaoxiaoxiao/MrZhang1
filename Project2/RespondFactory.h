#pragma once
#include "FactoryCodec.h"

//����ģʽ  ������  ��Ҫ���𴴽���Ӧ���ı�������
class RespondFactory :public FactoryCodec
{
public:
	RespondFactory();
	~RespondFactory();
	//�������д������󷽷�  ��������
	virtual Codec *createCodec(void *arg = NULL);
};

