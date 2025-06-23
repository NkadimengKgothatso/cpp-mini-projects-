#include <iostream>
using namespace std;

int main()
{
    string word;
    int counter=0;
    int counter1=0;
    int counter2=0;
    cin>>word;
    char c;
    for(int i=0;i<word.length();++i)
    {

        c=char(word[i]);
        if(c>=97&&c<=122)
        {
            counter++;
        }
        else if (c>=65 && c<=90)
        {
            counter1++;
        }
        else 
        {
            counter2++  ;
        }

    }

    if (counter>counter1)
        {
            cout<<"Lower"<<endl;
        }
    else if (counter1>counter)
        {
            cout<<"Upper"<<endl;
        }
    else 
        {
            cout<<"Same"<<endl;
        }

    return 0;
}