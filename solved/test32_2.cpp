// 개미굴 - trie 알고리즘

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>

#define endl "\n"
#define MAX 1000

using namespace std;

struct TRIE{
    bool isEnd;
    map<string, TRIE*> Child; // key: str - value: struct*
    map<string, TRIE*>::iterator IT; // 이터레이터

    TRIE() : isEnd(false){}
    ~TRIE(){
        for (IT = Child.begin(); IT != Child.end(); IT++){
            delete IT->second; // 차일드
        }
    } // 부모 노드에서부터 자식노드 하나씩 제거

    void insert_food(vector<string> vec){
        TRIE* NowTrie = this;
        for (int i = 0; i < vec.size(); i++){
            string tmp_s = vec[i];
            if (!NowTrie->Child[tmp_s]) NowTrie->Child[tmp_s] = new TRIE; // new 주소 리턴

            NowTrie = NowTrie->Child[tmp_s];
        }
        NowTrie->isEnd = true;
    }
};

int N, K;
string s;
vector<string> food;

void dfs(TRIE* Trie, int depth){
    map<string, TRIE*>::iterator IT;
    for (IT = Trie->Child.begin(); IT != Trie->Child.end(); IT++){
        for (int i = 0; i < depth; i++) cout << "--";
        cout << IT->first << endl;
        dfs(IT->second, depth+1);
    }
}

void find_answer(TRIE* root){ dfs(root, 0); }

void input_solution();

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input_solution();

    return 0;
}

void input_solution(){
    TRIE* root = new TRIE();
    cin >> N;
    while(N--){ // 0이면 종료, N번 반복
        food.clear();
        cin >> K;
        while(K--){ // K번 반복
            cin >> s;
            food.emplace_back(s);
        }
        root->insert_food(food);
    }
    find_answer(root);
    delete root;
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