/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:30:29 by leng-chu          #+#    #+#             */
/*   Updated: 2023/01/09 14:11:18 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

using std::cout;
using std::endl;

struct Node
{
	int	data;
	Node	*parent;
	Node	*left;
	Node	*right;
	int		color;
};

class RedBlackTree
{
	private:
		Node	*root;
		Node	*nullNode;

		void	initializeNULLNode(Node *node, Node *parent)
		{
			node->data = 0;
			node->parent = parent;
			node->left = nullptr;
			node->right = nullptr;
			node->color = 0;
		}

		// Inorder
		void	inOrderHelper(Node *node)
		{
			if (node != nullNode)
			{
				inOrderHelper(node->left);
				cout << node->data << " ";
				inOrderHelper(node->right);
			}
		}

		Node	*searchTreeHelper(Node *node, int key)
		{
			if (node == nullNode || key == node->data)
				return node;
			if (key < node->data)
				return searchTreeHelper(node->left, key);
			return searchTreeHelper(node->right, key);
		}

		void	rbTransplant(Node *u, Node *v)
		{
			if (u->parent == nullptr)
				root = v;
			else if (u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
			v->parent = u->parent;
		}

		// For balancing the tree after insertion
		void insertFix(Node *k)
		{
			Node	*u;

			while(k->parent->color == 1)
			{
				if (k->parent == k->parent->parent->right)
				{
					u = k->parent->parent->left;
					if (u->color == 1)
					{
						u->color = 0;
						k->parent->parent->color = 1;
						k = k->parent->parent;
					}
					else
					{
						if (k == k->parent->left)
						{
							k = k->parent;
							rightRotate(k);
						}
						k->parent->color = 0;
						k->parent->parent->color = 1;
						leftRotate(k->parent->parent);
					}
				}
				else
				{
					u = k->parent->parent->right;

					if (u->color == 1)
					{
						u->color = 0;
						k->parent->color = 0;
						k->parent->parent->color = 1;
						k = k->parent->parent;
					}
					else
					{
						if (k == k->parent->right)
						{
							k = k->parent;
							leftRotate(k);
						}
						k->parent->color = 0;
						k->parent->parent->color = 1;
						rightRotate(k->parent->parent);
					}
				}
				if (k == root)
					break;
			}
			root->color = 0;
		}

	public:
		RedBlackTree()
		{
			nullNode = new Node;
			nullNode->color = 0;
			nullNode->left = nullptr;
			nullNode->right = nullptr;
			root = nullNode;
		}

		~RedBlackTree()
		{	
			freeNode(root);
			delete nullNode;
		}

		void	freeNode(Node *t)
		{
			if (t == nullNode)
				return ;
			freeNode(t->left);
			freeNode(t->right);
			delete t;
		}

		void	inorder()
		{
			inOrderHelper(this->root);
		}

		Node	*searchTree(int k)
		{
			return searchTreeHelper(this->root, k);
		}

		Node	*minimum(Node *node)
		{
			while (node->left != nullNode)
				node = node->left;
			return node;
		}

		Node	*maximum(Node *node)
		{
			while (node->right != nullNode)
				node = node->right;
			return node;
		}

		void leftRotate(Node *x)
		{
			Node	*y = x->right;
			x->right = y->left;
			if (y->left != nullNode)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == nullptr)
				this->root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		}

		void	rightRotate(Node *x)
		{
			Node	*y = x->left;
			x->left = y->right;
			if (y->right != nullNode)
				y->right->parent = x;
			y->parent = x->parent;
			if (x->parent == nullptr)
				this->root = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;
		}

		void	insert(int key)
		{
			Node	*node = new Node;
			node->parent = nullptr;
			node->data = key;
			node->left = nullNode;
			node->right = nullNode;
			node->color = 1;

			Node	*y = nullptr;
			Node	*x = this->root;

			while (x != nullNode)
			{
				y = x;
				if (node->data < x->data)
					x = x->left;
				else
					x = x->right;
			}

			node->parent = y;
			if (y == nullptr)
				root = node;
			else if (node->data < y->data)
				y->left = node;
			else
				y->right = node;

			if (node->parent == nullptr)
			{
				node->color = 0;
				return ;
			}

			if (node->parent->parent == nullptr)
				return ;

			insertFix(node);
		}

		Node	*getRoot()
		{
			return (this->root);
		}
};
