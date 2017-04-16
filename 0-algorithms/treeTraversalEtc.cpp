#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
	int value;		// remember! there can be any comparable type.
	TreeNode* left;
TreeNode* right;
	TreeNode(int x) : value(x), left(NULL), right(NULL) { }
};

void pre_order_traversal (TreeNode* cur, vector<int>& ans)
{
	ans.push_back(cur->value);
	if (cur->left)
		pre_order_traversal(cur->left, ans);
	if (cur->right)
		pre_order_traversal(cur->right, ans);
}

void add_item (TreeNode* root, int val)
{
	while (true)
	{
		if (val < root->value) {
			if (root->left)
				root = root->left;
			else {
				TreeNode* temp = new TreeNode(val);
				root->left = temp;
				return;
			}
		}
		else if (val > root->value) {
			if (root->right)
				root = root->right;
			else {
				TreeNode* temp = new TreeNode(val);
				root->right = temp;
				return;
			}
		}
	}
}

void remove_node (TreeNode* root, int val, TreeNode* par = NULL)
{
	if ((root==NULL) || (root->value != val && !root->left && !root->right)) {
		cout << "Element not found." << endl;
		return;
	}
	if (root->value == val)
	{
		if (!root->left && !root->right) {
			if (par==NULL) {
				root->value=-1;
				return;
			}
			else {
				if (par->left == root)
					par->left = NULL;
				if (par->right == root)
					par->right = NULL;
				delete root;
			}
		}
		else if (!root->left) {
			TreeNode* r_right = root->right;
			root->value = r_right->value;
			root->left = r_right->left;
			root->right = r_right->right;
			delete r_right;
			return;
}
		else if (!root->right) {
			TreeNode* r_left = root->left;
			root->value = r_left->value;
			root->left = r_left->left;
			root->right = r_left->right;
			delete r_left;
			return;
		}
		else if (!root->right->left) {
			TreeNode* r_right = root->right;
			root->value = r_right->value;
			root->right = r_right->right;
			delete r_right;
			return;
		}
		else {
			TreeNode* parent = root;
			TreeNode* temp = root->right;
			while (temp->left) {
				parent = temp;
				temp = temp->left;
			}
			root->value = temp->value;
			delete temp;
			parent->left = NULL;
		}
	}
	else if (root->value > val)
		remove_node(root->left, val, root);
	else if (root->value < val)
		remove_node(root->right, val, root);
}

int main()
{
	int a[]={5,7,3,2,4,10,9};
	TreeNode* tree = new TreeNode(6);
	for (int i=0; i<7; i++)
		add_item(tree, a[i]);
	vector<int> output;
	pre_order_traversal(tree, output);
	cout << "Pre-order tree traversal: ";
	for (vector<int>::iterator it=output.begin(); it!=output.end(); it++)
		cout << *it << " ";
	remove_node(tree, 10);
	remove_node(tree, 17);
	remove_node(tree, 5);
	remove_node(tree, 15);
	remove_node(tree, -9);
	remove_node(tree, 2);
	remove_node(tree, 4);
	remove_node(tree, 15);
	output.clear();
	pre_order_traversal(tree, output);
	cout << endl << "Pre-order tree traversal: ";
	for (vector<int>::iterator it=output.begin(); it!=output.end(); it++)
		cout << *it << " ";
	return 0;
}
