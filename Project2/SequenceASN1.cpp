#define _CRT_SECURE_NO_WARNINGS
#include "SequenceASN1.h"

#include <iostream>

using namespace std;

//���캯��
SequenceASN1::SequenceASN1():BaseASN1()
{

}

//�����һ���ڵ�  
int SequenceASN1::writeHeadNode(int iValue)
{
	int ret = 0;
	ret = DER_ItAsn1_WriteInteger(iValue, &m_header);
	if (0 != ret)
	{
		cout << "DER_ItAsn1_WriteInteger failed..." << endl;
		return ret;
	}

	m_next = m_header;

	return 0;
}

int SequenceASN1::writeHeadNode(char * sValue, int len)
{
	int ret = 0;
	//�Ƚ�char* תΪANYBUF����
	ret = DER_ITCAST_String_To_AnyBuf(&m_temp, (unsigned char *)sValue, len);
	if (0 != ret)
	{
		cout << "DER_ITCAST_String_To_AnyBuf failed..." << endl;
		return ret;
	}

	//����char*
	ret = DER_ItAsn1_WritePrintableString(m_temp, &m_header);
	if (0 != ret)
	{
		cout << "DER_ItAsn1_WritePrintableString failed..." << endl;
		//�ͷ���ʱ�ڵ�ռ�
		DER_ITCAST_FreeQueue(m_temp);
		return ret;
	}

	//�ͷ���ʱ�ڵ�ռ�
	DER_ITCAST_FreeQueue(m_temp);

	m_next = m_header;

	return 0;
}

//��Ӻ�̽ڵ�
int SequenceASN1::writeNextNode(int iValue)
{
	int ret = 0;

	//���������з�ͷ���ڵ�
	ret = DER_ItAsn1_WriteInteger(iValue, &m_next->next);
	if (0 != ret)
	{
		cout << "DER_ItAsn1_WriteInteger failed..." << endl;
		return ret;
	}

	//m_nextָ���½ڵ�
	m_next = m_next->next;
	return 0;
}

//��ӽڵ� ������ͷ���
int SequenceASN1::writeNextNode(char * sValue, int len)
{
	int ret = 0;
	//�Ƚ�char* תΪANYBUF����
	ret = DER_ITCAST_String_To_AnyBuf(&m_temp, (unsigned char *)sValue, len);
	if (0 != ret)
	{
		cout << "DER_ITCAST_String_To_AnyBuf failed..." << endl;
		return ret;
	}

	//����char*
	ret = DER_ItAsn1_WritePrintableString(m_temp, &m_next->next);
	if (0 != ret)
	{
		cout << "DER_ItAsn1_WritePrintableString failed..." << endl;
		//�ͷ���ʱ�ڵ�ռ�
		DER_ITCAST_FreeQueue(m_temp);
		return ret;
	}

	//�ͷ���ʱ�ڵ�ռ�
	DER_ITCAST_FreeQueue(m_temp);

	//ָ����������һ���ڵ�
	m_next = m_next->next;

	return 0;
}

//����һ���ڵ�
int SequenceASN1::readHeadNode(int & iValue)
{
	int value;
	int ret = -1;

	//����
	ret = DER_ItAsn1_ReadInteger(m_header, (ITCAST_UINT32 *)&value);
	if (0 != ret)
	{
		cout << "DER_ItAsn1_ReadInteger failed... " << endl;
		return ret;
	}

	iValue = value;

	//ָ����һ���ڵ�
	m_next = m_header->next;

	return 0;
}

//��ȡ��һ���ڵ�
int SequenceASN1::readHeadNode(char * sValue)
{
	int ret = -1;

	//����char*����
	ret = DER_ItAsn1_ReadPrintableString(m_header, &m_temp);
	if (0 != ret)
	{
		cout << "DER_ItAsn1_ReadPrintableString failed.. " << endl;
		return ret;
	}

	//��������
	memcpy(sValue, m_temp->pData, m_temp->dataLen);

	m_next = m_next->next;

	//�ͷ���ʱ�ڵ�ռ�
	DER_ITCAST_FreeQueue(m_temp);

	return 0;
}

//�������������ڵ�
int SequenceASN1::readNextNode(int & iValue)
{
	int value;
	int ret = -1;

	//����
	ret = DER_ItAsn1_ReadInteger(m_next, (ITCAST_UINT32 *)&value);
	if (0 != ret)
	{
		cout << "DER_ItAsn1_ReadInteger failed... " << endl;
		return ret;
	}

	iValue = value;
	
	//ָ����һ���ڵ�
	m_next = m_next->next;

	return 0;
}

//�������������ڵ�
int SequenceASN1::readNextNode(char * sValue)
{
	int ret = -1;

	//����char*����
	ret = DER_ItAsn1_ReadPrintableString(m_next, &m_temp);
	if (0 != ret)
	{
		cout << "DER_ItAsn1_ReadPrintableString failed.. " << endl;
		return ret;
	}

	//��������
	memcpy(sValue, m_temp->pData, m_temp->dataLen);

	m_next = m_next->next;

	//�ͷ���ʱ�ڵ�ռ�
	DER_ITCAST_FreeQueue(m_temp);

	return 0;
}


//�����ṹ��
int SequenceASN1::packSequence(char ** outData, int & outLen)
{
	int ret = 0;

	//�����ṹ��  
	ret = DER_ItAsn1_WriteSequence(m_header, &m_temp);
	if (0 != ret)
	{
		cout << "DER_ItAsn1_WriteSequence failed..." << endl;
		return ret;
	}

#if 0
	cout << "dataLen: " << m_temp->dataLen << endl;
	cout << "data: " << m_temp->pData << endl;
#endif

	//����ռ�
	*outData = new char[m_temp->dataLen + 1];
	if (NULL == *outData)
	{
		//�ͷ���ʱ�ڵ�ռ�
		DER_ITCAST_FreeQueue(m_temp);

		cout << "new outData failed..." << endl;
		return MemoryErr;
	}

	//ʹ��ָ������
	memcpy(*outData, m_temp->pData, m_temp->dataLen);
	outLen = m_temp->dataLen;

	//�ͷ���ʱ�ڵ�ռ�
	DER_ITCAST_FreeQueue(m_temp);

	return 0;
}

//�����ṹ��
int SequenceASN1::unpackSequence(char * inData, int inLen)
{
	int ret = 0;

	//1. ��char*תΪANYBUF����
	ret = DER_ITCAST_String_To_AnyBuf(&m_temp, (unsigned char *)inData, inLen);
	if (0 != ret)
	{
		cout << "DER_ITCAST_String_To_AnyBuf failed..." << endl;
		return ret;
	}

	//2. �����ṹ��
	ret = DER_ItAsn1_ReadSequence(m_temp, &m_header);
	if (0 != ret)
	{
		//3. �ͷ���ʱ�ڵ�ռ�
		DER_ITCAST_FreeQueue(m_temp);

		cout << "DER_ItAsn1_ReadSequence failed..." << endl;

		return ret;
	}

	//3. �ͷ���ʱ�ڵ�ռ�
	DER_ITCAST_FreeQueue(m_temp);

	return 0;
}

void SequenceASN1::freeSequence(ITCAST_ANYBUF * node)
{
	int ret = 0;

	//�ͷ����� m_header
	if (NULL == node)
	{
		DER_ITCAST_FreeQueue(m_header);
	}
	else
	{
		//�ͷŽڵ�
		DER_ITCAST_FreeQueue(node);
	}
}
