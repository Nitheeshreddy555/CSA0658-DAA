// Program to solve Job Assignment problem
// using Branch and Bound
#include <bits/stdc++.h>
using namespace std;
#define N 4

// state space tree node
struct Node
{
	// stores parent node of current node
	// helps in tracing path when answer is found
	Node* parent;

	// contains cost for ancestors nodes
	// including current node
	int pathCost;

	// contains least promising cost
	int cost;

	// contain worker number
	int workerID;

	// contains Job ID
	int jobID;

	// Boolean array assigned will contains
	// info about available jobs
	bool assigned[N];
};

// Function to allocate a new search tree node
// Here Person x is assigned to job y
Node* newNode(int x, int y, bool assigned[],
			Node* parent)
{
	Node* node = new Node;

	for (int j = 0; j < N; j++)
		node->assigned[j] = assigned[j];
	node->assigned[y] = true;

	node->parent = parent;
	node->workerID = x;
	node->jobID = y;

	return node;
}

// Function to calculate the least promising cost
// of node after worker x is assigned to job y.
int calculateCost(int costMatrix[N][N], int x,
				int y, bool assigned[])
{
	int cost = 0;

	// to store unavailable jobs
	bool available[N] = {true};

	// start from next worker
	for (int i = x + 1; i < N; i++)
	{
		int min = INT_MAX, minIndex = -1;

		// do for each job
		for (int j = 0; j < N; j++)
		{
			// if job is unassigned
			if (!assigned[j] && available[j] &&
				costMatrix[i][j] < min)
			{
				// store job number
				minIndex = j;

				// store cost
				min = costMatrix[i][j];
			}
		}

		// add cost of next worker
		cost += min;

		// job becomes unavailable
		available[minIndex] = false;
	}

	return cost;
}

// Comparison object to be used to order the heap
struct comp
{
	bool operator()(const Node* lhs,
				const Node* rhs) const
	{
		return lhs->cost > rhs->cost;
	}
};

// print Assignments
void printAssignments(Node *min)
{
	if(min->parent==NULL)
		return;

	printAssignments(min->parent);
	cout << "Assign Worker " << char(min->workerID + 'A')
		<< " to Job " << min->jobID << endl;

}
int findMinCost(int costMatrix[N][N])
{
	
	priority_queue<Node*, std::vector<Node*>, comp> pq;

	
	bool assigned[N] = {false};
	Node* root = newNode(-1, -1, assigned, NULL);
	root->pathCost = root->cost = 0;
	root->workerID = -1;

	
	pq.push(root);

	
	while (!pq.empty())
	{
	
	Node* min = pq.top();


	pq.pop();


	int i = min->workerID + 1;

	
	if (i == N)
	{
		printAssignments(min);
		return min->cost;
	}
	
	for (int j = 0; j < N; j++)
	{
		
		if (!min->assigned[j])
		{
		
		Node* child = newNode(i, j, min->assigned, min);

		
		child->pathCost = min->pathCost + costMatrix[i][j];

		
		child->cost = child->pathCost +
			calculateCost(costMatrix, i, j, child->assigned);

		
		pq.push(child);
		}
	}
	}
}


int main()
{
	
	int costMatrix[N][N] =
	{
		{9, 2, 7, 8},
		{6, 4, 3, 7},
		{5, 8, 1, 8},
		{7, 6, 9, 4}
	};


	

	cout << "\nOptimal Cost is "
		<< findMinCost(costMatrix);

	return 0;
}

