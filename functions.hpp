#include "structures.hpp"
//-------------------------------------------General functions ----------------------------------------------------

//Loading function
void loadingFunc();

//Fill my Date data type objects with correct info.
Date date_handler(string linha);

//responsible to organize the parameters of my object of Date data type, into a nice and correct output into format year/month/day
string return_date(Date date);

//fill a string vector with informations separated by a certain delimiter
void tokenize(string const &str, const char delim, vector<string> &out);

//responsible for process my addresses removing the '/', making a plan line with spaces, so i can use it with my stringstream
Address address_handler(string line);

//Will read all my integers instead of a simple cin
int readInteger();

//Will represent all my menus options;
int readOptions(const vector<string> &menu);

//makes a proper print of the addres data type
string return_addres(Address endereco);

//Will generate a safe copy of a file;
void makeCopy(string filename);
//------------------------------------------- Agency functions ----------------------------------------------------

//Makes me a Agency object fully filled with information
Agency agency_handler(vector<string> linesInfo);

//-------------------------------------------- Clients functions -----------------------------------

//Function responsible to handle with my Clients data to the file of my clients.
Cliente client_handler(vector<string> clients);

//Creates all the clients presents in the file clients.txt
vector<Cliente> client_data(string tmp_client_data);

//it will automate de clients_question job
vector<string> clientQuestionHandler(vector<string> vec);

//creates a new vector<string> with the data needed to create my new client
vector<string> clients_questions();

//Add new client
vector<Cliente> add_client(vector<Cliente> &vec);

//remove a client (remove all data of that client)
void remove_client(vector<Cliente> &vec);

//Vector of Integers with the ID of the packages that a client have bought, the idea here is to be able to modify each element of this vector
void clients_packs(string line, vector<int> &aux);

//Update/change the information of a client;
void update_client(vector<Cliente> &vec);

//Print a specific client info based on NIF
void printClient(vector<Cliente> &vec);

//Print all data into a vector of clients
void print_all_clients(vector<Cliente> &vec);

//Writes the content of my client vector into a file;
void writeClients(string file_name, vector<Cliente> &vec);

// ------------------------------------------------------ Packs Functions -------------------------------------------------------

//Function responsible to understand wich components of the file is a Travel Package.
TravelPack packs_handler(vector<string> pack_vec);

//Function that creates a vector containing all the multiple Travel Packages provided by the agency.
vector<TravelPack> packs_data(string pack_file);

//Get's the ID of the last pack to be added to the packs file
int lastID(vector<TravelPack> &vec);

//Creates a new string vector filled with data that will be needed to create a new Travel Pack
vector<string> packQuestionHandler(vector<string> vec);

//Automates the input of information of new packages
vector<string> packs_questions(vector<TravelPack> &vec);

//Add new packages to the Travel Package file.
void add_packs(vector<TravelPack> &vec);

//Print all the content of my vector containing my packages
void print_all_packs(vector<TravelPack> &vec);

//Function to visualize packs data within a specific destiny
void printDestinyPack(vector<TravelPack> &vec);

//Visualize information of a pack between dates
void printFromDates(vector<TravelPack> &vec);

//Visualize information of a pack within a destiny and between dates
void printDestinyAndDates(vector<TravelPack> &vec);

//Print a certain package sold to a client
void printToClient(vector<TravelPack> &vec, vector<Cliente> &client);

//Print all the packages bought by the clients
void printPackageAllClients(vector<TravelPack> &packs, vector<Cliente> &client);

//Manage to sell a package to a certain client
void sellToClient(vector<TravelPack> &packs , vector<Cliente> &client);

//Attempt to create a function that removes a current Package provided by the travel agency.
void remove_packs(vector<TravelPack> &vec);

//Update/Change the information of a pack;
void update_packs(vector<TravelPack> &vec);

//prototipe of the function that writes the vector of Travel pack into a file
void writePacks(string file_name, vector<TravelPack> &vec);


//Manage to sell a package to a certain client
void sellToClient(vector<TravelPack> &packs , vector<Cliente> &client);

//Calculates and visualize the number and the total value of sold packages
void totalPackageSold(vector<TravelPack> &packs, vector<Cliente> &client);

//------------------------------------------------------------ MENU WINDOWS -------------- THIS IS TROUBLE --------------
//"Menu for agency"
int agency_operations(Agency &agency);

//Menu for clients, same thing ... headache if i have problems to fix, wich ofc will happen.
void clients_operations(Agency &agency, vector<Cliente> &clients);

//Menu for the packs operations this will give me a headache aswell.
void packs_operation(Agency &agency, vector<TravelPack> &packs, vector<Cliente> &clients);

//Main menu
void overalMenu(Agency &agency);