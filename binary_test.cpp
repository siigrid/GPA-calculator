#include<fstream.h>
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<process.h>
using namespace std;
class file
{
private:
	int roll;
	float age;
	char name[100];
public:
	void input();
	void show();
	char *getn()
	{
		return name;
	}
};file fileobj;
 
void file::input()
{
	cout<<"Enter the roll, Age and name :";
	cin>>roll>>age;
	gets(name);
}
void file::show()
{
	cout<<"Roll==> "<<roll<<endl;
	cout<<"Age ==> "<<age<<endl;
	cout<<"Name==> "<<name<<endl;
}
void Create();
void Add();
void Display();
void DisplayP();
void Modify();
void Delete();
 
fstream fil;
int main()
{
	int opt;
	while(1)
	{
		clrscr();
		cout<<"1.Create Data File"<<endl;
		cout<<"2.Add New Record in Data File"<<endl;
		cout<<"3.Display Record From Data File"<<endl;
		cout<<"4.Display Particular Record From Data File"<<endl;
		cout<<"5.Modify Paricular Record From Data File"<<endl;
		cout<<"6.Delete Particular Record From Data File"<<endl;
		cout<<"7.Exit From the Program"<<endl;
		cout<<"Enter your Option : "<<endl;
		cin>>opt;
		switch(opt)
		{
			case 1:
			{
				Create();
				cout<<"Display Main Menu"<<endl;
				getch();
				break;
			}
			case 2:
			{
				Add();
				cout<<"Display Main Menu"<<endl;
				getch();
				break;
			}
			case 3:
			{
				Display();
				cout<<"Display Main Menu"<<endl;
				getch();
				break;
			}
			case 4:
			{
				DisplayP();
				cout<<"Display Main Menu"<<endl;
				getch();
				break;
			}
			case 5:
			{
				Modify();
				cout<<"Display Main Menu"<<endl;
				getch();
				break;
			}
			case 6:
			{
				Delete();
				cout<<"Display Main Menu"<<endl;
				getch();
				break;
			}
			case 7:
			{
				exit(0);
			}
			default:
			{
				cout<<"Wrong Choice....Press Key For View the Main Menu";
				getch();
				clrscr();
			}
		}
	}
}
 
void Create()		//Function to Create Data File
{
	char ch='y';
	fil.open("binary.dat",ios::out| ios::binary);
	while(ch=='y' || ch =='Y')
	{
		fileobj.input();
		fil.write((char*)&fileobj, sizeof(fileobj));
		cout<<"Want to Continue.....";
		cin>>ch;
	}
	fil.close();
}
 
void Add()              //Function to Add New Record in Data File
{
	char ch='y';
	fil.open("binary.dat",ios::app| ios::binary);
	while(ch=='y' || ch =='Y')
	{
		fileobj.input();
		fil.write((char*)&fileobj, sizeof(fileobj));
		cout<<"Want to Continue.....";
		cin>>ch;
	}
	fil.close();
}
 
void Display()		//Function to Display All Record from Data File
{
	fil.open("binary.dat",ios::in| ios::binary);
	if(!fil)
	{
		cout<<"File not Found";
		exit(0);
	}
	else
	{
		fil.read((char*)&fileobj, sizeof(fileobj));
		while(!fil.eof())
		{
			fileobj.show();
			cout<<"Press Any Key....For Next Record"<<endl;
			getch();
			fil.read((char*)&fileobj, sizeof(fileobj));
		}
	}
	fil.close();
}
 
void DisplayP()		//Function to Display particular Record from Data File
{
	char n[100];
	cout<<"Enter Name that should be searched:";
	gets(n);
	fil.open("binary.dat",ios::in| ios::binary);
	if(!fil)
	{
		cout<<"File not Found";
		exit(0);
	}
	else
	{
		fil.read((char*)&fileobj, sizeof(fileobj));
		while(!fil.eof())
		{
			if(strcmp(n,fileobj.getn())==0)
			{
				fileobj.show();
				cout<<"Press Any Key...."<<endl;
				getch();
			}
			else
			{
				 cout<<"Press Any Key....For Search"<<endl;
				 getch();
			}
			fil.read((char*)&fileobj, sizeof(fileobj));
		}
	}
	fil.close();
}
void Modify()		//Function to Modify Particular Record from Data File
{
	char n[100];
	cout<<"Enter Name that should be searched:";
	gets(n);
	fil.open("binary.dat",ios::in| ios::out|ios::binary);
	if(!fil)
	{
		cout<<"File not Found";
		exit(0);
	}
	else
	{
		fil.read((char*)&fileobj, sizeof(fileobj));
		while(!fil.eof())
		{
			if(strcmp(n,fileobj.getn())==0)
			{
				fil.seekg(0,ios::cur);
				cout<<"Enter New Record.."<<endl;
				fileobj.input();
				fil.seekp(fil.tellg() - sizeof(fileobj));
				fil.write((char*)&fileobj, sizeof(fileobj));
			}
			else
			{
				 cout<<"Press Any Key....For Search"<<endl;
				 getch();
			}
			fil.read((char*)&fileobj, sizeof(fileobj));
		}
	}
	fil.close();
}
 
void Delete()		//Function to Delete Particular Record from Data File
{
	char n[100];
	cout<<"Enter Name that should be Deleted :";
	gets(n);
	ofstream o;
	o.open("new.dat",ios::out|ios::binary);
	fil.open("binary.dat",ios::in| ios::binary);
	if(!fil)
	{
		cout<<"File not Found";
		exit(0);
	}
	else
	{
		fil.read((char*)&fileobj, sizeof(fileobj));
		while(!fil.eof())
		{
			if(strcmp(n,fileobj.getn())!=0)
			{
				o.write((char*)&fileobj, sizeof(fileobj));
			}
			else
			{
				 cout<<"Press Any Key....For Search"<<endl;
				 getch();
			}
			fil.read((char*)&fileobj, sizeof(fileobj));
		}
	}
	o.close();
	fil.close();
	remove("binary.dat");
	rename("new.dat", "binary.dat");
}//end of program
