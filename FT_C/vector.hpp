/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:56:45 by leng-chu          #+#    #+#             */
/*   Updated: 2022/11/20 20:20:23 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <cstddef> // for linux ptrdiff_t
# include <stdexcept>

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
		typedef ptrdiff_t				difference_type;
		typedef size_t					size_type;
		/*** END OF MEMBER TYPES ***/
		
		/*** ATTRIBUTES ***/
		size_type		_capacity;
		size_type		_size;
		allocator_type	_myalloc;
		pointer _vec;
		/*** END OF ATTRIBUTES ***/
		
		public:
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

//			template<class InputIterator>
//				vector( InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type())
//				{
//					cout << "enter here?" << endl;
//					(void)first;
//					(void)last;
//					(void)alloc;
//				}

			vector(vector const & x)
			{
				(void)x;
			}

			// destructor
			~vector(void) { 
				for (size_type i = 0; i < _size; ++i)
					_myalloc.destroy(_vec + i);
				_myalloc.deallocate(_vec, _capacity);
				cout << "destructor" << endl; }

			// operator=
			vector & operator=(vector const & rhs);
			/*** END OF MEMBER FUNCTIONS ***/

			/*** ITERATORS ***/
			/*** END OF ITERATORS ***/

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
			/*** END OF CAPACITY ***/
			
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
			/*** END OF ELEMENT ACCESS ***/

			/*** MODIFIERS ***/
			/*** END OF MODIFIERS ***/

			/*** ALLOCATOR ***/
			/*** END OF ALLOCATOR ***/
			
			/*** NON-MEMBER FUNCTION OVERLOADS ***/
			/*** END OF NON-MEMBER FUNCTION OVERLOADS ***/
	};
}

#endif
