/* The songs must be chosen in pairs and the pair's durations must add up to a multiple of 60 seconds
   Return number of valid pairs
*/
#include <iostream>
#include <vector>
#include <set>
#include <bitset>

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




int lengthOfLongestSubstring(string s) {
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

int main(int argc, char** argv) {
	string A = "abcdddddab";
	cout << "input: "<<A<<endl;
	int ret = lengthOfLongestSubstring(A);
	cout << "ret: "<<ret <<endl;

}
