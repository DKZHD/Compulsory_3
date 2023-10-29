#pragma once
#include <map>
#include <vector>

template <typename T>
struct GraphNode
{
	T data;
	int NodeID=0;
	std::vector<std::pair<GraphNode*, unsigned int>> ConnectedVertices;
	bool Counted = false;
	bool Visited = false;
};
template <typename T>
class NodeClass
{
public:
	// Create a vertex. Can't be displayed if it isn't connected by an edge
	GraphNode<T>* CreateVertex(T data)
	{
		auto temp = new GraphNode<T>;
		temp->data = data;
		return temp;
	}
};
template <typename T>
class Edge
{
public:

	// Holds all information regarding an edge. Like the vertices connected and weight
	std::pair<std::pair<GraphNode<T>*, GraphNode<T>*>, unsigned int> edgeData;

	// Default constructor for Edge
	Edge(GraphNode<T>* from, GraphNode<T>* to, unsigned int weight)
	{
		std::pair<GraphNode<T>*, GraphNode<T>*> edge = std::make_pair(from,to);
		edgeData = std::make_pair(edge,weight);
	}
};
template <typename T>
class Graph
{
public:
	/// \brief Adds an edge into the graph, connecting two vertices
	/// \param from first vertex to connect
	/// \param to second vertex to connect
	/// \param weight Edge weight
	void addEdge(GraphNode<T>* from, GraphNode<T>* to, unsigned int weight)
	{
		from->ConnectedVertices.push_back(std::make_pair(to, weight));
		to->ConnectedVertices.push_back(std::make_pair(from, weight));
		EdgesInGraph.push_back(Edge<T>(from, to, weight));
	}

	// Returns amount of Vertices in graph 
	int getSize()
	{
		for(Edge<T> edge : EdgesInGraph)
		{
				if(edge.edgeData.first.first->Counted==false)
				{
					edge.edgeData.first.first->Counted = true;
					VerticesInGraph.push_back(edge.edgeData.first.first);
				}
				
				if (edge.edgeData.first.second->Counted == false)
				{
					edge.edgeData.first.second->Counted = true;
					VerticesInGraph.push_back(edge.edgeData.first.second);
				}

		}
		for (int i = 0; i < VerticesInGraph.size(); i++)
		{
			VerticesInGraph[i]->NodeID = i + 1;
		}
		return VerticesInGraph.size();
	}

	// Returns amount of edges in graph
	int getEdges()
	{
		return EdgesInGraph.size();
	}

	// Gets vertices adjacent to past in Vertex 
	static int getAdjacentVertices(GraphNode<T>* vertex)
	{
		return vertex->ConnectedVertices.size();
	}

	// Return True if graph doesn't have any vertices
	bool bIsEmpty()
	{
		return getSize() == 0;
	}

	// Visual representation of all edges in the graph
	void DrawGraph()
	{
		getSize();
		for(Edge<T> edge : EdgesInGraph)
		{
			PrintEdge(edge.edgeData.first.first->NodeID, edge.edgeData.second, edge.edgeData.first.second->NodeID);
		}
		
	}

	// Get stored data in a vertex. Can return any type as it is a template function
	static T GetVertexData(GraphNode<T>* vertex)
	{
		return vertex->data;
	}

	// Delete a vertex and all edges connected to it
	void DeleteVertex(GraphNode<T>* Vertex)
	{
		for (std::pair<GraphNode<T>*, unsigned int> pair : Vertex->ConnectedVertices)
		{
			DeleteEdge(pair.first, Vertex);
			if(Vertex->ConnectedVertices.empty())
				break;
		}
		if (Vertex->ConnectedVertices.empty())
			delete Vertex;
		else
		{
			DeleteVertex(Vertex);
		}
	}

	/// \brief Deletes edge between two vertices
	/// \param vertex1 First Vertex of the edge
	/// \param vertex2 Second Vertex of the edge
	void DeleteEdge(GraphNode<T>* vertex1, GraphNode<T>* vertex2)
	{
		for (auto it = EdgesInGraph.begin(); it != EdgesInGraph.end();)
		{
			if (it->edgeData.first == std::make_pair(vertex1, vertex2))
			{
				it = EdgesInGraph.erase(it);
			}
			else if (it->edgeData.first == std::make_pair(vertex2, vertex1))
			{
				it = EdgesInGraph.erase(it);
			}
			else
			{
				++it;
			}

		}
		RemoveReferences(vertex1, vertex2);
		RemoveReferences(vertex2, vertex1);
	}

	// Function for picking a random vertex and adding an edge between that and a new vertex 
	void ConnectRandomEdge(NodeClass<T> node_class)
	{
		getSize();
		srand(time(nullptr));
		int RandomVertex = rand() % VerticesInGraph.size();
		auto temp = node_class.CreateVertex(rand() % 50);
		addEdge(VerticesInGraph[RandomVertex], temp, rand() % 50);
	}

	// Returns true if target data exists in the graph. Only possible if there is a path to the value.
	bool bDoesExist_Depth(GraphNode<T>* Start, T TargetData)
	{
			Start->Visited = true;
			if (Start->data == TargetData)
				return true;
			bool hasFound = false;
			if(!Start->ConnectedVertices.empty())
			{
				for (auto element : Start->ConnectedVertices)
				{
					if (element.first->data == TargetData)
						hasFound = true;
					if(!element.first->Visited)
					{
						if (bDoesExistDepth(element.first, TargetData))
							hasFound = true;
					}
				}
			}
			if (hasFound)
			{
				return true;
			}
			return false;
	}

private:

	std::vector<GraphNode<T>*> VerticesInGraph;
	std::vector<Edge<T>> EdgesInGraph;

	// Function to remove references inside a graph node to a target
	void RemoveReferences(GraphNode<T>* vertex, GraphNode<T>* target)
	{
		for (auto it = vertex->ConnectedVertices.begin(); it != vertex->ConnectedVertices.end();)
		{
			if (it->first == target)

				it = vertex->ConnectedVertices.erase(it);
			else
				++it;
		}
	}
};
