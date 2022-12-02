/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:56:45 by leng-chu          #+#    #+#             */
/*   Updated: 2022/12/02 18:19:10 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <cstddef> // for linux ptrdiff_t
# include <stdexcept>
# include "color.hpp"
# include "myiterator.hpp"

using std::cout;
using std::endl;
using std::cin;

namespace	ft
{
	template <typename T, class Allocator = std::allocator<T> >
	class vector
	{
		/*** MEMBER TYPES ***/
		typedef T											value_type;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef std::ptrdiff_t				difference_type;
		typedef size_t					size_type;
		/*** END OF MEMBER TYPES ***/
		
		/*** ATTRIBUTES ***/
		size_type		_capacity;
		size_type		_size;
		allocator_type	_myalloc;
		pointer			 _vec;
		/*** END OF ATTRIBUTES ***/
		
		public:
			class iterator;
			typedef const iterator const_iterator;
			/*** MEMBER FUNCTIONS ***/
			// constructor
			explicit vector(const allocator_type & alloc = allocator_type())
				: _capacity(0), _size(0), _myalloc(alloc), _vec(0)
			{
				cout << YLW"default constructor"DEF << endl;
			}

			explicit vector(size_type count,
					const value_type & value = value_type(),
					const Allocator & alloc = allocator_type())
				: _capacity(count), _size(0), _myalloc(alloc)
			{
				cout << YLW"constructor with size count & value"DEF << endl;
				_vec = _myalloc.allocate(_capacity);
				for (size_type i = 0; i < count; ++i)
				{
					_myalloc.construct(_vec + i, value);
					_size++;
				}
			}

			template<class InputIterator,
				typename ft::enable_if<!ft::is_same<typename ft::iterator_traits<InputIterator>::value_type, void>::value, bool>::type>
				vector( InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type())
				{
					cout << YLW"constructor with iterator first & second"DEF << endl;
					(void)first;
					(void)last;
					(void)alloc;
				}

			vector(vector const & x)
			: _capacity(x._capacity), _size(x._size), _myalloc(x._myalloc), _vec(x._vec)
			{}

			// destructor
			~vector(void) { 
				for (size_type i = 0; i < _size; ++i)
					_myalloc.destroy(_vec + i);
				_myalloc.deallocate(_vec, _capacity);
				cout << RED"destructor"DEF << endl; }

			// operator=
			vector & operator=(vector const & rhs);

			/*** ITERATORS ***/
			iterator begin()
			{
				return (iterator(this->_vec, 0));
			}
			const_iterator begin() const
			{
				return (const_iterator(this->_vec, 0));
			}
			iterator end()
			{
				return (iterator(this->_vec, this->_size));
			}
			const_iterator end() const
			{
				return (NULL);
			}
			/*** CAPACITY ***/
			size_type size() const { return (_size); }
			size_type max_size() const { return (_myalloc.max_size()); }
			void resize(size_type n, value_type val = value_type())
			{
				if (n < _size)
					for (size_type i = n; i < _size; ++i)
						_myalloc.destroy(_vec + i);
				else if (n > _size)
				{
					if (n > _capacity)
					{
						pointer tmp = _vec;
						_vec = _myalloc.allocate(n);
						_capacity = n > _capacity * 2 ? n : _capacity * 2;
						for (size_type i = 0; i < _size; ++i)
						{
							_myalloc.construct(_vec + i, tmp[i]);
							_myalloc.destroy(tmp + i);
						}
						_myalloc.deallocate(tmp, _capacity);
						for (size_type i = _size; i < n; ++i)
							_myalloc.construct(_vec + i, val);
					}
					else
						for (size_type i = _size; i < n; ++i)
							_myalloc.construct(_vec + i, val);
				}
				_size = n;
			}
			size_type capacity() const { return (_capacity); }
			bool empty() const { return (_size == 0); }
			void reserve(size_type n)
			{
				if (n > _capacity)
				{
					pointer tmp = _vec;
					_vec = _myalloc.allocate(n);
					for (size_type i = 0; i < _size; ++i)
					{
						_myalloc.construct(_vec + i, tmp[i]);
						_myalloc.destroy(tmp + i);
					}
					_myalloc.deallocate(tmp, _capacity);
					_capacity = n;
				}
			}
			void	shrink_to_fit()
			{
				if (_capacity > _size)
				{
					pointer tmp = _vec;
					_vec = _myalloc.allocate(_size);
					for (size_type i = 0; i < _size; ++i)
					{
						_myalloc.construct(_vec + i, tmp[i]);
						_myalloc.destroy(tmp + i);
					}
					_myalloc.deallocate(tmp, _capacity);
					_capacity = _size;
				}
			}
			
			/*** ELEMENT ACCESS ***/
			reference operator[] (size_type n) { return (_vec[n]); }
			const_reference operator[] (size_type n) const { return (_vec[n]); }
			reference at (size_type n)
			{
				if (n >= _size)
					throw (std::out_of_range("out of range"));
				return (_vec[n]);
			}
			const_reference at (size_type n) const
			{
				if (n >= _size)
					throw (std::out_of_range("out of range"));
				return (_vec[n]);
			}
			reference front() { return (_vec[0]); }
			const_reference front() const { return (_vec[0]); }
			reference back() { return (_vec[_size - 1]); }
			const_reference back() const { return (_vec[_size - 1]); }
			value_type *data() { return (_vec); }
			value_type *data() const { return (_vec); }

			/*** MODIFIERS ***/

			/*** ALLOCATOR ***/
			allocator_type get_allocator() const { return (allocator_type(_myalloc)); }
			
			/*** NON-MEMBER FUNCTION OVERLOADS ***/
	};
	// my iterator
	template <typename T, class A>
	class vector<T, A>::iterator
	{
		typedef typename
		A::difference_type				difference_type;
		typedef typename
		A::value_type					value_type;
		typedef typename
		A::reference					reference;
		typedef typename
		A::pointer						pointer;
		typedef typename
		std::random_access_iterator_tag	iterator_category;

		value_type	_index;
		pointer		_data;
		public:
			iterator(void)
			:_index(0), _data(nullptr)
			{ cout << "iterator constructor" << endl; }
			iterator(pointer vec, value_type index)
			: _index(index), _data(vec)
			{ cout << "iterator constructor parameter" << endl; }
			~iterator(void)
			{ cout << "iterator destructor" << endl; }
			iterator(iterator const & src)
			: _index(src._index), _data(src._data)
			{ cout << "iterator copy constructor" << endl; }
			iterator & operator=(iterator const & rhs) {
				if (this != &rhs) {
					_index = rhs._index;
					_data = rhs._data;
				}
			}
			bool operator==(const iterator & other) const
			{ return (_index == other._index); }
			bool operator!=(const iterator & other) const
			{ return (_index != other._index); }
			bool operator<(const iterator & other) const
			{ return (_index < other._index); }
			bool operator>(const iterator & other) const
			{ return (_index > other._index); }
			bool operator<=(const iterator & other) const
			{ return (_index <= other._index); }
			bool operator>=(const iterator & other) const
			{ return (_index >= other._index); }

			iterator & operator++()
			{
				cout << "iterator add" << endl;
				this->_index++;
				return (*this);
			}
			iterator operator++(int)
			{
				iterator old(*this);
				(*this)++;
				return (old);
			}
			iterator & operator--()
			{
				this->_index--;
				return (*this);
			}
			iterator operator--(int)
			{
				iterator old(*this);
				(*this)--;
				return (old);
			}
			// iterator & operator+=(size_type);
			// iterator operator+(size_type) const;
			// friend iterator operator+(size_type, const iterator & other);
			// iterator & operator-=(size_type);
			// iterator operator-(size_type) const;
			difference_type operator-(iterator) const;
			reference operator*() const
			{
				return (this->_data[_index]);
			}
			pointer operator->() const;
			reference operator[](value_type) const;
	};
}
#endif
