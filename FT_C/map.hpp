/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 14:24:13 by leng-chu          #+#    #+#             */
/*   Updated: 2023/01/03 12:32:50 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "color.hpp"
# include <iterator>
# include "util.hpp"
# include "lib.hpp"

namespace	ft
{
	template<
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<std::pair<const Key, T> >
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
			typedef std::pair<const Key, T>	value_type;
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

		protected:
			size_type		_capacity;
			size_type		_size;
			allocator_type	_myalloc;
			pointer			_map;
			key_compare		_compare;

		public:
			/***CONSTRUCTOR & DESTRUCTOR***/
			explicit map(const Compare & comp = key_compare(), const allocator_type & alloc = Allocator())
				:_capacity(0), _size(0), _myalloc(alloc), _map(0), _compare(comp){
					cout << "constructor map default" << endl;
				}
			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value>::value_type* = 0)
			: _capacity(0), _size(0), _myalloc(alloc), _compare(comp)
			{
		//		if (_capacity < 0 || _capacity > max_size())
		//			throw(std::length_error("ft::map"));
				(void)first;
				(void)last;
			}
			map(const map & x): _capacity(x._capacity), _size(x._size), _myalloc(x._myalloc), _compare(x._compare)
			{
				// _map need to deep copy
			}
			~map()
			{
				cout << "destructor map" << endl;
			}

			/*** ITERATOR ***/
			iterator begin()
			{ return (iterator(this->_map)); }

			/*** ELEMENT ACCESS ***/
			mapped_type & operator[](const key_type & k)
			{
				if (_size == 0)
				{
					_size++;
					_capacity = _size;
					_map = _myalloc.allocate(_capacity);
					_myalloc.construct(_map, std::make_pair(k, 0));
				}
				return (_map->second);
			}

			/*** CAPACITY ***/
			bool empty() const
			{
				return (_size == 0);
			}

			size_type size() const
			{
				return (_size);
			}

			size_type max_size() const
			{
				if (ft::is_same<char, key_type>::value
					&& ft::is_same<char, mapped_type>::value)
					return (_myalloc.max_size() / 16);
				if ((sizeof(key_type) == sizeof(short)
						&& sizeof(key_type) >= sizeof(mapped_type))
						||
						(sizeof(mapped_type) == sizeof(short)
						 && sizeof(mapped_type) >= sizeof(key_type)))
					return (_myalloc.max_size() / 8);
				if ((sizeof(key_type) == sizeof(wchar_t)
						&& sizeof(key_type) >= sizeof(mapped_type))
						||
						(sizeof(mapped_type) == sizeof(wchar_t)
						 && sizeof(mapped_type) >= sizeof(key_type)))
					return (_myalloc.max_size() / 5);
				return (_myalloc.max_size() / 3);
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
			pointer	_map;
			friend class	mapiter<const V>;

		public:
			mapiter(void): _map(nullptr)
			{}
			~mapiter(void){}
			mapiter(value_type *map): _map(map){}
			mapiter(const mapiter & src) : _map(src._map){}
			mapiter & operator=(mapiter const & rhs)
			{
				if (this != rhs)
					_map = rhs._map;
				return (*this);
			}

			template<typename X, typename Y>
			friend bool operator==(const mapiter<X> & lhs, const mapiter<Y> & rhs)
			{ return (lhs._data == rhs._data); }
			
			template<typename X, typename Y>
			friend bool operator!=(const mapiter<X> & lhs, const mapiter<Y> & rhs)
			{ return (lhs._data != rhs._data); }

			mapiter & operator++()
			{
				_map++;
				return (*this);
			}

			mapiter operator++(int)
			{
				mapiter old(*this);
				this->_map++;
				return (old);
			}

			mapiter & operator--()
			{
				this->_map--;
				return (*this);
			}

			mapiter operator--(int)
			{
				mapiter old(*this);
				this->_map--;
				return (old);
			}

			reference operator*() const
			{ return (*_map); }

			pointer operator->() const
			{ return (this->_map); }
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
			pointer	_map;

		public:
			mapiter(void): _map(nullptr)
			{}
			~mapiter(void){}
			mapiter(value_type *map): _map(map){}
			mapiter(const mapiter<typename std::remove_const<value_type>::type> & src) : _map(src._map){}
			mapiter & operator=(mapiter const & rhs)
			{
				if (this != rhs)
					_map = rhs._map;
				return (*this);
			}

			template<typename X, typename Y>
			friend bool operator==(const mapiter<X> & lhs, const mapiter<Y> & rhs)
			{ return (lhs._data == rhs._data); }
			
			template<typename X, typename Y>
			friend bool operator!=(const mapiter<X> & lhs, const mapiter<Y> & rhs)
			{ return (lhs._data != rhs._data); }

			mapiter & operator++()
			{
				_map++;
				return (*this);
			}

			mapiter operator++(int)
			{
				mapiter old(*this);
				this->_map++;
				return (old);
			}

			mapiter & operator--()
			{
				this->_map--;
				return (*this);
			}

			mapiter operator--(int)
			{
				mapiter old(*this);
				this->_map--;
				return (old);
			}

			const_reference operator*() const
			{ return (*_map); }

			const_pointer operator->() const
			{ return (this->_map); }
	};
}

#endif
