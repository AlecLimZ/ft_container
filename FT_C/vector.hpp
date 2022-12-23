/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:56:45 by leng-chu          #+#    #+#             */
/*   Updated: 2022/12/23 17:38:35 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iterator>
# include <iostream>
# include <cstddef> // for linux ptrdiff_t
# include <stdexcept>
# include "color.hpp"
# include <algorithm>
# include <vector>
# include "util.hpp"

using std::cout;
using std::endl;
using std::cin;

namespace	ft
{
	template <typename T, class Allocator = std::allocator<T> >
	class vector
	{
		template <typename Iter>
		class myiterev;
		template <typename A>
		class myiter;
		public:
		/*** MEMBER TYPES ***/
		typedef T											value_type;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef std::ptrdiff_t				difference_type;
		typedef size_t					size_type;
		
		typedef myiter<value_type>			iterator;
		typedef myiter<const value_type>	const_iterator;	
		typedef myiterev<iterator>			reverse_iterator;
		typedef myiterev<const iterator>	const_reverse_iterator;
		/*** END OF MEMBER TYPES ***/

		protected:
		/*** ATTRIBUTES ***/
		size_type		_capacity;
		size_type		_size;
		allocator_type	_myalloc;
		pointer			 _vec;
		/*** END OF ATTRIBUTES ***/
		
		public:
			/*** MEMBER FUNCTIONS ***/
			// constructor
			explicit vector(const allocator_type & alloc = allocator_type())
				: _capacity(0), _size(0), _myalloc(alloc), _vec(0){}

			explicit vector(size_type count, const value_type & value = value_type(),
					const Allocator & alloc = allocator_type())
				: _capacity(count), _size(count), _myalloc(alloc)
			{
				if (count < 0 || count > max_size())
					throw (std::length_error("ft::vector"));
				if (_capacity)
					_vec = _myalloc.allocate(_capacity);
				for (size_type i = 0; i < count; ++i)
					_myalloc.construct(_vec + i, value);
			}

			//		template <typename InputIterator>
	//		vector(InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type(), typename ft::iterator_traits<InputIterator>::iterator_category* = 0)

			template <typename InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value>::value_type* = 0)
		//	: _capacity(std::distance(first, last)), _size(0), _myalloc(alloc)
			: _capacity(0), _size(0), _myalloc(alloc)
			{
				//if (first > last)
				if (_capacity < 0 || _capacity > max_size())
					throw (std::length_error("ft::vector"));
		//		if (_capacity)
		//			_vec = _myalloc.allocate(_capacity);
				while (first != last)
			//		_myalloc.construct(_vec + _size++, *first++);
					push_back(*first++);
				shrink_to_fit();
			}

			vector(vector const & x) : _capacity(x._capacity), _size(x._size),
									   _myalloc(allocator_type())
			{
				if (_capacity < 0)
					throw (std::length_error("vector"));
				if (_capacity)
					_vec = _myalloc.allocate(_capacity);
				const_iterator it = x.begin();
				const_iterator ite = x.end();
				int i = 0;
				while (it != ite)
					_myalloc.construct(_vec + i++, *it++);
			}

			~vector(void)
			{ 
				for (size_type i = 0; i < _size; ++i)
					_myalloc.destroy(_vec + i);
				if (_capacity)
					_myalloc.deallocate(_vec, _capacity);
			}

			// operator=
			vector & operator=(vector const & rhs)
			{
				if (this != &rhs)
				{
					for (size_type i = 0; i < _size; ++i)
						_myalloc.destroy(_vec + i);
					if (_capacity)
						_myalloc.deallocate(_vec, _capacity);
					_capacity = rhs._capacity;
					_size = rhs._size;
					if (rhs._size && _capacity)
					{
						const_iterator it = rhs.begin();
						const_iterator ite = rhs.end();
						if (_capacity)
							_vec = _myalloc.allocate(_capacity);
						int i = 0;
						while (it != ite)
							_myalloc.construct(_vec + i++, *it++);
					}
				}
				return (*this);
			}

			/*** ITERATORS ***/
			iterator begin()
			{ return (iterator(this->_vec)); }

			const_iterator begin() const
			{ 
				return (const_iterator(this->_vec)); }

			iterator end()
			{ return (iterator(this->_vec + this->_size)); }

			const_iterator end() const
			{ 
				return (const_iterator(this->_vec + this->_size)); }

			reverse_iterator rbegin()
			{
				return (reverse_iterator(end()));
			}
			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(end()));
			}
			reverse_iterator rend()
			{
				return (reverse_iterator(begin()));
			}
			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(begin()));
			}

			/*** CAPACITY ***/
			size_type size() const { return (_size); }
			size_type max_size() const {
				if (ft::is_same<char, value_type>::value
					|| ft::is_same<unsigned char, value_type>::value)
					return (_myalloc.max_size() / 2);
				return (_myalloc.max_size());
			}
			void resize(size_type n, value_type val = value_type())
			{
				if (n > max_size() || n < 0)
					throw (std::length_error("ft::vector"));
				if (n < _size)
					while (_size > n)
						_myalloc.destroy(_vec + (--_size));
				else if (n > _size)
				{
					if (n > _capacity)
					{
						pointer tmp = _vec;
						size_type tmpc = _capacity;
						_capacity = _capacity == 0 ? n : _capacity * 2;
						if (_capacity < n)
							_capacity = n;
						if (_capacity)
							_vec = _myalloc.allocate(_capacity);
						size_type i = 0;
						for (; i < _size; ++i)
						{
							_myalloc.construct(_vec + i, tmp[i]);
							_myalloc.destroy(tmp + i);
						}
						if (tmpc)
							_myalloc.deallocate(tmp, tmpc);
						while (i < n)
							_myalloc.construct(_vec + i++, val);
						_size = i;
					}
					else
						while (_size < n)
							_myalloc.construct(_vec + _size++, val);
				}
			}
			size_type capacity() const { return (_capacity); }
			bool empty() const { return (_size == 0); }
			void reserve(size_type n)
			{
				if (n > _capacity)
				{
					pointer tmp = _vec;
					if (n)
						_vec = _myalloc.allocate(n);
					for (size_type i = 0; i < _size; ++i)
					{
						_myalloc.construct(_vec + i, tmp[i]);
						_myalloc.destroy(tmp + i);
					}
					if (_capacity)
						_myalloc.deallocate(tmp, _capacity);
					_capacity = n;
				}
			}
			void	shrink_to_fit()
			{
				if (_capacity > _size)
				{
					pointer tmp = _vec;
					if (_size)
						_vec = _myalloc.allocate(_size);
					for (size_type i = 0; i < _size; ++i)
					{
						_myalloc.construct(_vec + i, tmp[i]);
						_myalloc.destroy(tmp + i);
					}
					if (_capacity)
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

			template<class InputIterator>
				void assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::value_type* = 0)
				{
					vector<value_type, Allocator> lol(first , last);
				//	while (first != last)
				//		lol.push_back(*first++);
					size_type sz = lol.size();
					for (size_type i = 0; i < _size; ++i)
						_myalloc.destroy(_vec + i);
					if (sz > _capacity)
					{
						pointer tmp = _vec;
						if (_capacity)
							_myalloc.deallocate(tmp, _capacity);
						_capacity = _capacity == 0 ? sz : _capacity * 2;
						if (_capacity < sz)
							_capacity = sz;
						if (_capacity)
							_vec = _myalloc.allocate(_capacity);
					}
					_size = 0;
					for (size_type j = 0; j < sz; ++j)
						_myalloc.construct(_vec + _size++, lol[j]);
				}

			void assign(size_type n, const value_type & val)
			{
				for (size_type i = 0; i < _size; ++i)
					_myalloc.destroy(_vec + i);
				if (n != _capacity)
				{
					pointer tmp = _vec;
					if (_capacity)
						_myalloc.deallocate(tmp, _capacity);
		//			_capacity = _capacity == 0 ? n : _capacity * 2;
		//			if (_capacity < n)
						_capacity = n;
					if (_capacity)
						_vec = _myalloc.allocate(_capacity);
					_size = 0;
					while (_size < n)
						_myalloc.construct(_vec + _size++, val);
				}
				else
				{
					_size = 0;
					while (_size < n)
						_myalloc.construct(_vec + _size++, val);
				}
			}

			void	push_back(const value_type & val)
			{
				_size++;
				if (_size > _capacity)
				{
					size_type tmpcap = _capacity;
					_capacity = _capacity == 0 ? 1 : _capacity * 2;
					pointer tmp = _vec;
					if (_capacity)
						_vec = _myalloc.allocate(_capacity);
					size_type i = 0;
					for (; i < tmpcap; ++i)
					{
						_myalloc.construct(_vec + i, tmp[i]);
						_myalloc.destroy(tmp + i);
					}
					if (tmpcap)
						_myalloc.deallocate(tmp, tmpcap);
					_myalloc.construct(_vec + i, val);
				}
				else
					_myalloc.construct(_vec + (_size - 1), val);
			}

			void	pop_back()
			{
				if (_size--)
					_myalloc.destroy(_vec + _size);
			}

			iterator insert(iterator position, const value_type & val)
			{
				const size_type distance = std::distance(begin(), position);
				iterator ret;
				if (_size + 1 > _capacity)
				{
					pointer tmp = _vec;
					size_type tmpc = _capacity;
					_capacity = _capacity == 0 ? _size + 1 : _capacity * 2;
					if (_capacity < _size + 1)
						_capacity = _size + 1;
					if (_capacity)
						_vec = _myalloc.allocate(_capacity);
					int p = 0;
					iterator it = tmp;
					while (it != position)
						_myalloc.construct(_vec + p++, *it++);
					_myalloc.construct(_vec + p++, val);
					it = tmp + _size;
					while (position != it)
						_myalloc.construct(_vec + p++, *position++);
					for (size_type j = 0; j < _size; ++j)
							_myalloc.destroy(tmp + j);
					if (tmpc)
						_myalloc.deallocate(tmp, tmpc);
					_size++;
					return (begin() + distance);
				}
				else
				{
					int max = _size;
					iterator last = end();
					if (_size)
						*last = _vec[_size - 1];
					_myalloc.construct(_vec + max, *last);
					_size++;
					iterator ite = end();
		//			while (ite != position)
		//				_vec[max--] = *(--ite - 1);
		//			*position = val;
		//			ret = position;
					ret = position;
					value_type holder = *position;
					value_type holder2;
					*position++ = val;
					while (position != ite)
					{
						holder2 = *position;
						*position = holder;
						holder = holder2;
						position++;
					}
				}
				return (ret);
			}
			void insert(iterator position, size_type n, const value_type & val)
			{
				if (n > max_size() || n < 0)
					throw (std::length_error("ft::vector"));
				iterator itmp = begin();
				iterator itmpe = end();
				if (_size + n > _capacity)
				{
					pointer tmp = _vec;
					size_type tmpcap = _capacity;
					_capacity = _capacity == 0 ? _size + n : _capacity * 2;
					if (_capacity < _size + n)
						_capacity = _size + n;
					if (_capacity)
						_vec = _myalloc.allocate(_capacity);
					int i = 0;
					while (itmp != position)
					{
						_myalloc.construct(_vec + i, *itmp++);
						_myalloc.destroy(tmp + i);
						i++;
					}
					int c = i;
					for (size_type j = 0; j < n; ++j)
						_myalloc.construct(_vec + i++, val);
					while (itmp != itmpe)
					{
						_myalloc.construct(_vec + i++, *itmp++);
						_myalloc.destroy(tmp + c++);
					}
					if (tmpcap)
						_myalloc.deallocate(tmp, tmpcap);
					_size += n;
				}
				else
				{
					_size += n;
					int i = _size - 1;
					int d = std::distance(position, itmpe); // get d before new construct
					int nn = n;
				//	while (n-- && --itmpe != itmp)
				//		_myalloc.construct(_vec + i--, *itmpe);
				//	if (itmpe != position)
				//	{
				//		while (--itmpe != position)
				//			_vec[i--] = *itmpe;
				//	}
				//	_vec[i--] = *position;
				//	while (nn--)
				//		_vec[i--] = val;
					while (n--)
						_myalloc.construct(_vec + i--, val);
					iterator copy = end() - (nn + 1);
					itmpe = end() - 1;
					while (d)
					{
						*itmpe-- = *copy--;
						d--;
					}
					while (nn--)
						*position++ = val;
				}
			}

			template <class InputIterator>
			void insert(iterator position, InputIterator first1, InputIterator last1, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::value_type* = 0)
			{
				vector<value_type, Allocator> lol(first1, last1);
				//size_type n = std::distance(first, last);
				size_type n = lol.size();
				iterator first = lol.begin();
				iterator last = lol.end();

				if (_size + n > _capacity)
				{
					size_type tmpc = _capacity;
					pointer tmp = _vec;
					_capacity = _capacity == 0 ? _size + n : _capacity * 2;
					if (_capacity < _size + n)
						_capacity = _size + n;
					if (_capacity)
						_vec = _myalloc.allocate(_capacity);
					iterator it = tmp;
					int i = 0;
					while (it != position)
						_myalloc.construct(_vec + i++, *it++);
					while (first != last)
						_myalloc.construct(_vec + i++, *first++);
					iterator ite = tmp + _size;
					while (position != ite)
						_myalloc.construct(_vec + i++, *position++);
					for (size_type j = 0; j < _size; ++j)
						_myalloc.destroy(tmp + j);
					if (tmpc)
						_myalloc.deallocate(tmp, tmpc);
					_size += n;
				}
				else
				{
					size_type max = _size + n;
					iterator ite = end() - n;
					while (_size < max)
						_myalloc.construct(_vec + _size++, *ite++);
					if (_size > 0)
					{
						ite = end() - (n + 1);
						iterator pass = ite - n;
						while (pass >= position)
							*ite-- = *pass--;
					}
					while (first != last)
						*position++ = *first++;
	//				_size += n;
	//				iterator ite = end() - 1;
	//				int max = _size + n - 1;
	//				for (size_type i = 0; i < n; ++i)
	//					_myalloc.construct(_vec + max--, *ite--);
	//				while (ite != position)
	//					_vec[max--] = *ite--;
	//				_vec[max--] = *ite--;
	//				while (last != first)
	//					_vec[max--] = *--last;
	//				_size += n;
				}
			}

			iterator erase(iterator position)
			{
				iterator itp = position;
				iterator ite = end();
				size_type range = std::distance(position, ite);
				if (range > 1)
					while (position != ite)
						*position++ = *(position + 1);
				if (range)
					_myalloc.destroy(_vec + (--_size));
				return (itp);
			}

			iterator erase(iterator first, iterator last)
			{
				iterator itp = first;
				iterator ite = end();
				size_type i = std::distance(first, last);
				size_type range = std::distance(last, ite);
				if (range)
					while (last != ite)
						*first++ = *last++;
				while (i--)
					_myalloc.destroy(_vec + (--_size));
				return (itp);
			}

			void clear()
			{
				for (size_type i = 0; i < _size; ++i)
					_myalloc.destroy(_vec + i);
				_size = 0;
			}

			void swap(vector & x)
			{
				if (this != &x)
				{
					pointer tmp = _vec;
					size_type tmpc = _capacity;
					size_type tmps = _size;
					allocator_type tmpa = _myalloc;

					_vec = x._vec;
					x._vec = tmp;

					_capacity = x._capacity;
					x._capacity = tmpc;

					_size = x._size;
					x._size = tmps;

					_myalloc = x._myalloc;
					x._myalloc = tmpa;
				}
			}
			/*** ALLOCATOR ***/
			allocator_type get_allocator() const { return (allocator_type(_myalloc)); }
			
			/*** NON-MEMBER FUNCTION OVERLOADS ***/
			template <class M, class Alloc>
				friend bool operator==(const vector<M, Alloc> & lhs, const vector<M, Alloc> & rhs)
				{
					if (lhs.size() != rhs.size())
						return (false);
					return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), ft::ft_equal<typename vector<M, Alloc>::value_type>));
				}

			template <class M, class Alloc>
				friend bool operator!=(const vector<M, Alloc> & lhs, const vector<M, Alloc> & rhs)
				{
					return (!(lhs == rhs));
				}

			template <class M, class Alloc>
				friend bool operator<(const vector<M, Alloc> & lhs, const vector<M, Alloc> & rhs)
				{
					return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
				}
			template <class M, class Alloc>
				friend bool operator<=(const vector<M, Alloc> & lhs, const vector<M, Alloc> & rhs)
				{
					return !(lhs > rhs);
				}
			
			template <class M, class Alloc>
				friend bool operator>(const vector<M, Alloc> & lhs, const vector<M, Alloc> & rhs)
				{
					return (rhs < lhs);
				}

			template <class M, class Alloc>
				friend bool operator>=(const vector<M, Alloc> & lhs, const vector<M, Alloc> & rhs)
				{
					return !(lhs < rhs);
				}

			template <class M, class Alloc>
				friend void swap(vector<T, Alloc> & lhs, vector<M, Alloc> & rhs);
	};

	template <class M, class Alloc>
		void swap(vector<M, Alloc> & lhs, vector<M, Alloc> & rhs)
		{
			lhs.swap(rhs);
	}

	/*** MY	VECTOR'S ITERATOR ***/
	template <typename T, class B>
	template<typename A>
	class vector<T, B>::myiter
	{
		public:
		typedef std::ptrdiff_t			difference_type;
		typedef A						value_type;
		typedef A&						reference;
		typedef A*						pointer;
		typedef typename
		std::random_access_iterator_tag	iterator_category;
		
		protected:
			pointer			_data;
			friend class	myiter<A const>;
			friend struct	iterator_traits<myiter>;
			friend class	myiterev<myiter>;
			template <typename Iter>
			friend class	myiterev;

		public:
			myiter(void) :_data(nullptr){}
			myiter(value_type * vec) :_data(vec){}
			myiter(myiter const & src) :_data(src._data){}
			myiter(vector<T, B>::iterator & src) :_data(src._data){}
			myiter(vector<T, B>::iterator src) :_data(src._data){}
			myiter & operator=(myiter const & rhs)
			{
				if (this != &rhs)
					_data = rhs._data;
				return (*this);
			}

			template<typename X, typename Y>
			friend bool operator==(const myiter<X> & lhs, const myiter<Y> & rhs)
			{ return (lhs._data == rhs._data); }

			template<typename X, typename Y>
			friend bool operator!=(const myiter<X> & lhs, const myiter<Y> & rhs)
			{ return (lhs._data != rhs._data); }

			template<typename X, typename Y>
			friend bool operator<(const myiter<X> & lhs, const myiter<Y> & rhs)
			{ return (lhs._data < rhs._data); }

			template<typename X, typename Y>
			friend bool operator>(const myiter<X> & lhs, const myiter<Y> & rhs)
			{ return (lhs._data > rhs._data); }

			template<typename X, typename Y>
			friend bool operator<=(const myiter<X> & lhs, const myiter<Y> & rhs)
			{ return (lhs._data <= rhs._data); }

			template<typename X, typename Y>
			friend bool operator>=(const myiter<X> & lhs, const myiter<Y> & rhs)
			{ return (lhs._data >= rhs._data); }

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
				this->_data--;
				return (old);
			}

			myiter & operator+=(size_t n)
			{
				this->_data += n;
				return (*this);
			}

			myiter operator+(size_t x) const
			{ return (myiter(_data + x)); }

			friend myiter operator+(size_t n, const myiter & other)
			{ return (other + n); }

			myiter & operator-=(size_t n)
			{ this->_data -= n; return (*this); }

			difference_type operator-(myiter x) const
			{ return (this->_data - x._data); }

			myiter operator-(size_t x) const
			{ return (myiter(_data - x)); }

			reference operator*() const
			{ return (*_data); }

			pointer operator->() const
			{ return (this->_data); }

			reference operator[](size_t i) const
			{ return (_data[i]); }
	};
	
	/*** MY VECTOR'S CONST ITERATOR ***/
	template <typename T, class B>
	template<typename A>
	class vector<T, B>::myiter<const A>
	{
		public:
		typedef std::ptrdiff_t			difference_type;
		typedef A						value_type;
		typedef A&						reference;
		typedef A*						pointer;
		typedef const A&				const_reference;
		typedef const A*				const_pointer;
		typedef typename
		std::random_access_iterator_tag	iterator_category;
		
		protected:
			pointer _data;
			friend struct	iterator_traits<myiter>;
			friend class	myiterev<myiter>;
			template <typename Iter>
			friend class	myiterev;

		public:
			myiter() :_data(nullptr){}
			~myiter() {}
			myiter(const myiter<typename std::remove_const<value_type>::type> & src)
				:_data(src._data){}
			myiter & operator=(const myiter & rhs)
			{
				if (this != &rhs)
					_data = rhs._data;
				return (*this);
			}

			template<typename X, typename Y>
			friend bool operator==(const myiter<X> & lhs, const myiter<Y> & rhs)
			{ return (lhs._data == rhs._data); }
			
			template<typename X, typename Y>
			friend bool operator!=(const myiter<X> & lhs, const myiter<Y> & rhs)
			{ return (lhs._data != rhs._data); }
			
			template<typename X, typename Y>
			friend bool operator<(const myiter<X> & lhs, const myiter<Y> & rhs)
			{ return (lhs._data < rhs._data); }
			
			template<typename X, typename Y>
			friend bool operator>(const myiter<X> & lhs, const myiter<Y> & rhs)
			{ return (lhs._data > rhs._data); }
			
			template<typename X, typename Y>
			friend bool operator<=(const myiter<X> & lhs, const myiter<Y> & rhs)
			{ return (lhs._data <= rhs._data); }
			
			template<typename X, typename Y>
			friend bool operator>=(const myiter<X> & lhs, const myiter<Y> & rhs)
			{ return (lhs._data >= rhs._data); }

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
				this->_data--;
				return (old);
			}
	
			myiter & operator+=(size_t n)
			{
				this->_data += n;
				return (*this);
			}
	
			myiter operator+(size_t x) const
			{ return (myiter(_data + x)); }
	
			friend myiter operator+(size_t n, const myiter & other)
			{ return (other + n); }
	
			myiter & operator-=(size_t n)
			{
				this->_data -= n;
				return (*this);
			}
	
			difference_type operator-(myiter x) const
			{ return (this->_data - x._data); }
	
			myiter operator-(size_t x) const
			{ return (myiter(_data - x)); }
	
			const_reference operator*() const
			{ return (*_data); }
	
			const_pointer operator->() const
			{ return (this->_data); }
	
			const_reference operator[](size_t i) const
			{ return (_data[i]); }
	};

	/*** Reverse Iterator ***/
	template <typename T, class B>
	template <typename Iter>
	class vector<T, B>::myiterev
	{
		public:
		typedef Iter
		iterator_type;
		typedef typename ft::iterator_traits<iterator_type>::iterator_category
		iterator_category;
		typedef typename ft::iterator_traits<iterator_type>::value_type
		value_type;
		typedef typename ft::iterator_traits<iterator_type>::difference_type
		difference_type;
		typedef typename ft::iterator_traits<iterator_type>::pointer
		pointer;
		typedef typename ft::iterator_traits<iterator_type>::reference
		reference;

		protected:
		pointer			_data;
		friend class	myiterev<const Iter>;

		public:
		myiterev(): _data(nullptr){}

		explicit myiterev(const iterator_type & x): _data(x._data - 1){}
		
		myiterev(value_type *vec) :_data(vec){}
		
		//myiterev(typename vector<T, B>::const_reverse_iterator other)
		//: _data(other._data){}
		
		myiterev(myiterev<const typename std::remove_const<Iter>::type> other)
		: _data(other._data){}

		myiterev(const myiterev <typename std::remove_const<Iter>::type>& other)
		: _data(other._data){}

		~myiterev(){}
		myiterev & operator=(const myiterev & other)
		{
			if (this != &other)
				this->_data = other._data;
			return (*this);
		}

		iterator_type base() const
		{
			return (iterator_type(_data + 1));
		}

		reference operator*() const
		{ return (*_data); }
		
		myiterev operator+(difference_type n) const
		{
			return (myiterev(_data - n));
		}

		myiterev & operator++()
		{
			this->_data--;
			return (*this);
		}
		myiterev operator++(int)
		{
			myiterev tmp(*this);
			this->_data--;
			return (tmp);
		}
		myiterev & operator+=(difference_type n)
		{
			this->_data -= n;
			return (*this);
		}
		myiterev operator-(difference_type n) const
		{
			return (myiterev(_data + n));
		}
		myiterev & operator--()
		{
			this->_data++;
			return (*this);
		}
		myiterev operator--(int)
		{
			myiterev tmp(*this);
			this->_data++;
			return (tmp);
		}
		myiterev & operator-=(difference_type n)
		{
			this->_data += n;
			return (*this);
		}
		pointer operator->() const
		{
			return (this->_data);
		}
		reference operator[](difference_type n) const
		{
			return (_data[-n]);
		}

		template<typename X, typename Y>
		friend bool operator==(const myiterev<X> & lhs, const myiterev<Y> & rhs)
		{ return (lhs._data == rhs._data); }
	
		template<typename X, typename Y>
		friend bool operator!=(const myiterev<X> & lhs, const myiterev<Y> & rhs)
		{ return (lhs._data != rhs._data); }
		
		template<typename X, typename Y>
		friend bool operator<(const myiterev<X> & lhs, const myiterev<Y> & rhs)
		{ return (lhs._data > rhs._data); }
		
		template<typename X, typename Y>
		friend bool operator>(const myiterev<X> & lhs, const myiterev<Y> & rhs)
		{ return (lhs._data < rhs._data); }
		
		template<typename X, typename Y>
		friend bool operator<=(const myiterev<X> & lhs, const myiterev<Y> & rhs)
		{ return (lhs._data >= rhs._data); }
		
		template<typename X, typename Y>
		friend bool operator>=(const myiterev<X> & lhs, const myiterev<Y> & rhs)
		{ return (lhs._data <= rhs._data); }

		friend myiterev operator+(difference_type n, const myiterev & rhs)
		{ return (rhs + n); }

		template<typename X, typename Y>
		friend difference_type operator-(const myiterev<X> & lhs, const myiterev<Y> & rhs)
		{ return rhs._data - lhs._data; }
	};
	
	/*** Const Reverse Iterator ***/
	template <typename T, class B>
	template <typename Iter>
	class vector<T, B>::myiterev<const Iter>
	{
		public:
		typedef Iter
		iterator_type;
		typedef typename ft::iterator_traits<iterator_type>::iterator_category
		iterator_category;
		typedef typename ft::iterator_traits<iterator_type>::value_type
		value_type;
		typedef typename ft::iterator_traits<iterator_type>::difference_type
		difference_type;
		typedef typename ft::iterator_traits<iterator_type>::pointer
		pointer;
		typedef typename ft::iterator_traits<iterator_type>::reference
		reference;
		typedef const value_type&	const_reference;
		typedef const value_type*	const_pointer;

		protected:
		pointer	_data;
		template <typename L>
		friend class	myiterev;

		public:
		myiterev(): _data(nullptr){}

//		typedef myiter<const value_type>	const_iterator;
//
		explicit myiterev(vector<T, B>::const_iterator x)
		: _data(x._data - 1){}

//		explicit myiterev(vector<T, B>:myiter<const value_type> x)
//		: _data(x._data - 1){}
		
//		explicit myiterev(typename vector<T, B>::myiter<typename std::remove_const<typename vector<T, B>::template myiter<const value_type> >::type> x)
//		: _data(x._data - 1){}

		explicit myiterev(const iterator_type & x): _data(x._data - 1){}
		
		myiterev(value_type *vec) : _data(vec){}

		myiterev(myiterev<const typename std::remove_const<Iter>::type> other)
		: _data(other._data){}

		myiterev(const myiterev <typename std::remove_const<Iter>::type>& other)
		: _data(other._data){}

//		myiterev(const myiterev <typename std::remove_const<Iter>::type>& other)
//			: _data(other._data){}

		~myiterev(){}

		myiterev & operator=(const myiterev & other)
		{
			if (this != &other)
				_data = other._data;
			return (*this);
		}

		iterator_type base() const
		{
			return (iterator_type(_data + 1));
		}

		const_reference operator*() const
		{
			return (*_data);
		}

		myiterev operator+(difference_type n) const
		{
			return (myiterev(_data - n));
		}

		myiterev & operator++()
		{
			this->_data--;
			return (*this);
		}
		myiterev operator++(int)
		{
			myiterev tmp(*this);
			this->_data--;
			return (tmp);
		}
		myiterev & operator+=(difference_type n)
		{
			this->_data -= n;
			return (*this);
		}
		myiterev operator-(difference_type n) const
		{
			return (myiterev(_data + n));
		}
		myiterev & operator--()
		{
			this->_data++;
			return (*this);
		}
		myiterev operator--(int)
		{
			myiterev tmp(*this);
			this->_data++;
			return (tmp);
		}
		myiterev & operator-=(difference_type n)
		{
			this->_data += n;
			return (*this);
		}

		const_pointer operator->() const
		{
			return (this->_data);
		}

		const_reference operator[](difference_type n) const
		{
			return (_data[-n]);
		}

		template<typename X, typename Y>
		friend bool operator==(const myiterev<X> & lhs, const myiterev<Y> & rhs)
		{ return (lhs._data == rhs._data); }

		template<typename X, typename Y>
		friend bool operator!=(const myiterev<X> & lhs, const myiterev<Y> & rhs)
		{ return (lhs._data != rhs._data); }

		template<typename X, typename Y>
		friend bool operator<(const myiterev<X> & lhs, const myiterev<Y> & rhs)
		{ return (lhs._data > rhs._data); }

		template<typename X, typename Y>
		friend bool operator>(const myiterev<X> & lhs, const myiterev<Y> & rhs)
		{ return (lhs._data < rhs._data); }

		template<typename X, typename Y>
		friend bool operator<=(const myiterev<X> & lhs, const myiterev<Y> & rhs)
		{ return (lhs._data >= rhs._data); }

		template<typename X, typename Y>
		friend bool operator>=(const myiterev<X> & lhs, const myiterev<Y> & rhs)
		{ return (lhs._data <= rhs._data); }
		
		friend myiterev operator+(difference_type n, const myiterev & rhs)
		{ return (rhs + n); }

		template<typename X, typename Y>
		friend difference_type operator-(const myiterev<X> & lhs, const myiterev<Y> & rhs)
		{ return rhs._data - lhs._data; }
	};
// this line before the end of the namespace ft
}
	
#endif
