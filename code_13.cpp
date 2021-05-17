//
// Created by yan on 2021/5/18.
//

#include <string>
#include <iostream>


using namespace std;


void GetNextVal(const std::string &str, int nextVal[]) {
    int j = 0;
    int k = -1;

    nextVal[0] = -1;
    while (j < (int) str.length()) {
        if (k == -1 or str[j] == str[k]) {
            ++j;
            ++k;
            if (str[j] != str[k]) {
                nextVal[j] = k;
            } else {
                nextVal[j] = nextVal[k];
            }
        } else {
            k = nextVal[k];
        }
    }
}


int KMPIndex(const std::string &str, const std::string &t) {
    int nextVal[t.length()];
    int i = 0;
    int j = 0;

    GetNextVal(t, nextVal);
    while (i < (int) str.length() and j < (int) t.length()) {
        if (j == -1 or str[i] == t[j]) {
            ++i;
            ++j;
        } else {
            j = nextVal[j];
        }
    }
    if (j >= (int) t.length()) {
        return i - (int) t.length();
    } else {
        return -1;
    }
}

int main() {
    int index;
    string string1 = "Hello, I'm yan. I am using Clion";
    string string2 = "yan";

    index = KMPIndex(string1, string2);
    cout << index << endl;

    return 0;
}