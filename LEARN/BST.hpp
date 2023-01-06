/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BST.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:03:32 by leng-chu          #+#    #+#             */
/*   Updated: 2023/01/06 15:20:27 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BST_H
# define BST_H

using namespace std;

struct Node
{
	int	data;
	Node	*parent;
	Node	*left;
	Node	*right;
};

typedef Node	*NodePtr;

// class Bst implements the operations in BST
class BST
{
	private:
		NodePtr	root;

		// initializes the nodes with appropirate values
		// all the pointers are set to point to the null pointer
		void	initializeNode(NodePtr node, int key)
		{
			node->data = key;
			node->parent = nullptr;
			node->left = nullptr;
			node->right = nullptr;
		}

		void	preOrderHelper(NodePtr node)
		{
			if (node != nullptr)
			{
				cout << node->data << " ";
				inOrderHelper(node->left);
				inOrderHelper(node->right);
			}
		}

		void	inOrderHelper(NodePtr node)
		{
			if (node != nullptr)
			{
				inOrderHelper(node->left);
				cout << node->data << " ";
				inOrderHelper(node->right);
			}
		}

		void postOrderHelper(NodePtr node)
		{
			if (node != nullptr)
			{
				postOrderHelper(node->left);
				postOrderHelper(node->right);
				cout << node->data << " ";
			}
		}

		NodePtr searchTreeHelper(NodePtr node, int key)
		{
			if (node == nullptr || key == node->data)
				return node;
			if (key < node->data)
				return searchTreeHelper(node->left, key);
			return searchTreeHelper(node->right, key);
		}

		NodePtr	deleteNodeHelper(NodePtr node, int key)
		{
			if (node == nullptr)
				return node;
			else if (key < node->data)
				node->left = deleteNodeHelper(node->left, key);
			else if (key > node->data)
				node->right = deleteNodeHelper(node->right, key);
			else
			{
				if (node->left == nullptr && node->right == nullptr)
				{
					delete node;
					node = nullptr;
				}
				else if (node->left == nullptr)
				{
					NodePtr temp = node;
					node = node->right;
					delete temp;
				}
				else if (node->right == nullptr)
				{
					NodePtr temp = node;
					node = node->left;
					delete temp;
				}
				else
				{
					NodePtr temp = minimum(node->right);
					node->data = temp->data;
					node->right = deleteNodeHelper(node->right, temp->data);
				}
			}
			return node;
		}

		void	printHelper(NodePtr root, string indent, bool last)
		{
			if (root != nullptr)
			{
					if (last)
					{
						cout << "└────";
						indent += "     ";
					}
					else
					{
						cout << "├────";
						indent += "|    ";
					}
				cout << root->data << endl;
				printHelper(root->left, indent, false);
				printHelper(root->right, indent, true);
			}
		}

	public:
		BST(): root(nullptr){}

		// Pre-order traversal
		void	preorder()
		{
			preOrderHelper(this->root);
		}
		
		void inorder()
		{
			inOrderHelper(this->root);
		}
		
		void postorder()
		{
			postOrderHelper(this->root);
		}
		
		NodePtr searchTree(int k)
		{
			return searchTreeHelper(this->root, k);
		}

		NodePtr minimum(NodePtr node)
		{
			while (node->left != nullptr)
				node = node->left;
			return node;
		}

		NodePtr maximum(NodePtr node)
		{
			while (node->right != nullptr)
				node = node->right;
			return node;
		}

		NodePtr successor(NodePtr x)
		{
			if (x->right != nullptr)
				return minimum(x->right);
			NodePtr y = x->parent;
			while (y != nullptr && x == y->right)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}

		NodePtr predecessor(NodePtr x)
		{
			if (x->left != nullptr)
				return maximum(x->left);

			NodePtr y = x->parent;
			while (y != nullptr && x == y->left)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}

		void insert(int key)
		{
			NodePtr node = new Node;
			node->parent = nullptr;
			node->left = nullptr;
			node->right = nullptr;
			node->data = key;
			NodePtr y = nullptr;
			NodePtr x = this->root;

			while (x != nullptr)
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
		}

		NodePtr	getRoot()
		{
			return (this->root);
		}

		NodePtr deleteNode(int data)
		{
			return deleteNodeHelper(this->root, data);
		}

		void	prettyPrint()
		{
			printHelper(this->root, "", true);
		}
};

#endif
