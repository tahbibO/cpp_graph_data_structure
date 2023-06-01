#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <string>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
using namespace std;

template <typename T>
class Edge
{
public:
    pair<T, T> e;
    int weight;
    T operator[](int index)
    {
        if (index == 0)
        {
            return get<0>(e);
        }
        else if (index == 1)
        {
            return get<1>(e);
        }
        else
        {
            throw std::out_of_range("Index out of range");
        }
    }
    Edge() {}
    
    Edge(T u, T v)
    {
        e = make_pair(u, v);
        weight = 0;
    }
    Edge(T u, T v, int w)
    {
        e = make_pair(u, v);
        weight = w;
    }
    string toString()
    {
        std::stringstream ss;
        ss << "(" << e.first << "," << e.second << ")";
        return ss.str();
    }
    string hash() const{
        std::stringstream ss;
        if (e.first > e.second) {
            ss << e.first << e.second;
        }else{
            ss << e.second << e.first;
        }
        return ss.str();
    }
    bool operator<(const Edge &e2) const
    {
       return (hash() < e2.hash());
    }
    bool operator>(const Edge &e2) const
    {
       return (hash() > e2.hash());
    }
    bool operator==(const Edge &e2) const
    {
       return (hash() == e2.hash());
    }
};

template <typename T>
class DirectedEdge : public Edge<T>
{
public:
    DirectedEdge(){};
    DirectedEdge(T u, T v)
    {
        e = make_pair(u, v);
        weight = 0;
    }
    DirectedEdge(T u, T v, int w)
    {
        e = make_pair(u, v);
        weight = w;
    }
    string hash() const {
        std::stringstream ss;
        ss << e.first << e.second;
        return ss.str();
    }
    bool operator<(const DirectedEdge &e2) const
    {
       return (hash() < e2.hash());
    }
    bool operator>(const DirectedEdge &e2) const
    {
       return (hash() > e2.hash());
    }
    bool operator==(const DirectedEdge &e2) const
    {
       return (hash() == e2.hash());
    }
};

template <typename T>
class Graph
{
public:
    Graph(set<T>, vector<Edge<T>>);
    Graph();
    bool addEdge(Edge<T>);
    bool addVertex(T);
    bool removeVertex(T);
    bool removeEdge(Edge<T>);
    vector<T> getNeighbours(T);
    vector<T> getVertices();
    vector<Edge<T>> getEdges();
    bool hasVertex(T);
    bool hasEdge(Edge<T>);
    void printGraph();
    int size();

protected:
    map<T, set<T>> adjList;
};

template <typename T>
Graph<T>::Graph(set<T> vertexSet, vector<Edge<T>> edgeSet)
{
    for (T vertex : vertexSet)
    {
        addVertex(vertex);
    }
    for (Edge<T> edge : edgeSet)
    {
        addEdge(edge);
    }
}

template <typename T>
Graph<T>::Graph() {}

template <typename T>
vector<Edge<T>> Graph<T>::getEdges()
{
    vector<Edge<T>> returnList;
    set<Edge<T>> returnSet;
    for (pair<T, set<T>> pair : adjList)
    {
        T u = pair.first;
        for (T v : pair.second)
        {
            returnSet.insert(Edge<T>(u, v));
        }
    }
    for (Edge<T> e : returnSet)
    {
        returnList.push_back(e);
    }
    return returnList;
}

template <typename T>
bool Graph<T>::addEdge(Edge<T> edge)
{


    if (!hasEdge(edge) && hasVertex(edge[0]) && hasVertex(edge[1]))
    {
        adjList[edge[0]].insert(edge[1]);
        adjList[edge[1]].insert(edge[0]);
        return true;
    }
    return false;
}

template <typename T>
bool Graph<T>::addVertex(T vertex)
{
    if (adjList.count(vertex) == 0)
    {
        adjList.insert(make_pair(vertex, set<T>()));
        return true;
    }
    return false;
}

template <typename T>
int Graph<T>::size() { return adjList.size(); }

template <typename T>
vector<T> Graph<T>::getNeighbours(T vertex)
{
    vector<T> returnList;
    for (T neighbour : adjList[vertex])
    {
        returnList.push_back(neighbour);
    }
    return returnList;
}

template <typename T>
vector<T> Graph<T>::getVertices()
{
    vector<T> returnList;
    for (pair<T, set<T>> p : adjList)
    {
        returnList.push_back(p.first);
    }
    return returnList;
}

template <typename T>
bool Graph<T>::hasEdge(Edge<T> edge)
{
    if (adjList.count(edge[0]))
    {
        if (adjList[edge[0]].count(edge[1]))
        {
            return true;
        }
    }
    return false;
}

template <typename T>
bool Graph<T>::hasVertex(T vertex)
{
    if (adjList.count(vertex))
    {
        return true;
    }
    return false;
}

template <typename T>
void Graph<T>::printGraph()
{

    for (pair<T, set<T>> pair : adjList)
    {
        cout << "{" << pair.first << " : ";
        for (T vertex : pair.second)
        {
            cout << vertex << " ";
        }
        cout << "}" << endl;
    }
}

template <typename T>
bool Graph<T>::removeVertex(T vertex)
{
    if (adjList.count(vertex))
    {
        adjList.erase(vertex);
        for (auto iterator = adjList.begin(); iterator != adjList.end();)
        {
            iterator->second.erase(vertex);
            iterator++;
        }
        return true;
    }
    return false;
}

template <typename T>
bool Graph<T>::removeEdge(Edge<T> edge)
{
    if (hasEdge(edge))
    {
        adjList[edge[0]].erase(edge[1]);
        adjList[edge[1]].erase(edge[0]);
        return true;
    }
    return false;
}

template <typename T>
class DirectedGraph : public Graph<T>
{
public:
    DirectedGraph(set<T>, vector<Edge<T>>);
    DirectedGraph();
    bool addEdge(Edge<T>);
    bool removeEdge(Edge<T>);
    vector<Edge<T>> getEdges();
};

template <typename T>
vector<Edge<T>> DirectedGraph<T>::getEdges()
{
    vector<Edge<T>> returnList;
    set<DirectedEdge<T>> returnSet;
    for (pair<T, set<T>> pair : adjList)
    {
        T u = pair.first;
        for (T v : pair.second)
        {
            returnSet.insert(DirectedEdge<T>(u, v));

        }
    }
    for (DirectedEdge<T> e : returnSet)
    {
        Edge<T> edge = Edge<T>(e[0], e[1]);
        returnList.push_back(edge);
    }
    return returnList;
}

template <typename T>
DirectedGraph<T>::DirectedGraph(set<T> vertexSet, vector<Edge<T>> edgeSet)
{
    for (T vertex : vertexSet)
    {
        DirectedGraph<T>::addVertex(vertex);
    }
    for (Edge<T> edge : edgeSet)
    {
        DirectedGraph<T>::addEdge(edge);
    }
}

template <typename T>
DirectedGraph<T>::DirectedGraph() {}

template <typename T>
bool DirectedGraph<T>::addEdge(Edge<T> edge)
{

    if (!Graph<T>::hasEdge(edge) && hasVertex(edge[0]) && hasVertex(edge[1]))
    {
        Graph<T>::adjList[edge[0]].insert(edge[1]);
        return true;
    }
    return false;
}

template <typename T>
bool DirectedGraph<T>::removeEdge(Edge<T> edge)
{
    if (Graph<T>::hasEdge(edge))
    {
        Graph<T>::adjList[edge[0]].erase(edge[1]);
        return true;
    }
    return false;
}

#endif