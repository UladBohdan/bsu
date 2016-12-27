#include <fstream>
#include <iostream>

using namespace std;

struct TreeNode {
    int value;
    int height, halfway;
    int dist, if_right, if_left, if_up; // for counting distance & half-ways
    TreeNode *left;
    TreeNode *right;

    TreeNode(int val) {
        value = val;
        left = NULL;
        right = NULL;
    }
};

TreeNode *root;
ifstream fin("tst.in");
ofstream fout("tst.out");
int k, to_delete = -1;

void add(int a) {

    TreeNode *temp = new TreeNode(a);
    if (root == NULL) {
        root = temp;
        return;
    }
    TreeNode *cur = root;
    while (true) {
        if (cur->value == a)
            return;
        else if (cur->value > a) {
            if (cur->left != NULL) {
                cur = cur->left;
            }
            else {
                cur->left = temp;
                return;
            }
        }
        else {
            if (cur->right != NULL)
                cur = cur->right;
            else {
                cur->right = temp;
                return;
            }
        }
    }
}

int count_height(TreeNode *cur = root) {
    if (cur->left == NULL && cur->right == NULL)
        cur->height = 0;
    else if (cur->left == NULL)
        cur->height = count_height(cur->right) + 1;
    else if (cur->right == NULL)
        cur->height = count_height(cur->left) + 1;
    else
        cur->height = max(count_height(cur->left), count_height(cur->right)) + 1;
    return cur->height;
}

void count_dist(TreeNode* cur = root, TreeNode* parent = NULL, bool i_left = true) {

    cur->if_right = (cur->right ? cur->right->height + 1 : 0);
    cur->if_left = (cur->left ? cur->left->height + 1 : 0);
    if (!parent)
        cur->if_up = 0;
    else if (i_left)
        cur->if_up = max(parent->if_right, parent->if_up) + 1;
    else
        cur->if_up = max(parent->if_left, parent->if_up) + 1;

    cur->dist = max(cur->if_right, max(cur->if_left, cur->if_up));

    cur->halfway = max(cur->if_up + cur->if_left,
                       max( cur->if_up + cur->if_right, cur->if_left + cur->if_right ));

    if (cur->right)
        count_dist(cur->right, cur, false);
    if (cur->left)
        count_dist(cur->left, cur, true);
}

void find(TreeNode *cur = root) {
    if (cur->left)
        find(cur->left);
    if ((cur->dist < k) && (cur->halfway < k))
        to_delete = cur->value;
    if (cur->right)
        find(cur->right);
}

void remove(TreeNode *cur = root, TreeNode *par = NULL) {
    if (cur->value == to_delete) {
        if (cur->right == NULL && cur->left == NULL) {
            if (par == NULL)
                root = NULL;
            else if (par->left == cur)
                par->left = NULL;
            else if (par->right == cur)
                par->right = NULL;
        }
        else if (cur->right == NULL) {
            TreeNode *temp = cur;
            if (par == NULL)
                root = cur->left;
            else if (par->right == cur)
                par->right = cur->left;
            else if (par->left == cur)
                par->left = cur->left;
            delete temp;
        }
        else if (cur->left == NULL) {
            TreeNode *temp = cur;
            if (par == NULL)
                root = cur->right;
            else if (par->right == cur)
                par->right = cur->right;
            else if (par->left == cur)
                par->left = cur->right;
            delete temp;
        }
        else {
            // BOTH SUBTREES EXIST
            if (cur->right->left == NULL) {
                TreeNode *temp = cur->right;
                cur->value = temp->value;
                cur->right = temp->right;
                delete temp;
            }
            else {
                TreeNode *parent = cur->right;
                TreeNode *temp = cur->right->left;
                while (temp->left) {
                    parent = temp;
                    temp = temp->left;
                }
                cur->value = temp->value;
                if (temp->right)
                    parent->left = temp->right;
                else
                    parent->left = NULL;
                delete temp;
            }
        }
    }
    else if (cur->value > to_delete) {
        remove(cur->left, cur);
    }
    else if (cur->value < to_delete) {
        remove(cur->right, cur);
    }

}

void out_prefix_left(TreeNode *cur = root) {
    if (cur == NULL)
        return;
    fout << cur->value << endl;
   // printf("%d (%d, %d, %d)\n", cur->value, cur->height, cur->dist, cur->halfway);
    out_prefix_left(cur->left);
    out_prefix_left(cur->right);
}

int main() {
    root = NULL;
    fin >> k;
    while (!fin.eof()) {
        int a = -1;
        fin >> a;
        if (a >= 0)
            add(a);
    }
    fin.close();
    //SOLUTION
    if (!root) {
        fout << "Empty";
        fout.close();
        return 0;
    }
    if (k <= 0) {
        out_prefix_left();
        fout.close();
        return 0;
    }
    root->height = count_height();
    count_dist();
    find();
    if (to_delete >= 0)
        remove();
    // OUTPUT
    if (root == NULL)
        fout << "Empty";
    else
        out_prefix_left();
    fout.close();
}