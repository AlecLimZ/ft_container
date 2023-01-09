/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:53:59 by leng-chu          #+#    #+#             */
/*   Updated: 2023/01/06 17:32:30 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDBLACKTREE_H
# define REDBLACKTREE_H

# include "Wrapper.h"

template <class Comparable>
class RedBlackTree;

template <class Comparable>
class RedBlackNode;

template <class Comparable>
class RedBlackTree
{
	public:
		RedBlackTree(void);
		RedBlackTree(const Comparable & negInf);
		RedBlackTree(const RedBlackTree & rhs);
		~RedBlackTree();

		Cref<Comparable> findMin() const;
		Cref<Comparable> findMax() const;
		Cref<Comparable> find(const Comparable & x) const;
		bool isEmpty() const;

		void 	makeEmpty();
		void	insert(const Comparable & x);
		void	remove(const Comparable & x);

		enum { RED, BLACK };

		const RedBlackTree & operator=(const RedBlackTree & rhs);

		typedef RedBlackNode<Comparable> Node;

	private:
		Node	*header; // The tree header (constains negInf)
		Node	*nullNode;

		// Used in insert routine and its helpers (logically static)
		Node	*current;
		Node	*parent;
		Node	*grand;
		Node	*great;

		// Uusal recursive stuff
		void	reclaimMemory(Node *t) const;
		RedBlackNode<Comparable> *clone(Node *t) const;

		// Red-Black tree manipulations
		void	handleReorient(const Comparable & item);
		RedBlackNode<Comparable>	*rotate(const Comparable & item,
										Node	*parent) const;
		void	rotateWithLeftChild(Node * & k2) const;
		void	rotateWithRightChild(Node * & k1) const;

	public:
		// get root node
		Node	*getNode(void);

		// Display
		void	displayRBT(Node *t);
};

template <class Comparable>
class RedBlackNode
{
	Comparable		element;
	RedBlackNode	*left;
	RedBlackNode	*right;
	int				color;

	RedBlackNode(const Comparable & theElement = Comparable(),
				RedBlackNode *lt = NULL, RedBlackNode *rt = NULL,
				int c = RedBlackTree<Comparable>::BLACK)
		: element(theElement), left(lt), right(rt), color(c){}
	friend class RedBlackTree<Comparable>;
};

#include "RedBlackTree.cc"
#endif
