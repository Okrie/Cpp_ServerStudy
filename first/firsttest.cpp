#include <iostream>
#include <iomanip>

#define TEXT "Welcome to C++ Programming!!"

using namespace std;

int main()

{
    // int a = 9;
    // int b;
    // string result;

    // cout << "9 => 10진수 " << a << endl;
    // cout << oct;
    // cout << "8진수 " << a << endl;
    // b = a;
    // cout << hex;
    // cout << "16진수 " << a << endl;
    // cout << b <<endl;
    // cout << dec;
    // cout << a*b <<endl;

    // if(a == b)
    // {
    //     cout << "?" << endl;
    // }

    // result = (a < b) ? "문젠데" : "그치";
    // cout << result;

    int arr_col_len, arr_row_len;

    int arr[3][4] = {

        {10, 20},

        {30, 40, 50, 60},

        {0, 0, 70, 80}

    };

    arr_col_len = sizeof(arr[0]) / sizeof(arr[0][0]);              // 2차원 배열의 열의 길이를 계산함

    arr_row_len = (sizeof(arr) / arr_col_len) / sizeof(arr[0][0]); // 2차원 배열의 행의 길이를 계산함

    int arr2[] = { 3, 5, 1, 4};

    //int (*address)[arr_col_len][arr_row_len] = (int (*)[arr_col_len][arr_row_len])&arr;
    int *address = arr2;
    cout << sizeof(address) << " " << sizeof(address[0]) << endl;
    for(int i = 0; i < sizeof(arr2)/sizeof(arr2[0]); i++)
    {
        cout << "print : " << *(address+i) << endl;
        // for(int j = 0; j < sizeof(address); j++)
        // {
        //     cout << "print : " << *address[i][j] << endl;
        //     cout << i << "  " << j << endl;
        // }
    }
    //delete address;
    //cout << "arr의 배열 요소의 값" << endl;
    
    // for( int i=0; i<3; ++i )
    // {
    //     for( int j=0; j<4; ++j )
    //     {
    //         cout << arr[i][j];
    //         printf("\r\n");
    //     }
    // }


    //cout << arr << endl;
    cout << sizeof(arr[0]) << endl;
    cout << arr[0];
    printf("\r\n\n");

    cout << sizeof(arr[0][0]) << endl;
    cout << arr[0][0];
    printf("\r\n");





    string name = "abdcmei!";
    string name2 = "!";
    //cout << "이름 입력 하세요 : " ;
    //cin >> name;
    //getline(cin, name);

    int SIZE = name.length();

    string::size_type index = name.find(name2);
    if(index != string::npos)
    {
        cout << "???";
    }

    //cout << SIZE << endl;

    //cout << name[0];

    // if(name.find('!') != string::npos)
    // {
    //     cout << "have '!' string";
    // }

    //cout << sizeof(arr) << endl;
    //cout << arr_col_len << endl;


    // for (int i = 0; i < arr_row_len; i++)

    // {

    //     for (int j = 0; j < arr_col_len; j++)

    //     {

    //         cout << setw(4) << arr[i][j];

    //     }

    //     cout << endl;

    // }







    return 0;

}