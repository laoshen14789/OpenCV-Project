#define _SERIAL_H_
#ifdef _SERIAL_H_
#include <Windows.h>
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
int serial_connect(HANDLE& hCom, wchar_t* serialport, int baudrate);
int Write(HANDLE hCom, char* lpOutBuffer, int length);
int Read(HANDLE hCom);
#endif

