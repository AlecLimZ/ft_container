/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:49:38 by leng-chu          #+#    #+#             */
/*   Updated: 2023/01/11 12:34:28 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYITERATOR_HPP
# define MYITERATOR_HPP

using std::ptrdiff_t;
using std::random_access_iterator_tag;

namespace ft
{

	// enable_if
	template<bool B, class T = void>
	struct enable_if
	{};

	template<class T>
	struct enable_if<true, T>
	{
		typedef T value_type;
	};

	// iterator_traits template class
	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef difference_type							distance_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
	};

	// iterator_trait specialization for pointer to non-const
	template <class T>
	struct iterator_traits<T*>
	{
		typedef T								value_type;
		typedef ptrdiff_t					difference_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	// iterator_trait specialization template for pointer to const
	template <class T>
	struct iterator_traits<const T*>
	{
		typedef T								value_type;
		typedef ptrdiff_t					difference_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	// is_same
	template <class T, class U>
	struct is_same : std::false_type {};
	
	template<class T>
	struct is_same<T, T> : std::true_type {};

	template <class T>
	struct is_integral
	{
		static const bool value = std::numeric_limits<T>::is_integer;
	};

	// lexicographical_compare
	template <class Iter1, class Iter2>
		bool lexicographical_compare(Iter1 a1, Iter1 a2, Iter2 b1, Iter2 b2)
		{
			while (a1 != a2)
			{
				if (b1 == b2 || *a1 > *b1)
					return (false);
				if (*a1 < *b1)
					return (true);
				a1++, b1++;
			}
			return (b1 != b2);
		}

	template <class Iter1, class Iter2, class Cmp>
		bool lexicographical_compare(Iter1 a1, Iter1 a2, Iter2 b1, Iter2 b2, Cmp comp)
		{
			while (a1 != a2 && b1 != b2)
			{
				if (!comp(*a1, *b1))
					return (false);
				a1++, b1++;
			}
			return (true);
		}

	template<typename T>
	bool ft_less(T a, T b)
	{
		return (a < b);
	}

	template <typename T>
	bool ft_not_eq(T a, T b)
	{
		return (a != b);
	}

	template <typename T>
	bool ft_equal(T a, T b)
	{
		return (a == b);
	}

	template<typename T>
	bool ft_greater(T a, T b)
	{
		return (a > b);
	}

	template<typename T>
	bool ft_less_eq(T a, T b)
	{
		return (a <= b);
	}

	template<typename T>
	bool ft_greater_eq(T a, T b)
	{
		return (a >= b);
	}

	// distance
	template <class InputIt>
	typename ft::iterator_traits<InputIt>::difference_type
	distance(InputIt first, InputIt last)
	{
		typename ft::iterator_traits<InputIt>::difference_type d = 0;
		while (first != last)
		{
			first++;
			d++;
		}
		return (d);
	}

	// ft::pair
	template <class T1, class T2>
	struct pair
	{
		typedef T1	first_type;
		typedef T2	second_type;

		first_type	first;
		second_type	second;

		// constructor
		pair():first(), second() {};
		template<class U, class V>
		pair(const pair<U, V> & pr)
		: first(pr.first), second(pr.second){}
		pair(const first_type & a, const second_type & b)
			: first(a), second(b){}
		pair(const first_type & a)
			: first(a), second(){}

		// operator=
		pair & operator=(const pair & pr)
		{
			if (this != &pr)
			{
				first = pr.first;
				second = pr.second;
			}
			return (*this);
		}

		// relational operator
		template <class A, class B>
		friend bool operator==(const pair<A, B> & lhs, const pair<A, B> & rhs)
		{
			return (lhs.first == rhs.first && lhs.second == rhs.second);
		}
		template <class A, class B>
		friend bool operator!=(const pair<A, B> & lhs, const pair<A, B> & rhs)
		{
			return !(lhs == rhs);
		}
		template <class A, class B>
		friend bool operator<(const pair<A, B> & lhs, const pair<A, B> & rhs)
		{
			return (lhs.first < rhs.first || (lhs.first < rhs.first && lhs.second < rhs.second));
		}
		template <class A, class B>
		friend bool operator<=(const pair<A, B> & lhs, const pair<A, B> & rhs)
		{
			return (!(rhs < lhs));
		}
		template <class A, class B>
		friend bool operator>(const pair<A, B> & lhs, const pair<A, B> & rhs)
		{
			return (rhs < lhs);
		}
		template <class A, class B>
		friend bool operator>=(const pair<A, B> & lhs, const pair<A, B> & rhs)
		{
			return (!(lhs < rhs));
		}
	};

	// ft::make_pair
	template <class T1, class T2>
	pair<T1, T2> make_pair(T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}
}

#endif
