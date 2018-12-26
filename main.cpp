#include<iostream>
#include<sstream>
#include<stdio.h>
#include<string>
#include<stdlib.h>
#include<vector>
#include<map>
#include <windows.h>

#include<iomanip>
#define TYPE_CHAR 1
#define TYPE_INT 2
#define TYPE_DOUBLE 3


using namespace std;
union data{
    char c;
    int i;
    double d;
};
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
class data_loader {
private:
    FILE* fp = NULL;
public:
    bool open_file(string file_name){
        fp = fopen(file_name.c_str(), "r");
        if(fp == NULL){
            cout <<"Error opening file: "<<file_name<<endl;
            return false;
        }
        else return true;
    }
    void load_char_data(string file_name, vector<data> &d){
        if(!open_file(file_name))
            return;
        data dat;
        while (fscanf(fp,"%c\n",&(dat.c))!= EOF) {
            d.push_back(dat);
        }
        fclose(fp);
    }
    void load_int_data(string file_name, vector<data> &d){
        if(!open_file(file_name))
            return;
        data dat;
        while (fscanf(fp,"%d\n",&(dat.i))!= EOF) {
            d.push_back(dat);
        }
        fclose(fp);
    }
    void load_double_data(string file_name,vector<data> &d){
        if(!open_file(file_name))
            return;
        data dat;
        while (fscanf(fp,"%lf\n",&(dat.d))!= EOF) {
            d.push_back(dat);
        }
        fclose(fp);
    }

};

class statistical_lib {
private:
    data_loader _data_loader;
    vector<data> _data;
    int type;
public:
    string data_set_name;
    statistical_lib(){
    }
    data sum(){
        data sum;
        return sum;
    }
    bool is_empty(){
        return _data.empty();
    }
    void load_data(string file_name, int type){
        this->type = type,
        data_set_name = file_name;
        _data.clear();
        switch(type){
        case TYPE_CHAR:
            _data_loader.load_char_data(file_name,this->_data);
            break;
        case TYPE_INT:
            _data_loader.load_int_data(file_name,this->_data);
            break;
        case TYPE_DOUBLE:
            _data_loader.load_double_data(file_name,this->_data);
            break;
        default:
            cout<<"Invalid input!"<<endl;
            return;
        }
        if(!_data.empty())
            cout<<"Data loaded from "<<file_name<<endl;
    }
    void print(){
        for(vector<data>::iterator it = _data.begin(); it != _data.end(); ++it){
            switch(type){
            case TYPE_CHAR:
                cout<<(*it).c<<endl;
                break;
            case TYPE_INT:
                cout<<(*it).i<<endl;
                break;
            case TYPE_DOUBLE:
                cout<<(*it).d<<endl;
                break;
            }
        }

    }
    double mean(){
        double mean = 0;
        double sum = 0;
        size_t length = _data.size();
        for(vector<data>::iterator it = _data.begin(); it != _data.end(); ++it){
            switch(type){
            case TYPE_CHAR:
                sum += (*it).c;
                break;
            case TYPE_INT:
                sum += (*it).i;
                break;
            case TYPE_DOUBLE:
                sum += (*it).d;
                break;
            }
        }
        mean = sum/length;
        return mean;
    }
    double standard_deviation(){
        double standard_deviation = 0;
        return standard_deviation;
    }
    void histogram(){
        SetConsoleTextAttribute(hConsole, 27);
        cout<<"\t\tGenerated Histogram:"<<endl;
        SetConsoleTextAttribute(hConsole, 15);

        switch(type){
        case TYPE_CHAR:
            map<char, int> frequency_table;
            for(vector<data>::iterator it = _data.begin(); it != _data.end(); ++it){
                frequency_table[(*it).c]++;
            }
            int max_num = 0;
            for(map<char,int>::iterator it = frequency_table.begin(); it!=frequency_table.end(); ++it){
                int length = (*it).second ;
                if(length> max_num)
                    max_num = length;
                cout<<"\t"<<(*it).first <<" |";
                for (int i = 0; i< length; i++){
                    cout<<"* ";
                }
                cout<<endl;
            }
            cout<<"\t"<<"  "<<setw(max_num*3)<<setfill('-')<<""<<endl;

            cout<<"\t"<<"   ";
            for(int i = 1; i<= max_num; i++){
                if(i>=10){
                    cout<<i;
                }
                else
                cout<<i<<" ";
            }
            cout<<endl;
            break;
        }


    }
};
statistical_lib _statistical_lib;

class menu_printer{
public:
    void print_title(){
        system("CLS");
        cout<<"+"<<setw(70)<<setfill('-')<<right<<"+"<<endl;
        SetConsoleTextAttribute(hConsole, 14);
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                     STATISTICAL LIBRARY"<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                       Assignment 1"<<"|"<<endl;
        SetConsoleTextAttribute(hConsole, 15);
        cout<<"+"<<setw(70)<<setfill('-')<<right<<"+"<<endl;
        setfill(' ');
    }
    void print_main_menu_no_data(){
        SetConsoleTextAttribute(hConsole, 12);
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"           There is no dataset loaded. Please load a data set."<<"|"<<endl;
        SetConsoleTextAttribute(hConsole, 15);
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                 1. Load a data set"<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                 0. Exit"<<"|"<<endl;
        cout<<"|"<<setw(70)<<setfill(' ')<<right<<"|"<<endl;
        cout<<"+"<<setw(70)<<setfill('-')<<right<<"+"<<endl;
        cout<<"Selection: ";


    }
    void print_main_menu(){
        SetConsoleTextAttribute(hConsole, 27);
        cout<<"|"<<setw(30)<<setfill(' ')<<left<<"           Loaded data set: "<<setw(39)<<left<<_statistical_lib.data_set_name<<"|"<<endl;
        SetConsoleTextAttribute(hConsole, 15);
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                 1. Load another data set"<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                 2. Print data set"<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                 3. Calculate mean"<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                 7. Visualize histogram"<<"|"<<endl;

        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                 0. Exit"<<"|"<<endl;
        cout<<"|"<<setw(70)<<setfill(' ')<<right<<"|"<<endl;
        cout<<"+"<<setw(70)<<setfill('-')<<right<<"+"<<endl;
        cout<<"Selection: ";
    }
    void print_load_data_menu(){
        cout<<"+"<<setw(70)<<setfill('-')<<right<<"+"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                  Please choose type of data:"<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                  1. char"<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                  2. int"<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                  3. double"<<"|"<<endl;
        cout<<"+"<<setw(70)<<setfill('-')<<right<<"+"<<endl;
        cout<<"Selection: ";

    }
};

int main()
{
    SetConsoleTextAttribute(hConsole, 15);
    bool running = true;
    int input = 0;
    string str_input = "";
    menu_printer p;
    data_loader f;
    while(running){
        p.print_title();
        if(_statistical_lib.is_empty()){
            p.print_main_menu_no_data();
            cin >> input;
            switch (input){
            case 0:
                running = false;
                break;
            case 1:
                p.print_load_data_menu();
                cin >> input;
                cout<<"Enter file name: ";
                cin >> str_input;
                _statistical_lib.load_data(str_input,input);
                break;
            default:
                cout<<"Invalid input!"<<endl;
                break;

            }
        }
        else{
            p.print_main_menu();
            cin >> input;
            switch (input){
            case 0:
                running = false;
                break;
            case 1:
                p.print_load_data_menu();
                cin >> input;
                cout<<"Enter file name: ";
                cin >> str_input;
                _statistical_lib.load_data(str_input,input);
                break;
            case 2:
                _statistical_lib.print();
                break;
            case 3:
                cout << "Mean = "<< _statistical_lib.mean()<<endl;
                break;
            case 7:

                _statistical_lib.histogram();



                break;
            default:
                cout<<"Invalid input"<<endl;
                break;
            }


        }
        fflush(stdin);
        system("PAUSE");

    }
}
