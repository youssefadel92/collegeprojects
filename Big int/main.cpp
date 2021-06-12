#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <iomanip>
#include "Bigint.h"

using namespace std;



int main(){
    int choice_1=0;
    cout<<"1-add/n2-substract";
    cin>>choice_1;

    // cout<<"hello world"<<endl;
    string str1 = "";
    string str2 = "";
    cout<<"Enter the first number: ";
    cin>>str1;
    cout<<"Enter the second number: ";
    cin>>str2;
    bigintadd b(str1);
    bigintadd b1(str2);
    if(choice_1 == 1){
        b + b1;
    }
    if(choice_1 == 2){
        b - b1;
    }
    return 0;
}
