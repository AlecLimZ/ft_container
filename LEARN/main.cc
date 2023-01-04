/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:31:37 by leng-chu          #+#    #+#             */
/*   Updated: 2023/01/04 17:31:47 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include <iostream>
#include <stdlib.h>
#include "myclass.hpp"
#include "iter.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <array>
#include <unordered_map>
#include <memory> // for unique make
#include <type_traits> // for enable_if
#include <numeric> // for std::reduce & accumulate()
#include <fstream>
#include <cstdlib>
#include <memory>
#include <string>
#include "../FT_C/vector.hpp"
#include <map>

using std::cout;
using std::endl;
using std::cin;
using std::vector;
//using std::iterator_traits;
using std::list;
using std::unordered_map;
using std::string;
using std::ostream;
using std::iterator_traits;
using std::array;
using std::ifstream;
using std::boolalpha;

template<class Comparable>
class RedBlackTree;

//Class that wraps a constant reference variable.
//Useful for return value from a container find method.

template<class Object>
class Cref
{
	public:
		Cref():obj(nullptr){}
		explicit Cref(const Object & x): obj(&x){}

		const Object & get() const
		{
			if (isNull())
				throw std::invalid_argument("it is NULL\n");
			else
				return (*obj);
		}
		bool isNull() const
		{
			return obj == nullptr;
		}

	private:
		const Object *obj;
};

template <class Comparable>
class RedBlackNode
{
	Comparable		element;
	RedBlackNode	*left;
	RedBlackNode	*right;
	int				color;

	RedBlackNode(const Comparable & theElement = Comparable(),
				RedBlackNode *lt = NULL,
				RedBlackNode *rt = NULL,
				int c = RedBlackTree<Comparable>::BLACK)
		: element(theElement), left(lt), right(rt), color(c){}

	friend class RedBlackTree<Comparable>;
};

template <class Comparable>
class RedBlackTree
{
	public:
		RedBlackTree(const Comparable & negInf);
		RedBlackTree(const RedBlackTree & rhs);
		~RedBlackTree();

		Cref<Comparable> find(const Comparable & x) const;
		bool	isEmpty() const;
		void	makeEmpty();
		void	insert(const Comparable & x);
		void	remove(const Comparable & x);

		enum { RED, BLACK };
		const RedBlackTree & operator=(const RedBlackTree & rhs);

		typedef RedBlackNode<Comparable> Node;

	private:
		Node *header;
		Node *nullNode;

		// Used in insert routine and its helpers
		Node	*current;
		Node	*parent;
		Node	*grand;
		Node	*great;

		// Usual recursive stuff
		void	reclaimMemory(Node *t) const;
		RedBlackNode<Comparable> * clone(Node *t) const;

		// Red-black tree manipulations
		void handleReorient(const Comparable & item);
		RedBlackNode<Comparable> *rotate(const Comparable & item,
										Node *parent) const;
		void	rotateWithLeftChild(Node * & k2) const
		{
			Node *k1 = k2->left;
			k2->left = k1->right;
			k1->right = k2;
			k2 = k1;
		}
		void	rotateWithRightChild(Node * & k1) const
		{
			Node *k2 = k1->right;
			k1->right = k2->left;
			k2->left = k1;
			k1 = k2;
		}
};

// Construct the tree
// negInf is a value less than or equal to all others.
template<class Comparable>
RedBlackTree<Comparable>::RedBlackTree(const Comparable & negInf)
{
	nullNode = new Node;
	nullNode->left = nullNode->right = nullNode;
	header = new Node(negInf);
	header->left = header->right = nullNode;
}

// Destroy the tree.
template <class Comparable>
RedBlackTree<Comparable>::~RedBlackTree()
{
	makeEmpty();
	delete nullNode;
	delete header;
}

// Internal method to reclaim internal nodes in subtree t
template <class Comparable>
void	RedBlackTree<Comparable>::reclaimMemory(Node *t) const
{
	if (t != t->left)
	{
		reclaimMemory(t->left);
		reclaimMemory(t->right);
		delete t;
	}
}

// Find item x in the tree
// Return the matching item wrapped in a Cref object
template <class Comparable>
Cref<Comparable> RedBlackTree<Comparable>::find(const Comparable & x) const
{
	nullNode->element = x;
	Node *curr = header->right;
	while (1)
	{
		if (x < curr->element)
			curr = curr->left;
		else if (curr->element < x)
			curr = curr->right;
		else if (curr != nullNode)
			return Cref<Comparable>(curr->element);
		else
			return Cref<Comparable>();
	}
}

//Insert item x into the tree.
//Throws DuplicateItemException if x is already present.
template <class Comparable>
void RedBlackTree<Comparable>::insert(const Comparable & x)
{
	current = parent = grand = header;
	nullNode->element = x;

	while (current->element != x)
	{
		great = grand;
		grand = parent;
		parent = current;
		current = x < current->element ?
				current->left : current->right;

		// Check if two red children; fix if so
		if (current->left->color == RED && current->right->color == RED)
			handleReorient(x);
	}

	// Insertion fails if already present
	if (current != nullNode)
		return ;
	current = new Node(x, nullNode, nullNode);

	// Attach to parent
	if (x < parent->element)
		parent->left = current;
	else
		parent->right = current;
	handleReorient(x);
}

// Internal routine that is called during an insertion
// if a node has two red children. Performs flip and rotations
// item is the item being inserted.
template<class Comparable>
void	RedBlackTree<Comparable>::handleReorient(const Comparable & item)
{
	// Do the color flip
	current->color = RED;
	current->left->color = BLACK;
	current->right->color = BLACK;

	if (parent->color == RED) // then have to rotate
	{
		grand->color = RED;
		if (item < grand->element != item < parent->element)
			parent = rotate(item, grand);
		current = rotate(item, great);
		current->color = BLACK;
	}
	header->right->color = BLACK; // Make root black
}

// internal routine that performs a single or double rotation
// Because the result is attached to the parent, there are
// four cases. Called by handleReorient.
// item is the item in handleReoirent.
// parent is the parent of the root of the rotated subtree.
// Return the root of the rotated subtree
template <class Comparable>
RedBlackNode<Comparable> * RedBlackTree<Comparable>::
rotate(const Comparable & item, Node *theParent) const
{
	if (item < theParent->element)
	{
		if (item < theParent->left->element)
			rotateWithLeftChild(theParent->left);
		else
			rotateWithRightChild(theParent->left);
		return theParent->left;
	}
	else
	{
		if (item < theParent->right->element)
			rotateWithLeftChild(theParent->right);
		else
			rotatewithRightChild(theParent->right);
		return theParent->right;
	}
}

int main()
{
	RedBlackTree<int> bst;
	bst.insert(55);
	bst.insert(40);
	bst.insert(65);
	bst.insert(60);
	bst.insert(75);
	bst.insert(57);
	
	return (0);
}
