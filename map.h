#include <iostream>
#include <iomanip>
#include <vector>

#define red true
#define black false

template <typename dataType>
class Comparator
{
public:
    bool operator()(dataType object1, dataType object2)
    {
        return object1 < object2;
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
            color = red;
        }
        Node *right;
        Node *left;
        Node *parent;
        bool color;
        std::pair<keyType, dataType> Data;
    };

    Node *root;

    Node *getGrandParent(Node *node)
    {
        if ((node != nullptr) and (node->parent != nullptr))
            return node->parent->parent;
        return nullptr;
    }

    Node *getUncle(Node *node)
    {
        Node *grandParent = getGrandParent(node);

        if (grandParent == nullptr)
            return nullptr;
        if (node->parent == grandParent->left)
            return grandParent->right;
        if (node->parent == grandParent->right)
            return grandParent->left;
    }

    void swapColor(Node *nodeA, Node *nodeB)
    {
        bool tempColor = nodeA->color;
        nodeA->color = nodeB->color;
        nodeB->color = tempColor;
    }

    void insertFix(Node *node)
    {

        Node *parentNode = nullptr;
        Node *grandParentNode = nullptr;
        while ((node != root) and (node->color != black) and (node->parent->color == red))
        {

            parentNode = node->parent;
            grandParentNode = getGrandParent(node);
            if (parentNode == grandParentNode->left)
            {

                Node *uncleNode = grandParentNode->right;
                if (uncleNode != nullptr and uncleNode->color == red)
                {
                    grandParentNode->color = red;
                    parentNode->color = black;
                    uncleNode->color = black;
                    node = grandParentNode;
                }

                else
                {
                    if (node == parentNode->right)
                    {
                        rotateLeft(parentNode);

                        node = parentNode;
                        parentNode = node->parent;
                    }
                    rotateRight(grandParentNode);
                    swapColor(parentNode, grandParentNode);
                    node = parentNode;
                }
            }

            else
            {
                Node *uncleNode = grandParentNode->left;
                if ((uncleNode != nullptr) && (uncleNode->color == red))
                {
                    grandParentNode->color = red;
                    parentNode->color = black;
                    uncleNode->color = black;
                    node = grandParentNode;
                }
                else
                {
                    if (node == parentNode->left)
                    {
                        rotateRight(parentNode);
                        node = parentNode;
                        parentNode = node->parent;
                    }
                    rotateLeft(grandParentNode);
                    swapColor(parentNode, grandParentNode);
                    node = parentNode;
                }
            }
        }
        root->color = black;
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
        Node *pivot = node->right;
        node->right = pivot->left;
        if (pivot->left != nullptr)
        {
            pivot->left->parent = node;
        }
        pivot->parent = node->parent;
        if (node->parent == nullptr)
        {
            this->root = pivot;
        }
        else if (node == node->parent->left)
        {
            node->parent->left = pivot;
        }
        else
        {
            node->parent->right = pivot;
        }
        pivot->left = node;
        node->parent = pivot;
    }

    void rotateRight(Node *node)
    {
        Node *pivot = node->left;
        node->left = pivot->right;
        if (pivot->right != nullptr)
        {
            pivot->right->parent = node;
        }
        pivot->parent = node->parent;
        if (node->parent == nullptr)
        {
            this->root = pivot;
        }
        else if (node == node->parent->right)
        {
            node->parent->right = pivot;
        }
        else
        {
            node->parent->left = pivot;
        }
        pivot->right = node;
        node->parent = pivot;
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

    //test
    std::vector<Node *> searchSheets(Node *node, std::vector<Node *> sheets)
    {
        if (node != nullptr && node->left == nullptr and node->right == nullptr)
        {
            sheets.push_back(node);
        }
        /*
            Если узел красный, то оба его дочерних элемента черные. Красно-черное дерево
        */
        if (node != nullptr && node->color == red)
        {
            if (node->left != nullptr && node->left->color != black)
            {
                std::cout << "Red node found in red\n";
            }
            if (node->right != nullptr && node->right->color != black)
            {
                std::cout << "Red node found in red\n";
            }
        }
        if (node != nullptr)
        {
            sheets = searchSheets(node->left, sheets);
            sheets = searchSheets(node->right, sheets);
        }
        return sheets;
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
        if (recursiveSearch(index, root) != nullptr)
        {
            return recursiveSearch(index, root)->Data.second;
        }
        else
        {
            return root->Data.second;
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
            root->color = black;
        }
    }

    int test()
    {
        std::vector<Node *> sheets;
        sheets = searchSheets(root, sheets);
        unsigned long Black = 0;
        unsigned long tempBlack = 0;
        unsigned long minPath = 0;
        unsigned long maxPath = 0;
        for (auto i : sheets)
        {
            Black = 0;
            unsigned long Path = 0;
            while (i->parent != nullptr)
            {
                if (i->color == black)
                {
                    Black++;
                }
                Path++;
                i = i->parent;
            }
            /*
                Черная высота из красно-черного дерева этого число черных узлов в любом пути от корня до листьев,
                причем эта высота является постоянной для Красно-черного дерева
           */
            if (Black != tempBlack && tempBlack != 0)
            {
                std::cout << "Black = " << Black << " tempBlack = " << tempBlack << "\n";
                return 1;
            }
            tempBlack = Black;
            Path++;
            if (minPath == 0 || minPath > Path)
            {
                minPath = Path;
            }
            if (maxPath == 0 || maxPath < Path)
            {
                maxPath = Path;
            }
        }
        /*
            Путь от корня до самого дальнего листа не более чем в два раза 
            длиннее, чем путь от корня до ближайшего листа Красно-черного дерева
        */
        if ((double)maxPath / (double)minPath > 2.0)
        {
            std::cout << "Error\n";
            return 1;
        }
        std::cout << "All test Done\n";
        return 0;
    }

    void print()
    {
        postorder(root);
    }
};