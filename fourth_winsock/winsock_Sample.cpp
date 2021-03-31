// 콘솔 응용 프로그램의 진입점을 정의

#include "stdafx.h"
#include <iostream>
#include <process.h>

#include "cSocket.h"
#include "bank.h"
#include <Windows.h>

//#define SERVER_IP "okrie.kro.kr"
#define SERVER_IP "220.76.165.94"
#define SERVER_PORT 8000

using namespace std;

int main()
{
    // 소켓 객체 생성
    cSocket socket;
    // 처리용 객체 생성

    int test;
    cout << "server 1 / client 2 : ";
    cin >> test;

    // echo 서버로 시작
    if(test == 1)
    {
        socket.InitSocket();
        socket.BindAndListen(SERVER_PORT);
        socket.StartServer();
    }
    // echo 클라이언트로 시작
    else if(test == 2)
    {
        socket.InitSocket();
        socket.Connect(SERVER_IP, SERVER_PORT);  
    }
    else{
        cout << "type 1 or 2" << endl;
        return 0;
    }

    return 0;
}