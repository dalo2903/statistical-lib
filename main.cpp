#include<iostream>
#include<sstream>
#include<stdio.h>
#include<string>
#include<stdlib.h>
#include<vector>
#include<map>
#include<windows.h>
#include<math.h>
#include<iomanip>
#include<algorithm>

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
bool compare_char(data i, data j){
    return (i.c<j.c);
}
bool compare_int(data i, data j){
    return (i.i<j.i);
}
bool compare_double(data i, data j){
    return (i.d<j.d);
}
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
public:
    int type;
    string data_set_name;
    statistical_lib(){
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
            sort(this->_data.begin(), this->_data.end(),compare_char);
            break;
        case TYPE_INT:
            _data_loader.load_int_data(file_name,this->_data);
            sort(this->_data.begin(), this->_data.end(), compare_int);
            break;
        case TYPE_DOUBLE:
            sort(this->_data.begin(), this->_data.end(), compare_double);
            _data_loader.load_double_data(file_name,this->_data);
            break;
        default:
            SetConsoleTextAttribute(hConsole, 12);
            cout<<"Invalid input"<<endl;
            SetConsoleTextAttribute(hConsole, 15);
            return;
        }
        if(!_data.empty())
            cout<<"Data loaded from "<<file_name<<endl;
    }

    void print(){
        for(vector<data>::iterator it = _data.begin(); it != _data.end(); ++it){
            switch(type){
            case TYPE_CHAR:
                cout<<(*it).c<<"\t";
                break;
            case TYPE_INT:
                cout<<(*it).i<<"\t";
                break;
            case TYPE_DOUBLE:
                cout<<(*it).d<<"\t";
                break;
            }
        }
    }
    double sum(){
        double sum = 0;
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
        return sum;
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
        double _mean = mean();
        size_t length = _data.size();
        for(vector<data>::iterator it = _data.begin(); it != _data.end(); ++it){
            switch(type){
            case TYPE_CHAR:
                standard_deviation += ((double)((*it).c) - _mean)*((double)((*it).c) - _mean);
                break;
            case TYPE_INT:
                standard_deviation += ((double)((*it).i) - _mean)*((double)((*it).i) - _mean);
                break;
            case TYPE_DOUBLE:
                standard_deviation += ((double)((*it).d) - _mean)*((double)((*it).d) - _mean);
                break;
            }
        }
        standard_deviation = sqrt(standard_deviation/length);
        return standard_deviation;
    }
    double variance(){
        double standard_deviation = 0;
        double _mean = mean();
        size_t length = _data.size();
        for(vector<data>::iterator it = _data.begin(); it != _data.end(); ++it){
            switch(type){
            case TYPE_CHAR:
                standard_deviation += ((double)((*it).c) - _mean)*((double)((*it).c) - _mean);
                break;
            case TYPE_INT:
                standard_deviation += ((double)((*it).i) - _mean)*((double)((*it).i) - _mean);
                break;
            case TYPE_DOUBLE:
                standard_deviation += ((double)((*it).d) - _mean)*((double)((*it).d) - _mean);
                break;
            }
        }
        standard_deviation = standard_deviation/length;
        return standard_deviation;
    }
    void histogram(){
        SetConsoleTextAttribute(hConsole, 27);
        cout<<"\t\tGenerated Histogram:"<<endl;
        SetConsoleTextAttribute(hConsole, 15);
        int max_num = 0;
        map<char, int> frequency_table_char;
        map<int, int> frequency_table_int;
        map<double, int> frequency_table_double;
        switch(type){
        case TYPE_CHAR:
            for(vector<data>::iterator it = _data.begin(); it != _data.end(); ++it){
                frequency_table_char[(*it).c]++;
            }
            for(map<char,int>::iterator it = frequency_table_char.begin(); it!=frequency_table_char.end(); ++it){
                int length = (*it).second ;
                if(length> max_num)
                    max_num = length;
                cout<<"\t"<<(*it).first <<"\t|";
                for (int i = 0; i< length; i++){
                    cout<<"* ";
                }
                cout<<endl;
            }
            cout<<"\t"<<"\t"<<setw(max_num*3)<<setfill('-')<<""<<endl;
            cout<<"\t"<<"\t ";
            for(int i = 1; i<= max_num; i++){
                if(i>=10){
                    cout<<i;
                }
                else
                cout<<i<<" ";
            }
            cout<<endl;
            break;
        case TYPE_INT:
            for(vector<data>::iterator it = _data.begin(); it != _data.end(); ++it){
                frequency_table_int[(*it).i]++;
            }
            for(map<int,int>::iterator it = frequency_table_int.begin(); it!=frequency_table_int.end(); ++it){
                int length = (*it).second ;
                if(length> max_num)
                    max_num = length;
                cout<<"\t"<<(*it).first <<"\t|";
                for (int i = 0; i< length; i++){
                    cout<<"* ";
                }
                cout<<endl;
            }
            cout<<"\t"<<"\t"<<setw(max_num*3)<<setfill('-')<<""<<endl;

            cout<<"\t"<<"\t ";
            for(int i = 1; i<= max_num; i++){
                if(i>=10){
                    cout<<i;
                }
                else
                cout<<i<<" ";
            }
            cout<<endl;
            break;
        case TYPE_DOUBLE:
            for(vector<data>::iterator it = _data.begin(); it != _data.end(); ++it){
                frequency_table_double[(*it).d]++;
            }
            for(map<double,int>::iterator it = frequency_table_double.begin(); it!=frequency_table_double.end(); ++it){
                int length = (*it).second ;
                if(length> max_num)
                    max_num = length;
                cout<<"\t"<<(*it).first <<"\t|";
                for (int i = 0; i< length; i++){
                    cout<<"* ";
                }
                cout<<endl;
            }
            cout<<"\t"<<"\t"<<setw(max_num*3)<<setfill('-')<<""<<endl;

            cout<<"\t"<<"\t ";
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
    double median(){
        double median = 0;
        int length = _data.size();
        if (length%2!=0) {
            int index = (length + 1)/2;
            switch (type) {
            case TYPE_CHAR:
                median = _data.at(index-1).c;
                break;
            case TYPE_INT:
                median = _data.at(index-1).i;
                break;
            case TYPE_DOUBLE:
                median = _data.at(index-1).d;
                break;
            }
        }
        else {
            int index = length/2;
            switch (type) {
             case TYPE_CHAR:
                median = (double)(_data.at(index-1).c + _data.at(index).c)/2;
                break;
            case TYPE_INT:
                median = (double)(_data.at(index-1).i + _data.at(index).i)/2;
                break;
            case TYPE_DOUBLE:
                median = (double)(_data.at(index-1).d + _data.at(index).d)/2;
                break;
            }
        }
        return median;
    }
    double Q1(){
        double Q1 = 0;
        int length = _data.size();
        int ele ;
        if (length%2!=0) {
            ele = (length -1)/2;
        }
        else {
            ele = length/2;
        }
        if (ele%2!=0) {
            int index = (ele + 1)/2;
            switch (type) {
             case TYPE_CHAR:
                Q1 = _data.at(index-1).c;
                break;
            case TYPE_INT:
                Q1 = _data.at(index-1).i;
                break;
            case TYPE_DOUBLE:
                Q1 = _data.at(index-1).d;
                break;
            }
        }
        else {
            int index = ele/2;
            switch (type) {
             case TYPE_CHAR:
                Q1 = (double)(_data.at(index-1).c + _data.at(index).c)/2;
                break;
            case TYPE_INT:
                Q1 = (double)(_data.at(index-1).i + _data.at(index).i)/2;
                break;
            case TYPE_DOUBLE:
                Q1 = (double)(_data.at(index-1).d + _data.at(index).d)/2;
                break;
            }
        }
        return Q1;
    }
    double Q3(){
        double Q3 = 0;
        int length = _data.size();
        int ele ;
        if (length%2!=0) {
            ele = (length -1)/2;
        }
        else {
            ele = length/2;
        }
        if (ele%2!=0) {
            int index = (ele + 1)/2 + ele +1;
            switch (type) {
             case TYPE_CHAR:
                Q3 = _data.at(index-1).c;
                break;
            case TYPE_INT:
                Q3 = _data.at(index-1).i;
                break;
            case TYPE_DOUBLE:
                Q3 = _data.at(index-1).d;
                break;
            }
        }
        else {
            int index = ele/2  + ele ;
            switch (type) {
             case TYPE_CHAR:
                Q3 = (double)(_data.at(index-1).c + _data.at(index).c)/2;
                break;
            case TYPE_INT:
                Q3 = (double)(_data.at(index-1).i + _data.at(index).i)/2;
                break;
            case TYPE_DOUBLE:
                Q3 = (double)(_data.at(index-1).d + _data.at(index).d)/2;
                break;
            }
        }
        return Q3;
    }
    vector<double> mode (){
        vector<double> results;
        map<char, int> frequency_table_char;
        map<int, int> frequency_table_int;
        map<double, int> frequency_table_double;
        int _max = 0;

        switch(type){
        case TYPE_CHAR:
            for(vector<data>::iterator it = _data.begin(); it != _data.end(); ++it){
                frequency_table_char[(*it).c]++;
            }
            for(map<char,int>::iterator it = frequency_table_char.begin(); it!=frequency_table_char.end(); ++it){
                if(_max < (*it).second) _max = (*it).second;
            }
            for(map<char,int>::iterator it = frequency_table_char.begin(); it!=frequency_table_char.end(); ++it){
                if(_max == (*it).second)
                    results.push_back((*it).first);
            }
            break;
        case TYPE_INT:
            for(vector<data>::iterator it = _data.begin(); it != _data.end(); ++it){
                frequency_table_int[(*it).i]++;
            }
            for(map<int,int>::iterator it = frequency_table_int.begin(); it!=frequency_table_int.end(); ++it){
                if(_max < (*it).second) _max = (*it).second;
            }
            for(map<int,int>::iterator it = frequency_table_int.begin(); it!=frequency_table_int.end(); ++it){
                if(_max == (*it).second)
                    results.push_back((*it).first);
            }
            break;
        case TYPE_DOUBLE:
            for(vector<data>::iterator it = _data.begin(); it != _data.end(); ++it){
                frequency_table_double[(*it).d]++;
            }
            for(map<double,int>::iterator it = frequency_table_double.begin(); it!=frequency_table_double.end(); ++it){
                if(_max < (*it).second) _max = (*it).second;
            }
            for(map<double,int>::iterator it = frequency_table_double.begin(); it!=frequency_table_double.end(); ++it){
                if(_max == (*it).second)
                    results.push_back((*it).first);
            }
            break;
        }
        return results;
    }
    void noise(){
        double standard_deviation = this->standard_deviation();
        double mean = this->mean();
        double z_score = 0;
        for(vector<data>::iterator it = _data.begin(); it != _data.end(); ){
            switch(type){
            case TYPE_CHAR:
                z_score = (double)((*it).c - mean )/ standard_deviation;
                if(z_score > 3){
                    cout<<(*it).c<<"IS NOISE";
                    it = _data.erase(it);
                }
                else ++it;
                break;
            case TYPE_INT:
                z_score = (double)((*it).i - mean )/ standard_deviation;
                if(z_score > 3){
                    cout<<(*it).i<<"IS NOISE";
                    it = _data.erase(it);
                }
                else ++it;
                break;
            case TYPE_DOUBLE:
                z_score = (double)((*it).d - mean )/ standard_deviation;
                if(z_score > 3){
                    cout<<(*it).d<<"IS NOISE";
                    it = _data.erase(it);
                }
                else ++it;
                break;
            }
        }
        cout<<"Data after noise reduction: "<<endl;
        histogram();
    }
};
statistical_lib _statistical_lib;

class menu_printer{
public:
    void print_title(){
        system("CLS");
        cout<<"+"<<setw(70)<<setfill('-')<<right<<"+"<<endl;
        cout<<"|";
        SetConsoleTextAttribute(hConsole, 14);
        cout<<setw(69)<<setfill(' ')<<left<<"                     STATISTICAL LIBRARY";
        SetConsoleTextAttribute(hConsole, 15);
        cout<<"|"<<endl;
        cout<<"|";
        SetConsoleTextAttribute(hConsole, 11);
        cout<<setw(69)<<setfill(' ')<<left<<"                         Assignment 1";
        SetConsoleTextAttribute(hConsole, 15);
        cout<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<right<<"Students       ID          "<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<right<<"Dinh Duy Kha      1411675        "<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<right<<"Nguyen Xuan Danh  1652736        "<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<right<<"Cu Huy Chien      1111111        "<<"|"<<endl;

        cout<<"+"<<setw(70)<<setfill('-')<<right<<"+"<<endl;
        setfill(' ');
    }
    void print_main_menu_no_data(){
        cout<<"|";
        SetConsoleTextAttribute(hConsole, 12);
        cout<<setw(69)<<setfill(' ')<<left<<"           There is no dataset loaded. Please load a data set.";
        SetConsoleTextAttribute(hConsole, 15);
        cout<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                 1. Load a data set"<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                 0. Exit"<<"|"<<endl;
        cout<<"|"<<setw(70)<<setfill(' ')<<right<<"|"<<endl;
        cout<<"+"<<setw(70)<<setfill('-')<<right<<"+"<<endl;
        cout<<"Selection: ";


    }
    void print_main_menu(){
        cout<<"|";
        SetConsoleTextAttribute(hConsole, 27);
        cout<<setw(30)<<setfill(' ')<<left<<"           Loaded data set: "<<setw(39)<<left<<_statistical_lib.data_set_name;
        SetConsoleTextAttribute(hConsole, 15);
        cout<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                 1. Calculate Sum"<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                 2. Calculate Mean"<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                 3. Calculate Standard Deviation"<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                 4. Calculate Variance"<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                 5. Calculate Q1, Median and Q3"<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                 6. Calculate mode"<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                 7. Visualize histogram"<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                 8. Visualize noise"<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                 9. Load another data set"<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                 10. Print data set"<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                 0. Exit"<<"|"<<endl;
        cout<<"|"<<setw(70)<<setfill(' ')<<right<<"|"<<endl;
        cout<<"+"<<setw(70)<<setfill('-')<<right<<"+"<<endl;
        cout<<"Selection: ";
    }
    void print_load_data_menu(){
        cout<<"+"<<setw(70)<<setfill('-')<<right<<"+"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                   Please choose type of data:"<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                   1. char"<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                   2. int"<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                   3. double"<<"|"<<endl;
        cout<<"|"<<setw(69)<<setfill(' ')<<left<<"                   0. Exit"<<"|"<<endl;

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
                if(input == 0)
                    break;
                cout<<"Enter file name: ";
                cin >> str_input;
                _statistical_lib.load_data(str_input,input);
                break;
            default:
                SetConsoleTextAttribute(hConsole, 12);
                cout<<"Invalid input"<<endl;
                SetConsoleTextAttribute(hConsole, 15);
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
                cout << "Sum = "<<setprecision(10)<< _statistical_lib.sum()<<endl;
                break;
            case 2:
                cout << "Mean = "<<setprecision(10)<< _statistical_lib.mean()<<endl;
                break;
            case 3:
                cout << "Standard deviation = "<<setprecision(10)<< _statistical_lib.standard_deviation()<<endl;
                break;
            case 4:
                cout << "Variance = "<<setprecision(10)<<_statistical_lib.variance()<<endl;
                break;
            case 5:
                cout << "Q1 = "<<setprecision(10)<<_statistical_lib.Q1()<<endl;
                cout << "Median = "<<setprecision(10)<<_statistical_lib.median()<<endl;
                cout << "Q3 = "<<setprecision(10)<<_statistical_lib.Q3()<<endl;
                cout << endl;
                break;
            case 6:{
                vector<double> results;
                results = _statistical_lib.mode();
                cout << "Mode = ";
                for(vector<double>::iterator it = results.begin(); it != results.end(); ++it){
                    switch(_statistical_lib.type){
                    case TYPE_CHAR:
                        cout<< (char)(*it);
                        break;
                    case TYPE_INT:
                        cout<< (*it);
                        break;
                    case TYPE_DOUBLE:
                        cout<< (*it);
                        break;
                    }
                    if(it!= results.end() - 1)
                        cout<<", ";
                }
                cout<<endl;
                break;
            }
            case 7:
                _statistical_lib.histogram();
                break;
            case 8:
                _statistical_lib.noise();
                break;
            case 9:
                p.print_load_data_menu();
                cin >> input;
                cout<<"Enter file name: ";
                cin >> str_input;
                _statistical_lib.load_data(str_input,input);
                break;
            case 10:
                _statistical_lib.print();
                break;
            default:
                SetConsoleTextAttribute(hConsole, 12);
                cout<<"Invalid input"<<endl;
                SetConsoleTextAttribute(hConsole, 15);
                break;
            }
        }
        fflush(stdin);
        system("PAUSE");

    }
}
