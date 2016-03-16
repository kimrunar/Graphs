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
    graph->insertVertex(n1);
    graph->insertVertex(n2);
    graph->insertVertex(n3);
    graph->insertEdge(n1,n2,10);
    graph->insertEdge(n2,n3,4);
    graph->insertEdge(n1,n4,2);
    graph->insertEdge(n4,n5,8);
    system("pause");
    graph->depthFirstTraversal(n1);



    return 0;
}
