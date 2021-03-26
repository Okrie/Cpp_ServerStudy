#include <iostream>
#include <iterator>
#include <set>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;

int main(void)
{
	int arr[5] = {10, 20, 30, 40, 50};	// 배열 생성 및 초기화 
	set<int> st(arr, arr+3);			// 배열의 일부 요소를 가지고 셋 컨테이너를 생성함. 
	cout << "현재 집합의 모든 요소는 다음과 같습니다." << endl;
	copy(st.begin(), st.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	
	st.insert(60);	// 요소의 추가 
	st.insert(70);	// 요소의 추가 
	st.erase(20);	// 요소의 삭제 
	cout << "현재 집합의 모든 요소는 다음과 같습니다." << endl;
	copy(st.begin(), st.end(), ostream_iterator<int>(cout, " "));

    

    map<string, int> mp;

    mp.insert(pair<string, int>("국어", 80)); // 익명의 pair 객체를 생성하여 추가함.

    mp["수학"] = 100; // 첨자 연산자를 이용하여 추가함.

    cout << "현재 맵의 모든 요소는 다음과 같습니다." << endl;

    map<string, int>::iterator it;

    for(it = mp.begin(); it != mp.end(); it++)
    {
        cout << it->first << " : " << it->second << endl;
    }

    string temp = "국어";
    cout << "찾는 " << temp << "의 점수는 " << mp.find(temp)->second << "점 입니다." << endl;

	return 0;
}