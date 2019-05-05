#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <regex>
#include <cstring>
#include <unistd.h> // for sleep()

using namespace std;
//------------------------------------------------------- Structs and Own Data Type ----------------------------------------------

struct Date{
    int ano, mes, dia;
};


struct Address{
    string rua_nome;
    int porta_number;
    string andar_number;
    string zip_code;
    string localidade;
};

struct TravelPack{
    int id;
    string local;
    Date end_date;
    Date start_date;
    string start_places;
    string sold_places;
    string price;
};

struct Cliente{
    string nome;
    string nif;
    int number_agregado;
    Address morada;
    string pacotes;
    int total_compras;
};


struct Agency{
    string nome;
    string nif;
    Address morada;
    string website;
    string clientes;
    string pacotes;
};