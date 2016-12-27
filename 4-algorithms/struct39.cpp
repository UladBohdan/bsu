#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<int> > s;
vector<vector<int> > t; // 2d segment tree 4*n x 4*n
int n;

void out_segment_tree() {
    cout << "SEGMENT TREE MATRIX:" << endl;
    for (int i=0; i<4*n; i++) {
        for (int j=0; j<4*n; j++) {
            cout << t[i][j] << " ";
        }
        cout << endl;
    }
}

void out_s_matrix() {
    cout << "S MATRIX" << endl;
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            cout << s[i][j] << " ";
        }
        cout << endl;
    }
}

void init() {
    s.resize(n, vector<int>(n));
    t.resize(4*n, vector<int>(4*n));
}

void mod_y(int x, int y, int a, int tree_x, int tree_y = 0, int l_y = 0, int r_y = n-1) {
    if (l_y > r_y)
        return;
    t[tree_x][tree_y] += a;
    if (l_y == r_y)
        return;
    int mid = l_y + (r_y - l_y) / 2;
    if (y <= mid) {
        mod_y(x, y, a, tree_x, tree_y*2+1, l_y, mid);
    } else {
        mod_y(x, y, a, tree_x, tree_y*2+2, mid+1, r_y);
    }
}

void mod_x(int x, int y, int a, int tree_x = 0, int l_x = 0, int r_x = n-1) {
    if (l_x > r_x)
        return;
    if (x >= l_x && x <= r_x) {
        mod_y(x, y, a, tree_x);
        if (l_x == r_x) {
            return;
        }
    }
    int mid = l_x + (r_x - l_x) / 2;
    if (x <= mid) {
        mod_x(x, y, a, tree_x*2+1, l_x, mid);
    } else {
        mod_x(x, y, a, tree_x*2+2, mid+1, r_x);
    }
}

void modify(int x, int y, int a) {
    mod_x(x, y, a);
    //out_s_matrix();
    //out_segment_tree();
}

int sum_y(int x1, int y1, int x2, int y2, int tree_x, int tree_y = 0, int l_y = 0, int r_y = n-1) {
    //cout << "SUM Y " << tree_x << " " << tree_y << "  " << l_y << " " << r_y << endl;
    if ( (y1 < l_y && y2 < l_y) || (y1 > r_y && y2 > r_y) ) {
        //cout << "RET 0 : " << y1 << " " << y2 << endl;
        return 0;
    }
    if (y1 <= l_y && y2 >= r_y) {
      //  cout << "RET T " << tree_x << " " << tree_y << endl;
        return t[tree_x][tree_y];
    }
    int mid = l_y + (r_y - l_y) / 2;
    return sum_y(x1, y1, x2, y2, tree_x, tree_y*2+1, l_y, mid) +
           sum_y(x1, y1, x2, y2, tree_x, tree_y*2+2, mid+1, r_y);
}

int sum_x(int x1, int y1, int x2, int y2, int tree_x = 0, int l_x = 0, int r_x = n-1) {
    //cout << "SUM X " << l_x << " " << r_x << endl;
    if ( (x1 < l_x && x2 < l_x) || (x1 > r_x && x2 > r_x) ) {
        return 0;
    }
    if (x1 <= l_x && x2 >= r_x) {
        return sum_y(x1, y1, x2, y2, tree_x);
    }
    int mid = l_x + (r_x - l_x) / 2;
    return sum_x(x1, y1, x2, y2, tree_x*2+1, l_x, mid) +
           sum_x(x1, y1, x2, y2, tree_x*2+2, mid+1, r_x);
}

int sum(int x1, int y1, int x2, int y2) {
    return sum_x(x1, y1, x2, y2);
}

int main() {
    ifstream cin("input.txt");
    ofstream cout("output.txt");
    while(true) {
        int cmd;
        cin >> cmd;
        switch(cmd) {
            case 0:
                cin >> n;
                init();
                break;
            case 1:
                int x, y, a;
                cin >> x >> y >> a;
                s[x][y] += a;
                modify(x,y,a);
                break;
            case 2:
                int l, b, r, t;
                cin >> l >> b >> r >> t;
                cout << sum(l,b,r,t) << endl;
                break;
            case 3:
                return 0;
        }
    }
}