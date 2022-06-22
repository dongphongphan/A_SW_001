/* Phong - self learning design pattern Server - Observer
/ Server has list of observer. This list is updated by Server 
/  Server own the data and will notify to Observer on data changed
/  Observer: Only listen for Server
*/

#include <iostream>
#include <vector>

using namespace std;

#define PRICE_COFFEE 100
#define PRICE_MILK   40
#define PRICE_SUGAR  10
#define PRICE_ICE    5

class I
{
public:
	virtual void do_it() = 0;
	virtual int get_price() = 0;
};
class Deco: public I
{
public:
	Deco(I* in):ptr(in){}
	Deco(){	}
	
	void do_it()
	{
		ptr->do_it();
	}
	int get_price()
	{
		return ptr->get_price();
	}
private:
	I* ptr;
};

class Coffee:public I
{
public:
	void do_it()
	{
		cout <<"coffee";
	}
	int get_price()
	{
		return PRICE_COFFEE;
	}
};
class Milk:public Deco
{
public:
	Milk(I* in):Deco(in){}
	void do_it()
	{
		cout <<"Milk";
		Deco::do_it();
	}
	int get_price()
	{
		return (PRICE_MILK + Deco::get_price());
	}
};
class Sugar:public Deco
{
public:
	Sugar(I* in):Deco(in){}
	void do_it()
	{
		cout <<"Sugar";
		Deco::do_it();
	}
	int get_price()
	{
		return (PRICE_SUGAR + Deco::get_price());
	}
};
class Ice:public Deco
{
public:
	Ice(I* in):Deco(in){}
	void do_it()
	{
		cout <<"Ice";
		Deco::do_it();
	}
	int get_price()
	{
		return (PRICE_ICE + Deco::get_price());
	}
};


int main( void ) {
   cout<<"Main: COFFEE: "<<PRICE_COFFEE<<" MILK: "<<PRICE_MILK<<" SUGAR: "<<PRICE_SUGAR<<" ICE: "<<PRICE_ICE<<"\n";
   
   I* coffee = new Deco();
   I* coffee_milk_sugar = new Sugar( new Milk(coffee));
   coffee_milk_sugar->do_it();
   cout<<" :"<<coffee_milk_sugar->get_price();
   cout<<"\n";
   
   
   delete coffee_milk_sugar;
   
}
