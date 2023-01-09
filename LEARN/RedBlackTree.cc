/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.cc                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:03:37 by leng-chu          #+#    #+#             */
/*   Updated: 2023/01/09 13:27:24 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
using namespace std;

#include "RedBlackTree.hpp"

template <class Comparable>
RedBlackTree<Comparable>::RedBlackTree(const Comparable & negInf)
{
	nullNode = new Node;
	nullNode->left = nullNode->right = nullNode;
	header = new Node(negInf);
	header->left = header->right = nullNode;
}

// Copy constructor
template <class Comparable>
RedBlackTree<Comparable>::RedBlackTree(const RedBlackTree<Comparable> & rhs)
{
	nullNode = new Node;
	nullNode->left = nullNode->right = nullNode;
	header = new Node(rhs.header->element);
	header->left = header->right = nullNode;
	*this = rhs;
}

// Destroy the tree
template <class Comparable>
RedBlackTree<Comparable>::~RedBlackTree()
{
	makeEmpty();
	delete nullNode;
	delete header;
}

// Insert item x into the tree.
// Throws DuplicateItemException if x is already present.
template <class Comparable>
void RedBlackTree<Comparable>::insert(const Comparable & x)
{
	current = parent = grand = header;
	nullNode->element = x;

	while (current->element != x)
	{
		great = grand; grand = parent; parent = current;
		current = x < current->element ? current->left : current->right;

		// Check if two red children
		if (current->left->color == RED && current->right->color == RED)
			handleReorient(x);
	}

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

template <class Comparable>
void RedBlackTree<Comparable>::remove(const Comparable & x)
{
	(void)x;
	cout << "sorry, no remove yet" << endl;
}

template <class Comparable>
Cref<Comparable> RedBlackTree<Comparable>::findMin() const
{
	if (isEmpty())
		return Cref<Comparable>();
	Node *itr = header->right;
	while (itr->left != nullNode)
		itr = itr->left;
	return Cref<Comparable>(itr->element);
}

template <class Comparable>
Cref<Comparable> RedBlackTree<Comparable>::findMax() const
{
	if (isEmpty())
		return Cref<Comparable>();
	Node *itr = header->right;
	while (itr->right != nullNode)
		itr = itr->right;
	return Cref<Comparable>(itr->element);
}

template <class Comparable>
Cref<Comparable> RedBlackTree<Comparable>::find(const Comparable & x) const
{
	nullNode->element = x;
	Node *curr = header->right;

	for (; ;)
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

template <class Comparable>
void	RedBlackTree<Comparable>::makeEmpty()
{
	reclaimMemory(header->right);
	header->right = nullNode;
}

template<class Comparable>
const RedBlackTree<Comparable> & RedBlackTree<Comparable>::operator=(const RedBlackTree<Comparable> & rhs)
{
	if (this != &rhs)
	{
		makeEmpty();
		header->right = clone(rhs.header->right);
	}
	return (*this);
}

template <class Comparable>
RedBlackNode<Comparable> *
RedBlackTree<Comparable>::clone(Node *t) const
{
	if (t == t->left)
		return nullNode;
	else
		return new RedBlackNode<Comparable>(t->element, clone(t->left), clone(t->right), t->color);
}

template <class Comparable>
void RedBlackTree<Comparable>::handleReorient(const Comparable & item)
{
	current->color = RED;
	current->left->color = BLACK;
	current->right->color = BLACK;

	if (parent->color == RED)
	{
		grand->color = RED;
		if (item < grand->element != item < parent->element)
			parent = rotate(item, grand);
		current = rotate(item, great);
		current->color = BLACK;
	}
	header->right->color = BLACK;
}

template <class Comparable>
RedBlackNode<Comparable> *
RedBlackTree<Comparable>::rotate(const Comparable & item, Node *theParent) const
{
	if (item < theParent->element)
	{
		item < theParent->left->element ?
			rotateWithLeftChild(theParent->left) :
			rotateWithRightChild(theParent->left);
		return theParent->left;
	}
	else
	{
		item < theParent->right->element ?
			rotateWithLeftChild(theParent->right) :
			rotateWithRightChild(theParent->right);
		return theParent->right;
	}
}

template <class Comparable>
void RedBlackTree<Comparable>::
rotateWithLeftChild(Node * & k2) const
{
	Node	*k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2 = k1;
}

template <class Comparable>
void RedBlackTree<Comparable>::
rotateWithRightChild(Node * & k1) const
{
	Node *k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1 = k2;
}

template <class Comparable>
void RedBlackTree<Comparable>::reclaimMemory(Node *t) const
{
	if (t != t->left)
	{
		reclaimMemory(t->left);
		reclaimMemory(t->right);
		delete t;
	}
}

template <class Comparable>
typename RedBlackTree<Comparable>::Node	*RedBlackTree<Comparable>::getNode(void)
{
	return (header->right);
}

template <class Comparable>
void	RedBlackTree<Comparable>::displayRBT(Node *t)
{
	if (t == nullNode)
		return ;
	Node *root = t;
	displayRBT(root->left);
	cout << root->element << " ";
	displayRBT(root->right);
}
