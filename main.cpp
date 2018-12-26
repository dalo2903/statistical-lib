#include <iostream>
#include<sstream>
#include<stdio.h>
#include<string>
#include <stdlib.h>
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
    size_t load_char_data(string file_name, data *d){
        size_t i = 0;
        if(!open_file(file_name))
            return 0;
        while (fscanf(fp,"%c\n",&(d[i].c))!= EOF) {
            i++;
        }
        fclose(fp);
        return i;
    }
    size_t load_int_data(string file_name, data *d){
        if(!open_file(file_name))
            return 0;
        size_t i = 0;
        while (fscanf(fp,"%d\n",&(d[i].i))!= EOF) {
            i++;
        }
        fclose(fp);
        return i;
    }
    size_t load_double_data(string file_name, data *d){
        if(!open_file(file_name))
            return 0;
        size_t i = 0;
        while (fscanf(fp,"%lf\n",&(d[i].d))!= EOF) {
            i++;
        }
        fclose(fp);
        return i;
    }

};

class statistical_lib {
private:
    data_loader _data_loader;
    data _data[100000];
    int type;
public:
    string data_set_name;
    size_t length;
    statistical_lib(){
        length = 0;
    }
    data sum(){
        data sum;
        return sum;
    }
    void load_data(string file_name, int type){
        this->type = type,
        this->data_set_name = file_name;
        switch(type){
        case TYPE_CHAR:
            this->length = _data_loader.load_char_data(file_name,this->_data);
            break;
        case TYPE_INT:
            this->length = _data_loader.load_int_data(file_name,this->_data);
            break;
        case TYPE_DOUBLE:
            this->length = _data_loader.load_double_data(file_name,this->_data);
            break;
        default:
            cout<<"Invalid input!"<<endl;
            return;
        }
        if(this->length > 0)
            cout<<"Data loaded from "<<file_name<<endl;
    }
    void print(){
        switch(type){
        case TYPE_CHAR:
            for(size_t i = 0; i < length; i++){
                cout<<_data[i].c<<endl;
            }
            break;
        case TYPE_INT:
            for(size_t i = 0; i < length; i++){
                cout<<_data[i].i<<endl;
            }
            break;
        case TYPE_DOUBLE:
            for(size_t i = 0; i < length; i++){
                cout<<_data[i].d<<endl;
            }
            break;
        }
    }
    double mean(){
        double mean = 0;
        double sum = 0;

        switch(type){
            case TYPE_CHAR:
                for (size_t i = 0; i< length; i++){
                sum += _data[i].c;
                }
                mean = sum/length;
                break;
            case TYPE_INT:
                for (size_t i = 0; i< length; i++){
                sum += _data[i].i;
                }
                mean = sum/length;
                break;
            case TYPE_DOUBLE:
                for (size_t i = 0; i< length; i++){
                sum += _data[i].d;
                }
                mean = sum/length;
                break;
        }
        return mean;
    }
    double standard_deviation(){
        double standard_deviation = 0;
        return standard_deviation;
    }
};
statistical_lib _statistical_lib;

class menu_printer{
public:
    void print_title(){
        system("CLS");
        cout<<"+"<<setw(70)<<setfill('-')<<right<<"+"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                     STATISTICAL LIBRARY"<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                       Assignment 1"<<"|"<<endl;
        cout<<"+"<<setw(70)<<setfill('-')<<right<<"+"<<endl;
        setfill(' ');
    }
    void print_main_menu_no_data(){
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"           There is no dataset loaded. Please load a data set."<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                 1. Load a data set"<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                 0. Exit"<<"|"<<endl;
        cout<<"|"<<setw(70)<<setfill(' ')<<right<<"|"<<endl;
        cout<<"+"<<setw(70)<<setfill('-')<<right<<"+"<<endl;
        cout<<"Selection: ";


    }
    void print_main_menu(){
        cout<<"|"<<setw(30)<<setfill(' ')<<left<<"           Loaded data set: "<<setw(39)<<left<<_statistical_lib.data_set_name<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                 1. Load another data set"<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                 2. Print data set"<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                 3. Calculate mean"<<"|"<<endl;
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
    bool running = true;
    int input = 0;
    string str_input = "";
    menu_printer p;
    data_loader f;
    while(running){
        p.print_title();
        if(_statistical_lib.length <= 0){
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
            default:
                cout<<"Invalid input"<<endl;
                break;
            }


        }
        fflush(stdin);
        system("PAUSE");

    }
}
