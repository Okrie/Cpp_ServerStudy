using namespace std;

class Bank{
    public:
    Bank();
    ~Bank();
    string nameId;
    void _init();
    void bankSystem(const char* userName, char* sz_msg);
    void displayBank(const char* userName, int bankMoney);
    int moneyCalculator(int calcul, int money, int bankMoney);
    int choiceMenu(const char* user, int* Money);
    int randNum(int a1, int a2, int r);

    private:
    bool isOpen;
    string fileName;
    int bankMoney;
    int bankNum;
    string str;
};