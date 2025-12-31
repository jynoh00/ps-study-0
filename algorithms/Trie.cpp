#include <iostream>
#include <map>

using namespace std;

int main(){
    map<string, int> m;
    
    m["qwe"] = 40;
    m["asd"] = 20;
    m["asd"] = 30;
    
    for (map<string, int>::iterator it = m.begin(); it != m.end(); it++){
        cout << it->first << endl;
        cout << it->second << endl;
    }
}