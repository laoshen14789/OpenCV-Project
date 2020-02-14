#include "Serial.h"

int serial_connect(HANDLE& hCom, wchar_t* serialport, int baudrate) {
	hCom = CreateFile(serialport, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);//打开串口，允许读和写，同步方式
	if (hCom == (HANDLE)-1) { 
		printf("串口打开失败\n"); 
		return-1;  
	}
	else printf("串口打开成功\n");
	SetupComm(hCom, 2048, 2048); //输入缓冲区和输出缓冲区的大小都是1024
	COMMTIMEOUTS TimeOuts; //设定读超时
	TimeOuts.ReadIntervalTimeout = 1000;
	TimeOuts.ReadTotalTimeoutMultiplier = 500;
	TimeOuts.ReadTotalTimeoutConstant = 5000; //设定写超时
	TimeOuts.WriteTotalTimeoutMultiplier = 500;
	TimeOuts.WriteTotalTimeoutConstant = 2000;
	SetCommTimeouts(hCom, &TimeOuts); //设置超时
	DCB dcb;
	GetCommState(hCom, &dcb);
	dcb.BaudRate = baudrate;//设置波特率
	dcb.fParity = 0; // 指定奇偶校验使能。若此成员为1，允许奇偶校验检查 …
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY; //指定奇偶校验方法。此成员可以有下列值： EVENPARITY 偶校验 NOPARITY 无校验 MARKPARITY 标记校验 ODDPARITY 奇校验
	dcb.StopBits = ONESTOPBIT; //指定停止位的位数。此成员可以有下列值： ONESTOPBIT 1位停止位 TWOSTOPBITS 2位停止位
	SetCommState(hCom, &dcb);
	PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);
	return 0;
}

int Write(HANDLE hCom, char* lpOutBuffer, int length) {//串口发送
	DWORD dwBytesWrite = (DWORD)length;
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	BOOL bWriteStat;
	OVERLAPPED m_osWrite;//建立Overlapped结构
	m_osWrite.InternalHigh = 0;
	m_osWrite.Offset = 0;
	m_osWrite.OffsetHigh = 0;
	m_osWrite.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);//初始化Overlapped结构
	ClearCommError(hCom, &dwErrorFlags, &ComStat);
	bWriteStat = WriteFile(hCom, lpOutBuffer, dwBytesWrite, &dwBytesWrite, &m_osWrite);//同步写串口
	if (!bWriteStat) {
		return -1;
	}
	PurgeComm(hCom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
	return 0;
}
int Read(HANDLE hCom) {//串口接收
	DWORD dwBytesRead = 1000;
	char* str = new char[(int)dwBytesRead];
	for (int t = 0; t <= (int)dwBytesRead - 1; t++) str[t] = 0;
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	OVERLAPPED m_osRead; //建立Overlapped结构
	memset(&m_osRead, 0, sizeof(OVERLAPPED));
	m_osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	ClearCommError(hCom, &dwErrorFlags, &ComStat);
	dwBytesRead = min(dwBytesRead, (DWORD)ComStat.cbInQue);
	if (!dwBytesRead) {//如果缓冲区为空，那么这里就会返回
		return -1;
	}
	BOOL bReadStatus;
	bReadStatus = ReadFile(hCom, str, dwBytesRead, &dwBytesRead, &m_osRead);//同步读串口，读取缓冲区的内容
	if (!bReadStatus) {
		return -1;
	}
	//if (dwBytesRead) printf("串口接受到的内容为:%d\r\n%s\r\n", (int)dwBytesRead, str);//如果读取出来的缓冲区的内容不为空，那么把读取出来的内容发送出来
	if (dwBytesRead) printf("串口接受到的内容为:%s\r\n",  str);//如果读取出来的缓冲区的内容不为空，那么把读取出来的内容发送出来
	return 0;
}
