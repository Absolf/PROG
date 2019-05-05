#include "functions.cpp"

int main(){
    //creating the fstream that will be responsible to open the agency file.
    ifstream agencyFile;
    string agency_file_name;
    cout << "Wich agency file would you like to use?\n*WARNING! Don't need to use the extension '.txt'"<<endl;
    cin >> agency_file_name;
    agency_file_name += ".txt"; 
    agencyFile.open(agency_file_name);
    string lines;
    loadingFunc();

    // verify if the file name provided by the user exists and if yes, it have been opened already, otherwhise gives an error message.
    if(agencyFile.good()){
        cout << "                Sucefully opened the file: " << agency_file_name<< endl;
    }else{
        cout << "                Can't open the file: " << agency_file_name << endl;
    }
    // create and fill the vector responsible to get the agency file lines, responsible to allow the opening of the clients and services file.
    vector<string> linesInfo;
    while (getline(agencyFile, lines)){
        linesInfo.push_back(lines);
    }
    Agency agency = agency_handler(linesInfo);

    overalMenu(agency);
    
    agencyFile.close();
    return 0;
    exit(0);   
}

    