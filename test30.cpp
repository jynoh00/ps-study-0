//CCW

#include <iostream>
#include <stdio.h>

#define endl "\n"

using namespace std;

pair<int, int> p[3];

void input();
int solution();

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    cout << solution() << endl;

    return 0;
}

void input(){
    for (int i = 0; i < 3; i++){
        int x, y;
        cin >> x >> y;
        p[i] = make_pair(x, y);
    }
}

bool isLine(float dx1, float dx2, float dy1, float dy2){
    if (abs(dy1/dx1) == abs(dy2/dx2)) return true;
}

int solution(){
    float dx1 = p[1].first - p[0].first, dy1 = p[1].second - p[0].second;
    float dx2 = p[2].first - p[0].first, dy2 = p[2].second - p[0].second;

    // p1 -> p2 : 직각
    if (dx1 == 0){ // 세로 직각
        if (dy1 > 0){ // 위쪽
            return dx2 < 0 ? 1 : (dx2 == 0 ? 0 : -1); // 왼쪽 -> 반시계, 중앙 -> 직선, 오른쪽 시계
        }else{ // 아래쪽
            return dx2 > 0 ? 1 : (dx2 == 0 ? 0 : -1); // 왼쪽 -> 시계, 중앙 -> 직선, 오른쪽 반시계
        }
    }
    if (dy1 == 0){ // 가로 직각
        if (dx1 > 0){ // 오른쪽
            return dy2 > 0 ? 1 : (dy2 == 0 ? 0 : -1);
        }else{ // 왼쪽
            return dy2 < 0 ? 1 : (dy2 == 0 ? 0 : -1);
        }
    }

    if (dx2 != 0 && isLine(dx1, dx2, dy1, dy2)) return 0; // 직각격자 제외 직선일 경우 0 리턴

    if (dx1 > 0 && dy1 > 0){ // ++, 1사분면
        if (dx2 == 0 && dy2 > 0) return 1; 
        if (dx2 == 0 && dy2 < 0) return -1;
        if (dy2 == 0 && dx2 > 0) return -1;
        if (dy2 == 0 && dx2 < 0) return 1;

        float d1 = dy1/dx1, d2 = dy2/dx2; // 기울기

        if (abs(d1) == abs(d2)) return 0; // 동일 기울기

        if (abs(d2) > abs(d1)){
            
        }
        else return 1; // 반시계 d1 < d2
    }

    if (dx1 < 0 && dy1 > 0){ // -+, 2사분면

    }

    if (dx1 < 0 && dy1 < 0){ // --, 3사분면

    }

    if (dx1 > 0 && dy1 < 0){ // +-, 4사분면

    }



}