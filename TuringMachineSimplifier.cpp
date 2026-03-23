#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std ;



string decimalToBinary(int n) {
    if (n == 0) return "0";
    string binary = "";
    while (n > 0) {
        binary = to_string(n % 2) + binary;
        n /= 2;
    }
    return binary;
}

string simulator(string instruction, int &lastState) {
    if (instruction == "") return "";

    string output;
    string part;
    vector<string> parts;
    vector<string> alphabet = {"0", "1", "_"};

    stringstream ss(instruction);
    while (getline(ss, part, '#')) {
        parts.push_back(part);
    }

    if (parts.size() < 5) return "";

    string qi = parts[0];
    string sn = parts[1];
    string qj = parts[2];
    string sm = parts[3];
    string D  = parts[4];

    // STAY
    if (D == "0") {
        lastState++;
        string inter = decimalToBinary(lastState);

        output += qi + "#" + sn + "#" + inter + "#" + sm + "#00;";

        for (string s : alphabet) {
            output += inter + "#" + s + "#" + qj + "#" + s + "#10;";
        }
    }

    // R2
    else if (D == "01") {
        lastState++;
        string inter = decimalToBinary(lastState);

        output += qi + "#" + sn + "#" + inter + "#" + sm + "#00;";

        for (string s : alphabet) {
            output += inter + "#" + s + "#" + qj + "#" + s + "#00;";
        }
    }

    // L2
    else if (D == "11") {
        lastState++;
        string inter = decimalToBinary(lastState);

        output += qi + "#" + sn + "#" + inter + "#" + sm + "#10;";

        for (string s : alphabet) {
            output += inter + "#" + s + "#" + qj + "#" + s + "#10;";
        }
    }

    // already L or R
    else {
        output += instruction + ";";
    }

    return output;
}


int getMaxState(vector<string> &instructions) {
    int maxState = 0;

    for (string instr : instructions) {
        if (instr == "") continue;

        stringstream ss(instr);
        string part;
        vector<string> parts;

        while (getline(ss, part, '#')) {
            parts.push_back(part);
        }

        if (parts.size() >= 3) {
            int qi = stoi(parts[0], nullptr, 2);
            int qj = stoi(parts[2], nullptr, 2);

            maxState = max(maxState, max(qi, qj));
        }
    }

    return maxState;
}

string mPrime(string machine) {
    vector<string> transitions;
    string part;

    // Split machine instructions
    stringstream ss(machine);
    while (getline(ss, part, ';')) {
        if (part != "")
            transitions.push_back(part);
    }

    // Compute max state
    int lastState = getMaxState(transitions);

    // Generate transformed transitions
    vector<string> newTransitions;
    for (string instr : transitions) {
        string t = simulator(instr, lastState);
        // split simulator output by ';' and add individually
        stringstream ts(t);
        string sub;
        while (getline(ts, sub, ';')) {
            if (sub != "")
                newTransitions.push_back(sub);
        }
    }

    // Sort transitions by state number and symbol
    vector<string> orderSymbols = {"_", "0", "1"};

    sort(newTransitions.begin(), newTransitions.end(), [&](string a, string b) {
        auto getParts = [](string s) {
            vector<string> p;
            string part;
            stringstream ss(s);
            while (getline(ss, part, '#')) p.push_back(part);
            return p;
        };

        vector<string> A = getParts(a);
        vector<string> B = getParts(b);

        // Compare state numbers (decimal)
        int stateA = stoi(A[0], nullptr, 2);
        int stateB = stoi(B[0], nullptr, 2);
        if (stateA != stateB) return stateA < stateB;

        // Compare symbol order (_,0,1)
        int posA = find(orderSymbols.begin(), orderSymbols.end(), A[1]) - orderSymbols.begin();
        int posB = find(orderSymbols.begin(), orderSymbols.end(), B[1]) - orderSymbols.begin();

        return posA < posB;
    });

    // Build final output string
    string output;
    for (string t : newTransitions) {
        output += t + ";";
    }

    return output;
}

int main (){
        string  machine;
       getline(cin, machine);


        cout << mPrime(machine) << endl;

    return 0;
}