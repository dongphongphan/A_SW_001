/* The songs must be chosen in pairs and the pair's durations must add up to a multiple of 60 seconds
   Return number of valid pairs
*/
#include <iostream>
#include <vector>
#include <set>
#include <bitset>
#include <stack>
#include <bits/stdc++.h>

using namespace std;
long playlist(vector<int> songs)
{
	long ret = 0;
	int listSize = songs.size();
	if(listSize < 2) return ret;
	for(int i = 0; i < listSize; i++)
	{
		for(int j = i+1; j < listSize; j++)
		{
			unsigned int duration = songs[i] + songs[j];
			if( duration >= 60 && duration%60 == 0)
			{
				ret++;
				cout << songs[i] <<" "<<songs[j]<<endl;
			}
		}
	}
	return ret;
}



int lengthOfLongestSubstring1(string s) {
    int x1 =0, x2=0;
    int ret = 0;
    set<char> Sub;
    while(x2 < s.length())
    {
    	set<char>::iterator it = Sub.find(s[x2]);
        if(it == Sub.end())
        {
            Sub.insert(s[x2]);
            x2++;
            //cout <<"Not found "<<s[x2] <<" x1="<<x1<<" x2=" << x2 << endl;
        }
        else if(x1 < x2)
        {
            Sub.erase(s[x1]);
            x1++;
            //cout <<"Found 1   "<<s[x2]<<" x1=" << x1 <<" x2="<<x2<< endl;
        }
        else
        {
            x2++;
            x1++;
            Sub.insert(s[x2]);
            //cout <<"Found 2   "<<s[x2]<<" x1=" << x1 <<" x2="<<x2<< endl;
        }
        if((x2-x1) > ret) ret = x2-x1;
    }
    return (ret);
}
int lengthOfLongestSubstring2(string s) {
        int x1 =0, x2=0;
        int ret = 0;
        map<char,int> Sub;
        while(x2 < s.length())
        {
            map<char,int>::iterator it = Sub.find(s[x2]);
            if(it != Sub.end())
            {
                for(;x1 <= it->second;x1++) {Sub.erase(s[x1]);}
                //printf("Found x1=%d x2=%d\n",x1,x2);
            }
            else
            {
                //Sub[s[x2]] = x2;
                Sub.insert({s[x2],x2});
                x2++;
            }
            ret = max(ret,x2-x1);
        }
        return (ret);
}
int lengthOfLongestSubstring(string s) {
    int x1 =0, x2=0;
    int ret = 0;
    set<char> Sub;
    {
        while (x2 < s.length())
        {
            set<char>::iterator it = Sub.find(s[x2]);
            if(it != Sub.end())
            {
                Sub.erase(s[x1++]);
            }
            else
            {
                Sub.insert(s[x2++]);
                ret = max(ret,x2-x1);
            }
        }
    }
    return (ret);
}
string removeDuplicates(string s, int k) 
{
	cout <<"input: "<<s<<endl;
    stack<pair<char,int>> stk;
    for(int i =0 ; i < s.length(); i++)
    {
        if(!stk.empty())
        {
            pair<char,int> temp = stk.top();
            if(temp.first == s[i] && temp.second >= k-1)
            {
                for(int l=1; l < k; l++) stk.pop();
            }
            else if(temp.first == s[i] && temp.second < k-1)
            {
                stk.push(pair<char,int>(s[i],temp.second+1));
            }
            else
            {
                stk.push(pair<char,int>(s[i],1));
            }
        }
        else
        {
            stk.push(pair<char,int>(s[i],1));
        }
    }
    string ret;
    while(!stk.empty())
    {
        ret += stk.top().first;
        stk.pop();
    }
    reverse(ret.begin(),ret.end());
    return ret;
}


int reverse(int x) {
    int ret = 0;
    int a = 0;
    while(x)
    {
        int temp = a*10 + x%10;
        if(a != temp / 10) return 0;
        x = x/10;
        ret = a = temp;
        //ret = a;
        printf("%d \n",ret);
    }
    
    return ret;
}
/* MCMXCIV = 1994 | LVIII = 58*/
int romanToInt(string s) {
    map<char,int> data = {{'M',1000},
                        	//{'CM',900},
	                        {'D',500},
	                        //{'CD',400},
	                        {'C',100},
	                        //{'XC',90},
	                        {'L',50},
	                        //{'XL',40},
	                        {'X',10},
	                        //{'IX',9},
	                        {'V',5},
	                        //{'IV',4},
	                        {'I',1}};
	int ret = data[s.back()];
	for(int i = s.length()-2; i >= 0; i--)
	{
		if(data[s[i]] >= data[s[i+1]])
		{
			ret += data[s[i]];
		}
		else
		{
			ret -= data[s[i]];
		}
	}
	return ret;
}
 string intToRoman(int num)
 {
 	string sym[] = {"M", "CM",  "D", "CD", "C", "XC", "L", "XL", "X", "IX","V", "IV","I"};
 	int val[] =    {1000, 900, 500,  400,  100,  90,  50,   40,  10,   9,   5,   4,   1};
 	string ret = "";
 	
 	for(int i = 0; num > 0;)
 	{
 		if(num >= val[i])
 		{
 			ret += sym[i];
 			num -= val[i];
		}
		else
		{
			i++;
		}
	}
 	
 	return ret;
 }
 
bool isPalindrome(string sub, int l, int r){
    while(l < r){
        if(sub[l] != sub[r]){
            return false;
        }
        l++;r--;
    }
    return true;
}
string longestPalindrome(string s) {
    string ret = s.substr(0,1);
    int maxLen = 0;
    int l=0, r =0;
    
    for(int k = 0; k < s.length(); k++)
    {
        l = r = k; 
        
        while(l >= 0 && r < s.length() && (s[l--] == s[r++]))
        {
            if(maxLen < (r-l-2))
            {
                maxLen = r-l-2;
                ret = s.substr(l+1,maxLen+1);
                cout <<"l= "<<l<<" r= "<<r<<endl;
            }
        }

        l = k;
        r = k+1;
        while(l >= 0 && r < s.length() && (s[l--] == s[r++]))
        {
            if(maxLen < (r-l-2))
            {
                maxLen = r-l-2;
                ret = s.substr(l+1,maxLen+1);
                cout <<"l= "<<l<<" r= "<<r<<endl;
            }
        }
    }
    return ret;
}
int main(int argc, char** argv) {

	std::set<int> Set;
	Set.insert(4);
	Set.insert(3);
	Set.insert(5);
	cout << *Set.begin();
/*
	cout << "in: "<<1994<< "\nret: "<<intToRoman(1994)<<endl;
	cout << "in: "<<58<< "\nret: "<<intToRoman(58)<<endl;
	cout << "in: "<<3<< "\nret: "<<intToRoman(3)<<endl;

	string s = "III";
	cout << "in: "<<s<< "\nret: "<<romanToInt(s)<<endl;
	s = "MCMXCIV";
	cout << "in: "<<s<< "\nret: "<<romanToInt(s)<<endl;
	s = "LVIII";
	cout << "in: "<<s<< "\nret: "<<romanToInt(s)<<endl;
	*/
	return 1;
}
