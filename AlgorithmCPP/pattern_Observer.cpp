/* Phong - self learning design pattern Server - Observer
/ Server has list of observer. This list is updated by Server 
/  Server own the data and will notify to Observer on data changed
/  Observer: can register and get notified by Server
*/

#include <iostream>
#include <vector>
#include <algorithm> //std:find

using namespace std;

class Subject;
using Func = std::function<void (string & data)>;

/////////////////////////////////////////////////////
class IObserver
{
public:
	virtual void update(string& data) = 0;
	void registerOb(Subject* ptrSub);
	void deRegisterOb(Subject *ptrSub);
};

class Subject
{
	vector<IObserver*> ObList;
	vector<Func> FuncList;
public:
	void addFun(Func func)
	{
		FuncList.push_back(func);
	}
	void addObs(IObserver* ptrOb)
	{
		if(ptrOb != NULL)
		ObList.push_back(ptrOb);
	}
	void removeObs(IObserver* ptrOb)
	{
		if(ptrOb != NULL)
		{
			vector<IObserver*>::iterator it = std::find(ObList.begin(),ObList.end(),ptrOb);
			if(it != ObList.end()) ObList.erase(it);
			return;
			/*
			for(vector<IObserver*>::iterator it = ObList.begin(); it != ObList.end(); ++it)
			{
				if(*it == ptrOb)
				{
					ObList.erase(it);
					break;
				}
			}*/
		}
	}
	void update(string & data)
	{
		for(auto i: ObList)
		{
			i->update(data);
		}
	}
	void updateFunc(string & data)
	{
		for(auto i: FuncList)
		{
			i(data);
		}
	}
};

void IObserver::registerOb(Subject* ptrSub)
{
	ptrSub->addObs(this);
}

void IObserver::deRegisterOb(Subject* ptrSub)
{
	ptrSub->removeObs(this);
}
//==================================================

class Weather: public Subject
{
public:
	void updateWeather(string& data)
	{
		Subject::update(data);
	}
};

class Human: public IObserver
{
public:
	void update(string& data)
	{
		cout<<"Human update: "<<data<<endl;
	}
};
class Company: public IObserver
{
public:
	void update(string& data)
	{
		cout<<"Company update: "<<data<<endl;
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef unsigned char		                uint8;  /*  8 bits */
typedef uint8 	                            UINT8;
typedef unsigned short int	                uint16;
typedef uint16 	                            UINT16;

#define MAKEWORD(lo, hi)    ((UINT16)((((UINT8)lo) & 0xffU) | ((UINT16)((((UINT8)hi) << 8) & 0xff00U))))

int main(int argc, char** argv) {
	
	uint16 i = 0;
	char Ar[4] = {0xFF,0xFF,'B','A'};
	i = MAKEWORD(Ar[0],Ar[1]);

	printf("i = %X",i);
	return 0;
}
