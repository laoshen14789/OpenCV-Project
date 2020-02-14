#include "Serial.h"

int serial_connect(HANDLE& hCom, wchar_t* serialport, int baudrate) {
	hCom = CreateFile(serialport, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);//�򿪴��ڣ��������д��ͬ����ʽ
	if (hCom == (HANDLE)-1) { 
		printf("���ڴ�ʧ��\n"); 
		return-1;  
	}
	else printf("���ڴ򿪳ɹ�\n");
	SetupComm(hCom, 2048, 2048); //���뻺����������������Ĵ�С����1024
	COMMTIMEOUTS TimeOuts; //�趨����ʱ
	TimeOuts.ReadIntervalTimeout = 1000;
	TimeOuts.ReadTotalTimeoutMultiplier = 500;
	TimeOuts.ReadTotalTimeoutConstant = 5000; //�趨д��ʱ
	TimeOuts.WriteTotalTimeoutMultiplier = 500;
	TimeOuts.WriteTotalTimeoutConstant = 2000;
	SetCommTimeouts(hCom, &TimeOuts); //���ó�ʱ
	DCB dcb;
	GetCommState(hCom, &dcb);
	dcb.BaudRate = baudrate;//���ò�����
	dcb.fParity = 0; // ָ����żУ��ʹ�ܡ����˳�ԱΪ1��������żУ���� ��
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY; //ָ����żУ�鷽�����˳�Ա����������ֵ�� EVENPARITY żУ�� NOPARITY ��У�� MARKPARITY ���У�� ODDPARITY ��У��
	dcb.StopBits = ONESTOPBIT; //ָ��ֹͣλ��λ�����˳�Ա����������ֵ�� ONESTOPBIT 1λֹͣλ TWOSTOPBITS 2λֹͣλ
	SetCommState(hCom, &dcb);
	PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);
	return 0;
}

int Write(HANDLE hCom, char* lpOutBuffer, int length) {//���ڷ���
	DWORD dwBytesWrite = (DWORD)length;
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	BOOL bWriteStat;
	OVERLAPPED m_osWrite;//����Overlapped�ṹ
	m_osWrite.InternalHigh = 0;
	m_osWrite.Offset = 0;
	m_osWrite.OffsetHigh = 0;
	m_osWrite.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);//��ʼ��Overlapped�ṹ
	ClearCommError(hCom, &dwErrorFlags, &ComStat);
	bWriteStat = WriteFile(hCom, lpOutBuffer, dwBytesWrite, &dwBytesWrite, &m_osWrite);//ͬ��д����
	if (!bWriteStat) {
		return -1;
	}
	PurgeComm(hCom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
	return 0;
}
int Read(HANDLE hCom) {//���ڽ���
	DWORD dwBytesRead = 1000;
	char* str = new char[(int)dwBytesRead];
	for (int t = 0; t <= (int)dwBytesRead - 1; t++) str[t] = 0;
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	OVERLAPPED m_osRead; //����Overlapped�ṹ
	memset(&m_osRead, 0, sizeof(OVERLAPPED));
	m_osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	ClearCommError(hCom, &dwErrorFlags, &ComStat);
	dwBytesRead = min(dwBytesRead, (DWORD)ComStat.cbInQue);
	if (!dwBytesRead) {//���������Ϊ�գ���ô����ͻ᷵��
		return -1;
	}
	BOOL bReadStatus;
	bReadStatus = ReadFile(hCom, str, dwBytesRead, &dwBytesRead, &m_osRead);//ͬ�������ڣ���ȡ������������
	if (!bReadStatus) {
		return -1;
	}
	//if (dwBytesRead) printf("���ڽ��ܵ�������Ϊ:%d\r\n%s\r\n", (int)dwBytesRead, str);//�����ȡ�����Ļ����������ݲ�Ϊ�գ���ô�Ѷ�ȡ���������ݷ��ͳ���
	if (dwBytesRead) printf("���ڽ��ܵ�������Ϊ:%s\r\n",  str);//�����ȡ�����Ļ����������ݲ�Ϊ�գ���ô�Ѷ�ȡ���������ݷ��ͳ���
	return 0;
}
