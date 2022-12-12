/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myiterator.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:49:38 by leng-chu          #+#    #+#             */
/*   Updated: 2022/12/08 14:55:23 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYITERATOR_HPP
# define MYITERATOR_HPP

using std::ptrdiff_t;
using std::random_access_iterator_tag;

namespace ft
{

	// enable_if
	template<bool, class T>
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
}

#endif
