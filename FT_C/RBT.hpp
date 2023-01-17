/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:30:29 by leng-chu          #+#    #+#             */
/*   Updated: 2023/01/17 11:23:29 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_HPP
# define RBT_HPP
#include <iostream>

using std::cout;
using std::endl;

template <typename T, typename Key, typename M>
struct Node
{
	T		data;
	Node	*parent;
	Node	*left;
	Node	*right;
	int		color;
	Node(Key key):data(key){}
	Node(void):data(){}
};

template <typename Key, typename M, typename T, class Compare = std::less<T> >
class RedBlackTree
{
	public:
		typedef Node<T, Key, M>		NodeM;
		typedef Node<T, Key, M>*	NodePtr;
		typedef std::size_t			size_type;
	private:
		NodePtr	root;
		NodePtr	nullNode;
		Compare	_cmp;
		size_type _size;

		void	initializeNULLNode(NodePtr node, NodePtr parent)
		{
			node->data.first = 0;
			node->parent = parent;
			node->left = nullptr;
			node->right = nullptr;
			node->color = 0;
		}

		// Inorder
		void	inOrderHelper(NodePtr node)
		{
			if (node != nullNode)
			{
				inOrderHelper(node->left);
				cout << node->data.first << " ";
				inOrderHelper(node->right);
			}
		}

		NodePtr	searchTreeHelper(NodePtr node, Key key) const
		{
			if (node == nullNode || key == node->data.first)
				return node;
		//	if (key < node->data)
			if (_cmp(key, node->data.first))
				return searchTreeHelper(node->left, key);
			return searchTreeHelper(node->right, key);
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

	public:
		// For balancing the tree after insertion
		void	insertFix(NodePtr k)
		{
			NodePtr	u;

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
		RedBlackTree(): _size(0)
		{
			nullNode = new NodeM;
			nullNode->color = 0;
			nullNode->parent = nullptr;
			nullNode->left = nullptr;
			nullNode->right = nullptr;
			root = nullNode;
		}
//		NodePtr	root;
//		NodePtr	nullNode;
//		Compare	_cmp;
//		size_type _size;
		~RedBlackTree()
		{	
			freeNode(root);
			delete nullNode;
		}

		RedBlackTree & operator=(const RedBlackTree & rhs)
		{
			if (this != &rhs)
			{
				freeNode(root);
				delete nullNode;
				nullNode = new NodeM;
				nullNode->color = 0;
				nullNode->parent = nullptr;
				nullNode->left = nullptr;
				nullNode->right = nullptr;
				root = nullNode;
				_cmp = rhs._cmp;
				_size = rhs._size;
			}
			return (*this);
		}

		void	freeNode(NodePtr t)
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

		NodePtr	searchTree(Key k) const
		{
			return searchTreeHelper(this->root, k);
		}

		NodePtr	minimum(NodePtr node)
		{
			while (node->left != nullNode)
				node = node->left;
			return node;
		}
		
		NodePtr	minimum(NodePtr node) const
		{
			while (node->left != nullNode)
				node = node->left;
			return node;
		}

		NodePtr	maximum(NodePtr node)
		{
			while (node->right != nullNode)
				node = node->right;
			return node;
		}
		
		NodePtr	maximum(NodePtr node) const
		{
			while (node->right != nullNode)
				node = node->right;
			return node;
		}

		void leftRotate(NodePtr x)
		{
			NodePtr	y = x->right;
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

		void	rightRotate(NodePtr x)
		{
			NodePtr	y = x->left;
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

		void	remove(NodePtr del)
		{
			int oricolor = del->color;
			(void)oricolor;

			NodePtr x;
			if (del->left == nullNode)
				x = del->right;
			x->parent = del->parent;
			delete del;
			del = x;
		}

		NodePtr	insert(Key key)
		{
			NodePtr	node = new NodeM(key);
			node->parent = nullptr;
			//node->data = ft::make_pair(key, 0);
			node->left = nullNode;
			node->right = nullNode;
			node->color = 1;

			NodePtr	y = nullptr;
			NodePtr	x = this->root;

			while (x != nullNode)
			{
				y = x;
				//if (node->data < x->data)
				if (node->data.first == x->data.first)
				{
					delete node;
					return (x);
				}
				if (_cmp(node->data.first, x->data.first))
					x = x->left;
				else
					x = x->right;
			}
			_size++;
			node->parent = y;
			if (y == nullptr)
				root = node;
			//else if (node->data < y->data)
			else if (_cmp(node->data.first, y->data.first))
				y->left = node;
			else
				y->right = node;

			if (node->parent == nullptr)
			{
				node->color = 0;
				return (node);
			}

			if (node->parent->parent == nullptr)
				return (node);

			insertFix(node);
			return (node);
		}
		
		ft::pair<NodePtr, bool>	insert2(Key key)
		{
			ft::pair<NodePtr, bool> ret;
			NodePtr	node = new NodeM(key);
			node->parent = nullptr;
			//node->data = ft::make_pair(key, 0);
			node->left = nullNode;
			node->right = nullNode;
			node->color = 1;

			NodePtr	y = nullptr;
			NodePtr	x = this->root;

			while (x != nullNode)
			{
				y = x;
				//if (node->data < x->data)
				if (node->data.first == x->data.first)
				{
					delete node;
					ret = ft::make_pair(x, 0);
					return (ret);
				}
				if (_cmp(node->data.first, x->data.first))
					x = x->left;
				else
					x = x->right;
			}
			_size++;
			ret = ft::make_pair(node, 1);
			node->parent = y;
			if (y == nullptr)
				root = node;
			//else if (node->data < y->data)
			else if (_cmp(node->data.first, y->data.first))
				y->left = node;
			else
				y->right = node;

			if (node->parent == nullptr)
			{
				node->color = 0;
				return (ret);
			}

			if (node->parent->parent == nullptr)
				return (ret);

			insertFix(node);
			return (ret);
		}
		
		NodePtr	insert3(NodePtr itn, Key key, M value)
		{
			NodePtr	node = new NodeM(key);
			node->parent = nullptr;
			//node->data = ft::make_pair(key, 0);
			node->left = nullNode;
			node->right = nullNode;
			node->color = 1;

			NodePtr	y = nullptr;
			NodePtr x;
	//		if (_cmp(root->data.first, key) && _cmp(itn->data.first, key))
	//			x = this->root;
	//		else
	//			x = itn;
			x = itn;
			if (itn->parent == nullptr)
				x = this->root;
			else if (x->parent && _cmp(x->parent->data.first, key))
			{
				while (x->parent && _cmp(x->parent->data.first, key))
					x = x->parent;
			}
			else
			{
				while (x->parent && _cmp(key, x->parent->data.first))
					x = x->parent;
			}
			while (x != nullNode)
			{
				y = x;
				//if (node->data < x->data)
				if (node->data.first == x->data.first)
				{
					delete node;
					return (x);
				}
				if (_cmp(node->data.first, x->data.first))
					x = x->left;
				else
					x = x->right;
			}
			_size++;
			node->data.second = value;
			node->parent = y;
			if (y == nullptr)
				root = node;
			//else if (node->data < y->data)
			else if (_cmp(node->data.first, y->data.first))
				y->left = node;
			else
				y->right = node;

			if (node->parent == nullptr)
			{
				node->color = 0;
				return (node);
			}

			if (node->parent->parent == nullptr)
				return (node);

			insertFix(node);
			return (node);
		}

		NodePtr	getRoot() const
		{
			return (this->root);
		}

		NodePtr getNull() const
		{
			return (this->nullNode);
		}

		size_type getSize() const
		{
			return (this->_size);
		}
};
#endif
