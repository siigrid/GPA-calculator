//add filestream EVERY-fucking-WHERE...
//check line 214
#define n_sub 3
#include <iostream>
#include <fstream>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "lexicon.h"

using namespace std;

float marks[n_sub];
const int n_settings = 2;
int n_fa = 0, n_gpa = 0;
int g_pos_file = 0, p_pos_file = 0;
char list[n_settings][10] = { "n_fa" , "n_gpa" };
const int name_len = 30;
const int ID_len = 10;

class std_details{
	char name[name_len];
	char ID[ID_len];
	int s_class;
	char sec;
	public: 
		std_details();
		string assign_ID(); //assigns a unique roll number while keeping check on the used IDs 
		void enter_details();	//function under construction...
		void add_details();
		void show_details();	
}w_det, r_det;	

class std_marks{	
	float perc[n_sub], gpa[n_sub], cgpa;
	public:
		std_marks();
		float calc_perc(int i); //calculates the percentage in each subject
		float calc_gpa(int j); //calculates the GPA in each subject
		float calc_cgpa(); //calculates the CGPA in each subject
		void add_marks();
		void show_marks();		
}w_marks, r_marks;	

void check_config(); //check the config file for any updates. 
void get_marks();	//input marks of the student in total "n_sub" subjects
 
int main(){
	check_config();
//	w_det.enter_details();
//	cout << endl;
//	w_det.add_details();
	r_det.show_details();
//	cout <<"Test output 1"<<endl;
	r_marks.show_marks();
//	get_marks();
//	cout <<"Test output 2"<<endl;	
//	w_marks.add_marks();
//	cout <<"Test output 3"<<endl;
	return 0;	
}

//Class Functions...

//class: student details

std_details::std_details(){
	for(int i=0 ; i<name_len ; i++ ){
		name[i] = '\0';	
	}
	for(int i=0 ; i<ID_len ; i++){
		ID[i] = '\0';	
	}
	sec = '\0';
	s_class = 0;	
}

string std_details::assign_ID(){
	char line[ID_len], line_1[ID_len];
	ifstream fin, fin_1;
	ofstream fout_1;
	fin.open("Files/unique_id.txt");
	fin_1.open("Files/used_unique_id.txt");
	while(!fin.eof()){	
		fin >> line;
		fin_1 >> line_1;
		//char* word = &line[0];
		//char* word_1 = &line_1[0];
		if( strcmp( line , line_1 )==0 ){			
			//compares the existing text file with a list of all the unique student id
			//if the id is already in use, it assigns a different id
			//if bool holds true: return value= 0
		}
		else{
			fin.close();
			fin_1.close();
			//include the following code elsewhere...
			/*
			fout_1.open("Files/used_unique_id.txt", ios::app);
			fout_1<<line<<"\n";	
			fout_1.close();
			*/ 
			strcpy( ID , line );
			//cout<<ID;
			return "\0";
		}	
	}
}

void std_details::enter_details( ){
	cout<<"Scholar ID: ";
	assign_ID();
	cout<<ID<<endl;
	cout<<"First Name: ";
	cin>>name;
	cout<<"Class: ";
	cin>>s_class;
	cout<<"Section: ";
	cin>>sec;
	return;
}

void std_details::add_details(){
	fstream fout;
	fout.open( "Files/details.dat", ios::out | ios::app | ios::binary );
	
	if( fout.is_open() ){
		fout.write( (char*)&w_det, sizeof( std_details ) );
		cout<<"Copy successful."<<endl;
		p_pos_file = fout.tellp();
	}
	fout.close();
	return;
}

void std_details::show_details() {
	ifstream fin;
	fin.open( "Files/details.dat", ios::in | ios::binary );
	//fin.seekg(0);
	
	while( fin.read( (char*)&r_det, sizeof( std_details ) ) ) {
		cout<< "Name: " << r_det.name << endl;
		cout<< "ID: " << r_det.ID << endl;
		cout<< "Class: " << r_det.s_class << endl;
		cout<< "Section: " << r_det.sec << endl;
		g_pos_file = fin.tellg();
	}
	cout<<g_pos_file<<endl;
	fin.close();
	return;
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
		gpa[j] = (perc[j]/100)*n_gpa;
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

void std_marks::add_marks(){
	fstream fout;
	/*cout<<"Percentage:- \n";
	for( int i = 0; i < n_sub; i++ ) {
		cout<<"\tSubject "<< (i+1) << ": " << w_marks.perc[i] << endl;
	}
	cout<<"GPA:- \n";
	for( int i = 0; i < n_sub; i++ ) {
		cout<<"\tSubject "<< (i+1) << ": " << w_marks.gpa[i] << endl;
	}
	cout <<"CGPA: " << w_marks.cgpa << endl;
	getch();*/
	fout.open( "Files/details.dat", ios::out | ios::app | ios::binary );
	fout.seekp( p_pos_file , ios_base::beg );
	if( fout.is_open() ){
		fout.write( (char*)&w_marks, sizeof( std_marks ) );
		cout<<"Copy successful."<<endl;
	}
	fout.close();
	return;
}

void std_marks::show_marks() {
	ifstream fin;
	fin.open( "Files/details.dat", ios::in | ios::binary );
	fin.seekg(g_pos_file, ios_base::beg);
	while( fin.read( (char*)&r_marks, sizeof( std_marks ) ) ) {
		cout<<"Percentage:- \n";
		for( int i = 0; i < n_sub; i++ ) {
			cout<<"\tSubject "<< (i+1) << ": " << r_marks.perc[i] << endl;
		}
		cout<<"GPA:- \n";
		for( int i = 0; i < n_sub; i++ ) {
			cout<<"\tSubject "<< (i+1) << ": " << r_marks.gpa[i] << endl;
		}
		cout <<"CGPA: " << r_marks.cgpa << endl;
	}
	fin.close();
	return;
}

//Class Functions END HERE

//Program Functions...

void check_config(){		
	char word[30];
	string range;
	fstream cfg;
	cfg.open("Files/config.txt", ios::in);
	/*if(cfg.is_open()){
		cout<<"OPEN..."<<endl;	
	}*/
	while( cfg >> word ){
		if(  ( ( word[0] == '/' ) && ( word[1] == '/' ) ) || strlen( word ) ==0 ){
			continue;	
		}
		for( int i=0 ; i < n_settings ; i++ ){
		
			if( strcmp( word , list[i] )==0 ){
				//cout<<"A";	
				for( int j=0 ; j < 2 ; j++ ){
					cfg >> word;
				}
				for( int j=0 ; j < strlen(word) ; j++ ){
					if( word[j] == '[' ){

						for( int k=( j+1 ) ; k < strlen(word) ; ){
							while ( word[k] != ']' ){
								range += word[k];
								k++;
							}
							break;
						}
					}
					else{
						continue;	
					}
				}
				char*marks = &range[0];
				switch(i){
					case 0:
						n_fa = conv_to_int( marks );
						break;
						
					case 1:
						n_gpa = conv_to_int( marks );
						break;
				}
			}
		}
		range = "\0";
	}
	cfg.close();
	//cout<<n_fa<<" : "<<n_gpa;
}

void get_marks(){
	cout<<"Enter marks:- \n";
	for( int i = 0 ; i < n_sub ; i++ ){
		cout<<"\tSubject "<< (i+1) << ": ";
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
	
	for( int i = 0 ; i < n_sub ; i++ ){
		cout<<endl<<"PERC: "<<w_marks.calc_perc(i);	
	}
	
	for( int i = 0 ; i < n_sub ; i++ ){
		cout<<endl<<"GPA:"<<w_marks.calc_gpa(i);	
	}
	cout<<endl<<"CGPA: "<<w_marks.calc_cgpa();
	/*fstream fout;
	fout.open( "Files/Marks.bin", ios::out | ios::app | ios::binary );
	fout.write( (char*)&st_marks, sizeof( std_marks ) );
	fout.close();*/
	return;
}

