#include "rb.h"
using ptr = RedBlackTree::ptr;

RedBlackTree::RedBlackTree(){}

const ptr RedBlackTree::getRoot() const
{ 
	return root; 
}

ptr RedBlackTree::insert(int data)
{
	ptr newnodePtr = new node(data);
	if (!root) {
		root = newnodePtr;
		root->color = 0; // set root color as black
		return newnodePtr;
	}
	insert(root, newnodePtr);
	return newnodePtr;
}

// auxiliary function to perform RBT insertion of a node
// you may assume start is not nullptr
void RedBlackTree::insert(ptr start, ptr newnodePtr)
{
	// choose direction
	node* pre = newnodePtr;
	node* par = start;
	while(start!=nullptr){
		par=start;
		if(pre->data>start->data) start=start->right;
		else start=start->left;
	}
	if(par->data>pre->data) par->left=pre;
	else par->right=pre;
	pre->parent = par;
	if(par->color == 0) return;
	// recurse down the tree
	fixup(pre);
	return;
}

// Credits to Adrian Schneider
void RedBlackTree::printRBT(ptr start, const std::string& prefix, bool isLeftChild) const
{
	if (!start) return;

	std::cout << prefix;
	std::cout << (isLeftChild ? "|--" : "|__" );
	// print the value of the node
	std::cout << start->data << "(" << start->color << ")" << std::endl;
	// enter the next tree level - left and right branch
	printRBT(start->left, prefix + (isLeftChild ? "│   " : "    "), true);
	printRBT(start->right, prefix + (isLeftChild ? "│   " : "    "), false);
}

// Function performing right rotation
// of the passed node
void RedBlackTree::rightrotate(ptr loc)
{
	node* par = loc->parent;
	node* t2 = loc->right;
	node* gpar=par->parent;

	bool left=false;
	if(par->parent->left==par) left=true;

	loc->parent=gpar;
	loc->right=par;
	par->parent=loc;
	par->left=t2;
	if(t2!=nullptr) t2->parent=par;	

	if(gpar==nullptr){
		root=loc;
		return;
	}


	if(left) gpar->left=loc;
	else gpar->right=loc;

}

// Function performing left rotation
// of the passed node
void RedBlackTree::leftrotate(ptr loc)
{
	node* par = loc->parent;
	node* t1 = loc->left;
	node* gpar=par->parent;

	bool left=false;
	if(par->parent->left==par) left=true;

	loc->parent=gpar;
	loc->left=par;
	par->parent=loc;
	par->right=t1;
	if(t1!=nullptr) t1->parent=par;	

	if(gpar==nullptr){
		root=loc;
		return;
	}

	if(left) gpar->left=loc;
	else gpar->right=loc;
}

// This function fixes violations
// caused by RBT insertion
void RedBlackTree::fixup(ptr loc)
{	
	bool left=true;
	if(loc==root) {loc->color = 0; return;}
	else if(loc->parent==root) {root->color = 0;return;}
	else if(loc->parent->color==0) {return;}
	node* unc = loc->parent->parent;
	if(unc->right == loc->parent) {unc=unc->left;left=true;}
	else {unc=unc->right;left=false;}
	if(unc!=nullptr && unc->color == 1){
		unc->color = 0;
		loc->parent->color = 0;
		loc->parent->parent->color = 1;
		fixup(loc->parent->parent);
	}
	else if(unc==nullptr){
		loc->parent->color = 0;
		loc->parent->parent->color = 1;
		fixup(loc->parent->parent);
	}
	else if(loc->parent->parent->right->right==loc || loc->parent->parent->left->left==loc){
		node* gpar=loc->parent->parent;
		if(left) leftrotate(loc->parent);
		else rightrotate(loc->parent);
		gpar->color=1;
		loc->parent->color=0;
	}
	else{
		node* par = loc->parent;
		if(left) rightrotate(loc);
		else leftrotate(loc);
		fixup(par);
	}

}

// Function to print inorder traversal
// of the fixated tree
void RedBlackTree::inorder(ptr start) const
{
	if (!start)
		return;
	
	inorder(start->left);
	std::cout << start->data << " ";
	inorder(start->right);
}