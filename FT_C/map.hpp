/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 14:24:13 by leng-chu          #+#    #+#             */
/*   Updated: 2023/01/14 14:21:33 by leng-chu         ###   ########.fr       */
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
			typedef mapitrev<const iterator> const_reverse_iterator;
			typedef RedBlackTree<Key, mapped_type, value_type, key_compare> RBTclass;
			typedef typename RedBlackTree<Key, mapped_type, value_type, key_compare>::NodePtr NodePtr;
			typedef typename RedBlackTree<Key, mapped_type, value_type, key_compare>::NodeM NodeM;

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
			map(const map & x): _size(x._size), _myalloc(x._myalloc), _rbtmap(), _compare(x._compare)
			{
				// _map need to deep copy
				const_iterator it = x.begin();
				const_iterator ite = x.end();
			//	while (it != ite)
					//insert
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

			reverse_iterator rbegin()
			{
				return (reverse_iterator(--end()));
			}

			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(--end()));
			}

			reverse_iterator rend()
			{
				//return (++reverse_iterator(begin()));
				return (reverse_iterator(begin()));
			}

			const_reverse_iterator rend() const
			{
				//return (++const_reverse_iterator(begin()));
				return (const_reverse_iterator(begin()));
			}

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

			mapped_type & at(const key_type & k)
			{
				NodePtr find = _rbtmap.searchTree(k);
				if (find == _rbtmap.getNull())
					throw(std::invalid_argument("ft::map::at: key not found\n"));
				return (find->data.second);
			}

			const mapped_type & at(const key_type & k) const
			{
				NodePtr find = _rbtmap.searchTree(k);
				if (find == _rbtmap.getNull())
					throw(std::invalid_argument("ft::map::at: key not found\n"));
				return (find->data.second);
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
				if (sizeof(value_type) == 12) // lol dont know why 12 return different size
					return (tmp.max_size() / (28 + sizeof(value_type)));
				return (tmp.max_size() / (32 + sizeof(value_type)));
			}
			/*** MODIFIERS ***/
			ft::pair<iterator, bool> insert(const value_type & val)
			{
				ft::pair<iterator, bool> ret;
				ft::pair<NodePtr, bool> box;

//				_rbtmap.insert2(val.first);
				box = _rbtmap.insert2(val.first);
//				value_type tmp = check->data;
				if (box.second)
					box.first->data.second = val.second;
		//		else
		//			cout << "FALSE!" << endl;
//				check->data.second = val.second;
				ret = ft::make_pair(iterator(&_rbtmap, box.first), box.second);
				return (ret);
			}
			iterator insert(iterator position, const value_type & val);
			template <class InputIterator>
			void insert(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::value_type* = 0);
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
			typedef std::bidirectional_iterator_tag	iterator_category;

		protected:
			RBTclass	*_rc;
			NodePtr		_map;
			key_compare	_compare;
			friend class	mapiter<const V>;
			friend class	mapitrev<iterator>;
			friend class	mapitrev<const iterator>;

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
				{
					_rc = rhs._rc;
					_map = rhs._map;
					_compare = rhs._compare;
				}
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
						_map = nullptr;
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
						_map = nullptr;
					else
						_map = p;
				}
				return (old);
			}

			reference operator*() const
			{ return (_map->data); }

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
			typedef std::bidirectional_iterator_tag	iterator_category;

		protected:
			const RBTclass	*_rc;
			NodePtr		_map;
			key_compare	_compare;
			template <typename Iter>
			friend class mapitrev;

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
				{
					_rc = rhs._rc;
					_map = rhs._map;
					_compare = rhs._compare;
				}
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
						_map = nullptr;
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
						_map = nullptr;
					else
						_map = p;
				}
				return (old);
			}

			const_reference operator*() const
			{ return (_map->data); }
			
			const_pointer operator->() const
			{ return (&_map->data); }
	};

	template<typename K, typename T, typename C, typename A>
	template<typename Iter>
	class map<K, T, C, A>::mapitrev
	{
		public:
			typedef map<K, T, C, A>				MAP;
			typedef Iter						iterator_type;
			typedef typename ft::iterator_traits<iterator>::value_type
				value_type;
			typedef typename ft::iterator_traits<iterator>::difference_type
				difference_type;
			typedef typename ft::iterator_traits<iterator>::pointer
				pointer;
			typedef typename ft::iterator_traits<iterator>::reference
				reference;
			typedef typename ft::iterator_traits<iterator>::iterator_category
				iterator_category;
		protected:
			RBTclass	*_rc;
			NodePtr		_map;
			key_compare	_compare;
			friend class mapitrev<const Iter>;
			friend class mapitrev<const_iterator>;

		public:
			mapitrev(void)
			: _rc(nullptr), _map(nullptr), _compare(){}
			~mapitrev(void){}
			mapitrev(reverse_iterator it)
			: _rc(it._rc), _map(it._map), _compare(it._compare)
			{}
	//		mapitrev(const_iterator it)
	//		: _rc(it._rc), _map(it._map), _compare(it._compare){}
			mapitrev(iterator it)
			: _rc(it._rc), _map(it._map), _compare(it._compare)
			{
		//		if (_map == nullptr)
		//			cout << "pass" << endl;
		//		else if (_map == _rc->getNull())
		//			cout << "null" << endl;
				if (_rc->getSize() >= 1 && _map == _rc->minimum(_rc->getRoot()))
						_map = _rc->getNull();
			}
			mapitrev(const mapitrev & src)
			: _rc(src._rc), _map(src._map), _compare(src._compare){}
			mapitrev & operator=(mapitrev const & rhs)
			{
				if (this != &rhs)
				{
					_rc = rhs._rc;
					_map = rhs._map;
					_compare = rhs._compare;
				}
				return (*this);
			}

			iterator_type base() const
			{
			//mapiter(const RBTclass *rc, NodePtr n): _rc(rc), _map(n){}
				mapitrev tmp(*this);
				--tmp;
				return (iterator(_rc, tmp._map));
			}

			template<typename X, typename Y>
			friend bool operator==(const mapitrev<X> & lhs, const mapitrev<Y> & rhs)
			{
				return (lhs._map->data.first == rhs._map->data.first);
			}

			template<typename X, typename Y>
			friend bool operator!=(const mapitrev<X> & lhs, const mapitrev<Y> & rhs)
			{
				return (!(lhs == rhs));
			}

			mapitrev & operator++()
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
//				_it--;
				return (*this);
			}

			mapitrev operator++(int)
			{
				mapitrev old(*this);
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

			mapitrev & operator--()
			{
		//		_it++;
				NodePtr nullNode = _rc->getNull();
				if (_rc->getSize() == 0)
					_map = nullNode;
				else if (_map == nullNode && _rc->getSize() >= 1)
					_map = _rc->minimum(_rc->getRoot());
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
						_map = nullptr;
					else
						_map = p;
				}
				return (*this);
			}

			mapitrev operator--(int)
			{
				mapitrev old(*this);
				NodePtr nullNode = _rc->getNull();
				if (_rc->getSize() == 0)
					_map = nullNode;
				else if (_map == nullNode && _rc->getSize() >= 1)
					_map = _rc->minimum(_rc->getRoot());
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
						_map = nullptr;
					else
						_map = p;
				}
				return (old);
			}

			reference operator*() const
			{
				return (_map->data);
			}

			pointer operator->() const
			{
				return (&_map->data);
			}
	};

	template<typename K, typename T, typename C, typename A>
	template <typename Iter>
	class map<K, T, C, A>::mapitrev<const Iter>
	{
		public:
			typedef map<K, T, C, A>		MAP;
			typedef Iter				iterator_type;
			typedef typename	ft::iterator_traits<iterator_type>::value_type
				value_type;
			typedef typename	ft::iterator_traits<iterator_type>::difference_type
				difference_type;
			typedef const value_type& const_reference;
			typedef const value_type* const_pointer;
			typedef typename	ft::iterator_traits<iterator>::iterator_category
				iterator_category;
		protected:
			const RBTclass	*_rc;
			NodePtr		_map;
			key_compare	_compare;
		public:
			mapitrev(void)
			: _rc(nullptr), _map(nullptr), _compare(){}
			~mapitrev(void){}
			mapitrev(reverse_iterator it)
			: _rc(it._rc), _map(it._map), _compare(it._compare)
			{}
			mapitrev(const_iterator it)
			: _rc(it._rc), _map(it._map), _compare(it._compare)
			{
			//	if (_map == _rc->minimum(_rc->getRoot()))
				if (_rc->getSize() >= 1 && _map == _rc->minimum(_rc->getRoot()))
						_map = _rc->getNull();
			}
			mapitrev(iterator it)
			: _rc(it._rc), _map(it._map), _compare(it._compare)
			{
			//	if (_map == _rc->minimum(_rc->getRoot()))
				if (_rc->getSize() >= 1 && _map == _rc->minimum(_rc->getRoot()))
						_map = _rc->getNull();
			}
			mapitrev(const mapitrev & src)
			: _rc(src._rc), _map(src._map), _compare(src._compare){}
			mapitrev & operator=(mapitrev const & rhs)
			{
				if (this != &rhs)
				{
					_rc = rhs._rc;
					_map = rhs._map;
					_compare = rhs._compare;
				}
				return (*this);
			}
			
			iterator_type base() const
			{
			//mapiter(const RBTclass *rc, NodePtr n): _rc(rc), _map(n){}
				return (++iterator(_rc, _map));
			}

			template<typename X, typename Y>
			friend bool operator==(const mapitrev<X> & lhs, const mapitrev<Y> & rhs)
			{
				return (lhs._map->data.first == rhs._map->data.first);
			}

			template<typename X, typename Y>
			friend bool operator!=(const mapitrev<X> & lhs, const mapitrev<Y> & rhs)
			{
				return (!(lhs == rhs));
			}

			mapitrev & operator++()
			{
				NodePtr nullNode = _rc->getNull();
				if (_rc->getSize() == 0)
					_map = nullNode;
//				else if (_map == nullNode && _rc->getSize() >= 1)
//					_map = _rc->maximum(_rc->getRoot());
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
//				_it--;
				return (*this);
			}

			mapitrev operator++(int)
			{
				mapitrev old(*this);
				NodePtr nullNode = _rc->getNull();
				if (_rc->getSize() == 0)
					_map = nullNode;
//				else if (_map == nullNode && _rc->getSize() >= 1)
//					_map = _rc->maximum(_rc->getRoot());
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

			mapitrev & operator--()
			{
		//		_it++;
				NodePtr nullNode = _rc->getNull();
				if (_rc->getSize() == 0)
					_map = nullNode;
				else if (_map == nullNode && _rc->getSize() >= 1)
					_map = _rc->minimum(_rc->getRoot());
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
						_map = nullptr;
					else
						_map = p;
				}
				return (*this);
			}

			mapitrev operator--(int)
			{
				mapitrev old(*this);
				NodePtr nullNode = _rc->getNull();
				if (_rc->getSize() == 0)
					_map = nullNode;
				else if (_map == nullNode && _rc->getSize() >= 1)
					_map = _rc->minimum(_rc->getRoot());
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
						_map = nullptr;
					else
						_map = p;
				}
				return (old);
			}

			const_reference operator*() const
			{
				return (_map->data);
			}

			const_pointer operator->() const
			{
				return (&_map->data);
			}
	};
}

#endif
