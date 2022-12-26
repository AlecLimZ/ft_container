/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 14:24:13 by leng-chu          #+#    #+#             */
/*   Updated: 2022/12/26 17:42:06 by leng-chu         ###   ########.fr       */
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
		template <typename A>
		class mapiter;
		template <typename A>
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

			// Element access
			mapped_type & operator[](const key_type & k)
			{
				return (_map[k].second);
			}
	};
}

#endif
