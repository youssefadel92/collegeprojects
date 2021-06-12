#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <iomanip>
using namespace std;
class bigintadd{
private:
    string number1;
public:
bigintadd()
{
    number1 = "";
}
bigintadd(string str1)
{
    number1 = str1;
}

 bigintadd operator+(bigintadd mat)
 {
    string str_1 = number1;
    string str_2 = mat.getNumber();
    cout << sum(str_1, str_2) << endl;
    return sum(str_1 , str_2);
}
//done


bigintadd operator-(bigintadd test)
        {
            string str_1 = number1;
            string str_2 = test.getNumber();
            cout << Diff2(str_1 , str_2);
            return Diff2(str_1 , str_2);
        }

//done
string getNumber()
{
    return number1;
}
//done
bool smaller(string str1, string str2)
        {
    int n1 = str1.length(), n2 = str2.length();
    if (n1 < n2) {
        return true;
    }
    if (n2 < n1) {
        return false;
        }
    for (int i=0; i<n1; i++){
        if (str1[i] < str2[i]) {
            return true;
        }
        else if (str1[i] > str2[i]) {
            return false;
        }
    }
    return false;
}

string Diff2(string str1, string str2)
{

    bool s=false;
            if(str2[0] == '-'&&str1[0]!='-'){//6--3=6+3
                str2.erase(0,1);
                return sum(str1 , str2);
            }
            if(str2[0] == '-'&&str1[0]=='-'){
                str2.erase(0,1);
                str1.erase(0,1);
                swap(str1,str2);//-3--6=-3+6=6-3
            }
            if(str1[0] == '-'&&str2[0]!='-'){//-8-3
                    string d;
                    d.push_back('-');
                    d.push_back(str2[0]);
                    return sum(str1,d);
            }

    // assert str not smaller if though we will swap then put negative at first of string
    if (smaller(str1, str2)){
        s=smaller(str1,str2);
        swap(str1, str2);

    }
    // Take an empty string for storing result
    string str = "";

    // Calculate length of both string
    int n1 = str1.length(), n2 = str2.length();//20000000
                                               // 1000000
    // Reverse both of strings
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());

    int carry = 0;


    // Run loop till small string length
    // and subtract digit of str1 to str2
    for (int i=0; i<n2; i++)
    {
        // Do school mathematics, compute difference of
        // current digits

        int sub = ((str1[i]-'0')-(str2[i]-'0')-carry);

        // If subtraction is less then zero
        // we add then we add 10 into sub and
        // take carry as 1 for calculating next step
        if (sub < 0)
        {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;

        str.push_back(sub+'0');
    }

    // subtract remaining digits of larger number
    for (int i=n2; i<n1; i++)
    {
        int sub = ((str1[i]-'0') - carry);     //2400-3311

        // if the sub value is -ve, then make it positive
        if (sub < 0)
        {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;

        str.push_back(sub+'0');
    }
        if (s==true){
            str.push_back('-');
        }
    // reverse resultant string
    reverse(str.begin(), str.end());
    return str;
}


string sum(string str1 , string str2)
        {
            bool s=false;
            if(str1[0] == '-' && str2[0] == '-')//-6-3
            {
                s=true;
                str1.erase(0,1);
                str2.erase(0,1);
            }
            if(str1[0] == '-'&&str2[0]!='-'){//-8+6=6-8
                str1.erase(0,1);
                return Diff2(str2,str1);
            }


            if(str1[0] != '-'&&str2[0]=='-'){//3+-6=3-6
                str2.erase(0,1);
                return Diff2(str1 , str2);
            }

            if(str1.length() > str2.length())
            {
                swap(str1,str2);
            }
            string str = "";
            int n1 = str1.length();
            int n2 = str2.length();

            reverse(str1.begin(), str1.end());
            reverse(str2.begin(), str2.end());

            int carry = 0;

            for(int i = 0 ; i < n1 ; ++i)
                {
                    int sum = ((str1[i] - '0') + (str2[i] - '0') + carry);
                    str.push_back(sum%10 + '0');
                    carry = sum/10;
                }
            for(int i = n1 ; i < n2 ; ++i)
                {
                    int sum = ((str2[i] - '0') + carry);
                    str.push_back(sum%10 + '0');
                    carry = sum/10;
                }
            if(carry)
                {
                    str.push_back(carry + '0');
                }

        if (s==true){
            str.push_back('-');
        }
        reverse(str.begin(), str.end());
        return str;
}


};
#endif
