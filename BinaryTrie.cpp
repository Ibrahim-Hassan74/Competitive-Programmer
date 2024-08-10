struct BinaryTrie {
    struct Node {
        Node *ch[2];
        int fre[2];

        Node() {
           ch[0] = ch[1] = 0;
           fre[0] = fre[1] = 0;
        }
    };
    Node *root = new Node();
    BinaryTrie() {
       //insert(0);
    }
    void insert(int n) {
       Node *cur = root;
       for (int i = 31; ~i; --i) {
          int idx = (n >> i) & 1;
          if (!cur->ch[idx])
             cur->ch[idx] = new Node();
          cur->fre[idx]++;
          cur = cur->ch[idx];
       }
    }
    void erase(int n, int i, Node *cur) {
       if (i == -1) return;
       int idx = (n >> i) & 1;
       erase(n, i - 1, cur->ch[idx]);
       cur->fre[idx]--;
       if (!cur->fre[idx]) {
          delete cur->ch[idx];
          cur->ch[idx] = 0;
       }
    }
    int query(int n) {
       int ret = 0;
       Node *cur = root;
       for (int i = 31; ~i; --i) {
          int idx = (n >> i) & 1;
          if (cur->ch[!idx]) {
             ret += (1LL << i);
             cur = cur->ch[!idx];
          } else if (cur->ch[idx]) {
             cur = cur->ch[idx];
          } else {
             return -1;
          }
       }
       return ret;
    }
};
