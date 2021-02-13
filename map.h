#include <iostream>
template<typename dataType>
class Comparator{
    public: 
    bool operator()(dataType object1, dataType object2){
        if(object1 < object2){
            return true;
        } else {
            return false; 
        }
    }
};

template<typename keyType, typename dataType, template <class> class comparator = Comparator>
class map {
    private: 

    // color, true = red, false = black
    struct Node{
        Node(keyType const& key, dataType const& data, Node *parentPtr){
            right = nullptr; 
            left = nullptr; 
            this->parentPtr = parentPtr; 
            Data = std::make_pair(key, data); 
            color = true;
        }
        Node *right;
        Node *left; 
        Node *parentPtr;
        bool color;
        std::pair<keyType,dataType> Data;  
    }; 

    Node *root; 

    void insert(keyType const& key, dataType const& data, Node *node){
        if(key <= node->Data.first){
            if(node -> left != nullptr){
                insert(key, data, node->left);
            } else {
                node -> left = new Node(key, data, node); 
            } 
        } else {
            if(node->right != nullptr){
                insert(key, data, node -> right);
            } else {
                node->right = new Node(key, data, node); 
            } 
        }
    }

    void clear(Node *node){
        if(node != nullptr){
            clear(node->left);
            clear(node->right);
            delete node;
            node = nullptr;
        }
    }

    Node* recursiveCopy(Node *origNode, Node *copyParent) {
        if (origNode == nullptr) {
            return nullptr;
        }
        Node *copy = new Node(origNode->Data.first, origNode->Data.second, copyParent);
        copy->color = origNode->color; 
        copy->left = recursiveCopy(origNode->left, copy);
        copy->right = recursiveCopy(origNode->right, copy);
        return copy;
    }

    Node *recursiveSearch(keyType key, Node* node){
        if (node != nullptr){
            if (key == node->Data.first){
                return node;
            }
            if (key <= node->Data.first){
                return recursiveSearch(key, node->left);
            } else{
                return recursiveSearch(key, node->right);    
            }
        } else {
            return nullptr;
        }
    }

    public: 

    map(){
        root = nullptr; 
    }

    map(map<keyType,dataType,comparator> const& origMap){
        root = new Node(origMap.root->Data.first,origMap.root->Data.second, nullptr);
        root->color = origMap.root->color; 
        root->left = recursiveCopy(origMap.root->left, root); 
        root->right = recursiveCopy(origMap.root->right, root); 
    }

    ~map(){
        clear(root);
        root = nullptr; 
    }

    void clear(){
        clear(root);
        root = nullptr;
    }

    map<keyType,dataType,comparator>& operator=(map<keyType,dataType,comparator> const& origMap){
        if(root != nullptr){
            clear(root);
        }
        root = new Node(origMap.root->Data.first,origMap.root->Data.second, nullptr);
        root->color = origMap.root->color; 
        root->left = recursiveCopy(origMap.root->left, root); 
        root->right = recursiveCopy(origMap.root->right, root); 
        return *this; 
    }

    bool isEmpety(){
        return root == nullptr; 
    }

    dataType& operator[](keyType const& index){
        return recursiveSearch(index, root)->Data.second;
    };

    bool search(keyType const& index){
        return recursiveSearch(index, root) != nullptr;
    }

    void insert(keyType const& key, dataType const& data){
        if(root != nullptr){
            insert(key, data, root);
        } else {
            root = new Node(key, data, nullptr);
            root->color = false;
        }
    }
};

