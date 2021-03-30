using namespace std;

class Bank{
    public:
    void _init();
    void displayBank(char* userName, int bankMoney);
    int moneyCalculator(int calcul, int money, int bankMoney);
    int choiceMenu(char* user, int* Money);
    int randNum(int a1, int a2, int r);
};