#include <iostream>
#include <fstream>
#include <random>
#include <iterator>
#include <ctime>
#include "bank.h"
#include <string.h>

using namespace std;

Bank::Bank()
{   // 사용 준비를 위한 초기화
    isOpen = false;
    _init();
}

Bank::~Bank()
{   // 사용 종료후 재사용을 위한 초기화?
    _init();
}


void Bank::_init()
{
    nameId = "";
    fileName = "C:\\c\\Cpp learn\\Cpp_ServerStudy\\data\\";
    bankMoney = 0;
    bankNum = 0;
    str = "";
}

void Bank::displayBank(const char* userName, int bankMoney)
{
    if(bankMoney <= 0)
    {
        cout << "현재 " << userName << "님의 계좌 잔액이 없습니다." << endl;
    }
    else{
        cout << "현재 " << userName << "님의 계좌 잔액은" << bankMoney << "원이 있습니다." << endl;
    }
}

int Bank::moneyCalculator(int calcul, int money, int bankMoney)
{
    char sz_msg[100];
    switch (calcul)
    {
        case 1:
            bankMoney += money;
            sprintf(sz_msg, "%d원 입금. 보유 잔액은 %d원 입니다.", money, bankMoney);
            cout << sz_msg << endl;
            //cout << money << "원 입금. 보유 잔액은 " << bankMoney << "원 입니다." << endl;
            return bankMoney;
        case 2:
            bankMoney -= money;
            sprintf(sz_msg, "%d원 출금. 보유 잔액은 %d원 입니다.", money, bankMoney);
            cout << sz_msg << endl;
            //cout << money << "원 출금. 보유 잔액은 " << bankMoney << "원 입니다." << endl;
            return bankMoney;
        default:
            break;
    }
    return 0;
}

int Bank::choiceMenu(const char* user, int* Money)
{
    int menuNum, changeMoney;

    do{
        cout << "Bank Menu\n 1. 입금\n 2. 출금\n 3. 현재 잔고\n 4. 종료\nInput Menu : ";
        cin >> menuNum;
        switch (menuNum)
        {
            // case 0:
            //     cout << "이름에 맞게 계좌가 개설됩니다.";
            //     break;
            case 1:
                cout << "원하는 입금 금액을 입력해주세요 : ";
                cin >> changeMoney;
                *Money = moneyCalculator(1, changeMoney, *Money);
                break;

            case 2:
                cout << "원하는 출금 금액을 입력해주세요 : ";
                cin >> changeMoney;
                *Money = moneyCalculator(2, changeMoney, *Money);
                break;
            
            case 3:
                displayBank(user, *Money);
                break;

            case 4:
                break;

            case 100:
                cout << "랜덤값 확인 조정\t";
                cout << randNum(1, 400, 3) << endl;
                cout << endl;
                break;

            default:
                cout << "번호를 잘못 입력하셨습니다. 다시 입력해주세요" << endl;
                //break;
        }
    }while(menuNum<4 | menuNum == 100);

    return *Money;
}

int Bank::randNum(int a1, int a2, int r)
{
    srand((unsigned int)time(NULL));
    int raNd = rand()*rand()+rand();
    random_device rd;
    mt19937 gen(rd()+raNd);
    uniform_int_distribution<int> dis(a1, a2);

    return dis(gen);
}

void Bank::bankSystem(const char* userName, char* sz_msg)
{
    vector<string> strlist;
    string nameU = userName;
    string temp;

    ifstream file;
    file.open(fileName + userName + ".txt");
    if(!file.is_open())
    {
        sprintf(sz_msg, "No Data\n Create New Data");
        cout << sz_msg << endl;
        //cout << "No Data\n Create New Data" << endl;

        ofstream newFile;
        newFile.open(fileName + userName + ".txt");
        newFile << userName << "," << randNum(10000000, 99999999, rand()%11111) << "," << bankMoney << endl; //계좌가 없으면 user의 계좌 생성
        newFile.close();
        file.close();
        isOpen = false;
    }else   isOpen = true;

    if(!isOpen){
        file.open(fileName + userName + ".txt");
    }    
    if(file.is_open())
    {
        sprintf(sz_msg, "Bank System is On");
        cout << sz_msg << endl;
        //cout << "Bank System is On" << endl;
        
        while(!file.eof())
        {
            cout << "????" << endl;
            getline(file, str, ',');
            strlist.push_back(str);
        }
        bankNum = stoi(strlist.at(1));
        bankMoney = stoi(strlist.at(strlist.size()-1));
        cout << "!!!!" << endl;
    }

    float rateNum = randNum(1, 400, rand()%11111)/(100.0f);

    sprintf(sz_msg, "어서오세요. %s님\n 오늘의 이자율은 %.3f % 입니다.", userName, rateNum);
    cout << sz_msg << endl;
    //cout << "어서오세요. " << userName << "님\n 오늘의 이자율은 " << rateNum << "% 입니다.\n" << endl;
    
    choiceMenu(userName, &bankMoney);
    
    sprintf(sz_msg, "\n업무를 종료합니다.");
    cout << sz_msg;
    //cout << "\n업무를 종료합니다." << endl;
    bankMoney += bankMoney*rateNum/100; //업무 종료 후 이자 더함
    file.close();

    //save data
    ofstream saveFile;
    saveFile.open(fileName + userName + ".txt", ios_base::app);
    saveFile << userName << "," << bankNum << "," << bankMoney << endl;
    saveFile.close();
    
}
