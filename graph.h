#ifndef GRAPH_H
#define GRAPH_H

#include "graphadt.h"
#include <stack>
#include <queue>
#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
using namespace std;

class Graph : public GraphADT {

public:
    // General graph methods
    Node* aVertex();
    void insertVertex(Node* n);
    void insertEdge(Node* v, Node* w, int i = 0);
    void removeVertex(Node* n);
    void removeEdge(Edge* e);
    std::vector<Edge*>& incidentEdges(Node* n);
    Node** endVertices(Edge* e);
    Node* opposite(Node* n, Edge* e);
    bool areAdjacent(Node* v, Node* w);

    // Methods for directed edges
    bool isDirected(Edge* e);
    void insertDirectedEdge(Node* v, Node* w, int i = 0);
    Node* origin(Edge* e);
    Node* destination(Edge* e);

    // Generic methods
    int numVertices();
    int numEdges();
    vector<Node*>& vertices();
    vector<Edge*>& edges();

    // Algorithms
    void depthFirstTraversal(Node* n);
    void breadthFirstTraversal(Node* n);
    vector<Edge*> primsAlgorithm();
    void dijkstrasAlgorithm(Node* n);

private:
    void setAllUnvisited();
    vector<Node*> verticeList;
    vector<Edge*> edgeList;
};


Node* Graph::aVertex()
{
    if(verticeList.size() > 0)
        return verticeList.at(0);
    else
        return NULL;
}

void Graph::insertVertex(Node* n)
{
    verticeList.push_back(n);
}

void Graph::insertEdge(Node *v, Node *w, int i)
{
    Edge* e = new Edge(v, w, i);
    edgeList.push_back(e);
    v->edgeList.push_back(e);
    w->edgeList.push_back(e);
}

void Graph::removeEdge(Edge *e)
{

    Node* v = e->endpoint[0];
    Node* w = e->endpoint[1];

    vector<Edge*>::iterator iv = v->edgeList.begin();
    while(iv != v->edgeList.end()){
        if((*iv)->endpoint[0] == v && (*iv)->endpoint[1] == w ){
            swap(*iv, v->edgeList.back());
            v->edgeList.pop_back();



        }else{
            iv++;
        }
    }


    vector<Edge*>::iterator iw = w->edgeList.begin();
    while(iw != w->edgeList.end()){

        if((*iw)->endpoint[0] == v && (*iw)->endpoint[1] == w ){
            swap(*iw, w->edgeList.back());
            w->edgeList.pop_back();



        }else{
            iw++;
        }
    }

    vector<Edge*>::iterator i = edgeList.begin();
    while(i != edgeList.end()){
        if((*i)->endpoint[0] == v && (*i)->endpoint[1] == w ){
            swap(*iw, edgeList.back());
            edgeList.pop_back();




        }else{
            i++;
        }



    }



}


void Graph::removeVertex(Node *n)
{
    vector<Node*>::iterator i = verticeList.begin();
    while(i != verticeList.end()){
        if((*i) == n){
            swap(*i, verticeList.back());
            verticeList.pop_back();




        }else{
            i++;
        }


}
}

std::vector<Edge*>& Graph::incidentEdges(Node *n)
{
    return n->edgeList;
}

Node** Graph::endVertices(Edge *e)
{
    return e->endpoint;
}

Node* Graph::opposite(Node *n, Edge *e)
{
    if(e->endpoint[0] == n)
        return e->endpoint[1];
    else
        return e->endpoint[0];
}

bool Graph::areAdjacent(Node *v, Node *w)
{
    std::vector<Edge*>::iterator i = v->edgeList.begin();
    while(i != v->edgeList.end()){
        if((*i)->endpoint[0] == w || (*i)->endpoint[1] == w){
            return true;
        }
    }
    return false;
}

bool Graph::isDirected(Edge *e)
{
    return e->isDirected;
}

void Graph::insertDirectedEdge(Node *v, Node *w, int i)
{
    Edge* e = new Edge(v, w, i, true);
    edgeList.push_back(e);
    v->edgeList.push_back(e);
    w->edgeList.push_back(e);
}

Node *Graph::origin(Edge *e)
{
    if(e->isDirected)
        return e->endpoint[0];
    else
        return NULL;
}

Node *Graph::destination(Edge *e)
{
    if(e->isDirected)
        return e->endpoint[1];
    else
        return NULL;
}

int Graph::numVertices()
{
    return verticeList.size();
}

int Graph::numEdges()
{
    return edgeList.size();
}

std::vector<Node*>& Graph::vertices()
{
    return verticeList;
}

std::vector<Edge*>& Graph::edges()
{
    return edgeList;
}

void Graph::depthFirstTraversal(Node* n)
{
    setAllUnvisited();
    stack<Node*> verticeStack;
    verticeStack.push(n);
    while(!verticeStack.empty()){
        Node* v = verticeStack.top();
        verticeStack.pop();
        if(!v->visited){
            for(vector<Edge*>::iterator i = v->edgeList.begin(); i != v->edgeList.end(); i++){
                verticeStack.push(opposite(v, *i));
            }
            cout << v->data << " ";


            v->visited = true;
        }
    }
    cout << endl;
}

void Graph::breadthFirstTraversal(Node* n)
{
    setAllUnvisited();
  queue<Node*> q;
    q.push(n);
   while(!q.empty()){
      Node* v = q.front();
      q.pop();
       if(!v->visited){
           for(vector<Edge*>::iterator i = v->edgeList.begin(); i != v->edgeList.end(); i++){
               q.push(opposite(v, *i));
           }
          v->visited = true;
          cout << v->data << " ";
       }
   }
   cout << endl;
}

void Graph::setAllUnvisited()
{
    for(vector<Node*>::iterator i = verticeList.begin(); i != verticeList.end(); i++){
        (*i)->visited = false;
    }
}

/*
 *  Here we create a functor class that we can use to create a priority queue for Edges
 */
class CompareEdges
{
public:
    bool operator()(const Edge* e, const Edge* f)
    {
        /* Returns true if edge e has higher weight than edge f */
        return e->weight > f->weight;
    }
};

std::vector<Edge*> Graph::primsAlgorithm()
{
    Node* aktuell;
    int minimum = 9999;
    setAllUnvisited();
    vector<Node*> v;
    int inner = 0;
    int a = 0;

    for(vector<Node*>::iterator i = verticeList.begin(); i != verticeList.end(); i++){
        for(vector<Edge*>::iterator j = (*i)->edgeList.begin(); j != (*i)->edgeList.end(); j++){

    a = (*i)->edgeList[inner]->weight;
    Node* denne = (*i);
    if(a < minimum && denne->visited==false){
        minimum = a;
        if(opposite((*i),(*j))->visited == false){
        aktuell = denne;
        cout << "new candidate" << endl;
        }
     }else{
        cout << "throw"<< endl;
    }
        inner++;
        minimum = 888888;
    }
    if(aktuell != nullptr){
        v.push_back(aktuell);
        aktuell->visited = true;
        aktuell = nullptr;
}

        inner = 0;
   }

}

//    Node* aktuell = q.front();
//    v.push(aktuell);
//    aktuell->visited = true;
//    Node* theOne = aktuell;

//    while(!q.empty()){

//    minste = 99999;

//    for(vector<Edge*>::iterator i = aktuell->edgeList.begin(); i != aktuell->edgeList.end(); i++){
//    int a = (*i)-> weight;


//    if((*i)->endpoint[1]->visited == false ||(*i)->endpoint[0]->visited == false ){
//        if(a < minste){
//            minste = a;
//            theOne = this->opposite(aktuell, (*i));
//        }
//    }


//    }
//    for(vector<Edge*>::iterator i = aktuell->edgeList.begin(); i != aktuell->edgeList.end(); i++){
//        Node * l = this->opposite(aktuell,(*i));
//        if(l->visited == true){
//            ferdig = false;
//        }
//    }
//    if(ferdig){
//    theOne->visited=true;
//    v.push(theOne);
//    cout << theOne->data << " ,";
//    }else{
//        for(vector<Node*>::iterator i = verticeList.begin(); i != verticeList.end(); i++){
//            if((*i)->visited == false){
//               aktuell = (*i);
//               break;
//            }
//        }
//        ferdig = true;
//    }

 //   }






//}

/*
 *  Here we create a functor class that we can use to create a priority queue for Nodes
 */
class CompareNodeDistance
{
public:
    bool operator()(const Node* v, const Node* w)
    {
        /* Returns true if node v has longer path than node w */
        return v->distance > w->distance;
    }
};

void Graph::dijkstrasAlgorithm(Node *n)
{
    setAllUnvisited();
    n->distance = 0;
    std::priority_queue<Node*,std::vector<Node*>,CompareNodeDistance> unvisitedNodes(verticeList.begin(), verticeList.end());

    while(!unvisitedNodes.empty()){
        // Find min distance node
        Node* v = unvisitedNodes.top();
        unvisitedNodes.pop();
        for(std::vector<Edge*>::iterator i = v->edgeList.begin(); i != v->edgeList.end(); i++){
            Node* w = opposite(v,*i);
            int dist = v->distance + (*i)->weight;
            if( dist < w->distance ){
                w->distance = dist;
                w->previous = v;
            }
        }
    }
}

#endif // GRAPH_H
