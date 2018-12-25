#include <iostream>
#include<sstream>
#include<stdio.h>
#include<string>
#include <stdlib.h>


using namespace std;

union data{
    char c;
    int i;
    double d;
};

class file_loader {
private:
    FILE* fp = NULL;
public:
    size_t load_data(string file_name, data* d, int type){
        size_t arr_size = 0;
        switch(type){
        case 1:
            arr_size = load_char_data(file_name, d);
            break;
        case 2:
            arr_size = load_int_data(file_name, d);
            break;
        case 3:
            arr_size = load_char_data(file_name, d);
            break;
        }
        return arr_size;
    }
    size_t load_char_data(string file_name, data *d){
        fp = fopen(file_name.c_str(), "r");
        size_t i = 0;
        char ch;
        while ((ch = fgetc(fp))!= EOF) {
            if(ch!='\n'){
                d[i].c = ch;
                i++;
            }
        }
        fclose(fp);
        return i;
    }
     size_t load_int_data(string file_name, data *d){
        fp = fopen(file_name.c_str(), "r");
        size_t i = 0;
        char ch;
        while ((ch = fgetc(fp))!= EOF) {
            if(ch!='\n'){
                d[i].i = ch - '0';
                i++;
            }
        }
        fclose(fp);
        return i;
    }

};

class statistical_lib {
public:
    data _data[10000];
    int type;
    size_t length;
    data sum(){
        data sum;
        return sum;
    }
    void print(){
        switch(type){
        case 1:
            for(int i = 0; i < length; i++){
                cout<<_data[i].c<<endl;
            }
            break;

        case 2:
            for(int i = 0; i < length; i++){
                cout<<_data[i].i<<endl;
            }
            break;

        }
    }
    double mean(){
        double mean = 0;
        return mean;
    }
    double standard_deviation(){
        double standard_deviation = 0;
        return standard_deviation;
    }
};
class menu_printer{
public:
    void print_main_menu_no_data(){
        cout<<"Statistical Library"<<endl;
        cout<<"1. Load a data set"<<endl;
        cout<<"0. Exit"<<endl;
    }
    void print_main_menu(){
        cout<<"Statistical Library"<<endl;
        cout<<"1. Load a data set"<<endl;
        cout<<"2. Load a data set"<<endl;
        cout<<"0. Exit"<<endl;
    }
    void print_load_data_menu(){
        cout<<"Please choose type of data: "<<endl;
        cout<<"1. char"<<endl;
        cout<<"2. int"<<endl;
        cout<<"3. double"<<endl;
    }
};
int main()
{
    statistical_lib _statistical_lib;
    bool data_loaded = false;
    bool running = true;
    int input = 0;
    string str_input = "";
    menu_printer p;
    file_loader f;
    while(running){
        if(data_loaded == false){
            p.print_main_menu_no_data();
            cin >> input;
            switch (input){
            case 0:
                running = false;
                break;
            case 1:
                p.print_load_data_menu();
                cin >> input;
                switch(input){
                case 1:
                    cout<<"Enter file name:";
                    cin >> str_input;
                    _statistical_lib.type = 1;
                    _statistical_lib.length = f.load_data(str_input,_statistical_lib._data, 1);
                    data_loaded = true;
                    break;
                case 2:
                    cout<<"Enter file name:";
                    cin >> str_input;
                    _statistical_lib.type = 2;
                    _statistical_lib.length = f.load_data(str_input,_statistical_lib._data, 2);
                    data_loaded = true;
                    break;
                    break;
                case 3:
                    break;
                }
                fflush(stdin);
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
                switch(input){
                case 1:
                    cout<<"Enter file name:";
                    cin >> str_input;
                    _statistical_lib.type = 1;
                    _statistical_lib.length = f.load_data(str_input,_statistical_lib._data, 1);
                    data_loaded = true;
                    break;
                case 2:
                    cout<<"Enter file name:";
                    cin >> str_input;
                    _statistical_lib.type = 2;
                    _statistical_lib.length = f.load_data(str_input,_statistical_lib._data, 2);
                    data_loaded = true;
                    break;
                case 3:
                    break;
                }
            case 2:
                _statistical_lib.print();
                break;

            }
            fflush(stdin);

        }

    }
    /*
    file_loader f;
    data_array d;
    d.type = 1;
    string file_name = "test.dat";
    int l = f.load_data(file_name,d);

    return 0;*/
}
