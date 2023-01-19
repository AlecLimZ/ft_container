/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:30:29 by leng-chu          #+#    #+#             */
/*   Updated: 2023/01/19 17:36:53 by leng-chu         ###   ########.fr       */
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

template <typename Key, typename M, typename P, class RAlloc, class Compare = std::less<Key> >
class RedBlackTree
{
	public:
		typedef Node<P, Key, M>					NodeM;
		typedef Node<P, Key, M>*				NodePtr;
		typedef std::size_t						size_type;
		typedef typename RAlloc::template rebind<NodeM>::other	rebindN;
	protected:
		NodePtr	root;
		NodePtr	nullNode;
		Compare	_cmp;
		size_type _size;
		rebindN	_alloc;

		void	initializeNULLNode(NodePtr node, NodePtr parent)
		{
			node->data.first = 0;
			node->parent = parent;
			node->left = nullptr;
			node->right = nullptr;
			node->color = 0;
		}

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

		void	deleteFix(NodePtr x)
		{
			NodePtr s;
		    while (x != root && x->color == 0)
			{
				if (x == x->parent->left)
				{
					s = x->parent->right;
					if (s == nullptr) // MARK
						s = nullNode;
					if (s->color == 1)
					{
						s->color = 0;
						x->parent->color = 1;
						leftRotate(x->parent);
						s = x->parent->right;
					}
					
					if (s == nullptr) // MARK
						s = nullNode;
					if (s == nullNode || (s->left->color == 0 && s->right->color == 0))
					{
						s->color = 1;
						x = x->parent;
					}
					else
					{
						if (s->right->color == 0)
						{
							s->left->color = 0;
							s->color = 1;
							rightRotate(s);
							s = x->parent->right;
						}
					
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
						s->color = 0;
						x->parent->color = 1;
						rightRotate(x->parent);
						s = x->parent->left;
					}
					if (s == nullNode || (s->right->color == 0 && s->right->color == 0))
					{
						s->color = 1;
						x = x->parent;
					}
					else
					{
						if (s->left->color == 0)
						{
							s->right->color = 0;
							s->color = 1;
							leftRotate(s);
							s = x->parent->left;
						}
					
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

	public:
		RedBlackTree(): _size(0), _alloc(RAlloc())
		{
			nullNode = _alloc.allocate(1); // MARK
			nullNode->color = 0;
			nullNode->parent = nullptr;
			nullNode->left = nullptr;
			nullNode->right = nullptr;
			root = nullNode;
		}
		~RedBlackTree()
		{	
			freeNode(root);
			_alloc.deallocate(nullNode, 1);
		}

		RedBlackTree & operator=(const RedBlackTree & rhs)
		{
			if (this != &rhs)
			{
				freeNode(root);
				_alloc.deallocate(nullNode, 1);
				nullNode = _alloc.allocate(1); // MARK
				nullNode->color = 0;
				nullNode->parent = nullptr;
				nullNode->left = nullptr;
				nullNode->right = nullptr;
				root = nullNode;
				_cmp = rhs._cmp;
				_size = 0; // coz insert is doing the _size thing in the map
				_alloc = rhs._alloc;
			}
			return (*this);
		}

		void	freeNode(NodePtr t)
		{
			if (t == nullNode)
				return ;
			freeNode(t->left);
			freeNode(t->right);
			_alloc.destroy(t);
			_alloc.deallocate(t, 1);
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
			if (y == nullNode)
				return ;
			x->right = y->left;
			if (y->left != nullNode && y->left != nullptr)
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
			if (y == nullNode)
				return ;
			x->left = y->right;
			if (y->right != nullNode && y->right != nullptr)
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

		void	clear()
		{
			freeNode(root);
			root = nullNode;
			_size = 0;
		}

		void	swap(RedBlackTree & x)
		{
			NodePtr	rtmp = root;
			NodePtr	rnull = nullNode;
			Compare	c = _cmp;
			size_type s = _size;

			root = x.root;
			nullNode = x.nullNode;
			_cmp = x._cmp;
			_size = x._size;

			x.root = rtmp;
			x.nullNode = rnull;
			x._cmp = c;
			x._size = s;
		}

		void	remove(NodePtr del)
		{
			NodePtr x;
			NodePtr y;
			if (del == nullNode)
				return ;
			_size--;
			y = del;
			int y_original_color = y->color;
			if (del != nullNode && del->right == nullptr) // MARK
				del->right = nullNode;
			if (del != nullNode && del->left == nullptr) // MARK
				del->left = nullNode;
			if (del->left == nullNode)
			{
				x = del->right;
				rbTransplant(del, del->right);
			}
			else if (del->right == nullNode)
			{

				x = del->left;
				rbTransplant(del, del->left);
			}
			else
			{
				y = minimum(del->right);
				y_original_color = y->color;
				x = y->right;
				if (y->parent == del)
					x->parent = y;
				else
				{
					rbTransplant(y, y->right);
					y->right = del->right;
					y->right->parent = y;
				}
				rbTransplant(del, y);
				y->left = del->left;
				y->left->parent = y;
				y->color = del->color;
			}
			if (del != nullNode)
				_alloc.destroy(del);
			_alloc.deallocate(del, 1);
			if (x != nullNode && x->left == nullptr)
				x->left = nullNode;
			if (x != nullNode && x->right == nullptr)
				x->right = nullNode;
			if (y_original_color == 0)
				deleteFix(x);
		}

		NodePtr	insert(Key key)
		{
			NodePtr node = _alloc.allocate(1); // MARK
			_alloc.construct(node, NodeM(key)); // MARK
			node->parent = nullptr;
			node->left = nullNode;
			node->right = nullNode;
			node->color = 1;

			NodePtr	y = nullptr;
			NodePtr	x = this->root;

			while (x != nullNode)
			{
				y = x;
				if (node->data.first == x->data.first)
				{
					_alloc.destroy(node);
					_alloc.deallocate(node, 1);
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
			NodePtr node = _alloc.allocate(1); // MARK
			_alloc.construct(node, NodeM(key)); // MARK
			node->parent = nullptr;
			node->left = nullNode;
			node->right = nullNode;
			node->color = 1;

			NodePtr	y = nullptr;
			NodePtr	x = this->root;

			while (x != nullNode)
			{
				y = x;
				if (node->data.first == x->data.first)
				{
					_alloc.destroy(node);
					_alloc.deallocate(node, 1);
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
			NodePtr node = _alloc.allocate(1); // MARK
			_alloc.construct(node, NodeM(key)); // MARK
			node->parent = nullptr;
			node->left = nullNode;
			node->right = nullNode;
			node->color = 1;

			NodePtr	y = nullptr;
			NodePtr x;
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
			while (x != nullNode && _size != 0)
			{
				y = x;
				if (node->data.first == x->data.first)
				{
					_alloc.destroy(node);
					_alloc.deallocate(node, 1);
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
