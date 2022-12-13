/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:56:45 by leng-chu          #+#    #+#             */
/*   Updated: 2022/12/13 11:11:43 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iterator>
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
	template <typename A>
	class myiter;
	template <typename A>
	class myiter<A const>;
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
			typedef myiter<value_type>	iterator;
			typedef myiter<const value_type>	const_iterator;
			class reverse_iterator;
		//	typedef const iterator<const value_type> const_iterator;

			typedef const reverse_iterator	const_reverse_iterator;
			/*** MEMBER FUNCTIONS ***/
			// constructor
			explicit vector(const allocator_type & alloc = allocator_type())
				: _capacity(0), _size(0), _myalloc(alloc), _vec(0)
			{
			}

			explicit vector(size_type count,
					const value_type & value = value_type(),
					const Allocator & alloc = allocator_type())
				: _capacity(count), _size(0), _myalloc(alloc)
			{
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
				 }

			// operator=
			vector & operator=(vector const & rhs);

			/*** ITERATORS ***/
			iterator begin()
			{
				if (_size == 0) return (iterator());
				return (iterator(this->_vec));
			}
			const_iterator begin() const
			{
				if (_size == 0) return (const_iterator());
				return (const_iterator(this->_vec));
			}
			iterator end()
			{
				if (_size == 0) return (iterator());
				return (iterator(this->_vec + this->_size));
			}
			const_iterator end() const
			{
				if (_size == 0) return (const_iterator());
				return (const_iterator(this->_vec + this->_size));
			}
			reverse_iterator rbegin()
			{
				if (_size == 0) return (reverse_iterator());
				return (reverse_iterator((*this).end()));
			}
			const_reverse_iterator rbegin() const
			{
				if (_size == 0) return (const_reverse_iterator());
				return (const_reverse_iterator((*this).end()));
			}
			reverse_iterator rend()
			{
				if (_size == 0) return (reverse_iterator());
				return (reverse_iterator((*this).begin()));
			}
			reverse_iterator rend() const
			{
				if (_size == 0) return (const_reverse_iterator());
				return (const_reverse_iterator((*this).begin()));
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
			void	push_back(const value_type & val)
			{
				_size++;
				if (_size > _capacity)
				{
					size_type tmpcap = _capacity;
					_capacity = _capacity == 0 ? 1 : _capacity * 2;
					pointer tmp = _vec;
					_vec = _myalloc.allocate(_capacity);
					size_type i = 0;
					for (; i < tmpcap; ++i)
					{
						_myalloc.construct(_vec + i, tmp[i]);
						_myalloc.destroy(tmp + i);
					}
					_myalloc.deallocate(tmp, tmpcap);
					_myalloc.construct(_vec + i, val);
				}
				else
					_myalloc.construct(_vec + (_size - 1), val);
			}
			/*** ALLOCATOR ***/
			allocator_type get_allocator() const { return (allocator_type(_myalloc)); }
			
			/*** NON-MEMBER FUNCTION OVERLOADS ***/
	};
	// my iterator
	template<typename A>
	class myiter
	{
		public:
		typedef std::ptrdiff_t				difference_type;
		typedef A					value_type;
		typedef A&					reference;
		typedef A*						pointer;
		typedef typename
		std::random_access_iterator_tag	iterator_category;
		
		protected:
		pointer		_data;
		public:
			friend class myiter<A const>;
			myiter(void)
			:_data(nullptr){}
			myiter(value_type *vec)
			:_data(vec){}
			~myiter(void){}
			myiter(myiter const & src)
			: _data(src._data){}
			myiter & operator=(myiter const & rhs) {
				if (this != &rhs) {
					_data = rhs._data;
				}
				return (*this);
			}
			bool operator==(const myiter & other) const
			{ return (_data == other._data); }
			bool operator!=(const myiter & other) const
			{ return (_data != other._data); }
			bool operator<(const myiter & other) const
			{ return (_data < other._data); }
			bool operator>(const myiter & other) const
			{ return (_data > other._data); }
			bool operator<=(const myiter & other) const
			{ return (_data <= other._data); }
			bool operator>=(const myiter & other) const
			{ return (_data >= other._data); }

			myiter & operator++()
			{
				_data++;
				return (*this);
			}
			myiter operator++(int)
			{
				myiter old(*this);
				this->_data++;
				return (old);
			}
			myiter & operator--()
			{
				this->_data--;
				return (*this);
			}
			myiter operator--(int)
			{
				myiter old(*this);
				(*this)--;
				return (old);
			}
			// myiter & operator+=(size_t);
			myiter operator+(size_t x) const
			{
				return (myiter(_data + x));
			}
			// friend myiter operator+(size_t, const myiter & other);
			// myiter & operator-=(size_t);
			// myiter operator-(size_t) const;
			//difference_type operator-(myiter x) const
			myiter operator-(size_t x) const
			{
				myiter tmp(_data - x);
				return (tmp);
			}
			reference operator*() const
			{
				return (*_data);
			}
			pointer operator->() const
			{
				return (this->_data);
			}
			reference operator[](size_t i) const
			{
				return (_data[i]);
			}
	};
	template <typename A>
	class myiter<const A>
	{
		typedef std::ptrdiff_t				difference_type;
		typedef A					value_type;
		typedef A&					reference;
		typedef A*						pointer;
		typedef const A&	const_reference;
		typedef typename
		std::random_access_iterator_tag	iterator_category;
		
		protected:
		pointer _data;
		public:
			myiter():_data(nullptr){}
			~myiter(){}
			myiter(const myiter<typename std::remove_const<value_type>::type> & src):_data(src._data){}
		myiter & operator=(const myiter & rhs) {
			if (this != &rhs) {
				_data = rhs._data;
			}
			return (*this);
		}
		bool operator==(const myiter & other) const
		{ return (_data == other._data); }
		bool operator!=(const myiter & other) const
		{ return (_data != other._data); }
		bool operator<(const myiter & other) const
		{ return (_data < other._data); }
		bool operator>(const myiter & other) const
		{ return (_data > other._data); }
		bool operator<=(const myiter & other) const
		{ return (_data <= other._data); }
		bool operator>=(const myiter & other) const
		{ return (_data >= other._data); }

		myiter & operator++()
		{
			_data++;
			return (*this);
		}
		myiter operator++(int)
		{
			myiter old(*this);
			this->_data++;
				return (old);
		}
		myiter & operator--()
		{
			this->_data--;
			return (*this);
		}
		myiter operator--(int)
		{
			myiter old(*this);
			(*this)--;
			return (old);
		}
		// myiter & operator+=(size_t);
		myiter operator+(size_t x) const
		{
			return (myiter(_data + x));
		}
		// friend myiter operator+(size_t, const myiter & other);
		// myiter & operator-=(size_t);
		// myiter operator-(size_t) const;
		//difference_type operator-(myiter x) const
		myiter operator-(size_t x) const
		{
			myiter tmp(_data - x);
			return (tmp);
		}
		const_reference operator*() const
		{
			return (*_data);
		}
		const pointer operator->() const
		{
			return (this->_data);
		}
		const_reference operator[](size_t i) const
		{
			return (_data[i]);
		}
	};
	template <typename T, class A>
	class vector<T, A>::reverse_iterator
	{
		typedef iterator iterator_type;
		typedef typename ft::iterator_traits<iterator>::iterator_category
		iterator_category;
		typedef typename ft::iterator_traits<iterator>::value_type
		value_type;
		typedef typename ft::iterator_traits<iterator>::difference_type
		difference_type;
		typedef typename ft::iterator_traits<iterator>::pointer
		pointer;
		typedef typename ft::iterator_traits<iterator>::reference
		reference;
		typedef typename ft::iterator_traits<iterator>::size_type
		size_type;

		pointer			_data;
		size_type		_index;
		public:
		reverse_iterator(): _data(nullptr), _index(0){}

		reverse_iterator(iterator_type x): _data(x._data), _index(x._index - 1)
		{ if (_index <= 0) _index = 0; }

		reverse_iterator(const reverse_iterator & other)
		: _data(other._data), _index(other._index){}

		~reverse_iterator(){}
		reverse_iterator & operator=(const reverse_iterator & other)
		{
			if (this != &other)
			{
				this->_index = other._index;
				this->_data = other._data;
			}
			return (*this);
		}
		iterator_type base() const
		{
			iterator_type base(_data, _index + 1);
			return (base);
		}
		reference operator*() const { return (_data[_index]); }
		reverse_iterator operator+(difference_type n) const
		{
			reverse_iterator plus(_data, _index - n);
			return (plus);
		}
		reverse_iterator & operator++()
		{
			this->_index--;
			if (this->_index < 0)
				this->_index = 0;
			return (*this);
		}
		reverse_iterator operator++(int)
		{
			reverse_iterator tmp(*this);
			this->_index -= 1;
			return (tmp);
		}
		reverse_iterator & operator+=(difference_type n);
		reverse_iterator operator-(difference_type n) const
		{
			reverse_iterator tmp(_data, _index - n);
			return (tmp);
		}
		reverse_iterator & operator--()
		{
			if (_data[_index])
				this->index++;
			return (*this);
		}
		reverse_iterator operator--(int)
		{
			reverse_iterator tmp(*this);
			(*this)--;
			return (tmp);
		}
		reverse_iterator & operator-=(difference_type n);
		pointer operator->() const;
		reference operator[](difference_type n) const;
	
		bool operator!=(const_reverse_iterator & rhs)
		{
			return (this->_index != rhs._index);
		}
	};

	// non-member function overloads for reverse iterator
	template <class T, class A>
	bool operator==(typename vector<T, A>::const_reverse_iterator & lhs, typename vector<T, A>::const_reverse_iterator & rhs);
	
//	template <class T, class A>
//	bool operator!=(typename vector<T, A>::const_reverse_iterator & lhs, typename vector<T, A>::const_reverse_iterator & rhs);

	template <class T, class A>
	bool operator<(typename vector<T, A>::const_reverse_iterator & lhs, typename vector<T, A>::const_reverse_iterator & rhs);
	
	template <class T, class A>
	bool operator<=(typename vector<T, A>::const_reverse_iterator & lhs, typename vector<T, A>::const_reverse_iterator & rhs);
	
	template <class T, class A>
	bool operator>(typename vector<T, A>::const_reverse_iterator & lhs, typename vector<T, A>::const_reverse_iterator & rhs);
	
	template <class T, class A>
	bool operator>=(typename vector<T, A>::const_reverse_iterator & lhs, typename vector<T, A>::const_reverse_iterator & rhs);

	template <class T, class A>
	typename vector<T, A>::reverse_iterator operator+(typename vector<T, A>::reverse_iterator::difference_type n, typename vector<T, A>::const_reverse_iterator & rev_it);
	
//				typename ft::enable_if<!ft::is_same<typename ft::iterator_traits<InputIterator>::value_type, void>::value, bool>::type>
	template <class T, class A, typename ft::enable_if<!ft::is_integral<T>::value, bool> >
	typename vector<T, A>::reverse_iterator operator-(typename vector<T, A>::reverse_iterator::difference_type n, typename vector<T, A>::const_reverse_iterator & rev_it);
// this line before the end of the namespace ft
}
	
#endif
