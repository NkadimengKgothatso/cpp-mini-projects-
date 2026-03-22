#include <iostream>
#include <vector>
#include <sstream>
using namespace std;


string decoder(string table, string word) {
    vector<string> encodings;
    string part;
    vector<string>mapping;
    string alph;
    string output;

   
    stringstream ss(table);

    while (getline(ss, part, '|')) {
        encodings.push_back(part);
    }

    for(string part:encodings){
        stringstream ss(part);

        while (getline(ss, alph , '=')) {
        mapping.push_back(alph);
    }
        
    }

    for (int i = 0; i < word.size(); i++) {
        
        for (int j = 0; j < mapping.size(); j += 2) { 
           if (word[i] == mapping[j][0]) {
                output += mapping[j + 1];
               
                break;
            }
        }
       
    }
   
    return output;
}

int main() {
    string table;
    string word;

    
    getline(cin, table);
    getline(cin, word);

    cout<<decoder(table, word)<<endl;

    return 0;
}