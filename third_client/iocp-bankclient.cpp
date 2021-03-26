// iocp-client.cpp : 콘솔 응용 프로그램의 진입점을 정의
//

#include "stdafx.h"
// winsock2 사용을 위해 아래 코멘트 추가
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>

using namespace std;

#define MAX_BUFFER  1024
#define SERVER_PORT 8000
#define SERVER_IP   "127.0.0.1"

struct stSOCKETINFO
{   
    /* data */
    WSAOVERLAPPED overlapped;
    WSABUF databuf;
    SOCKET socket;
    char messageBuffer[MAX_BUFFER];
    int recvBytes;
    int sendBytes;
};

int main()
{
    WSADATA wsaData;
    // 윈속 버전을 2.2로 초기화
    int nRet = WSAStartup(MAKEWORD(2,1), &wsaData);
    if(nRet !=0)
    {
        cout << "ERROR : " << WSAGetLastError() << endl;
        return false;
    }

    // tcp 소켓 생성
    SOCKET clientsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(clientsocket == INVALID_SOCKET)
    {
        cout << "ERROR : " << WSAGetLastError() << endl;
        return false;
    }

    cout << "socket initiallize success." << endl;

    // 접속할 서버 정보를 저장할 구조체
    SOCKADDR_IN stServerAddr;

    char szOutMsg[MAX_BUFFER];
    char sz_socketbuf_[MAX_BUFFER];
    stServerAddr.sin_family = AF_INET;
    // 접속할 서버 포트 및 IP
    stServerAddr.sin_port = htons(SERVER_PORT);
    stServerAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    nRet = connect(clientsocket, (sockaddr *)&stServerAddr, sizeof(sockaddr));
    if(nRet == SOCKET_ERROR)
    {
        cout << "ERROR : " << WSAGetLastError() << endl;
        return false;
    }

    cout << "Connection success..." << endl;
    while(true)
    {
        cout << ">>";
        cin >> szOutMsg;
        if(_strcmpi(szOutMsg, "quit") == 0) break;

        int nSendLen = send(clientsocket, szOutMsg, strlen(szOutMsg), 0);

        if(nSendLen == -1)
        {
            cout << "ERROR : " << GetLastError() << endl;
            return false;
        }
        
        cout << "Message sended : bytes[" << nSendLen << "], message : [" << szOutMsg << "]" << endl;

        int nRecvLen = recv(clientsocket, sz_socketbuf_, 1024, 0);
        if(nRecvLen == 0)
        {
            cout << "ERROR : " << WSAGetLastError() << endl;
            closesocket(clientsocket);
            return false;
        }
        else if(nRecvLen == -1)
        {
            cout << "ERROR : " << WSAGetLastError() << endl;
            closesocket(clientsocket);
            return false;
        }

        sz_socketbuf_[nRecvLen] = NULL;
        cout << "Message received : bytes[" << nRecvLen << "], message : [" << sz_socketbuf_ << "]" << endl;
    }

    closesocket(clientsocket);
    cout << "Client has been terminated..." << endl;

    return 0;
}