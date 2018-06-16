//add filestream EVERY-fucling-WHERE...

#define n_sub 3
#include <iostream>
#include <fstream>
#include <string.h>
#include <windows.h>
#include "lexicon.h"

using namespace std;

float marks[n_sub];
int n_fa = 0;

class std_details{
	string name;
	char* ID;
	char sec;
	int s_class;
	public: 
		std_details(); 
		void get_details(int s_no);	//function under construction...
};

class std_marks{
	float perc[n_sub], gpa[n_sub], cgpa;
	public:
		std_marks();
		float calc_perc(int i);
		float calc_gpa(int j);
		float calc_cgpa();		
};

void check_config(); //check the config file for any updates. 
void get_marks();
char* assign_ID();
 
int main(){
	/*
	cout<<"Enter the no. of student  you want to enter the details of: ";
	cin x;
	cout<<endl;
	int x;
	*/
	std_marks mk24;
	check_config();
	get_marks();	
	
	/*
	for( int i = 0 ; i < n_sub ; i++ ){
		cout<<endl<<"PERC: "<<mk24.calc_perc(i);	
	}
	
	for( int i = 0 ; i < n_sub ; i++ ){
		cout<<endl<<"GPA:"<<mk24.calc_gpa(i);	
	}
	
	cout<<endl<<"CGPA: "<<mk24.calc_cgpa();	
	*/
	
	return 0;	
}

//Class Functions...

//class: student details

std_details::std_details(){
	name = "";
	sec = '\0';
	s_class = 0;	
}

void std_details::get_details( int s_no ){
	cout<<"Scholar ID: ";
	ID = assign_ID();
	cout<<ID<<endl;
	cout<<"First Name: ";
	cin>>name;
	cout<<"Section: ";
	cin>>sec;
	cout<<"Class: ";
	cin>>s_class;
}

//class: student marks
std_marks::std_marks(){
		int i=0;
		for( ; i< n_sub ; i++){
			perc[i] = 0;
			gpa[i] = 0;	
		}
		cgpa = 0;
}

float std_marks::calc_perc(int i){
		perc[i] = (marks[i]/n_fa)*100;
		return perc[i];
}

float std_marks::calc_gpa(int j){
		gpa[j] = (perc[j]/100)*5; //keep it variable.. preferable use file streaming later
		return gpa[j];
}

float std_marks::calc_cgpa(){
		int k = 0;
		for( ; k < n_sub ; k++){
			cgpa += gpa[k];	
		}
		cgpa /= 3;
		return cgpa;
}

//Class Functions END HERE

//Program Functions...

void check_config(){
	char word[30];
	string marks;
	fstream cfg;
	cfg.open("Files/config.txt", ios::in);
	while( cfg>>word ){
		if( ( word[0] == '/' ) && ( word[1] == '/' ) ){
			continue;	
		}
		for( int i = 0 ; i < 30 ; i++ ){
			if(word[i] == '['){
				for( int j = i + 1 ; j < 30 ; j++ ){
					if(word[j] == ']'){
						break;	
					}
					marks += word[j]; 
				}
			}
			else{
				break;	
			}
		}
	}
	cfg.close();
	char* mks = &marks[0];
	n_fa = conv_to_int(mks);
	//cout<<marks<<endl;
}

void get_marks(){
	cout<<"Enter marks:- \n";
	for( int i = 0 ; i < n_sub ; i++ ){
		cin>>marks[i];
		if( ( marks[i] <= n_fa ) && ( marks[i] >= 0 ) ){
			continue;
		}
		else{
			cout<<"Marks lie out of range. \nRange: 0-"<<n_fa;
			getch();
			cout<<"\r";
			gotoXY( 0 , -2 , 1 );
			cout<<"       \n                              \n                \r";
			gotoXY( 0 , -2 , 1 );
			marks[i] = 0;
			i--;
		}
	}	
}

char* assign_ID(){
	char* line;
	char* line_1;
	ifstream fin, fin_1;
	ofstream fout_1;
	fin.open("Files/unique_id.txt");
	fin_1.open("Files/used_unique_id.txt");
	while(!fin.eof()){	
		fin >> line;
		fin_1 >> line_1;
		if( strcmp( line , line_1 )==0 ){			
			//compares the existing text file with a list of all the unique student id
			//if the id is already in use, it assigns a different id
			//if bool holds true: return value= 0
		}
		else{
			fin.close();
			fin_1.close();
			fout_1.open("Files/used_unique_id.txt", ios::app);
			fout_1<<line<<"\n";	
			fout_1.close();
			return line;
		}	
	}
}	