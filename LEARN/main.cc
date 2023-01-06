/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:31:37 by leng-chu          #+#    #+#             */
/*   Updated: 2023/01/06 17:32:01 by leng-chu         ###   ########.fr       */
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
#include "RedBlackTree.hpp"

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

using namespace std;

struct Node
{
	int		data;
	Node	*parent;
	Node	*left;
	Node	*right;
	int		color;
};

typedef Node *NodePtr;

class RBTree
{
	private:
		NodePtr	root;
		NodePtr	TNULL;

		void	initializeNULLNode(NodePtr node, NodePtr parent)
		{
			node->data = 0;
			node->parent = parent;
			node->left = nullptr;
			node->right = nullptr;
			node->color = 0;
		}

		void	preOrderHelper(NodePtr node)
		{
			if (node != TNULL)
			{
				cout << node->data << " ";
				preOrderHelper(node->left);
				preOrderHelper(node->right);
			}
		}

		void	inOrderHelper(NodePtr node)
		{
			if (node != TNULL)
			{
				inOrderHelper(node->left);
				cout << node->data << " ";
				inOrderHelper(node->right);
			}
		}

		void	postOrderHelper(NodePtr node)
		{
			if (node != TNULL)
			{
				postOrderHelper(node->left);
				postOrderHelper(node->right);
				cout << node->data << " ";
			}
		}

		NodePtr searchTreeHelper(NodePtr node, int key)
		{
			if (node == TNULL || key == node->data)
				return node;
			if (key < node->data)
				return searchTreeHelper(node->left, key);
			return searchTreeHelper(node->right, key);
		}

		// fix the rb tree modified by the delete operation
		void	fixDelete(NodePtr x)
		{
			NodePtr	s;
			while (x != root && x->color == 0)
			{
				if (x == x->parent->left)
				{
					s = x->parent->right;
					if (s->color == 1)
					{
						// case 3.1
						s->color = 0;
						x->parent->color = 1;
						leftRotate(x->parent);
						s = x->parent->right;
					}
					if (s->left->color == 0 && s->right->color == 0)
					{
						// case 3.2
						s->color = 1;
						x = x->parent;
					}
					else
					{
						if (s->right->color == 0)
						{
							// case 3.3
							s->left->color = 0;
							s->color = 1;
							rightRotate(s);
							s = x->parent->right;
						}

						// case 3.4
						s->color = x->parent->color;
						x->parent->color = 0;
						s->right->color = 0;
						leftRotate(x->parent);
						x = root;
					}
				}
				else
				{
					s = x->parent->left;
					if (s->color == 1)
					{
						// case 3.1
						s->color = 0;
						x->parent->color = 1;
						rightRotate(x->parent);
						s = x->parent->left;
					}
					if (s->right->color == 0 && s->right->color == 0)
					{
						// case 3.2
						s->color = 1;
						x = x->parent;
					}
					else
					{
						if (s->left->color == 0)
						{
							// case 3.3
							s->right->color = 0;
							s->color = 1;
							leftRotate(s);
							s = x->parent->left;
						}

						// case 3.4
						s->color = x->parent->color;
						x->parent->color = 0;
						s->left->color = 0;
						rightRotate(x->parent);
						x = root;
					}
				}
			}
			x->color = 0;
		}

		void	rbTransplant(NodePtr u, NodePtr v)
		{
			if (u->parent == nullptr)
				root = v;
			else if (u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
			v->parent = u->parent;
		}

		void	deleteNodeHelper(NodePtr node, int key)
		{
			NodePtr z = TNULL;
			NodePtr x, y;
			while (node != TNULL)
			{
				if (node->data == key)
					z = node;
				if (node->data <= key)
					node = node->right;
				else
					node = node->left;
			}

			if (z == TNULL)
				return ;
			y = z;
			int y_original_color = y->color;
			if (z->left == TNULL)
			{
				x = z->right;
				rbTransplant(z, z->right);
			}
			else if (z->right == TNULL)
			{
				x = z->left;
				rbTransplant(z, z->left);
			}
			else
			{
				y = minimum(z->right);
				y_original_color = y->color;
				x = y->right;
				if (y->parent == z)
					x->parent = y;
				else
				{
					rbTransplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				rbTransplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}
			delete z;
			if (y_original_color == 0)
			{
				fixDelete(x);
			}
		}

		void fixInsert(NodePtr k)
		{
			NodePtr	u;
			while (k->parent->color == 1)
			{
				if (k->parent == k->parent->parent->right)
				{
					u = k->parent->parent->left;
					if (u->color == 1)
					{
						u->color = 0;
						k->parent->color = 0;
						k->parent->parent->color = 1;
						k = k->parent->parent;
					}
					else
					{
						if (k == k->parent->left)
						{
							// case 3.2.2
							k = k->parent;
							rightRotate(k);
						}
						// case 3.2.1
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

		void printHelper(NodePtr root, string indent, bool last)
		{
			if (root != TNULL)
			{
				cout << indent;
				if (last)
				{
					cout << "R----";
					indent += "     ";
				}
				else
				{
					cout << "L----";
					indent += "|    ";
				}

				string sColor = root->color ? "RED" : "BLACK";
				cout << root->data << "(" << sColor << ")" << endl;
				printHelper(root->left, indent, false);
				printHelper(root->right, indent, true);
			}
			// cout << root->left->data << endl;
		}
	public:
		RBTree()
		{
			TNULL = new Node;
			TNULL->color = 0;
			TNULL->left = nullptr;
			TNULL->right = nullptr;
			root = TNULL;
		}

		// Pre-Order traversal
		// Node->Left Subtree->Right Subtree
		void preorder()
		{
			preOrderHelper(this->root);
		}

		// In-Order traversal
		// Left Subtree->Node->Right Subtree
		void	inorder()
		{
			inOrderHelper(this->root);
		}

		// Post-Order traversal
		// Left Subtree -> Right Subtree -> Node
		void	postorder()
		{
			postOrderHelper(this->root);
		}

		// search the tree for the key k
		// and return the corresponding node
		NodePtr searchTree(int k)
		{
			return searchTreeHelper(this->root, k);
		}

		// find the node with the minimum key
		NodePtr minimum(NodePtr node)
		{
			while (node->left != TNULL)
				node = node->left;
			return node;
		}

		// find the node with the maximum key
		NodePtr maximum(NodePtr node)
		{
			while (node->right != TNULL)
				node = node->right;
			return node;
		}

		// find the successor of a given node
		NodePtr successor(NodePtr x)
		{
			// if the right subtree is not null,
			// the successor is the leftmost node in the
			// right subtree
			if (x->right != TNULL)
				return minimum(x->right);

			// else it is the lowest ancestor of x whose
			// left child is also an ancestor of x
			NodePtr y = x->parent;
			while (y != TNULL && x == y->right)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}

		// find the predecessor of a given node
		NodePtr predecessor(NodePtr x)
		{
			if (x->left != TNULL)
				return maximum(x->left);

			NodePtr y = x->parent;
			while (y != TNULL && x == y->left)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}

		// rotate left at node x
		void leftRotate(NodePtr x)
		{
			NodePtr y = x->right;
			x->right = y->left;
			if (y->left != TNULL)
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

		void rightRotate(NodePtr x)
		{
			NodePtr y = x->left;
			x->left = y->right;
			if (y->right != TNULL)
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

		void insert(int key)
		{
			NodePtr node = new Node;
			node->parent = nullptr;
			node->data = key;
			node->left = TNULL;
			node->right = TNULL;
			node->color = 1;

			NodePtr y = nullptr;
			NodePtr x = this->root;

			while (x != TNULL)
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

			fixInsert(node);
		}

		NodePtr getRoot()
		{
			return this->root;
		}

		// delete the node from the tree
		void deleteNode(int data)
		{
			deleteNodeHelper(this->root, data);
		}

		void prettyPrint()
		{
			if (root)
				printHelper(this->root, "", true);
		}
};

int main()
{
	RBTree bst;
	bst.insert(8);
	bst.insert(18);
	bst.insert(5);
	bst.insert(15);
	bst.insert(17);
	bst.insert(25);
	bst.insert(40);
	bst.insert(80);
	bst.deleteNode(25);
	bst.prettyPrint();
	bst.inorder();
	return (0);
}
