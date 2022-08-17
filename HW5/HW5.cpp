#include <iostream>
#include <fstream>
#include <string.h>
#include <stdexcept>
#define maxints 100
#define INF 10000 // infinite
using namespace std;

// function to print the shortest path
void path(int graph[maxints][maxints], int relation[], int pr[], int v)
{
    if (pr[v] == -1)
        return;
    // recursive
    path(graph, relation, pr, pr[v]);
    cout << relation[pr[v]] << "->";
}

// function to print the final results
void printSolution(int graph[maxints][maxints], int relation[], int dist[], int pr[], int end)
{

    // print the constructed distance array
    cout << "The shortest distance is: " << dist[end] << endl;
    // output the path
    cout << "The shortest path is: " << endl;
    path(graph, relation, pr, end);
    cout << relation[end];
    cout << endl;
}

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int graph[maxints][maxints], int V, int relation[], int start, int end)
{
    int dist[V];          // dist[i] will hold the shortest
    int visit[V];         // whether vertices is visited
    int *pr = new int[V]; // predecessor vertices
    int x;                // shortest flag

    // Initialize all distances as INF and visit as false
    for (int i = 0; i < V; i++)
    {
        visit[i] = 0;
        dist[i] = graph[start][i];
        if (dist[i] < INF)
            pr[i] = start;
        // there is no way
        else
            pr[i] = -1;
    }

    // Distance of source vertex from itself is always 0
    dist[start] = 0;
    visit[start] = 1;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++)
    {
        // Pick the minimum distance vertex
        int min = INF;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++)

            // Update dist[v] only if is not in visit
            if ((!visit[v]) && (dist[v] < min))
            {
                // update the shortest path
                min = dist[v];
                x = v;
            }
        visit[x] = 1; // mark
        for (int i = 0; i < V; i++)
        {
            // update shortest path
            if ((!visit[i]) && (dist[i] > dist[x] + graph[x][i]))
            {
                dist[i] = dist[x] + graph[x][i];
                pr[i] = x;
            }
        }
    }
    // utils
    cout << "From building " << relation[start]
         << " to building " << relation[end] << endl;
    // print
    printSolution(graph, relation, dist, pr, end);
}

// functions to find the mapping index of a building
int mapping(int aim, int relation[])
{
    int index;
    for (int i = 0; i < 21; i++)
    {
        if (relation[i] == aim)
        {
            // return mapping index
            index = i;
        }
    }
    return index; // placehold
}

// create the mapping from buildings to index
void createMapping(int temp[], int relation[], int V)
{
    int max = V * 2 - 1;
    int i, j;
    int flag = 1; // index in relation mapping array
    // bubble sort
    for (i = 0; i < max; i++)
    {
        for (j = i + 1; j < V * 2; j++)
        {
            if (temp[j] < temp[i])
            {
                // swap
                int tmp = temp[i];
                temp[i] = temp[j];
                temp[j] = tmp;
            }
        }
    }
    // the first vertice
    relation[0] = temp[0];
    // start loop
    for (i = 1; i < V * 2; i++)
    {
        // find a different vertice
        if (temp[i - 1] != temp[i])
        {
            // add to mapping array
            relation[flag] = temp[i];
            flag += 1;
        }
    }
}
int main()
{
    ifstream inf;
    int count = 0;
    int x;
    int list[maxints];
    int start, end;              // start and end building
    int graph[maxints][maxints]; // edge graoh
    int flag;                    // flag
    memset(graph, INF, sizeof(graph));
    inf.open("ints.txt");
    if (inf.fail())
    {
        cerr << "Error: Could not open input file\n";
        exit(1);
    } // activate the exception handling of inf stream
    inf.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    while (count < maxints)
    {
        // keep reading until reading maxints or
        // until a reading failure is caught.
        try
        {
            inf >> x;
        }
        // Check for reading failure due to end of file or
        // due to reading a non‐integer value from the file.
        catch (std::ifstream::failure e)
        {
            break;
        }
        list[count++] = x;
    }
    // for (int i = 0; i < count; i++)
    //  cout << list[i] << endl;
    inf.close(); // Close the file at the end of your program.

    int V = list[0];  // find the number of vertices
    int temp[V * 2];  // temp array
    int relation[21]; // relation mapping array
    flag = 1;
    int i = 0; // another flag
    // find all vertices
    while (flag < count)
    {
        temp[i] = list[flag];
        temp[i + V] = list[flag + 1];
        flag += 3;
        i += 1;
    }
    createMapping(temp, relation, V); // mapping
    flag = 1;
    // create edge graph
    while (flag < count)
    {
        int v1 = mapping(list[flag], relation);
        int v2 = mapping(list[flag + 1], relation);
        // undirect graph
        graph[v1][v2] = list[flag + 2];
        graph[v2][v1] = list[flag + 2];
        flag += 3;
    }

    // building range
    cout << "Buildings are in the range of [";
    for (int i = 0; i < V; i++)
        cout << relation[i] << " ";
    cout << "], please choose" << endl;
    // ask for user inputs
    cout << endl;
    cout << "Input Start Building: ";
    cin >> start;
    cout << "Input Destination Building: ";
    cin >> end;
    // start search
    dijkstra(graph, V, relation, mapping(start, relation), mapping(end, relation));

    return 0;
}