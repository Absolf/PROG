#include "functions.hpp"
//-------------------------------------------General functions ----------------------------------------------------

//Loading function
void loadingFunc(){
    std::cout << "Loading Please Wait";
    int i = 0;
    while (i<=0)
    {
        sleep(1);
        std::cout << "." << std::flush;
        sleep(1);
        std::cout << "." << std::flush;
        sleep(1);
        std::cout << "." << std::flush;
        sleep(1);
        std::cout << "\b\b\b   \b\b\b" << std::flush;
        i++;
    }
    cout << endl;
    
}
//Fill my Date data type objects with correct info.
Date date_handler(string linha){
    Date data;
    linha = regex_replace(linha,regex("/")," ");
    istringstream teste(linha);
    teste >> data.ano >> data.mes >> data.dia;
    //cout << data.ano << "/"<<data.mes<<"/"<<data.dia<<endl;
    return data;
}
//responsible to organize the parameters of my object of Date data type, into a nice and correct output into format year/month/day
string return_date(Date date){
    stringstream ss;
    string date_output;
    if (date.mes < 10 && date.dia < 10){
        ss << date.ano << "/0" << date.mes << "/0" << date.dia;
        date_output = ss.str();
    }else if(date.mes <10 && date.dia > 10){
        ss << date.ano << "/0" << date.mes << "/" << date.dia;
        date_output = ss.str();
    }else if(date.mes > 10 && date.dia< 10) {
        ss << date.ano << "/" << date.mes << "/0" << date.dia;
        date_output = ss.str();
    }else{
        ss << date.ano << "/" << date.mes << "/" << date.dia;
        date_output = ss.str();
    }
    return date_output;
}
//fill a string vector with informations separated by a certain delimiter
void tokenize(string const &str, const char delim, vector<string> &out){
        stringstream ss(str);
        string s;
        while(getline(ss,s,delim)){
            out.push_back(s);
        }
}

//function that process my addresses removing the '/', making a plan line with spaces, so i can use it with my stringstream
Address address_handler(string line){
    Address endereco;
    vector<string> addres_vec;
    tokenize(line, '/', addres_vec);
    for(int i=0; i < addres_vec.size();i++){
        if (i==0){
            endereco.rua_nome = addres_vec.at(0);
        }
        else if (i==1){
            istringstream teste(addres_vec.at(1));
            teste >> endereco.porta_number;
        }
        else if (i==2){
            endereco.andar_number = addres_vec.at(2);
        }
        else if (i==3){
            endereco.zip_code = addres_vec.at(3);
        }
        else if (i==4){
            endereco.localidade = addres_vec.at(4);
        }
    }
    return endereco;
}
//function that will read all my integers instead of a simple cin
int readInteger(){
    int x;
    cin >> x;
    while(cin.fail()){
        
        cout << "Please type a integer number\n";
        cin >> x;
        if(cin.fail()){
            cin.clear();
            cin.ignore();
            cout<<"You have entered a wrong input \n";
            cin >> x;
        }
        if(!cin.fail()){
            return x;
        }
    }
    return x;
}
//Function that will represent all my menus options;
int readOptions(const vector<string> &menu){
    cout << ":::::::::::::::::::::::::::::::::::"<< endl;
    cout<< "             options             "<<endl;
    cout << ":::::::::::::::::::::::::::::::::::"<< endl;
    for(size_t i = 0; i< menu.size(); i++){
        cout <<i+1 <<" - " <<menu.at(i)<<endl;
    }
    cout << "0 - Quit\nAnswer: ";
    int option = readInteger();//Function yet to finish
    while (option < 0 || option > menu.size()){
        option = readInteger();
    }
    return option;
}

string return_addres(Address endereco){
    stringstream ss;
    string address_output;
    ss << "Rua: "<< endereco.rua_nome <<endl;
    ss << "Nº porta/prédio: " << endereco.porta_number << endl;
    ss << "Andar: " << endereco.andar_number<< endl;
    ss << "Código postal: "<< endereco.zip_code << endl;
    ss << "Localidade: " << endereco.localidade << endl;
    address_output = ss.str();
    return address_output;
}
//------------------------------------------- Agency functions ----------------------------------------------------

//function that makes me a Agency object fully filled with information
Agency agency_handler(vector<string> linesInfo){
    Agency agency;
    agency.nome = linesInfo.at(0);
    agency.nif = linesInfo.at(1);
    agency.website = linesInfo.at(2);
    agency.morada = address_handler(linesInfo.at(3));
    agency.clientes = linesInfo.at(4);
    agency.pacotes = linesInfo.at(5);
    return agency;
}
//-------------------------------------------- Clients functions -----------------------------------

//Function responsible to handle with my Clients data to the file of my clients.
Cliente client_handler(vector<string> clients){
    Cliente client;
    client.nome = clients.at(0);
    client.nif = clients.at(1);
    istringstream teste(clients.at(2));
    teste >> client.number_agregado;
    client.morada = address_handler(clients.at(3));
    client.pacotes = clients.at(4);
    client.total_compras = count(clients.at(4).begin(), clients.at(4).end(), ';') +1;
    return client;
}
//Função que me cria um vetor com todos os clientes presentes no texto;
vector<Cliente> client_data(string tmp_client_data){
    cout<<"i started"<<endl;
    vector<Cliente> client_info;
    ifstream file;
    string lines;
    vector<string> clients_lines;
    file.open(tmp_client_data);
    while(getline(file, lines, '\n')){
        if (lines == "::::::::::"){
            client_info.push_back(client_handler(clients_lines));
            clients_lines.clear();
        }else{
            clients_lines.push_back(lines);
        }
    }
    client_info.push_back(client_handler(clients_lines));
    file.close();
    cout<< "im working";
    return client_info;
}
//it will automate de clients_question job
vector<string> clientQuestionHandler(vector<string> vec){
    string line;
    vector<string> new_client;
    cout <<"::::::::::"<<endl;
    cin.ignore();
    for (size_t i = 0; i< vec.size(); i++){
        cout<< vec.at(i);
        getline(cin,line);
        new_client.push_back(line);
    }
    cout <<"::::::::::"<<endl;
    return new_client;
}
//creates a new vector<string> with the data needed to create my new client
vector<string> clients_questions(){
    string line;
    vector<string> nClient_questions = {"Client name: ","NIF number: ","Nº family members: ","Address: ","Package list: "};
    cout << endl;
    vector<string> new_client = clientQuestionHandler(nClient_questions);
    return new_client;
}

//Add new client
vector<Cliente> add_client(vector<Cliente> &vec){
    vector<string> new_client = clients_questions();
    Cliente aux = client_handler(new_client);
    vec.push_back(aux);
    return vec;
}
//remove a client (remove all data of that client)
void remove_client(vector<Cliente> &vec){
    string nif;
    cout <<"What's the nif of the client you want to remove?"<<endl;
    cin >> nif;
    for(size_t i = 0;i<vec.size(); i++){
        if(vec.at(i).nif == nif){
            auto it = vec.begin() +i;
            rotate(it, it+1,vec.end());
            cout <<"The client with the NIF: " << vec.back().nif << " it's being deleted! " << endl;
            vec.pop_back();
        }
    }
}
//Vector of Integers with the ID of the packages that a client have bought, the idea here is to be able to modify each element of this vector
void clients_packs(string line, vector<int> &aux){
    line = regex_replace(line,regex(";")," ");
    istringstream test(line);
    int i;
    while(test >> i){
        aux.push_back(i);
    }
}
//update/change the information of a client;
void update_client(vector<Cliente> &vec){
    print_all_clients(vec);
    int op;
    string line;
    string nif;
    cout <<"What's the nif of the client you want to update? "<<endl;
    cin >> nif;
    cin.ignore();
    vector<string> menu = {"Name","NIF","Family Number","Address","Package"};
    for(size_t i = 0; i < vec.size(); i++){
        if(vec.at(i).nif == nif){
            op = readOptions(menu);
                if(op == 1){
                    cout << "New Name: ";
                    cin.ignore();
                    getline(cin, line);
                    vec.at(i).nome = line;
                }
                if(op == 2){
                    cout << "New NIF: ";
                    cin.ignore();
                    getline(cin, line);
                    vec.at(i).nif = line;
                }
                if(op == 3){
                    cout << "New family number: ";
                    cin.ignore();
                    getline(cin, line);
                    istringstream transform(line);
                    transform >> vec.at(i).number_agregado;
                }
                if(op==4){
                    cout << "New address: ";
                    cin.ignore();
                    getline(cin, line);
                    vec.at(i).morada = address_handler(line);
                }
                if(op==5){
                    cout << "New package: ";
                    cin.ignore();
                    getline(cin, line);
                    vec.at(i).pacotes = line;  
                }       
        }
    }    
}
//print a specifi client
void printClient(vector<Cliente> &vec){
    cout << ":::::Please provide us with the client Name or NIF:::::";
    cout << "Wich information suits you?  ";
    vector<string> menu = {"Name","NIF"};
    int op = readOptions(menu);
    string line;
        if(op == 1){
            cout << "Whats the name of the client?"<<endl;
            cin.ignore();
            getline(cin, line);
            for(size_t i = 0; i< vec.size(); i++){
                if(line == vec.at(i).nome){
                    cout<<"::::::::::"<<endl;
                    cout<< "Name: "<< vec.at(i).nome<<endl;
                    cout <<"NIF: "<<vec.at(i).nif<<endl;
                    cout << "Family members: "<< vec.at(i).number_agregado<< endl;
                    cout << "----Address--- \n" << return_addres(vec.at(i).morada);
                    cout << "Packages: "<< vec.at(i).pacotes<< endl;
                }
            }
        }
        if(op == 2){
            cin.ignore();
            cout << "Whats the NIF of the client?"<<endl;
            getline(cin, line);
            for(size_t i = 0; i< vec.size(); i++){
                if(line == vec.at(i).nif){
                    cout<<"::::::::::"<<endl;
                    cout<< "Name: "<< vec.at(i).nome<<endl;
                    cout <<"NIF: "<<vec.at(i).nif<<endl;
                    cout << "Family members: "<< vec.at(i).number_agregado<< endl;
                    cout << "----Address--- \n" << return_addres(vec.at(i).morada);
                    cout << "Packages: "<< vec.at(i).pacotes<< endl;
                }
            }
        } 
}
//Print all my clients.
void print_all_clients(vector<Cliente> &vec){
    cout << ":::::The current clients in our database are:::::";
    for(size_t i = 0; i < vec.size(); i++){
        cout<<"::::::::::"<<endl;
        cout<< "Name: "<< vec.at(i).nome<<endl;
        cout <<"NIF: "<<vec.at(i).nif<<endl;
        cout << "Family members: "<< vec.at(i).number_agregado<< endl;
        cout << "----Address--- \n" << return_addres(vec.at(i).morada);
        cout << "Packages: "<< vec.at(i).pacotes<< endl;
    }
}
void makeCopy(string filename){
    ifstream ifile;
    string line;
    vector<string> file;
    tokenize(filename, '.', file);

    ifile.open(filename);
    string outname = file.at(0) +"_copy.txt";
    ofstream ofile;
    ofile.open(outname);
    while(getline(ifile,line)){
        ofile << line<<endl;
    }
    //cout << "Ponto na posição : " << pos;
    ifile.close();
    ofile.close();
}
void writeClients(string file_name, vector<Cliente> &vec){
    makeCopy(file_name);
    cout<< "A copy of the previous file have been made in case of data lost!";
    ofstream file;
    file.open(file_name);
    if(file.is_open()){
        for (size_t i = 0;i<vec.size(); i++){
            file << vec.at(i).nome<<endl;
            file << vec.at(i).nif<<endl;
            file << vec.at(i).number_agregado<< endl;
            file << vec.at(i).morada.rua_nome << " / " << vec.at(i).morada.porta_number<<" / " << vec.at(i).morada.andar_number << " / " << vec.at(i).morada.zip_code << " / " << vec.at(i).morada.localidade << endl;
            if (i< vec.size() -1){
                file <<"::::::::::"<<endl;
            } 
        }
    }
    file.close();
}
// ------------------------------------------------------ Packs Functions -------------------------------------------------------

//function responsible to understand wich components of the file is a Travel Package.
TravelPack packs_handler(vector<string> pack_vec){
    TravelPack services;
    istringstream id_converter(pack_vec.at(0));
    id_converter >> services.id;
    services.local = pack_vec.at(1);
    services.start_date = date_handler(pack_vec.at(2));
    services.end_date = date_handler(pack_vec.at(3));
    istringstream price_converter(pack_vec.at(4));
    price_converter >> services.price;
    istringstream start_places_converter(pack_vec.at(5));
    start_places_converter >> services.start_places;
    istringstream sold_places_converter(pack_vec.at(6));
    sold_places_converter >> services.sold_places;
    return services;
}

//function that creates a vector containing all the multiple Travel Packages provided by the agency.
vector<TravelPack> packs_data(string pack_file){
    vector<TravelPack> data_of_pack;
    ifstream data;
    string lines;
    vector<string> pack_temp;
    data.open(pack_file);
    getline(data,lines);// Eliminates the first line IDK what to do with it yet.
    while (getline(data, lines,'\n')){
        if (lines == "::::::::::"){
            data_of_pack.push_back(packs_handler(pack_temp));
            pack_temp.clear();
        }
        else{
            pack_temp.push_back(lines);
        }
    }
    data_of_pack.push_back(packs_handler(pack_temp));
    //cout << data_of_pack.at(0).start_date.ano << endl; // test to verify is i'm gettin the right values to my vector of Travel Packs
    data.close();
    cout << "Ive done it sucessfully!"<<endl;
    return data_of_pack;
}

//get's the ID of the last pack to be added to the packs file
int lastID(vector<TravelPack> &vec){
    int id= vec.back().id;
    if(id < 0 ){
        id *=-1;
        id ++;
    }else
    {
        id ++;
    }

    return id;
}
/*
vector<string> packQuestionHandler(vector<string> vec){
    string line;
    vector<string> new_pack;
    cout<<"::::::::::::::"<<endl;
    cin.ignore();
    for(size_t i = 0; i<vec.size(); i++){
        cout << vec[i];
        getline(cin,line);
        new_pack.push_back(line);
    }
    cout <<":::::::::::::";
    return new_pack;
}
*/

//Automates the input of information of new packages IDK why i had to use this old prototype, because i was getting an out_of_range error.
vector<string> packs_questions(vector<TravelPack> &vec){
    vector<string> new_pack;
    string line;
    int id = lastID(vec);
    new_pack.push_back(to_string(id));

    for(int i = 0; i < 6; i++){
        if(i == 0){
                cout << "Local: ";
                cin.ignore();
                getline(cin, line);
                new_pack.push_back(line);
        }
        if(i == 1){
                cout << "Start date: ";
                getline(cin, line);
                new_pack.push_back(line);
        }
        if(i==2){
                cout <<"End date: ";
                getline(cin, line);
                new_pack.push_back(line);
        }
        if(i == 3){
                cout<<"Price per person: ";
                getline(cin, line);
                new_pack.push_back(line);
        }
        if(i == 4){
                cout << "Max places: ";
                getline(cin, line);
                new_pack.push_back(line);
        }
        if(i==5){
                cout << "Sold places: ";
                getline(cin, line);
                new_pack.push_back(line);
        }
        
    }
    return new_pack;
}
/*This was a better version that in the end i got a out_of_range error and didn't have enought time to fix it
vector<string> packs_questions(vector<TravelPack> &vec){
    vector<string> nPacks_questions = {"Location: ","Start Date: ","End Date: ","Price per person: ","Max places: ", "Sold Places: "};
    cout<<endl;
    vector<string> new_pack;
    int id = lastID(vec);
    new_pack.push_back(to_string(id));
    new_pack=packQuestionHandler(nPacks_questions);
    return new_pack;
}
*/
//Add new packages to the Travel Package file.
void add_packs(vector<TravelPack> &vec){ 
    vector<string> new_pack = packs_questions(vec);  
    TravelPack test = packs_handler(new_pack);
    vec.push_back(test);
    //return vec;
}

//print all the content of my vector containing my packages
void print_all_packs(vector<TravelPack> &vec){
    vector<TravelPack>::iterator it;
    it = vec.begin();
    int i =0;
    for(auto it = vec.begin(); it !=vec.end() ; it ++){
        cout << "::::::::::::::::::"<<endl;
        cout << "Unique id: "<< vec.at(i).id <<"\nLocal: "<< vec.at(i).local<< "\nDate of start: " << return_date(vec.at(i).start_date)<< "\nDate of end: " << return_date(vec.at(i).end_date)
        << "\nPrice per person: " << vec.at(i).price <<"\nAmmount of places: "<< vec.at(i).start_places << "\nSold places: " << vec.at(i).sold_places <<endl;               
        cout << ":::::::::::::::::::::::::::::::";
        i++;
    }
}

//Function to visualize packs data within a specific destiny
void printDestinyPack(vector<TravelPack> &vec){
    string destiny;
    cout <<"What's the destiny you would like to access?\n"<<endl;
    cin >> destiny;
    int cont;
    for(size_t i = 0; i<vec.size();i++){
        string vec_dest = vec.at(i).local;
        vector<string> dest_vec;
        tokenize(vec_dest,' ',dest_vec);
        if(destiny == dest_vec.at(0)){
            cout<<endl;
            cout << "Unique id: "<< vec.at(i).id <<"\nLocal: "<< vec.at(i).local<< "\nDate of start: " << return_date(vec.at(i).start_date)<< "\nDate of end: " << return_date(vec.at(i).end_date)
            << "\nPrice per person: " << vec.at(i).price <<"\nAmmount of places: "<< vec.at(i).start_places << "\nSold places: " << vec.at(i).sold_places <<endl;               
            cont++;
            if(cont >1 && i<(vec.size()-1)){
                cout << ":::::::::::::::::::::::::::::::";
            }
        }
    }
}

//Visualize information of a pack between dates
void printFromDates(vector<TravelPack> &vec){
    string start_date;
    string end_date;
    Date startDate;
    Date endDate;
    cin.clear();
    cin.ignore();
    cout <<"What is the start date? \n*Input exemple '2019/05/21'"<<endl;
    getline(cin,start_date);
    startDate = date_handler(start_date);
    cout <<"What is the end date? \n*Input exemple '2019/05/26'"<<endl;
    cin.ignore();
    getline(cin,end_date);
    endDate = date_handler(end_date);
    cout<<endl;
    for(size_t i = 0; i<vec.size();i++){
        if(((vec.at(i).start_date.mes >= startDate.mes) && (vec.at(i).end_date.mes <= endDate.mes)) && ((vec.at(i).start_date.dia >= startDate.dia) && (vec.at(i).end_date.dia <= endDate.dia))){
                cout << "Unique id: "<< vec.at(i).id <<"\nLocal: "<< vec.at(i).local<< "\nDate of start: " << return_date(vec.at(i).start_date)<< "\nDate of end: " << return_date(vec.at(i).end_date)
                << "\nPrice per person: " << vec.at(i).price <<"\nAmmount of places: "<< vec.at(i).start_places << "\nSold places: " << vec.at(i).sold_places <<endl;  
                cout << "::::::::::"<<endl;
        }
    }
}

//Visualize information of a pack within a destiny and between dates
void printDestinyAndDates(vector<TravelPack> &vec){
    string destiny;
    cout <<"What's the destiny you would like to access?\n"<<endl;
    cin >> destiny;
    int cont;
    string start_date;
    string end_date;
    Date startDate;
    Date endDate;
    cin.clear();
    cin.ignore();
    cout <<"What is the start date? \n*Input exemple '2019/05/21'"<<endl;
    getline(cin,start_date);
    startDate = date_handler(start_date);
    cout <<"What is the end date? \n*Input exemple '2019/05/26'"<<endl;
    cin.ignore();
    getline(cin,end_date);
    endDate = date_handler(end_date);
    cout<<endl;
    for(size_t i = 0; i<vec.size();i++){
        string vec_dest = vec.at(i).local;
        vector<string> dest_vec;
        tokenize(vec_dest,' ',dest_vec);
        if(destiny == dest_vec.at(0) && (((vec.at(i).start_date.mes >= startDate.mes) && (vec.at(i).end_date.mes <= endDate.mes)) && ((vec.at(i).start_date.dia >= startDate.dia) && (vec.at(i).end_date.dia <= endDate.dia)))){
            cout<<endl;
            cout << "Unique id: "<< vec.at(i).id <<"\nLocal: "<< vec.at(i).local<< "\nDate of start: " << return_date(vec.at(i).start_date)<< "\nDate of end: " << return_date(vec.at(i).end_date)
            << "\nPrice per person: " << vec.at(i).price <<"\nAmmount of places: "<< vec.at(i).start_places << "\nSold places: " << vec.at(i).sold_places <<endl;               
            cont++;
            if(cont >1 && i<(vec.size()-1)){
                cout << ":::::::::::::::::::::::::::::::";
            }
        }
    }
        
}

//print a certain package sold to a client
void printToClient(vector<TravelPack> &vec, vector<Cliente> &client){
    string clientNif;
    cin.ignore();
    cout <<"What's the nif of the client you want to verify?"<<endl;
    getline(cin, clientNif);
    vector<int> clientPacks;
    for(size_t i = 0; i<client.size(); i++){
        if(client.at(i).nif == clientNif){
            clients_packs(client.at(i).pacotes, clientPacks);
            for(size_t j = 0; j < vec.size(); j++){
                if(find(clientPacks.begin(), clientPacks.end(), vec.at(j).id)  != clientPacks.end()){
                    cout << "\nClient: " << client.at(i).nome <<endl;
                    cout << "Has the packages:"<<endl;
                    cout << "Unique id: "<< vec.at(j).id <<"\nLocal: "<< vec.at(j).local<< "\nDate of start: " << return_date(vec.at(j).start_date)<< "\nDate of end: " << return_date(vec.at(j).end_date)
                    << "\nPrice per person: " << vec.at(j).price <<"\nAmmount of places: "<< vec.at(j).start_places << "\nSold places: " << vec.at(j).sold_places <<endl;               
                    cout<<":::::::::::::"<<endl;
                }
            }
        }
    }
}

//Print packages sold to all clients
void printPackageAllClients(vector<TravelPack> &packs, vector<Cliente> &client){
    vector<int> clientPacks;
    for(size_t i = 0; i<client.size(); i++){
        clients_packs(client.at(i).pacotes, clientPacks);
            for(size_t j = 0; j < packs.size(); j++){
                if(find(clientPacks.begin(), clientPacks.end(), packs.at(j).id)  != clientPacks.end()){
                    cout << "\nClient: " << client.at(i).nome <<endl;
                    cout << "Has the packages:"<<endl;
                    cout << "Unique id: "<< packs.at(j).id <<"\nLocal: "<< packs.at(j).local<< "\nDate of start: " << return_date(packs.at(j).start_date)<< "\nDate of end: " << return_date(packs.at(j).end_date)
                    << "\nPrice per person: " << packs.at(j).price <<"\nAmmount of places: "<< packs.at(j).start_places << "\nSold places: " << packs.at(j).sold_places <<endl;               
                    cout<<":::::::::::::"<<endl;
                }
            }
    }
}

//Attempt to create a function that removes a current Package provided by the travel agency.
void remove_packs(vector<TravelPack> &vec){
    int id;
    cout << "What's the ID of the package you would like to remove?"<<endl;
    cin >> id;
    for(size_t i = 0 ; i<vec.size();i++){
        if(vec.at(i).id == id){
            auto it = vec.begin() + i;
            rotate(it, it+1, vec.end());
            cout << "The Package of id[" << vec.back().id << "] it's being deleted!" << endl;
            vec.pop_back();
        }
    }
}

//Update/Change the information of a pack;
void update_packs(vector<TravelPack> &vec){
    vector<TravelPack>::iterator it;
    it = vec.begin();
    int update_id;
    cout << "What's the ID of the package you would like to update?"<<endl;
    cin >> update_id;
    int i = 0;
    int op;
   
    string line;
    for(auto it = vec.begin(); it !=vec.end() ; it ++){
        if(vec.at(i).id == update_id){
            cout <<"The id[" <<  vec.at(i).id << "] have been found"<<endl;
            cout << "proceeding to update into my package "<<endl;
            cout<< "::::::::::::::::::::"<<endl;
            cout << "options: "<<endl;
            cout << "1 - Local \n2 - start date \n3 - End date \n4 - Price per person \n5 - Ammount of places \n6 - Sold places"<< endl; 
            cin >> op;

            if(op == 1){
                cout << "New data?: "<<endl;
                cin.ignore();
                getline(cin, line);
                vec.at(i).local = line;
            }
            if(op == 2){
                cout << "New data?: "<<endl;
                cin.ignore();
                getline(cin, line);
                vec.at(i).start_date = date_handler(line);
            }
            if(op == 3){
                cout << "New data?: "<<endl;
                cin.ignore();
                getline(cin, line);
                vec.at(i).end_date = date_handler(line);
            }
            if(op == 4){
                cout << "New data?: "<<endl;
                cin.ignore();
                getline(cin, line);
                istringstream price_converter(line);
                price_converter >> vec.at(i).price;
            }
            if(op == 5){
                cout << "New data?: "<<endl;
                cin.ignore();
                getline(cin, line);
                istringstream start_place_converter(line);
                start_place_converter >> vec.at(i).start_places;
            }
            if(op == 6){
                cout << "New data?: "<<endl;
                cin.ignore();
                getline(cin, line);
                istringstream sold_places_converter(line);
                sold_places_converter >> vec.at(i).sold_places;
            }
        }
        i++;
    }

}

//prototipe of the function that writes the vector of Travel pack into a file
void writePacks(string file_name, vector<TravelPack> &vec){
    makeCopy(file_name);
    ofstream file;
    file.open(file_name);
    file << vec.back().id<<endl;
    if(file.is_open()){
        for (size_t i = 0;i<vec.size(); i++){
            file<<endl;
            file << vec.at(i).id <<endl;
            file << vec.at(i).local<< endl;
            file << return_date(vec.at(i).start_date)<<endl;
            file << return_date(vec.at(i).end_date)<<endl;
            file << vec.at(i).price << endl;
            file << vec.at(i).start_places << endl;
            file << vec.at(i).sold_places << endl;               
            if(i<vec.size() -1){
                file <<"::::::::::";
            }
        }
    }
    file.close();
}

//Manage to sell a package to a certain client
void sellToClient(vector<TravelPack> &packs , vector<Cliente> &client){
    string clientNif;
    int id;
    vector<int> clientPacks;
    cout <<"Type the NIF of the client you would like to sel the package"<<endl;
    cin.ignore();
    getline(cin, clientNif);
    cout<<"Type the ID of the package you would like to sell to the client"<<endl;
    cin >> id;
    for(size_t i = 0; i<client.size(); i++){
        if(client.at(i).nif == clientNif){
            clients_packs(client.at(i).pacotes, clientPacks);
            if(find(clientPacks.begin(), clientPacks.end(), id)  != clientPacks.end()){
                cout<<"Client already have that package! "<<endl;
            }
            else{
                for(size_t j = 0 ; j < packs.size(); j++){
                    if(packs.at(j).id == id){
                        //This chunk of the code, before the next if, adds 1 to the sold places and add to the client vector the new id sold to that client
                        istringstream sold(packs.at(j).sold_places);
                        int addi;
                        sold >> addi;
                        addi +=1;
                        packs.at(j).sold_places = to_string(addi);
                        clientPacks.push_back(id);
                        //This bit transform the ID into a negative number if sold places = to start places
                        if(packs.at(j).sold_places == packs.at(j).start_places){
                            packs.at(j).id *= -1;
                        }
                        //this bit of the code will puth the new packs at the client packs parameter
                        stringstream newPacks;
                        copy( clientPacks.begin(), clientPacks.end(), ostream_iterator<int>(newPacks, ";"));
                        string substitute = newPacks.str();
                        substitute = substitute.substr(0, substitute.length()-1);
                        client.at(i).pacotes = substitute;
                        cout<<"\nSold\n";
                    }
                    if(packs.at(j).id == (id* -1)){
                        cout <<"\n*Warning!*\n*Sorry! Travel Package not available, reached it's maximum capacity!"<<endl;
                    }
                }
            }
        }
    }
}

//Calculates and visualize the number and the total value of sold packages
void totalPackageSold(vector<TravelPack> &packs, vector<Cliente> &client){
    int cont=0, value = 0;
    vector<int> clientPacks;
    for(size_t i=0; i<client.size(); i++){
        clients_packs(client.at(i).pacotes, clientPacks);
        for(size_t j = 0; j<packs.size(); j++){
            if(find(clientPacks.begin(), clientPacks.end(), packs.at(j).id) !=clientPacks.end()){
                cout <<"Package ID: " <<packs.at(j).id<<endl;
                cout << "Client owner:" <<client.at(i).nome;
                cont++;
                istringstream prices(packs.at(j).price);
                int price;
                prices >> price;
                value += price;
            }
        }
    }
    cout<<"\nThe ammount of sold packages is: "<<cont<<endl;
    cout<<"The total value of those packages is: " << value<<endl;
}
//------------------------------------------------------------ MENU WINDOWS -------------- THIS IS TROUBLE --------------
//"Menu for agency"
int agency_operations(Agency &agency){
    //simple user interface
    cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"<< endl;
    cout << "                          Welcome to the agency " << agency.nome << endl;
    cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"<< endl;
    cout << endl;
    int op;
    cout << "What would you like to manage?: " << endl;
    vector<string> menu = {"Clients","Package"};
    op = readOptions(menu);
    cout << endl;
    //attempt to fill the  services & clients structs with data from the files.
    cout << endl;
    return op;
} 

//Menu for clients, same thing ... headache if i have problems to fix, wich ofc will happen.
void clients_operations(Agency &agency, vector<Cliente> &clients){
        ifstream clientsFile;
        clientsFile.open(agency.clientes);
        if(clientsFile.good()){
            cout << "Clients database up to date. file " << agency.clientes << " successfully readed from the current directory" << endl;
        }else{
            cout << "Can't open the clients database file" << agency.clientes << "it's not on the current directory " << endl;
        }
 
        
        cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"<<endl;
        cout << "                             Clients                                  " <<endl;
        cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"<<endl;
        cout << endl;
        vector<string> menu = {"Create new Client","Remove existing Client","Update Client Information","Print a specif client","Print agency clients"};
        int op = readOptions(menu);

        if(op == 1){
            add_client(clients);
            while (op == 1){
                cout << "Do you want to add another client? \n1 - Yes \n0 - No \n"<<endl;
                op = readInteger();
                if(op == 0){
                    print_all_clients(clients);
                }else{
                    add_client(clients);
                }
            }
        }
        
        if(op == 2){
            remove_client(clients);
            while (op > 0){
                cout << "Do you want to remove another client? \n1 - Yes \n0 - No \n"<<endl;
                op = readInteger();
                if(op == 0){
                    print_all_clients(clients);
                }else{
                    remove_client(clients);
                }
            }
        }
        if (op == 3){
            update_client(clients);
            while (op > 0){
                cout << "Do you want to update another client? \n1 - Yes \n0 - No \n"<<endl;
                op = readInteger();
                if(op == 0){
                    print_all_clients(clients);
                }else{
                    update_client(clients);
                }
            }
        }
        if (op == 4){
            printClient(clients);
            while(op >0){
                cout << "Do you want to see the information of other client? \n1 - Yes \n0 - No \n"<<endl;
                op = readInteger();
                if(op == 1){
                    printClient(clients);
                }
            }
        }
        if (op == 5){
            print_all_clients(clients);
        }
        clientsFile.close();
}

//Menu for the packs operations this will give me a headache aswell.
void packs_operation(Agency &agency, vector<TravelPack> &packs, vector<Cliente> &clients){
        ifstream packsFile;
        packsFile.open(agency.pacotes);
        cout << "Opening file: " << agency.pacotes << endl;
        cout << endl;
        if(packsFile.good()) {
            cout << "Services database up to date. file " << agency.pacotes << " successfully readed from the current directory"<< endl;
        }else {
        cout << "Can't open the services database file" << agency.pacotes << "it's not on the current directory " << endl;
        }
        cout << endl;
        //Uses the function that creates my vector of Travel Packs to actually make a vector filled with information 
        cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"<<endl;
        cout << "                             Packages                                 " <<endl;
        cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"<<endl;
        cout << endl;
        
        vector<string> menu = {"Create new Package","Remove existing Package","Update Package Information","Visualize Travel Packs", "Sell a package to a client","Nº of sold Packages and total value"};
        int op = readOptions(menu);
        //It means the agency manager wants to add a new package.
        if(op == 1){
            add_packs(packs);
            while(op > 0){
                cout <<"Do you want to add another travel pack? \n1 - Yes \n0 - No \n"<<endl;
                op = readInteger();
                if(op == 0){
                    print_all_packs(packs);
                }else{
                    add_packs(packs);
                }
            }
        }
        //It means the agency manager wants to remove one package.
        if(op == 2){
            remove_packs(packs);
            while(op > 0){
                cout<<"Do you want to remove another Travel Pack? \n1 - Yes \n0 - No\n"<<endl;
                op = readInteger();
                if(op == 0){
                    print_all_packs(packs);
                }else{
                    remove_packs(packs);
                }
            }  
        }
        //Agency Manager will update the data of an existing Package
        if(op == 3){
            update_packs(packs);
            while(op > 0){
                cout << "Do you want to update another pack? \n0 - No\n1 - Yes \nAnswer: ";
                op = readInteger();
                if(op == 0){
                    print_all_packs(packs);
                }else{
                    update_packs(packs);
                }
            }
        }
        //All kinds of package visualization
        if(op == 4){
            cout << "How would you like to search for Travel Packs?"<<endl;
            vector<string> packsVisualizationOptions = {"All Travel Packs","Related to a destiny","Between dates","Related to a destiny and between dates","Sold to a client", "Sold to all clients"};
            op = readOptions(packsVisualizationOptions);
            if(op==1){
                print_all_packs(packs);
            }
            if(op==2){
                printDestinyPack(packs);
                while(op >0){
                    cout<<"\nWould you like to verify the packs of another destiny? \n1 - Yes \n0 - No"<<endl;
                    op = readInteger();
                    if(op == 1){
                        printDestinyPack(packs);
                    }
                }
            }
            if(op==3){
                printFromDates(packs);
                while(op>0){
                    cout<<"\nWould you like to verify the packs from another date? \n1 - Yes \n0 - No"<<endl;
                    cin >> op;
                    if(op == 1){
                        printFromDates(packs);
                    }
                }
            }
            if(op == 4){
                printDestinyAndDates(packs);
                while(op>0){
                    cout<<"\nWould you like to verify the packs from another destiny & date? \n1 - Yes \n0 - No"<<endl;
                    cin >> op;
                    if(op == 1){
                        printDestinyAndDates(packs);
                    }
                }
            }
            if(op == 5){
                printToClient(packs,clients);
                while(op>0){
                    cout<<"\nWould you like to verify the packs sold to another client? \n1 - Yes \n0 - No"<<endl;
                    cin >> op;
                    if(op == 1){
                        printDestinyAndDates(packs);
                    }
                }
            }
            if(op == 6){
                printPackageAllClients(packs, clients);
                while(op>0){
                    cout<<"\nWould you like to verify the packs sold to the Clients? \n1 - Yes \n0 - No"<<endl;
                    cin >> op;
                    if(op > 0){
                        printPackageAllClients(packs, clients);
                    }
                }
            }
        }
        //Sell a package to a client
        if(op == 5){
            sellToClient(packs, clients);
            while(op > 0){
                cout << "Do you want to sell another pack? \n0 - No\n1 - Yes \nAnswer: ";
                op = readInteger();
                if(op > 0){
                    sellToClient(packs, clients);
                }
            }
        }
        //Total Value and number of sold packages
        if(op == 6){
            totalPackageSold(packs, clients);
            while(op>0){
                cout<<"\nWould you like to verify again? \n1 - Yes \n0 - No"<<endl;
                cin >> op;
                if(op > 0){
                    totalPackageSold(packs, clients);
                }
            }
        }
        packsFile.close();
}
//Main menu
void overalMenu(Agency &agency){
    cout << "I am starting overal Menu \n"<<endl;
    int op;
    op = agency_operations(agency);
    vector<Cliente> clients = client_data(agency.clientes);
    vector<TravelPack> packages = packs_data(agency.pacotes);
    cout << "Ive created the vectors";
    while(op !=0){
    if(op == 1)
    {
        clients_operations(agency,clients);
        cout << "\nWould you like to keep managing the clients? \n1-Yes \n0-No"<<endl;
        cin >> op;
        while(op !=0){
            clients_operations(agency,clients);
            cout << "\nWould you like to keep managing the clients? \n1-Yes \n0-No"<<endl;
            cin >> op;
        }
        
    }
    if(op == 2){
        packs_operation(agency,packages,clients);
        cout << "\nWould you like to keep managing the Packages? \n1-Yes \n0-No"<<endl;
        cin >> op;
        while(op !=0){
            packs_operation(agency,packages,clients);
            cout << "\nWould you like to keep managing the Packages? \n1-Yes \n0-No"<<endl;
            cin >> op;
        }
    }
        cout << "Are you sure you want to quit? \nYes - 0 \nNo - 1"<<endl;
        cin >> op;
        if(op == 1){
            op = agency_operations(agency);
        }
        writeClients(agency.clientes, clients);
        writePacks(agency.pacotes, packages);  
    }
    cout << "\nExit sucefull! "<<endl;   
}
