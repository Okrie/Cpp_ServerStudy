#include <iostream>
#include <fstream>
#include <random>
#include <iterator>
#include <list>
#include <ctime>

using namespace std;

void _init();
void displayBank(string userName, int bankMoney);
int moneyCalculator(int calcul, int money, int bankMoney);
int choiceMenu(string* user, int* Money);
int randNum(int a1, int a2, int r);

int main()
{
    string fileName = "C:\\c\\Cpp learn\\data\\";
    string userName;
    int bankMoney = 0;
    int bankNum;
    string str;
    
    vector<string> strlist;

    

    cout << "Input User Name : ";
    getline(cin, userName);

    ifstream file;
    file.open(fileName + userName + ".txt");
    if(!file.is_open())
    {
        cout << "No Data\n Create New Data" << endl;

        ofstream newFile;
        newFile.open(fileName + userName + ".txt");
        newFile << userName << "," << randNum(10000000, 99999999, rand()%11111) << "," << bankMoney << endl; //계좌가 없으면 user의 계좌 생성
        newFile.close();
        file.close();
    }

    file.open(fileName + userName + ".txt");
    if(file.is_open())
    {
        cout << "Bank System is On" << endl;
        while(!file.eof())
        {
            getline(file, str, ',');
            strlist.push_back(str);
        }
        bankNum = stoi(strlist.at(1));
        bankMoney = stoi(strlist.at(strlist.size()-1));
    }

    float rateNum = randNum(1, 400, rand()%11111)/(100.0f);

    cout << "어서오세요. " << userName << "님\n 오늘의 이자율은 " << rateNum << "% 입니다.\n" << endl;
    
    choiceMenu(&userName, &bankMoney);
    
    cout << "\n업무를 종료합니다." << endl;
    bankMoney += bankMoney*rateNum/100; //업무 종료 후 이자 더함
    file.close();

    //save data
    ofstream saveFile;
    saveFile.open(fileName + userName + ".txt", ios_base::app);
    saveFile << userName << "," << bankNum << "," << bankMoney << endl;
    saveFile.close();

    return 0;
}


void displayBank(string userName, int bankMoney)
{
    if(bankMoney <= 0)
    {
        cout << "현재 " << userName << "님의 계좌 잔액이 없습니다." << endl;
    }
    else{
        cout << "현재 " << userName << "님의 계좌 잔액은" << bankMoney << "원이 있습니다." << endl;
    }
}

int moneyCalculator(int calcul, int money, int bankMoney)
{
    switch (calcul)
    {
        case 1:
            bankMoney += money;
            cout << money << "원 입금. 보유 잔액은 " << bankMoney << "원 입니다." << endl;
            return bankMoney;
        case 2:
            bankMoney -= money;
            cout << money << "원 출금. 보유 잔액은 " << bankMoney << "원 입니다." << endl;
            return bankMoney;
        default:
            break;
    }
    return 0;
}

int choiceMenu(string* user, int* Money)
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
                displayBank(*user, *Money);
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

int randNum(int a1, int a2, int r)
{
    srand((unsigned int)time(NULL));
    int raNd = rand()*rand()+rand();
    random_device rd;
    mt19937 gen(rd()+raNd);
    uniform_int_distribution<int> dis(a1, a2);

    return dis(gen);
}
