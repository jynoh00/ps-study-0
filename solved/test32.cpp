// 개미굴

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>

#define endl "\n"
#define MAX 1000

using namespace std;

int N;
vector<vector<string>> v_v;
string s_bar = "--";
bool isClear[MAX];

void input();
void solution();

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solution();

    return 0;
}

void input(){
    cin >> N;
    for (int i = 0; i < N; i++){
        int tmp_num; cin >> tmp_num;
        vector<string> v;
        for (int j = 0; j < tmp_num; j++){
            string s;
            cin >> s;
            v.emplace_back(s);
        }
        v_v.emplace_back(v);
    }
}

void solution(){
    sort(v_v.begin(), v_v.end());

    vector<vector<string>> real_v;

    for (int i = 0; i < v_v.size(); i++){
        if (i == v_v.size()-1) continue;

        if (v_v[i].size() == v_v[i+1].size()){ // 크기 동일
            bool isSame = true;
            for (int j = 0; j <v_v[i].size(); j++){
                if (v_v[i][j] != v_v[i][j]){
                    isSame = false;
                    break;
                }
            }
            if (isSame == true){ // 같으면
                
            }
        }
    }

    string tmp_s = v_v[0][0];

    cout << tmp_s << endl;
    for (vector<string> v : v_v){
        for (int i = 0; i < v.size(); i++){
            if (i == 0){
                if (v[i] == tmp_s) continue;
                else{ // 다른 경우
                    tmp_s = v[i];
                    cout << tmp_s << endl;
                    continue;
                }
            }else{
                for (int k = 0; k < i; k++) cout << s_bar;
                cout << v[i] << endl;
            }
        }
    }
}


/*
개미는 뚠뚠

로봇개미

각층에 먹이가 있는 방을 따라감. -> 더이상 내려갈 수 없으면 신호를 보냄
각 방의 먹이 정보를 알려줌

KIWI BANANA
KIWI APPLE
APPLE APPLE
APPLE BANANA KIWI

APPLE
--APPLE
--BANANA
----KIWI
KIWI
--APPLE
--BANANA

깊이 얕은 순 -> 사전순

정보 N개 (1~1000)





*/