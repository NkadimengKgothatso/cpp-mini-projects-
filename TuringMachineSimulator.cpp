#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

struct Transition {
    string nextState;
    string writeSymbol;
    string direction;
};

string decoder(string machine){
    string output;

    for (int i = 0; i < machine.length(); i += 3){
        string part = machine.substr(i, 3);

        if (part == "000") output += "0";
        else if (part == "001") output += "1";
        else if (part == "010") output += "_";
        else if (part == "100") output += "#";
        else if (part == "101") output += ";";
    }

    return output;
}





int main() {

    string machine;
    string input;

    getline(cin, machine);
    getline(cin, input);

    string decodedMachine = decoder(machine);

    vector<string> instru;
    string part;
    stringstream ss(decodedMachine);

    while (getline(ss, part, ';')) {
        if (part != "")
            instru.push_back(part);
    }

    map<pair<string, string>, Transition> delta;

    for (string instr : instru) {
        stringstream ss(instr);
        vector<string> parts;
        string p;

        while (getline(ss, p, '#')) {
            parts.push_back(p);
        }

        if (parts.size() < 5) continue;

        string qi = parts[0];
        string sn = parts[1];
        string qj = parts[2];
        string sm = parts[3];
        string D  = parts[4];

        delta[{qi, sn}] = {qj, sm, D};
    }

    vector<string> tape;

    if (input == "_") {
        tape.push_back("_");
    } else {
        for (char c : input) {
            tape.push_back(string(1, c));
        }
    }

    string currentState = "0";
    int head = 0;
    int steps = 0;

    while (steps < 1000000) {

        if (head < 0) {
            tape.insert(tape.begin(), "_");
            head = 0;
        }
        if (head >= tape.size()) {
            tape.push_back("_");
        }

        string currentSymbol = tape[head];

        if (delta.find({currentState, currentSymbol}) == delta.end()) {
            break;
        }

        Transition t = delta[{currentState, currentSymbol}];

        tape[head] = t.writeSymbol;

        if (t.direction == "00") head++;
        else if (t.direction == "10") head--;

        currentState = t.nextState;
        steps++;

        if (currentState == "1" || currentState == "10") break;
    }

    int start = 0;
    while (start < tape.size() && tape[start] == "_" && start != head) {
        start++;
    }

    int end = tape.size() - 1;
    while (end >= 0 && tape[end] == "_" && end != head) {
        end--;
    }

    if (start > end) {
        cout << "#" << currentState << "#_" << endl;
        return 0;
    }

    string left = "";
    string right = "";

    for (int i = start; i <= end; i++) {
        if (i < head) left += tape[i];
        else right += tape[i];
    }

    if (left == "" && head == start && tape[head] == "_") {
        right = "_" + right;
    }

    cout << left << "#" << currentState << "#" << right << endl;

    return 0;
}