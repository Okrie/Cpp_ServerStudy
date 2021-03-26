#include "stdafx.h"
#include <iostream>

#include "cSocket.h"

using namespace std;

cSocket::cSocket()
{
    socket_ = INVALID_SOCKET;
    socket_connect_ = INVALID_SOCKET;
    ZeroMemory(sz_socketbuf_, MAX_BUFFER);
}

cSocket::~cSocket()
{
    // winsock 사용을 끝냄
    WSACleanup();
}

bool cSocket::InitSocket()
{
    WSADATA wsaData;
    // 윈속 버전을 2.2버전으로 초기화
    int nRet = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(nRet != 0)
    {
        cout << "[ERROR] : " << WSAGetLastError() << endl;
        return false;
    }

    // TCP 소켓 생성
    socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(socket_ == INVALID_SOCKET)
    {
        cout << "[ERROR] : " << WSAGetLastError() << endl;
        return false;
    }
    
    cout << "socket initialize success." << endl;
    return true;
}

void cSocket::CloseSocket(SOCKET socketClose, bool bIsForce)
{
    struct linger stLinger = {0, 0};    // SO_DONTLINGER로 설정
    // bIsForce가 true면 SO_LINGER, timeout = 0 으로 설정하여
    // 강제 종료 시킨다. 주의 : 데이터 손실이 있을 수 있음
    if(bIsForce == true)
    {
        stLinger.l_onoff = true;
        // socketClose 소켓의 데이터 송수신을 모두 중단
        shutdown(socketClose, SD_BOTH);
        // 소켓 옵션을 설정
        setsockopt(socketClose, SOL_SOCKET, SO_LINGER, (char *)&stLinger, sizeof(stLinger));
        // 소켓 연결을 종료
        closesocket(socketClose);

        socketClose = INVALID_SOCKET;
    }
}

bool cSocket::BindAndListen(int nBindPort)
{
    SOCKADDR_IN stServerAddr;
    stServerAddr.sin_family = AF_INET;
    // 서버 포트를 설정
    stServerAddr.sin_port = htons(nBindPort);
    stServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // 위에서 지정한 서버 주소 정보와 소켓을 연결
    int nRet = bind(socket_, (SOCKADDR *)&stServerAddr, sizeof(SOCKADDR_IN));
    if(nRet != 0)
    {
        cout << "[ERROR] : " << WSAGetLastError() << endl;
        return false;
    }

    // 접속 요청을 받아 들이기 위해 소켓을 등록하고 접속 대기 큐를 5로 설정
    nRet = listen(socket_, 5);
    if(nRet != 0)
    {
        cout << "[ERROR] : " << WSAGetLastError() << endl;
        return false;
    }

    cout << "Server enroll success." << endl;
    return true;
}

bool cSocket::StartServer()
{
    char szOutput[MAX_BUFFER];
    // 접속된 클라이언트의 주소 정보를 저장할 구조체
    SOCKADDR_IN stClientAddr;
    int nAddrLen = sizeof(SOCKADDR_IN);

    cout << "Server Starting..." << endl;

    // 클라이언트의 접속 요청이 들어올 때 까지 대기
    socket_connect_ = accept(socket_, (SOCKADDR *)&stClientAddr, &nAddrLen);
    if(socket_connect_ == INVALID_SOCKET)
    {
        cout << "[ERROR] : " << WSAGetLastError() << endl;
        return false;
    }

    sprintf_s(szOutput, "Client Connect : IP(%s) SOCKET(%d)", inet_ntoa(stClientAddr.sin_addr), socket_connect_);
    cout << szOutput << endl;

    // 클라이언트에서 메시지가 오면 다시 클라이언트에게 보냄
    while(true)
    {
        int nRecvLen = recv(socket_connect_, sz_socketbuf_, MAX_BUFFER, 0);
        if(nRecvLen == 0 || nRecvLen == -1)
        {
            cout << "[ERROR] : " << WSAGetLastError() << endl;
            CloseSocket(socket_connect_);
            
            // 다시 서버를 시작해 접속 요청을 받음
            StartServer();
            return false;
        }

        sz_socketbuf_[nRecvLen] = NULL;
        cout << "message received : bytes[" << nRecvLen << "], message : [" << sz_socketbuf_ << "]" << endl;
        
    }
}