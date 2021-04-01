// 콘솔 응용 프로그램의 진입점을 정의

#include "stdafx.h"
#include <iostream>
#include <process.h>

#include "cSocket.h"
#include <Windows.h>

#define SERVER_PORT 8000

using namespace std;

int main()
{
    // 소켓 객체 생성
    cSocket socket;
    // 처리용 객체 생성
    
    socket.InitSocket();
    socket.BindAndListen(SERVER_PORT);
    socket.StartServer();
    
    return 0;
}