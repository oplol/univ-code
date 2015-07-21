#ifndef H_AVLTree
#define H_AVLTree
#include <iostream>
using namespace std;

//Definition of the AVL node
template <class elemT>
struct AVLNode
{
	elemT info;
	int bfactor;  //balance factor
	AVLNode<elemT> *llink;
	AVLNode<elemT> *rlink;
};

//Definition of the class
template <class elemT>
class AVLTreeType
{
public:
	void inorderTraversal() const;
      //Function to do an inorder traversal of the AVL tree.
    void preorderTraversal() const;
      //Function to do a preorder traversal of the AVL tree.
    void postorderTraversal() const;
      //Function to do a postorder traversal of the AVL tree.

	void inorderTraversal(void (*visit)(elemT&) );
	  //Function with function parameter to do an inorder traversal of the AVL tree.
    void preorderTraversal(void (*visit)(elemT&) );
	  //Function with function parameter to do a preorder traversal of the AVL tree.
    void postorderTraversal(void (*visit)(elemT&) );
	  //Function with function parameter to do a postorder traversal of the AVL tree.

	void rnl_inorderTraversal(void (*visit)(elemT&, int) );
	  //Function with function parameter to hierarchially do an in order traversal of the AVL tree.

	int treeHeight() const;
      //Returns the height of the AVL tree.
    int treeNodeCount() const;
      //Returns the number of nodes in the AVL tree.
    int treeLeavesCount() const;
      //Returns the number of leaves in the AVL tree.
	void destroyTree();
      //Deallocates the memory space occupied by the AVL tree.
      //Postcondition: root = NULL;

	void insert(const elemT &newItem);
	  //Function to insert newItem in the AVL tree
	AVLTreeType();    
	  //default constructor; set root to NULL

private:
	AVLNode<elemT>* root;

    void inorder(AVLNode<elemT> *p) const;
      //Function to do an inorder traversal of the AVL
      //tree to which p points.  
    void preorder(AVLNode<elemT> *p) const;
      //Function to do a preorder traversal of the AVL
      //tree to which p points.  
    void postorder(AVLNode<elemT> *p) const;
      //Function to do a postorder traversal of the AVL
      //tree to which p points.

	void inorder(AVLNode<elemT> *p, void (*visit)(elemT&) );
	  //Function with function parameter to do an inorder traversal of the AVL
      //tree to which p points.
    void preorder(AVLNode<elemT> *p, void (*visit)(elemT&) );
	  //Function with function parameter to do a preorder traversal of the AVL
      //tree to which p points.  
    void postorder(AVLNode<elemT> *p, void (*visit)(elemT&) );
	  //Function with function parameter to do a postorder traversal of the AVL
      //tree to which p points.

	void rnl_inorder(AVLNode<elemT> *p, void (visit)(elemT&, int), int );
	  //Function with function parameter to hierarchially do an in order traversal of the AVL
	  //tree to which p points.

	int height(AVLNode<elemT> *p) const;
      //Function to return the height of the AVL tree
      //to which p points. 
    int max(int x, int y) const;
      //Returns the larger of x and y.
    int nodeCount(AVLNode<elemT> *p) const;
      //Function to return the number of nodes in the AVL 
      //tree to which p points 
    int leavesCount(AVLNode<elemT> *p) const;
      //Function to return the number of leaves in the AVL 
      //tree to which p points 

	void destroy(AVLNode<elemT>* &p);
      //Function to destroy the AVL tree to which p points. 
      //Postcondition: p = NULL

	void rotateToLeft(AVLNode<elemT>* &root);
	  //Function to rotate to left
    void rotateToRight(AVLNode<elemT>* &root);
	  //Function to rotate to right
    void balanceFromLeft(AVLNode<elemT>* &root);
	  //Function to balance from left
    void balanceFromRight(AVLNode<elemT>* &root);
	  //Function to balance from right
    void insertIntoAVL(AVLNode<elemT>* &root,
                       AVLNode<elemT>  *newNode,
                       bool& isTaller);
	  //Fucntion to insert an item

};


//Definition of member functions

template <class elemT>
AVLTreeType<elemT>::AVLTreeType()
{
    root = NULL;
}

template <class elemT>
void AVLTreeType<elemT>::inorderTraversal() const
{
    inorder(root);
}

template <class elemT>
void AVLTreeType<elemT>::preorderTraversal() const
{
    preorder(root);
}

template <class elemT>
void AVLTreeType<elemT>::postorderTraversal() const
{
    postorder(root);
}

template <class elemT>
int AVLTreeType<elemT>::treeHeight() const
{
    return height(root);
}

template <class elemT>
int AVLTreeType<elemT>::treeNodeCount() const
{
    return nodeCount(root);
}

template <class elemT>
int AVLTreeType<elemT>::treeLeavesCount() const
{
    return leavesCount(root);
}

template <class elemT>
void AVLTreeType<elemT>::destroyTree()
{
    destroy(root);
}

template <class elemT>
void AVLTreeType<elemT>::insert(const elemT &newItem)
{
	bool isTaller =  false;
	AVLNode<elemT> *newNode;

	newNode = new AVLNode<elemT>;
	newNode->info = newItem;
	newNode->bfactor = 0;
	newNode->llink = NULL;
	newNode->rlink = NULL;

	insertIntoAVL(root, newNode, isTaller);
}

template <class elemT>
void AVLTreeType<elemT>::inorder(AVLNode<elemT> *p) const
{
    if (p != NULL)
    {
        inorder(p->llink);
        cout << p->info << " ";
        inorder(p->rlink);
    }
}

template <class elemT>
void AVLTreeType<elemT>::preorder(AVLNode<elemT> *p) const
{
	if (p != NULL)
	{
		cout<<p->info<<" ";
		preorder(p->llink);
		preorder(p->rlink);
	}
}

template <class elemT>
void AVLTreeType<elemT>::postorder(AVLNode<elemT> *p) const
{
    if (p != NULL)
    {
        postorder(p->llink);
        postorder(p->rlink);
        cout << p->info << " ";
    }		
}

template <class elemT>
int AVLTreeType<elemT>::height(AVLNode<elemT> *p) const
{
    if (p == NULL)
        return 0;
    else
        return 1 + max(height(p->llink), height(p->rlink));
}

template <class elemT>
int AVLTreeType<elemT>::max(int x, int y) const
{
    if (x >= y)
        return x;
    else
        return y;
}

template <class elemT>
int AVLTreeType<elemT>::nodeCount(AVLNode<elemT> *p) const
{
    if (p == NULL)
		return 0;
	else 
		return 1 + nodeCount(p -> llink) + nodeCount(p -> rlink);
}

template <class elemT>
int AVLTreeType<elemT>::leavesCount(AVLNode<elemT> *p) const
{
    if (p == NULL)
		return 0;
	else 
		if (p -> llink == NULL && p -> rlink == NULL)
			return 1;
		else
			return leavesCount(p -> llink) + leavesCount(p -> rlink);
}

template <class elemT>
void  AVLTreeType<elemT>::destroy(AVLNode<elemT>* &p)
{
    if (p != NULL)
    {
        destroy(p->llink);
        destroy(p->rlink);
        delete p;
        p = NULL;
    }
}

template <class elemT>
void  AVLTreeType<elemT>::rotateToLeft(AVLNode<elemT>* &root)
{
     AVLNode<elemT> *p; //pointer to the root of the
                           //right subtree of root
     if(root == NULL)
        cerr<<"Error in the tree."<<endl;
     else
        if(root->rlink == NULL)
           cerr<<"Error in the tree:"
               <<" No right subtree to rotate."<<endl;
        else
        {   p = root->rlink;
            root->rlink = p->llink; //the left subtree of p 
                             //becomes the right subtree of root
            p->llink = root; 
            root = p;	//make p the new root node
        }
}//end rotateLeft

template <class elemT>
void AVLTreeType<elemT>::rotateToRight(AVLNode<elemT>* &root)
{
	AVLNode<elemT> *p;  //pointer to the root of 
	                    //the left subtree of root
	if (root == NULL)
		cerr << "Error in the tree" << endl;
	else if (root->llink == NULL)
		cerr << "Error in the tree:"
		     << " No left subtree to rotate." << endl;
	else
	{
		p = root->llink;
		root->llink = p->rlink; //the right subtree of p becomes
		                        //the left subtree of root
		p->rlink = root;
		root = p;   //make p the new root node
	}
}//end rotateRight

template <class elemT>
void AVLTreeType<elemT>::balanceFromLeft(AVLNode<elemT>* &root)
{
	AVLNode<elemT> *p;
	AVLNode<elemT> *w;

	p = root->llink;    //p points to the left subtree of root

	switch (p->bfactor)
	{
		case -1:
			root->bfactor = 0;
			p->bfactor = 0;
			rotateToRight(root);
			break;
		case 0:
			cerr << "Error: Cannot balance from the left." << endl;
			break;
		case 1:
			w = p->rlink;
			switch (w->bfactor)  //adjust the balance factors
			{
			case -1:
				root->bfactor = 1;
				p->bfactor = 0;
				break;
			case 0:
				root->bfactor = 0;
				p->bfactor = 0;
				break;
			case 1:
				root->bfactor = 0;
				p->bfactor = -1;
			}//end switch

			w->bfactor = 0;
			rotateToLeft(p);
			root->llink = p;
			rotateToRight(root);
	}//end switch
}//end balanceFromLeft

template <class elemT>
void AVLTreeType<elemT>::balanceFromRight(AVLNode<elemT>* &root)
{
    AVLNode<elemT> *p;
	AVLNode<elemT> *w;

	p = root->rlink;    //p points to the right subtree of root

	switch (p->bfactor)
	{
	case -1:
		w = p->llink;
		switch (w->bfactor) //adjust the balance factors
		{
		case -1:
			root->bfactor = 0;
			p->bfactor = 1;
			break;
		case 0:
			root->bfactor = 0;
			p->bfactor = 0;
			break;
		case 1:
			root->bfactor = -1;
			p->bfactor = 0;
		}//end switch

		w->bfactor = 0;
		rotateToRight(p);
		root->rlink = p;
		rotateToLeft(root);
		break;

	case 0:
		cerr << "Error: Cannnot balance from the right." << endl;
		break;

	case 1:
		root->bfactor = 0;
		p->bfactor = 0;
		rotateToLeft(root);
	}//end switch
}//end balanceFromRight

template<class elemT>
void AVLTreeType<elemT>::insertIntoAVL(AVLNode<elemT>* &root, 
			                          AVLNode<elemT> *newNode, 
									  bool& isTaller)
{
    if(root == NULL)
    {
       root = newNode;
       isTaller = true;
    }
    else
       if(root->info == newNode->info)
          cerr<<"No duplicates are allowed."<<endl;
       else
          if(root->info > newNode->info) //newItem goes in 
                                         //the left subtree
          {
             insertIntoAVL(root->llink, newNode, isTaller);

             if(isTaller)             //after insertion, the 
                                      //subtree grew in height
                switch(root->bfactor)
                {
                case -1: balanceFromLeft(root);
                         isTaller = false;
                         break;
                case 0:  root->bfactor = -1;
                         isTaller = true;
                         break;
                case 1:  root->bfactor = 0;
                         isTaller = false;
                }//end switch
          }//end if
          else                     //newNode goes in the right subtree
          {
             insertIntoAVL(root->rlink, newNode, isTaller);

             if(isTaller)              //after insertion, the 
                                       //subtree grew in height
                switch(root->bfactor)
                {
                case -1: root->bfactor = 0;
                         isTaller = false;
                         break;
                case 0:  root->bfactor = 1;
                         isTaller = true;
                         break;
                case 1:  balanceFromRight(root);
                         isTaller = false;
                }//end switch
          }//end else
}//end insertIntoAVL

template <class elemT>
void AVLTreeType<elemT>::inorderTraversal(void (*visit)(elemT& item) )
{
	inorder(root, *visit);
}

template <class elemT>
void AVLTreeType<elemT>::preorderTraversal(void (*visit)(elemT& item) )
{
	preorder(root, *visit);
}

template <class elemT>
void AVLTreeType<elemT>::postorderTraversal(void (*visit)(elemT& item) )
{
	postorder(root, *visit);
}

template <class elemT>
void AVLTreeType<elemT>::inorder(AVLNode<elemT>* p, void (*visit) (elemT& item) )
{
	if (p != NULL)
	{
		inorder(p->llink, *visit);
		(*visit)(p->info);
		inorder(p->rlink, *visit);
	}
}

template <class elemT>
void AVLTreeType<elemT>::preorder(AVLNode<elemT>* p, void (*visit) (elemT& item) )
{
	if (p != NULL)
	{
	    (*visit)(p->info);
		preorder(p->llink, *visit);
		preorder(p->rlink, *visit);
	}
}

template <class elemT>
void AVLTreeType<elemT>::postorder(AVLNode<elemT>* p, void (*visit) (elemT& item) )
{
	if (p != NULL)
	{
		postorder(p->llink, *visit);
		postorder(p->rlink, *visit);
	    (*visit)(p->info);
	}
}

template <class elemT>
void AVLTreeType<elemT>::rnl_inorderTraversal(void (*visit) (elemT& item, int num) )
{
	rnl_inorder(root, *visit, 0);
}

template <class elemT>
void AVLTreeType<elemT>::rnl_inorder(AVLNode<elemT>* p, void (*visit)(elemT& item, int num), int lvl = 0)
{
    if (p != NULL)
	{
		lvl++;
		rnl_inorder(p->rlink, *visit, lvl);
	    (*visit)(p->info, lvl - 1);
		rnl_inorder(p->llink, *visit, lvl--);
	}
}

#endif


