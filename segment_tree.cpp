struct Node {
    int sum;

    Node() { sum = OO; }

    Node(int x) { sum = x; }

    void change(int x) { sum = x; }
};

struct segment_tree {
private:
    int tree_size;
    vector<Node> seg;

    Node merge(Node &left, Node &right) {
       Node ans = Node();
       ans.sum = min(left.sum, right.sum);
       return ans;
    }

    void init(vector<int> &v, int n, int l, int r) {
       if (r - l == 1) {
          if (l < v.size())
             seg[n] = Node(v[l]);
          return;
       }
       int mid = (l + r) / 2;
       init(v, 2 * n + 1, l, mid);
       init(v, 2 * n + 2, mid, r);
       seg[n] = merge(seg[2 * n + 1], seg[2 * n + 2]);
    }

    void set(int idx, int val, int n, int lx, int rx) { // 0 indexed and r not included
       if (rx - lx == 1) {
          seg[n].change(val);
          return;
       }
       int mid = (lx + rx) / 2;
       if (idx < mid) {
          set(idx, val, 2 * n + 1, lx, mid);
       } else {
          set(idx, val, 2 * n + 2, mid, rx);
       }
       seg[n] = merge(seg[2 * n + 1], seg[2 * n + 2]);
    }

    Node get(int l, int r, int n, int lx, int rx) { // 0 indexed and r not included

       if (lx >= l && rx <= r)
          return seg[n];
       if (lx >= r || rx <= l)
          return Node();
       int mid = (lx + rx) / 2;
       Node lf = get(l, r, 2 * n + 1, lx, mid);
       Node ri = get(l, r, 2 * n + 2, mid, rx);
       return merge(lf, ri);
    }

public:
    segment_tree(int n) {
       tree_size = 1;
       while (tree_size < n) tree_size *= 2;
       seg.assign(2 * tree_size, Node());
    }

    void set(int idx, int val) {
       set(idx, val, 0, 0, tree_size);
    }

    int get(int l, int r) {
       return get(l, r, 0, 0, tree_size).sum;
    }

    void init(vector<int> &v) {
       init(v, 0, 0, tree_size);
    }

};
