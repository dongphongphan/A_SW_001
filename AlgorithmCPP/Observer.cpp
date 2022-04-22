/* Phong - self learning design pattern Server - Observer
/ Server has list of observer. This list is updated by Server 
/  Server own the data and will notify to Observer on data changed
/  Observer: Only listen for Server
*/

#include <iostream>
#include <vector>

class Server;
/////////////////////////////////////////////////////
class Observer
{
public:
	virtual void update(std::string data) = 0;
	virtual void update(int data) = 0;
	/*register is same as addObserver */
	bool registerCB(Server* serv);
	/*deRegisterCB is same as removeObserver */
	bool deRegisterCB(Server* serv);
};

////////////////////////////////// create derived class for client
class A : public Observer
{
	void update(std::string data){std::cout<<"Observer A update msg: "<< data <<std::endl;}
	void update(int data){ std::cout<<"Observer A update int: "<< data << std::endl;} 		
};
class B : public Observer
{
	void update(std::string data){std::cout<<"Observer B update msg: "<< data <<std::endl;}
	void update(int data){ std::cout<<"Observer B update int: "<< data << std::endl;} 	
};
class C : public B
{
	void update(std::string data){std::cout<<"Observer C update msg: "<< data <<std::endl;}
	void update(int data){ std::cout<<"Observer C update int: "<< data << std::endl;} 
};
/////////////////////////////////////////////////////
class Server
{
public:
	Server(){}
	~Server(){}
	/*Add cli to Observer list. Does not check if cli exist in list or not*/
	/*register is same as addObserver */
	void addObserver(Observer* cli)
	{
		ObserverList.push_back(cli);
	}
	/*remove one cli from list, if cli was added multiple time, only remove one cli*/
	/*deRegisterCB is same as removeObserver */
	bool removeObserver(Observer* cli)
	{
		for(std::vector<Observer*>::iterator it = ObserverList.begin(); it != ObserverList.end(); ++it)
		{
			if(*it == cli)
			{
				std::cout<< "remove Observer\n";
				ObserverList.erase(it);
				return true;
			}
		}
		return false;
	}
	void SendData(std::string msg)
	{
		for(std::vector<Observer*>::iterator it = ObserverList.begin(); it != ObserverList.end(); ++it)
		{
			(*it)->update(msg);
		}
	}
	void SendData(int data)
	{
		//std::cout<< "SendData\n";
		for(std::vector<Observer*>::iterator it = ObserverList.begin(); it != ObserverList.end(); ++it)
		{
			(*it)->update(data);
		}
	}
private:
	std::vector<Observer*> ObserverList;
};

bool Observer::registerCB(Server* serv)
{
	serv->addObserver(this);
	return 1;
}
bool Observer::deRegisterCB(Server* serv)
{
	serv->removeObserver(this);
	return 1;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
	
	Server sev;
	A a;
	B b;
	C c;
	std::string data = "Data to send from server";
	sev.addObserver(&a);
	sev.addObserver(&b);
	
	sev.SendData(data);
	
	b.deRegisterCB(&sev);
	c.registerCB(&sev);
	sev.SendData(data);
	
	return 0;
}
