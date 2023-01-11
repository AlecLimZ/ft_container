/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 14:24:13 by leng-chu          #+#    #+#             */
/*   Updated: 2023/01/11 16:20:42 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <iterator>
# include "util.hpp"
# include "lib.hpp"
# include "RBT.hpp"

namespace	ft
{
	template<
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<ft::pair<const Key, T> >
			>
	class map
	{
		template <typename V>
		class mapiter;
		template <typename V>
		class mapitrev;
		public:
			typedef Key	key_type;
			typedef T	mapped_type;
			typedef ft::pair<const Key, T>	value_type;
			typedef std::size_t	size_type;
			typedef std::ptrdiff_t	difference_type;
			typedef Compare	key_compare;
			typedef Allocator	allocator_type;
			typedef value_type&	reference;
			typedef const value_type&	const_reference;
			typedef typename Allocator::pointer	pointer;
			typedef typename Allocator::const_pointer	const_pointer;
			typedef mapiter<value_type>	iterator;
			typedef mapiter<const value_type> const_iterator;
			typedef mapitrev<iterator>	reverse_iterator;
			typedef mapitrev<const_iterator> const_reverse_iterator;
			typedef RedBlackTree<Key, mapped_type, value_type, key_compare> RBTclass;
			typedef typename RedBlackTree<Key, mapped_type, value_type, key_compare>::NodePtr NodePtr;

		protected:
			size_type		_size;
			allocator_type	_myalloc;
			RBTclass		_rbtmap;
			key_compare		_compare;

		public:
			/***CONSTRUCTOR & DESTRUCTOR***/
			explicit map(const Compare & comp = key_compare(), const allocator_type & alloc = Allocator())
				:_size(0), _myalloc(alloc), _compare(comp){
			//		cout << "constructor map default" << endl;
				}
			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value>::value_type* = 0)
			: _size(0), _myalloc(alloc), _compare(comp)
			{
				if (_size > max_size())
					throw(std::length_error("ft::map"));
				NodePtr	check;
				value_type tmp;
				while (first != last)
				{
					check = _rbtmap.insert(first->first);
					if (check->data.second == tmp.second)
						check->data.second = first->second;
					first++;
				}
				_size = _rbtmap.getSize();
			}
			map(const map & x): _size(x._size), _myalloc(x._myalloc), _compare(x._compare)
			{
				// _map need to deep copy
			}
			~map()
			{
			//	for (size_type i = 0; i < _capacity; ++i)
			//		_myalloc.destroy(_map + i);
			//	_myalloc.deallocate(_map, _capacity);
		//		cout << "destructor map" << endl;
			}

			//test
			void	print(void)
			{
				_rbtmap.inorder();
			}
			/*** ITERATOR ***/
			iterator begin()
			{
		//		NodePtr start = _rbtmap.minimum(_rbtmap.getRoot());
		//		return (iterator(start));
				return (iterator(&_rbtmap));
			}
			
			const_iterator begin() const
			{
			//	return (const_iterator(_rbtmap.minimum(_rbtmap.getRoot())));
				return (const_iterator(&_rbtmap));
			}

			iterator end()
			{ return (iterator(&_rbtmap, _rbtmap.getNull())); }

			const_iterator end() const
			{ return (const_iterator(&_rbtmap, _rbtmap.getNull())); }

			/*** ELEMENT ACCESS ***/
			mapped_type & operator[](const key_type & k)
			{
		//		NodePtr check = _rbtmap.searchTree(k);
		//		if (check == _rbtmap.getNull())
		//		{
				NodePtr	check = _rbtmap.insert(k);
		//		}
				return (check->data.second);
			}

			/*** CAPACITY ***/
			bool empty() const
			{
				return (_size == 0);
			}

			size_type size() const
			{
				return (_rbtmap.getSize());
			}

			size_type max_size() const
			{
//				if (sizeof(key_type) == sizeof(std::string)
//						&& sizeof(mapped_type) == sizeof(std::string))
//					return (230584300921369395);
//				if (sizeof(key_type) == sizeof(std::string)
//						|| sizeof(mapped_type) == sizeof(std::string))
//					return (_myalloc.max_size() / 2);
//				if (ft::is_same<char, key_type>::value
//					&& ft::is_same<char, mapped_type>::value)
//					return (_myalloc.max_size() / 16);
//				if ((sizeof(key_type) == sizeof(short)
//						&& sizeof(key_type) >= sizeof(mapped_type))
//						||
//						(sizeof(mapped_type) == sizeof(short)
//						 && sizeof(mapped_type) >= sizeof(key_type)))
//					return (_myalloc.max_size() / 8);
//				if ((sizeof(key_type) == sizeof(wchar_t)
//						&& sizeof(key_type) >= sizeof(mapped_type))
//						||
//						(sizeof(mapped_type) == sizeof(wchar_t)
//						 && sizeof(mapped_type) >= sizeof(key_type)))
//					return (_myalloc.max_size() / 5);
//				return (_myalloc.max_size() / 3);
				std::allocator<char> tmp;
				if (sizeof(value_type) == 2)
					return (tmp.max_size() / 32);
				return (tmp.max_size() / (32 + sizeof(value_type)));
			}
			/*** MODIFIERS ***/
			/*** OBSERVERS ***/
			/*** OPERATIONS ***/
			/*** ALLOCATOR ***/
	};

	template<typename K, typename T, typename C, typename A>
	template <typename V>
	class map<K, T, C, A>::mapiter
	{
		public:
			typedef map<K, T, C, A> 		MAP;
			typedef MAP::difference_type	difference_type;
			typedef V						value_type;
			typedef V&						reference;
			typedef V*						pointer;
			std::bidirectional_iterator_tag	iterator_category;

		protected:
			RBTclass	*_rc;
			NodePtr		_map;
			key_compare	_compare;
			friend class	mapiter<const V>;

		public:
			mapiter(void): _map(nullptr)
			{}
			~mapiter(void){}
		//		NodePtr start = _rbtmap.minimum(_rbtmap.getRoot());
			mapiter(RBTclass *rc): _rc(rc)
			{
				if (_rc->getSize() == 0)
					_map = _rc->getNull();
				else
					_map = _rc->minimum(_rc->getRoot());
			}
			mapiter(RBTclass *rc, NodePtr n): _rc(rc), _map(n)
			{}
			mapiter(const mapiter & src)
			: _rc(src._rc), _map(src._map), _compare(src._compare){}
			mapiter & operator=(mapiter const & rhs)
			{
				if (this != &rhs)
					_map = rhs._map;
				return (*this);
			}

			template<typename X, typename Y>
			friend bool operator==(const mapiter<X> & lhs, const mapiter<Y> & rhs)
			{
				return (lhs._map->data.first == rhs._map->data.first);
			}
			
			template<typename X, typename Y>
			friend bool operator!=(const mapiter<X> & lhs, const mapiter<Y> & rhs)
			{ return (!(lhs == rhs)); }

			mapiter & operator++()
			{
				NodePtr nullNode = _rc->getNull();
				if (_rc->getSize() == 0)
					_map = nullNode;
				else if (((_map->left == nullNode || _map->right == nullNode)
						&& _map->parent == nullptr) || _map->parent == nullNode)
						_map = nullNode;
				else if (_map->parent && _compare(_map->data.first, _map->parent->data.first)
						&& _map->right == nullNode)
						_map = _map->parent;
				else if (_map->right != nullNode)
					_map = _rc->minimum(_map->right);
				else
				{
						NodePtr p = _map->parent;
						while (p != nullptr && _compare(p->data.first, _map->data.first))
							p = p->parent;
						if (p == nullptr)
							_map = nullNode;
						else
							_map = p;
				}
				return (*this);
			}

			mapiter operator++(int)
			{
				mapiter old(*this);
				NodePtr nullNode = _rc->getNull();
				if (_rc->getSize() == 0)
					_map = nullNode;
				else if (((_map->left == nullNode || _map->right == nullNode)
						&& _map->parent == nullptr) || _map == nullNode)
						_map = nullNode;
			//	else if (_map->parent && _compare(_map->data.first, _map->parent->data.first)
			//			&& _map->right == nullNode)
			//			_map = _map->parent;
				else if (_map->right != nullNode)
					_map = _rc->minimum(_map->right);
				else
				{
						NodePtr p = _map->parent;
						while (p != nullptr && _compare(p->data.first, _map->data.first))
							p = p->parent;
						if (p == nullptr)
							_map = nullNode;
						else
							_map = p;
				}
				return (old);
			}

			mapiter & operator--()
			{
				NodePtr nullNode = _rc->getNull();
				if (_rc->getSize() == 0)
					_map = nullNode;
				else if (_map == nullNode && _rc->getSize() >= 1)
					_map = _rc->maximum(_rc->getRoot());
				else if (_map->left != nullNode)
					_map = _rc->maximum(_map->left);
				else
				{
					NodePtr p = _map->parent;
					while (p != nullptr && _compare(_map->data.first, p->data.first))
						p = p->parent;
					if (p == nullptr)
						_map = nullNode;
					else
						_map = p;
				}
				return (*this);
			}

			mapiter operator--(int)
			{
				mapiter old(*this);
				NodePtr nullNode = _rc->getNull();
				if (_rc->getSize() == 0)
					_map = nullNode;
				else if (_map == nullNode && _rc->getSize() >= 1)
					_map = _rc->maximum(_rc->getRoot());
				else if (_map->left != nullNode)
					_map = _rc->maximum(_map->left);
				else
				{
					NodePtr p = _map->parent;
					while (p != nullptr && _compare(_map->data.first, p->data.first))
						p = p->parent;
					if (p == nullptr)
						_map = nullNode;
					else
						_map = p;
				}
				return (old);
			}

			reference operator*() const
			{ return (*_map->data); }

			pointer operator->() const
			{
				return (&_map->data);
			}
	};
	
	template<typename K, typename T, typename C, typename A>
	template <typename V>
	class map<K, T, C, A>::mapiter<const V>
	{
		public:
			typedef map<K, T, C, A> 		MAP;
			typedef MAP::difference_type	difference_type;
			typedef V						value_type;
			typedef const V&				const_reference;
			typedef const V*				const_pointer;
			std::bidirectional_iterator_tag	iterator_category;

		protected:
			const RBTclass	*_rc;
			NodePtr		_map;
			key_compare	_compare;

		public:
			mapiter(void): _map(nullptr)
			{}
			~mapiter(void){}
			mapiter(const RBTclass *rc): _rc(rc)
			{
				if (_rc->getSize() == 0)
					_map = _rc->getNull();
				else
					_map = _rc->minimum(_rc->getRoot());
			}
			mapiter(const RBTclass *rc, NodePtr n): _rc(rc), _map(n){}
			mapiter(const mapiter<typename std::remove_const<value_type>::type> & src)
			: _rc(src._rc), _map(src._map), _compare(src._compare){}
			mapiter & operator=(mapiter const & rhs)
			{
				if (this != rhs)
					_map = rhs._map;
				return (*this);
			}

			template<typename X, typename Y>
			friend bool operator==(const mapiter<X> & lhs, const mapiter<Y> & rhs)
			{ return (lhs._map->data.first == rhs._map->data.first); }
			
			template<typename X, typename Y>
			friend bool operator!=(const mapiter<X> & lhs, const mapiter<Y> & rhs)
			{ return (!(lhs == rhs)); }

			mapiter & operator++()
			{
				NodePtr nullNode = _rc->getNull();
				if (_rc->getSize() == 0)
					_map = nullNode;
				else if (((_map->left == nullNode || _map->right == nullNode)
						&& _map->parent == nullptr) || _map->parent == nullNode)
					_map = nullNode;
				else if (_map->parent && _compare(_map->data.first, _map->parent->data.first) && _map->right == nullNode)
					_map = _map->parent;
				else if (_map->right != nullNode)
					_map = _rc->minimum(_map->right);
				else
				{
					NodePtr p = _map->parent;
					while (p != nullptr && _compare(p->data.first, _map->data.first))
						p = p->parent;
					if (p == nullptr)
						_map = nullNode;
					else
						_map = p;
				}
				return (*this);
			}

			mapiter operator++(int)
			{
				mapiter old(*this);
				NodePtr nullNode = _rc->getNull();
				if (_rc->getSize() == 0)
					_map = nullNode;
				else if (((_map->left == nullNode || _map->right == nullNode)
						&& _map->parent == nullptr) || _map->parent == nullNode)
					_map = nullNode;
				else if (_map->parent && _compare(_map->data.first, _map->parent->data.first) && _map->right == nullNode)
					_map = _map->parent;
				else if (_map->right != nullNode)
					_map = _rc->minimum(_map->right);
				else
				{
					NodePtr p = _map->parent;
					while (p != nullptr && _compare(p->data.first, _map->data.first))
						p = p->parent;
					if (p == nullptr)
						_map = nullNode;
					else
						_map = p;
				}
				return (old);
			}

			mapiter & operator--()
			{
				NodePtr nullNode = _rc->getNull();
				if (_rc->getSize() == 0)
					_map = nullNode;
				else if (_map == nullNode && _rc->getSize() >= 1)
					_map = _rc->maximum(_rc->getRoot());
				else if (_map->left != nullNode)
					_map = _rc->maximum(_map->left);
				else
				{
					NodePtr p = _map->parent;
					while (p != nullptr && _compare(_map->data.first, p->data.first))
						p = p->parent;
					if (p == nullptr)
						_map = nullNode;
					else
						_map = p;
				}
				return (*this);
			}

			mapiter operator--(int)
			{
				mapiter old(*this);
				NodePtr nullNode = _rc->getNull();
				if (_rc->getSize() == 0)
					_map = nullNode;
				else if (_map == nullNode && _rc->getSize() >= 1)
					_map = _rc->maximum(_rc->getRoot());
				else if (_map->left != nullNode)
					_map = _rc->maximum(_map->left);
				else
				{
					NodePtr p = _map->parent;
					while (p != nullptr && _compare(_map->data.first, p->data.first))
						p = p->parent;
					if (p == nullptr)
						_map = nullNode;
					else
						_map = p;
				}
				return (old);
			}

			const_reference operator*() const
			{ return (*_map->data); }

			const_pointer operator->() const
			{ return (&_map->data); }
	};
}

#endif
