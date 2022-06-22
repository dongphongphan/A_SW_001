/*

Given a set of messages (containing ID and payload) and:
- a dispatching-entity,
  (propagating these messages to registered applications)
- a scheduling-entity,
  (calling the registered application's worker method)


    |-------------------|
    | Application       |<--------------
    |-------------------|              | schedule
            ^                          |
            | onMessage                |
            |                |-------------------|
            |                | Scheduler         |
    |-------------------|    |-------------------|
    | Dispatcher        |
    |-------------------|
            ^
            | messages
            |
            |
    /---------- bus (e.g. CAN, LIN, ETH, etc. ---/


1) Implement class "Application" (see below) which:
- is schedulable
- receives the messages
- prints the received messages to stdout when
  it is scheduled (function toStr may be used
  as helper for printing, see below)

2) Introduce a filter-mechanism which allows
different instances of the application
to get different message streams

3) Apply the following filters:
- filter messages with even IDs
- filter every 2nd message


Don't modify:
- class Message
- class Dispatcher
- class Schedulable


You're free to:
- use any standard container/algorithm, etc.
- look up things on the internet
- ignore indentation/code-style

*/

/* ********** ********** ********** */

#include <iostream>
#include <sstream>

#include <algorithm>
#include <functional>
#include <map>
#include <vector>

using namespace std;
/* ********** ********** ********** */

using FuncType = std::function<void (const string&)>;

class Dispatcher
{
public:
	void regsiterF(const FuncType& f) // must be const reference because lambda return temporary obj)
	{
		Flist.push_back(f);
	}
	void dispatch(const string& msg)
	{
		for(const auto& i : Flist)
		{
			i(msg);
		}
		return;
	}
	
private:
	std::vector< FuncType > Flist;
	//std::vector< std::function<void (const string&)> > Flist;
};

class Application
{
public:
	void onMessage(string s)
	{
		cout <<"App: "<<s<<endl;
	}
	void operator()(string s){cout <<"App operator: "<<s<<endl;}
	std::function<void (const string& s)> AppCB = [this](const string& s){onMessage("Func " + s);};
};
vector<string> payload = 
{
	"1: holiday school",
	"2: Private property",
	"3: Landing safe",
	"4: Fly to the moon",
	"5: Thinking hard",
	"6: hope chance",
	"7: Private property",
	"8: Landing safe",
	"9: Fly to the moon",
	"10: Thinking hard",
};

int main()
{

	
	Dispatcher disp;
	Application app;
	
	auto AppLambda = [&app](const string& s) {app.onMessage(s);};
	disp.regsiterF(AppLambda);
	
	std::function<void (const string& s)> AppFunc = [&app](const string& s){app.onMessage(s);};
	disp.regsiterF(AppFunc);
	
	app("abc");
	//disp.regsiterF(app.AppCB);
	
	
	
	for(const auto& i: payload)
	{
		disp.dispatch(i);
	}
	return 1;
}



