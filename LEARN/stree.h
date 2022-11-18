/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stree.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:04:36 by leng-chu          #+#    #+#             */
/*   Updated: 2022/11/18 11:08:44 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STREE_H
# define STREE_H

template <typename Comparable>
class BinarySearchTree
{
	public:
		class BstIterator{};
		typedef BstIterator const_iterator;
		typedef const_iterator iterator;

		BinarySearchTree();
		BinarySearchTree(const BinarySearchTree & rhs);
		BinarySearchTree(BinarySearchTree && rhs);
		~BinarySearchTree();
		BinarySearchTree & operator=(const BinarySearchTree & rhs);
		BinarySearchTree & operator=(const BinarySearchTree && rhs);

		const_iterator find(const Comparable & item) const;
		const_iterator begin() const;
		const_iterator end() cont;
		const Comparable & findMin() const;
		const Comparable & findMax() const;
		bool contains(const Comparable & x) const;
		bool isEmpty() const { return root = nullptr; }
		void printTree(ostream & out = cout) const;
		void makeEmpty();
		void insert(const Comparable & x);
		void remove(const Comparable & x);

	private:
		BinaryNode<Comparable> *root;
};

#endif
