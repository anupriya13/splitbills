#include<bits/stdc++.h>
using namespace std;

int N;
vector<string>onlyname;

int getMin(int arr[])
{
    int minInd = 0;
    for (int i=1; i<N; i++)
        if (arr[i] < arr[minInd])
            minInd = i;
    return minInd;
}

int getMax(int arr[])
{
    int maxInd = 0;
    for (int i=1; i<N; i++)
        if (arr[i] > arr[maxInd])
            maxInd = i;
    return maxInd;
}


int minOf2(int x, int y)
{
    return (x<y)? x: y;
}




void topologicalSortUtil(int v, bool visited[],
                                stack<int>& Stack,vector<vector<int>>graph)
{

    visited[v] = true;



    for (auto i = 0; i <N; ++i)
        if (!visited[i] && graph[v][i])
            topologicalSortUtil(i, visited, Stack,graph);


    Stack.push(v);
}

void topologicalSort(vector<vector<int>>graph)
{
    stack<int> Stack;

    bool* visited = new bool[N];
    for (int i = 0; i < N; i++)
        visited[i] = false;


    for (int i = 0; i < N; i++)
        if (visited[i] == false)
            topologicalSortUtil(i, visited, Stack,graph);

    int i = 1;
    while (Stack.empty() == false) {
        cout << i<<". "<< onlyname[Stack.top()] << endl;
        Stack.pop();
        i++;

    }
    cout<<endl;
}

void minCashFlowRec(int amount[],vector<vector<int>>&dependency)
{


    int mxCredit = getMax(amount), mxDebit = getMin(amount);


    if (amount[mxCredit] == 0 && amount[mxDebit] == 0)
        return;


    int min = minOf2(-amount[mxDebit], amount[mxCredit]);
    amount[mxCredit] -= min;
    amount[mxDebit] += min;


    cout << onlyname[mxDebit] << " pays " << min
         << " to " << onlyname[mxCredit] << endl;

    dependency[mxDebit][mxCredit]=min;

    minCashFlowRec(amount,dependency);
}


void minCashFlow(vector<vector<int>>graph)
 {

     int amount[N] = {0};

     for (int p=0; p<N; p++)
        for (int i=0; i<N; i++)
           amount[p] += (graph[i][p] -  graph[p][i]);

    vector<vector<int>>dependency(N,vector<int>(N,0));
    minCashFlowRec(amount,dependency);
         cout<<endl;
     cout<<"Order of person from most dependent (paying to another person) to least dependent (getting from another person)"<<endl;
    topologicalSort(dependency);

 }


int main()
{

    cout<<"Enter the total number of Friends: ";
    cin>>N;


    map<string,pair<int,int>>name;

    cout<<"Enter names of each person: "<<endl;
    for(int i = 0; i < N; i++)
    {
        string temp;
        cout<<"Name of Person "<<i+1<<": ";
        cin>>temp;
        onlyname.push_back(temp);
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        name[temp] = {i,0};
    }
    cout<<endl;

    int q;
    cout<<"Enter number of transactions: ";
    cin>>q;

    int sum = 0;
    vector<vector<int>>graph(N,vector<int>(N,0));

    while(q--)
    {
        int amount;
        string nm;

        cout<<"Payer name: ";
        cin>>nm;
        cout<<"Enter Amount: ";
        cin>>amount;

        int topay = amount/N;
        int index = name[nm].first;
        for(int i = 0; i < N; i++)
        {
            if(i!=index)
            graph[i][index] += topay;
        }
        sum += amount;

        transform(nm.begin(), nm.end(), nm.begin(), ::tolower);
        if(name.find(nm)!=name.end())
        name[nm].second+=amount;

    }
    cout<<endl;
    cout<<"Total money spend: "<<sum<<endl;



     cout<<"Graph formed is"<<endl;
     for(int i = 0; i < N; i++)
     {
         for(int j = 0; j < N; j++)
             cout<<graph[i][j]<<" ";
         cout<<endl;
     }

    cout<<endl;


    minCashFlow(graph);

    return 0;
}
