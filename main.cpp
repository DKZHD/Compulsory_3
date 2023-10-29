
#include "StandardTreeLib.h"
#include "Graph.h"


int main()
{
	NodeClass<int> node_class;
	GraphNode<int>* node1 = node_class.CreateVertex(15);
	GraphNode<int>* node2 = node_class.CreateVertex(12);
	GraphNode<int>* node3 = node_class.CreateVertex(9);
	GraphNode<int>* node4 = node_class.CreateVertex(20);
	GraphNode<int>* node5 = node_class.CreateVertex(20);
	GraphNode<int>* node6 = node_class.CreateVertex(40);
	Graph<int> graph;
	
	graph.addEdge(node1, node3, 20);
	graph.addEdge(node1, node4, 5);
	graph.addEdge(node6, node1,19);
	graph.addEdge(node2, node3, 12);
	graph.addEdge(node4, node3, 16);
	graph.addEdge(node4, node5, 30);
	graph.DrawGraph();


	TreeRoot<int> Tree(5);
	Tree.newChild(25, Tree.Root);
	Tree.newChild(10, Tree.Root);
	Tree.newChild(12, Tree.Root->child[0]);
	Tree.newChild(15, Tree.Root->child[1]);
	Tree.newChild(29, Tree.Root->child[0]->child[0]);
	


	return 0;
}

