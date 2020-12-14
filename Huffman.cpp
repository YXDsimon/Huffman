#include <queue>
#include <map>
#include <string>
#include <iostream>
using namespace std;
template <typename T>
void print_queue(T &q)
{
    while (!q.empty())
    {
        cout << q.top()->name << " ";
        q.pop();
    }
    cout << '\n';
}
struct node
{
    char name;
    int value;
    node *lchild;
    node *rchild;
    node(char n, int v)
    {
        name = n;
        value = v;
        lchild = NULL;
        rchild = NULL;
    }
    node(int v)
    {
        name = '\0';
        value = v;
        lchild = NULL;
        rchild = NULL;
    }
};
void traverse(const node *n, map<char, string> &m, string code) //递归遍历
{
    if (n->lchild)
        traverse(n->lchild, m, code + '0');
    if (n->rchild)
        traverse(n->rchild, m, code + '1');
    if (!n->lchild && !n->rchild)
        m[n->name] = code;
}
void traverse(node *n, map<char, string> &m) //非递归遍历
{
    pair<node *, string> tempP;
    queue<pair<node *, string>> Q;
    pair<node *, string> p(n, "");
    Q.push(p);
    while (!Q.empty())
    {
        tempP = Q.front();
        Q.pop();
        if (tempP.first->lchild)
        {
            string code = tempP.second;
            pair<node *, string> p(tempP.first->lchild, code + '0');
            Q.push(p);
        }
        if (tempP.first->rchild)
        {
            string code = tempP.second;
            pair<node *, string> p(tempP.first->rchild, code + '1');
            Q.push(p);
        }
        if (!tempP.first->rchild && !tempP.first->lchild)
        {
            m[tempP.first->name] = tempP.second;
        }
    }
}
auto cmp = [](node *left, node *right) { return (left->value) > (right->value); };
int main()
{
    node *n;
    priority_queue<node *, vector<node *>, decltype(cmp)> Q(cmp);
    n = new node('a', 8);
    Q.push(n);
    n = new node('b', 3);
    Q.push(n);
    n = new node('c', 4);
    Q.push(n);
    n = new node('d', 6);
    Q.push(n);
    n = new node('e', 5);
    Q.push(n);
    n = new node('f', 5);
    Q.push(n);
    node *n1;
    node *n2;
    node *N;
    while (Q.size() > 1)
    {
        n1 = Q.top();
        Q.pop();
        n2 = Q.top();
        Q.pop();
        N = new node(n1->value + n2->value);
        N->lchild = n1;
        N->rchild = n2;
        Q.push(N);
    }
    map<char, string> m;
    traverse(Q.top(), m);
    auto iter = m.begin();
    while (iter != m.end())
    {
        cout << iter->first << ": " << iter->second << endl;
        iter++;
    }
    return 0;
}
