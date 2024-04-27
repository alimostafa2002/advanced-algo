#include <iostream>
#include <stack>
#include <vector>
#include <cmath>
using namespace std;

class Node
{
    public:
        string d;
        Node* l;
        Node* r;
        
        Node(string data)
        {
            d = data;
            l = NULL;
            r = NULL;
        }
    
        
};

class Tree
{
    public:
        Node* root;
        
        Tree()
        {
            root = NULL;
        }
        
        

        double rCalcRes()
        {
            return calcR(root);
        }

        double calcR(Node* current)
        {
            if (current->l == NULL && current->r == NULL)
            {
                return stod(current->d);
            }
            else
            {
                string m = current->d;
                if (m == "+")
                {
                    return calcR(current->l) + calcR(current->r);
                }
                if (m == "-")
                {
                    return calcR(current->l) - calcR(current->r);
                }
                if (m == "*")
                {
                    return calcR(current->l) * calcR(current->r);
                }
                else
                {
                    return calcR(current->l) / calcR(current->r);
                }
            }
        }
        
        void rnExTre(string sx)
        {
            root = epTre(sx);
        }
        
        Node* epTre(string stt)
        {
            stack<int> stacko;
            vector<int> vicko;
            string newStr = cleanS(stt);
            int n = newStr.length();
            for (int i = 0; i < n; i++)
            {
                char cuElent = newStr[i];
                if (cuElent == '(')
                {
                    stacko.push(i);
                }
                else if (cuElent == ')')
                {
                     stacko.pop();
                }
                else if (stacko.size() == 0 && (cuElent == '+' || cuElent == '-' || cuElent == '*' || cuElent == '/'))
                {
                    vicko.push_back(i);
                }
            }
            int m;
            if (vicko.size() == 0)
            {
                return new Node(newStr);
            }
            else if (vicko.size() == 1)
            {
                m = vicko.at(0);
            }
            else
            {
                int operSymbolIndex = prece(newStr, vicko);
                m= vicko.at(operSymbolIndex);
            }
            Node* ne1 = new Node(newStr.substr(m, 1));
            ne1->l = epTre(newStr.substr(0, m));
            ne1->r = epTre(newStr.substr(m+1, n-m-1));
            return ne1;
        }
        
        string cleanS(string s)
        {
            stack<int> stacko;
            vector<int> vicko;
            int n = s.length();
            for (int i = 0; i < n - 1; i++)
            {
                char currElement = s[i];
                if (currElement == '(')
                {
                    stacko.push(i);
                }
                else if (currElement == ')')
                {
                    stacko.pop();
                }
            }
            if (stacko.size() == 1 && stacko.top() == 0)
            {
                return s.substr(1, n-2);
            }
            return s;
        }
        
        int prece(string s, vector<int> vicko)
        {
            for (char ope : {'-', '+', '*', '/'})
            {
                for (int i = 0; i < vicko.size(); i++)
                {
                    if (s[vicko.at(i)] == ope)
                    {
                        return i;
                    }
                }
            }
        }
        
        void rExTreTra()
        {
            exTreTra(root);
        }
        
        void exTreTra(Node* root)
        {
            if (!root)
            {
                return;
            }
            cout << "(";
            exTreTra(root->l);
            cout << root->d;
            exTreTra(root->r);
            cout << ")";
        }
        
        int hei(Node* root)
        {
            if (root == nullptr)
            {
                return 0;
            }
            return 1 + max(hei(root->l), hei(root->r));
        }
        
        int getcolmun(int h)
        {
            if (h == 1)
            {
                return 1;
            }
            return getcolmun(h - 1) + getcolmun(h - 1) + 1;
        }
        
        void printTree(string **M, Node *root, int col, int row, int height)
        {
            if (root == NULL)
            {
                return;
            }
            M[row][col] = root->d;
            printTree(M, root->l, col - pow(2, height - 2), row + 1, height - 1);
            printTree(M, root->r, col + pow(2, height - 2), row + 1, height - 1);
        }
        
        void pExTre()
        {
            int ho = hei(root);
            int coll = getcolmun(ho);
            string **t = new string*[ho];
            for (int i = 0; i < ho; i++)
            {
                t[i] = new string[coll];
            }
            printTree(t, root, coll / 2, 0, ho);
            for (int i = 0; i < ho; i++)
            {
                for (int j = 0; j < coll; j++)
                {
                    if (t[i][j] == "")
                    {
                        cout << " ";
                    }
                    else
                    {
                        cout << t[i][j];
                    }
                }
                cout << endl;
            }
        }
};


int main()
{
    Tree* tr = new Tree();
    string x = "(((4+1)*(1-0))/((2+2)+((4-2)-2))*6)";
    tr->rnExTre(x);
    cout << "Expression tree:" << endl;
    tr->pExTre();
    cout << endl;
    cout << "Value: " << tr->rCalcRes() << endl;
    cout << endl;
    return 0;
}
