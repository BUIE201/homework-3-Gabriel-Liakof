#include <iostream>
#include <vector>

using namespace std;

struct Node
{
	int i;
	Node* pLeft;
	Node* pRight;

	Node(int iIn) : i(iIn), pLeft(nullptr), pRight(nullptr) {}
};

void InsertToTree(Node*& pRoot, Node* pNew)
{
	if (!pRoot)
	{
		pRoot = pNew;
		return;
	}

	if (pNew->i <= pRoot->i)
		InsertToTree(pRoot->pLeft, pNew);
	else
		InsertToTree(pRoot->pRight, pNew);
}


void PrintTree(Node* pRoot, int Level)
{
	if (!pRoot)
		return;

	PrintTree(pRoot->pRight, Level + 1);

	for (int i = 0; i < Level; i++)
		cout << "  ";
	cout << pRoot->i << endl;

	PrintTree(pRoot->pLeft, Level + 1);
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FindMaxSum(Node* pRoot) { // finds the maxium sum of branches from the root node by checking
	if (pRoot == nullptr)			//  every child node's left and right sums and returing the bigger one.
	{
		return 0;
	}
	int leftsum = 0;
	int rightsum = 0;

	leftsum = FindMaxSum(pRoot->pLeft);
	rightsum = FindMaxSum(pRoot->pRight);

	if (leftsum < rightsum) { return rightsum + pRoot->i; }
	else { return leftsum + pRoot->i; }
}
vector<int> MaxBranch; /// keeps the max branch
bool FindTheMaxBranch(Node* pRoot, int maxsum) { // finds the nodes of the branch with maximum sum
		if (maxsum == 0) { ///checks if there is a branch that sums up to the max sum
			return 1;   
		}
		if (pRoot == nullptr) { 
			return 0; 
		}
		
		bool leftside = FindTheMaxBranch(pRoot->pLeft, maxsum - pRoot->i); //removes node values from the sum value
																		
		bool rightside = FindTheMaxBranch(pRoot->pRight, maxsum - pRoot->i);//removes node values from the sum value
		
		if ((leftside || rightside)) { MaxBranch.push_back(pRoot->i); }
		
		return leftside || rightside; // if one sum become 0, means that the branch to that node is the maxsum branch
									  // this value returns 1, recursive function records the nodes in this branch to the MaxBranch vector
									  // via the condition at the upper row(74).
}


void PrintMaxSumBranchandItsSum(Node* pRoot) { // Prints results.
	FindTheMaxBranch(pRoot, FindMaxSum(pRoot));
	cout << "Branch with the largest sum is:";
	for (int i = 0; i < MaxBranch.size(); i++) {
		cout << MaxBranch[i] << " ";
	}
	cout << "-> SUM= ";

	cout << FindMaxSum(pRoot);
}



int main()
{
	int i;

	Node* pRoot = nullptr;
	while (true)
	{
		cin >> i;
		if (i == 99)
			break;

		Node* p = new Node(i);
		InsertToTree(pRoot, p);
	}

	PrintTree(pRoot, 1);

	PrintMaxSumBranchandItsSum(pRoot);



}
