#pragma once
#include "FactoryCodec.h"


//������  ֻ���𴴽������ı�������
class RequestFactory : public FactoryCodec
{
public:
	RequestFactory();
	~RequestFactory();

	virtual Codec *createCodec(void *arg = NULL);
};

