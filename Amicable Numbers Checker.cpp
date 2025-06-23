#include<iostream>
using namespace std;

string amic(int x,int y)
{
    int sum1=0;
    int sum2=0;
    string c;
    for (int i=0;i<x;i++)
    {
        if (x%i==0)
        {
            sum1=sum1+i;
        }
        else

        {
            continue;
        }
    }
    for (int i=0;i<y;i++)
    {
        if (y%i==0)
        {
            sum2=sum2+i;
        }
        else{
            continue;
        }
    }

    if(sum1==y&&sum2==x)
    {
        c="Amicable";
    }
    else

    {
        c="Not amicable";
    }

return c;
cout <<"blahh"<<endl;

}




int main()
 
{
    int N,x,y;
    cin>>N ;
    string d;
    for (int i =0;i<N;i++)
    {
        cin>>x>>y;
        d=amic(x,y);
        cout<<d<<endl;
    }
    
}