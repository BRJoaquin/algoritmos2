#ifndef BST_TREE
#define BST_TREE

#include <cassert>
template <class T>
class BST
{
private:
    class BSTNode
    {
    public:
        // The element stored in the node
        T element;

        // The subtree rooted at the left child
        BSTNode *left;

        // Rhe subtree rooted at the right child
        BSTNode *right;

        // Constructor
        BSTNode(T element) : element(element), left(NULL), right(NULL) {}

        // Destructor: Once you delete a node, you need to delete all the nodes in the subtrees
        ~BSTNode()
        {
            delete left;
            delete right;
        }
    };

    // The root of the BST
    BSTNode *root;

    
    void insert(T element, BSTNode *&node)
    {
        if (node == NULL)
        {
            node = new BSTNode(element);
        }
        else if (element < node->element)
        {
            insert(element, node->left);
        }
        else if (element > node->element)
        {
            insert(element, node->right);
        }
    }

    T min(BSTNode *node)
    {
        assert(!this->isEmpty());
        if (node->left == NULL)
        {
            return node->element;
        }
        return min(node->left);
    }

    T max(BSTNode *node)
    {
        assert(!this->isEmpty());
        if (node->right == NULL)
        {
            return node->element;
        }
        return max(node->right);
    }

    void remove(T element, BSTNode *&node)
    {
        if (node == NULL)
        {
            return;
        }
        else if (element < node->element)
        {
            remove(element, node->left);
        }
        else if (element > node->element)
        {
            remove(element, node->right);
        }
        else
        {
            if (node->left == NULL && node->right == NULL)
            {
                delete node;
                node = NULL;
            }
            else if (node->left == NULL)
            {
                BSTNode *temp = node;
                node = node->right;
                delete temp;
            }
            else if (node->right == NULL)
            {
                BSTNode *temp = node;
                node = node->left;
                delete temp;
            }
            else
            {
                T min = min(node->right);
                node->element = min;
                remove(min, node->right);
            }
        }
    }

    bool existe(BSTNode *node, T buscado) {
        if(node == NULL) {
            return false;
        }

        BSTNode* nodeIzq = node->left;
        BSTNode* nodeDer = node->right;

        bool existeIzq = existe(nodeIzq, buscado);
        bool existeDer = existe(nodeDer, buscado);

        return existeIzq || existeDer || node->element == buscado;
    }

    bool existe(BSTNode *node, T buscado) {
        if(node == NULL) {
            return false;
        }
        if(node->element == buscado) {
            return true;
        }


        BSTNode* nodeIzq = node->left;
        BSTNode* nodeDer = node->right;

        if(node->element < buscado) {
            return existe(nodeIzq, buscado);
        } else {
            return existe(nodeDer, buscado);
        }
    }

    void inOrder(BSTNode *node, void (*each)(T))
    {
        if (node == NULL)
        {
            return;
        }
        inOrder(node->left, each);
        each(node->element);
        inOrder(node->right, each);
    }

public:
    // Default constructor, creates an empty tree
    BST() : root(NULL) {}

    // Performs an insertion into the BST (disregarding duplicates)
    void insert(T element)
    {
        this->insert(element, root);
    }

    // Performs a removal from the BST (if it exists)
    void remove(T element)
    {
        this->remove(element, root);
    }

    // Returns true if the BST is empty, false otherwise
    void isEmpty()
    {
        return root == NULL;
    }

    // Takes a function pointer and applies it to every element in the BST (in order)
    void inOrder(void (*each)(T))
    {
        inOrder(root, each);
    }

    ~BST()
    {
        delete root;
    }
};

#endif