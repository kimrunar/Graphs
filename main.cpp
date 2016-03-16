#include <iostream>
#include "edge.h"
#include "graph.h"
#include "node.h"

using namespace std;

int main()
{
    Graph *graph = new Graph();
    Node *n1= new Node('a');
    Node *n2= new Node('b');
    Node *n3=new Node('c');
    Node *n4=new Node('d');
    Node *n5=new Node('e');
    Node *n6=new Node('f');
    Edge *e1 = new Edge(n1,n2,1);
    Edge *e2 = new Edge(n1,n3,1);
    Edge *e3 = new Edge(n1,n4,3);
    Edge *e4 = new Edge(n1,n6,5);
    Edge *e5 = new Edge(n2,n3,2);
    Edge *e6 = new Edge(n2,n5,2);
    Edge *e7 = new Edge(n5,n6,1);

    graph->insertVertex(n1);
    graph->insertVertex(n2);
    graph->insertVertex(n3);
    graph->insertVertex(n4);
    graph->insertVertex(n5);
    graph->insertEdge(e1->endpoint[0],e1->endpoint[1],e1->weight);
    graph->insertEdge(e2->endpoint[0],e2->endpoint[1],e2->weight);
    graph->insertEdge(e3->endpoint[0],e3->endpoint[1],e3->weight);
    graph->insertEdge(e4->endpoint[0],e4->endpoint[1],e4->weight);
    graph->insertEdge(e5->endpoint[0],e5->endpoint[1],e5->weight);
    graph->insertEdge(e6->endpoint[0],e6->endpoint[1],e6->weight);
    graph->insertEdge(e7->endpoint[0],e7->endpoint[1],e7->weight);

    system("pause");
    graph->depthFirstTraversal(n1);
    graph->removeEdge(e4);
    graph->depthFirstTraversal(n1);


    return 0;
}
