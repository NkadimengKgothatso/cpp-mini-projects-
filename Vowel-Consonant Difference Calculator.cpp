#include <iostream>
#include <string>

using namespace std;

int main() {
	string x;
	cin >> x;
	int vowels = 0;
	int consonants = 0;
	for (int i = 0; i < x.length(); ++i){
		
		if (x[i] == 'a' || x[i] == 'e' || x[i] == 'i' || x[i] == 'o' || x[i] == 'u'){
			vowels = vowels + 1;
		}
		else{
			consonants = consonants + 1;
		}		
	}
	int d = vowels - consonants;
	if (d < 0){
		d = -d;
	}
        cout << d << endl;
        return 0;
}
