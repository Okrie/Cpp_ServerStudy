// 콘솔 응용 프로그램의 진입점을 정의

#include "stdafx.h"
#include <iostream>
#include <process.h>

#include "cSocket.h"
#include <Windows.h>

#define SERVER_IP "127.0.0.1"
//#define SERVER_IP "220.76.165.94"
#define SERVER_PORT 8000

using namespace std;

int main()
{
    // 소켓 객체 생성
    cSocket socket;
    // 처리용 객체 생성

    socket.InitSocket();
    socket.Connect(SERVER_IP, SERVER_PORT);  
    

    return 0;
}