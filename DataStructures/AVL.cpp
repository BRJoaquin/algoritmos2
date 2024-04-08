#ifndef AVL_TREE
#define AVL_TREE

// based on: https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
template <class T>
class AVL
{
private:
    class AVLNode
    {
    public:
        T element;
        AVLNode *left;
        AVLNode *right;
        int height;
        AVLNode(T element) : element(element), left(NULL), right(NULL), height(1) {}
    };

    AVLNode *root; // root of the tree

    // A utility function to get the height of the tree.
    // In case of an empty tree, it returns 0.
    int height(AVLNode *node)
    {
        if (node == NULL)
        {
            return 0;
        }
        return node->height;
    }

    // A utility function to right
    // rotate subtree rooted with y
    AVLNode *rightRotate(AVLNode *B)
    {
        AVLNode *A = B->left;
        AVLNode *T2 = A->right;

        // Perform rotation
        A->right = B;
        B->left = T2;

        // Update heights
        B->height = std::max(height(B->left),
                             height(B->right)) +
                    1;
        A->height = std::max(height(A->left),
                             height(A->right)) +
                    1;

        // Return new root
        return A;
    }

    // A utility function to left
    // rotate subtree rooted with x
    AVLNode *leftRotate(AVLNode *A)
    {
        AVLNode *B = A->right;
        AVLNode *T2 = B->left;

        // Perform rotation
        B->left = A;
        A->right = T2;

        // Update heights
        A->height = std::max(height(A->left),
                             height(A->right)) +
                    1;
        B->height = std::max(height(B->left),
                             height(B->right)) +
                    1;

        // Return new root
        return B;
    }

    // Get Balance factor of node N
    int getBalance(AVLNode *node)
    {
        if (node == NULL)
            return 0;
        return height(node->right) - height(node->left);
    }

    // Recursive function to insert a element
    // in the subtree rooted with node and
    // returns the new root of the subtree.
    AVLNode *insert(AVLNode *node, T element)
    {
        /* 1. Perform the normal BST insertion */
        if (node == NULL)
            return new AVLNode(element);
        if (element < node->element)
            node->left = insert(node->left, element);
        else if (element > node->element)
            node->right = insert(node->right, element);
        else // Equal elements are not allowed in BST
            return node;

        /* 2. Update height of this ancestor AVLnode */
        node->height = 1 + std::max(height(node->left),
                                    height(node->right));

        /* 3. Get the balance factor of this ancestor
            node to check whether this node became
            unbalanced */
        int balance = getBalance(node);

        // If this node becomes unbalanced, then
        // there are 4 cases

        // Left Left Case
        if (balance < -1 && element < node->left->element)
            return rightRotate(node);

        // Right Right Case
        if (balance > 1 && element > node->right->element)
            return leftRotate(node);

        // Left Right Case
        if (balance < -1 && element > node->left->element)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance > 1 && element < node->right->element)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        /* return the (unchanged) node pointer */
        return node;
    }
    void inOrder(AVLNode *node, void (*each)(T))
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
    AVL() : root(NULL) {}

    void insert(T element)
    {
        root = insert(root, element);
    }

    // TODO: implement this
    // void remove(T element)
    // {
    //     root = remove(root, element);
    // }

    bool contains(T element)
    {
        return contains(root, element);
    }

    void inOrder(void (*each)(T))
    {
        inOrder(root, each);
    }
};

#endif