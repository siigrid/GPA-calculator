#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

class test{
	int number;
	char name[10];
	public:
		void enter_details(void);
		void add_details();	
}c1;

int main(){
	char word[30];
	c1.enter_details();
	//cout<<"RETURNED";
	c1.add_details();
	system("cls");	
	ifstream db;
	db.open("test_case.dat", ios::in | ios::binary);
	db >> word;
	cout<<word;
	return 0;
}

void test::enter_details(){
	cout<<"number: ";
	cin>>number;
	cout<<"Name: ";
	cin>>name;	
}

void test::add_details(){
	fstream db;
	db.open("test_case.dat", ios::out | ios::app | ios::binary);
	if(db.is_open()){ cout<<"OPEN..."; }
	db.write( ( char* )&c1, sizeof( test ) );
	db.close();
}
