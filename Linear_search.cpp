#include <iostream>
using namespace std;
int linear_search(int a[],int n,int x)
{
    for(int i=0;i<n;i++)
    {
        if(a[i]==x)
        return(i);
    }
    return(-1);
}
int main()
{
    int n;
    int a[10],x;
    cout<<"how many element=";

    cin>>n;
    cout<<"enter "<<n <<" elements=";
    for (int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    cout<<"Enter the element to be search=";
    cin>>x;
    int position=linear_search(a,n,x);
    if(position==-1)cout<<"Element not found";
    else cout<<"element found at position="<<position;
    return 0;
}



/*
PS D:\Samiksha Gunjal> cd "d:\Samiksha Gunjal\" ; if ($?) { g++ linear_search.cpp -o linear_search } ; if ($?) { .\linear_search }
how many element=6
enter 6 elements=10
20
30
40
50
60
Enter the element to be search=40
element found at position=3
*/
