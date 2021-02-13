#include <iostream>
#include <iomanip>
template <typename dataType>
class Comparator
{
public:
    bool operator()(dataType object1, dataType object2)
    {
        if (object1 < object2)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

template <typename keyType, typename dataType, template <class> class comparator = Comparator>
class map
{
private:
    // color, true = red, false = black
    struct Node
    {
        Node(keyType key, dataType data, Node *parent)
        {
            right = nullptr;
            left = nullptr;
            this->parent = parent;
            Data = std::make_pair(key, data);
            color = true;
        }
        Node *right;
        Node *left;
        Node *parent;
        bool color;
        std::pair<keyType, dataType> Data;
    };

    Node *root;

    void insertFix(Node *node)
    {
        Node *temp;
        if (root == node)
        {
            node->color = false;
            return;
        }
        while (node->parent != nullptr && node->parent->color)
        {
            Node *temp1 = node->parent->parent;
            if (temp1->left == node->parent)
            {
                if (temp1->right != nullptr)
                {
                    temp = temp1->right;
                    if (temp->color)
                    {
                        node->parent->color = false;
                        temp->color = false;
                        temp1->color = true;
                        node = temp1;
                    }
                }
                else
                {
                    if (node->parent->right == node)
                    {
                        node = node->parent;
                        rotateLeft(node);
                    }
                    node->parent->color = false;
                    temp1->color = true;
                    rotateRight(temp1);
                }
            }
            else
            {
                if (temp1->left != NULL)
                {
                    temp = temp1->left;
                    if (temp->color)
                    {
                        node->parent->color = false;
                        temp->color = false;
                        temp1->color = true;
                        node = temp1;
                    }
                }
                else
                {
                    if (node->parent->left == node)
                    {
                        node = node->parent;
                        rotateRight(node);
                    }
                    node->parent->color = false;
                    temp1->color = true;
                    rotateLeft(temp1);
                }
            }
            root->color = false;
        }
    }

    void insert(keyType key, dataType data, Node *node)
    {
        Node *x = nullptr;
        if (key <= node->Data.first)
        {
            if (node->left != nullptr)
            {
                insert(key, data, node->left);
            }
            else
            {
                node->left = new Node(key, data, node);
                x = node->left;
            }
        }
        else
        {
            if (node->right != nullptr)
            {
                insert(key, data, node->right);
            }
            else
            {
                node->right = new Node(key, data, node);
                x = node->right;
            }
        }
        if (x != nullptr)
        {
            insertFix(x);
        }
    }

    void clear(Node *node)
    {
        if (node != nullptr)
        {
            clear(node->left);
            clear(node->right);
            delete node;
            node = nullptr;
        }
    }

    Node *recursiveCopy(Node *origNode, Node *copyParent)
    {
        if (origNode == nullptr)
        {
            return nullptr;
        }
        Node *copy = new Node(origNode->Data.first, origNode->Data.second, copyParent);
        copy->color = origNode->color;
        copy->left = recursiveCopy(origNode->left, copy);
        copy->right = recursiveCopy(origNode->right, copy);
        return copy;
    }

    Node *recursiveSearch(keyType key, Node *node)
    {
        if (node != nullptr)
        {
            if (key == node->Data.first)
            {
                return node;
            }
            if (key <= node->Data.first)
            {
                return recursiveSearch(key, node->left);
            }
            else
            {
                return recursiveSearch(key, node->right);
            }
        }
        else
        {
            return nullptr;
        }
    }

    void rotateLeft(Node *node)
    {
        Node *select = node->right;
        select->parent = node->parent;
        if (node->parent != nullptr)
        {
            if (node->parent->left == node)
            {
                node->parent->left = select;
            }
            else
            {
                node->parent->right = select;
            }
        }
        node->right = select->left;
        if (select->left != nullptr)
        {
            select->left->parent = node;
        }
        node->parent = select;
        select->left = node;
    }

    void rotateRight(Node *node)
    {
        Node *select = node->left;
        select->parent = node->parent;
        if (node->parent != nullptr)
        {
            if (node->parent->left == node)
            {
                node->parent->left = select;
            }
            else
            {
                node->parent->right = select;
            }
        }
        node->left = select->right;
        if (select->right != nullptr)
        {
            select->right->parent = node;
        }
        node->parent = select;
        select->right = node;
    }

    void postorder(Node *p, int indent = 0)
    {
        if (p != NULL)
        {
            if (p->right)
            {
                postorder(p->right, indent + 4);
            }
            if (indent)
            {
                std::cout << std::setw(indent) << ' ';
            }
            if (p->right)
                std::cout << "  /\n"
                          << std::setw(indent) << ' ';
            std::cout << p->Data.first << (p->color ? "R\n " : "B\n ");
            if (p->left)
            {
                std::cout << std::setw(indent) << ' ' << "  \\\n";
                postorder(p->left, indent + 4);
            }
        }
    }

public:
    map()
    {
        root = nullptr;
    }

    map(map<keyType, dataType, comparator> const &origMap)
    {
        root = new Node(origMap.root->Data.first, origMap.root->Data.second, nullptr);
        root->color = origMap.root->color;
        root->left = recursiveCopy(origMap.root->left, root);
        root->right = recursiveCopy(origMap.root->right, root);
    }

    ~map()
    {
        clear(root);
        root = nullptr;
    }

    void clear()
    {
        clear(root);
        root = nullptr;
    }

    map<keyType, dataType, comparator> &operator=(map<keyType, dataType, comparator> const &origMap)
    {
        if (this != &origMap)
        {
            if (root != nullptr)
            {
                clear(root);
            }
            root = new Node(origMap.root->Data.first, origMap.root->Data.second, nullptr);
            root->color = origMap.root->color;
            root->left = recursiveCopy(origMap.root->left, root);
            root->right = recursiveCopy(origMap.root->right, root);
        }
        return *this;
    }

    bool isEmpety()
    {
        return root == nullptr;
    }

    dataType &operator[](keyType const &index)
    {
        if(recursiveSearch(index, root) != nullptr){
            return recursiveSearch(index, root)->Data.second;
        } else {
            throw std::runtime_error("Error: No node with such a key was found\n");
        }
        
    };

    bool search(keyType const &index)
    {
        return recursiveSearch(index, root) != nullptr;
    }

    void insert(keyType key, dataType data)
    {
        if (root != nullptr)
        {
            insert(key, data, root);
        }
        else
        {
            root = new Node(key, data, nullptr);
            root->color = false;
        }
    }

    void print()
    {
        postorder(root);
    }
};