#include <iostream>
using namespace std;
class node
{
public:
    string word;
    string meaning;
    node *left, *right;
};
class BST
{
public:
    node *root;
    BST()
    {
        root = NULL;
    }

    void CreateTree(node *&root)
    {
        node *temp = new node;
        cout << "Enter root node of tree (data):- " << endl;
        cin >> temp->word;
        cout << "Enter the Meaning :" << endl;
        cin >> temp->meaning;
        temp->left = NULL;
        temp->right = NULL;
        if (root == NULL)
        {
            root = temp;
        }
        else
        {
            InsertNode(root, temp);
        }
    }

    void InsertNode(node *root, node *temp)
    {
        if (root == NULL)
        {
            cout << "Tree is empty...." << endl;
        }
        else if (root->word > temp->word)
        {
            if (root->left == NULL)
            {
                root->left = temp;
            }
            else
            {
                InsertNode(root->left, temp);
            }
        }
        else
        {
            if (root->right == NULL)
            {
                root->right = temp;
            }
            else
            {
                InsertNode(root->right, temp);
            }
        }
    }
    void InorderDisplay(node *root)
    {
        if (root == NULL)
        {
            return;
        }
        else
        {
            InorderDisplay(root->left);
            cout << root->word << "->";
            cout << root->meaning << endl;
            InorderDisplay(root->right);
        }
    }
    void Search(node *root, string key)
    {
        if (root == NULL)
        {
            cout << "Key is not present in Tree" << endl;
            return;
        }
        if (root->word > key)
        {
            Search(root->left, key);
        }
        else if (root->word < key)
        {
            Search(root->right, key);
        }
        else // (root->word == key)
        {
            cout << "Key is present in tree" << endl;
            return;
        }
    }
    node *modify(node *root, string val, string mean)
    {
        if (root == NULL)
        {
            cout << "tree is empty" << endl;
            return NULL;
        }
        if (root->word > val)
        {
            root->left = modify(root->left, val, mean);
        }
        else if (root->word < val)
        {
            root->right = modify(root->right, val, mean);
        }
        else
        {
            root->meaning = mean;
        }
        return root;
    }
    node *deletenode(node *root, string value)
    {
        if (root == NULL)
        {
            return NULL;
        }
        else if (value < root->word)
        {
            root->left = deletenode(root->left, value);
        }
        else if (value > root->word)
        {
            root->right = deletenode(root->right, value);
        }
        else
        {
            if (root->left == NULL && root->right == NULL)
            {
                delete root;
                return NULL;
            }
            else if (root->right == NULL)
            {
                node *temp = root;
                root = root->left;
                delete temp;
                return root;
            }
            else if (root->left == NULL)
            {
                node *temp = root;
                root = root->right;
                delete temp;
                return root;
            }
            else
            {
                node *temp = findmax(root->left);
                root->word = temp->word;
                root->left = deletenode(root->left, temp->word);
            }
        }
        return root;
    }

    node *findmax(node *root)
    {
        if (root == NULL)
            return NULL;
        else if (root->right == NULL)
            return root;
        else
            return findmax(root->right);
    }
};
int main()
{
    BST b;
    int ch;
    string key;
    bool ch1 = true;
    string mean;
    string val, value;
    while (ch1)
    {
        cout << "1.Create Tree" << endl;
        cout << "2.Insert Element." << endl;
        cout << "3.Display Tree." << endl;
        cout << "4.Search the element" << endl;
        cout << "5.modify" << endl;
        cout << "6.Delete" << endl;
        cout << "Enter your choice : " << endl;
        cin >> ch;
        switch (ch)
        {
        case 1:
            b.CreateTree(b.root);
            cout << "Tree created successfully....." << endl;
            break;
        case 2:
            node *temp;
            temp = new node;
            cout << "Enter new node data:- ";
            cin >> temp->word;
            cout << "Enter The Meaning :" << endl;
            cin >> temp->meaning;
            temp->left = NULL;
            temp->right = NULL;
            b.InsertNode(b.root, temp);
            cout << "Node added successfully....." << endl;
            break;
        case 3:
            cout << "node in tree are - " << endl;
            b.InorderDisplay(b.root);
            break;
        case 4:
            cout << "Enter the key want to find:- ";
            cin >> key;
            b.Search(b.root, key);
            break;
        case 5:
            cout << " Enter the data to modify meaning" << endl;
            cin >> val;
            cout << "Enter meaning " << endl;
            cin >> mean;
            b.modify(b.root, val, mean);
            break;
        case 6:
            cout << "Enter the data to delete :" << endl;
            cin >> value;
            b.deletenode(b.root, value);
            cout << "node deleted ..." << endl;
            break;

        default:
            ch1 = false;
            break;
        }
    }
    return 0;
}
