#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
    int num;
    vector<int> storage;
    cin>>num;
    int counter=0;
    while (num!=-1)
        {
           storage.push_back(num);
           counter++;
           cin>>num;
            
        }
    sort(storage.begin(),storage.end());
cout<<storage[counter-2]<<endl;





return 0;
}