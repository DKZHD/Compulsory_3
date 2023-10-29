#pragma once
#include <iostream>
#include <vector>

#define PrintTwo(X,Y) std::cout << X << Y << std::endl
#define PrintOne(X) std::cout << X << std::endl
#define PrintDirectory(X,Y) std::cout << "Directory: " << X << "->" << Y << std::endl
#define PrintEdge(X,Y,Z) std::cout << X << "--" <<"("<< Y <<")"<< "--" <<Z << std::endl

template <typename T> 
struct Node
{
	Node* Parent = nullptr;
	std::vector<Node*> child;
	T VariableToHold;
};

// I know I could have used a class, but I wanted to use structs
template <typename T>
struct TreeRoot
{
	

	//Default Constructor
	TreeRoot(T Value)
	{
		Root = NewNode(Value);
	}

	// Create a new node without a parent, use newChild instead
	Node<T>* NewNode(T Value)
	{
		Node<T>* temp = new Node<T>;
		temp->VariableToHold = Value;
		Nodes.push_back(temp);
		return temp;
	}

	// Create a new node, parented to another node
	Node<T>* newChild(T Value, Node<T>* ParentNode)
	{
		Node<T>* temp = NewNode(Value);
		temp->Parent = ParentNode;
		ParentNode->child.push_back(temp);
		return temp;
	}

	// Writes the values and amount of children for a specified node to console
	void PrintChildren(Node<T>* node)
	{
		for (Node<T>* temp : node->child)
		{
			PrintOne(temp->VariableToHold);
		}
		PrintTwo("Amount of Children: ", node->child.size());
	}

	// Returns true if checked node is Root
	bool bIsRoot(Node<T>* node)
	{
		return node->Parent == nullptr;
	}

	// Returns true if checked node is a leaf
	bool bIsLeaf(Node<T>* node)
	{
		return node->child.empty();
	}

	// Returns true if tree is empty
	bool bIsEmpty()
	{
		return Root == nullptr;
	}

	// Returns a pointer to the Root
	Node<T>* GetRoot()
	{
		return Root;
	}

	// Returns the size of the Tree
	int GetTreeSize()
	{
		return Nodes.size();
	}

	// Writes the depth to a specified node to the console
	void GetDepth(Node<T>* node)
	{
		if (node->Parent != nullptr)
		{
			Depth++;
			GetDepth(node->Parent);
		}
		else
		{
			PrintTwo("Depth is: ", Depth);
			Depth = 0;
		}
			
	}

	// Deletes a node and all its children from the tree
	void DeleteNode(Node<T>* nodetodelete)
	{
		if(HasChild(nodetodelete))
		{
			for (auto node : nodetodelete->child)
			{
				DeleteNode(node);
			}
		}
		delete nodetodelete;
	}

	// Returns true if the specified node has at least one child
	bool HasChild(Node<T>* node)
	{
		return !node->child.empty();
	}

	// Returns true if target value is found in tree
	bool bElementExist_Depth(Node<T>* root,int TargetValue)
	{
		bool HasFound = false;
		for (int i = 0; i < root->child.size(); i++)
		{
			if (root->child[i]->VariableToHold == TargetValue)
			{
				HasFound = true;
			}
			if (bElementExist_Depth(root->child[i], TargetValue))
				HasFound = true;
		}
		if(HasFound)
		{
			return true;
		}
		return false;
	}

	// Creates a new node parented to a random node in the tree
	Node<T>* InsertRandomNode()
	{
		srand(time(nullptr));
		Node<T>* temp = newChild(rand() % 100, Nodes[rand() % Nodes.size()]);
		return temp;
	}

private:
	std::vector<Node<T>*> Nodes;
	int Depth = 0;
	Node<T>* Root;
};

