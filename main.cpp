
#include "StandardTreeLib.h"
#include "Graph.h"


int main()
{

	PrintOne("Graph: ");
	// Create Node Class
	NodeClass<int> node_class;

	// Add vertices to node class
	GraphNode<int>* node1 = node_class.CreateVertex(15);
	GraphNode<int>* node2 = node_class.CreateVertex(12);
	GraphNode<int>* node3 = node_class.CreateVertex(9);
	GraphNode<int>* node4 = node_class.CreateVertex(20);
	GraphNode<int>* node5 = node_class.CreateVertex(20);
	GraphNode<int>* node6 = node_class.CreateVertex(40);
	Graph<int> graph;

	// Add edges to graph based on the vertices
	graph.addEdge(node1, node3, 20);
	graph.addEdge(node1, node4, 5);
	graph.addEdge(node6, node1,19);
	graph.addEdge(node2, node3, 12);
	graph.addEdge(node4, node3, 16);
	graph.addEdge(node4, node5, 30);

	// Writes data of a specified vertex
	PrintOne(graph.GetVertexData(node1));

	// Writes size of the graph to console
	PrintOne(graph.getSize());

	// Deletes edge
	//graph.DeleteEdge(node1, node3);

	// Draws visible edges connecting vertices
	graph.DrawGraph();

	PrintOne("Tree: ");

	// Create Tree
	TreeRoot<int> Tree(5);

	// Add Children
	Tree.newChild(25, Tree.GetRoot());
	Tree.newChild(10, Tree.GetRoot());
	Tree.newChild(12, Tree.GetRoot()->child[0]);
	Tree.newChild(15, Tree.GetRoot()->child[1]);
	Tree.newChild(29, Tree.GetRoot()->child[0]->child[0]);

	// Write children to console
	Tree.PrintChildren(Tree.GetRoot());

	return 0;
}

