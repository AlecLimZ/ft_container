/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:23:01 by leng-chu          #+#    #+#             */
/*   Updated: 2023/01/19 16:48:48 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

#include <deque>
#include <vector>
#include "vector.hpp"
#include <list>

namespace ft
{
	template<class T, class Container = std::deque<T> >
	class stack
	{
		public:
			typedef Container						container_type;
			typedef typename Container::value_type		value_type;
			typedef	typename Container::size_type		size_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference	const_reference;

		protected:
			Container _c;

		public:
			explicit stack(const container_type & ctnr = container_type())
			:	_c(ctnr){}
			~stack(){}

			bool empty() const
			{
				return (_c.empty());
			}

			size_type size() const
			{
				return (_c.size());
			}

			value_type & top()
			{
				return (_c.back());
			}
			
			const value_type & top() const
			{
				return (_c.back());
			}

			void push(const value_type & val)
			{
				_c.push_back(val);
			}

			void pop()
			{
				_c.pop_back();
			}

			void swap(stack & x)
			{
				_c.swap(x._c);
			}

			/*** non-member function ***/
			template <class D, class Cont>
			friend bool operator==(const stack<D, Cont> & lhs, const stack<D, Cont> & rhs)
			{
				return (lhs._c == rhs._c);
			}
			template <class D, class Cont>
			friend bool operator!=(const stack<D, Cont> & lhs, const stack<D, Cont> & rhs)
			{
				return (lhs._c != rhs._c);
			}
			template <class D, class Cont>
			friend bool operator<(const stack<D, Cont> & lhs, const stack<D, Cont> & rhs)
			{
				return (lhs._c < rhs._c);
			}
			template <class D, class Cont>
			friend bool operator<=(const stack<D, Cont> & lhs, const stack<D, Cont> & rhs)
			{
				return (lhs._c <= rhs._c);
			}
			template <class D, class Cont>
			friend bool operator>(const stack<D, Cont> & lhs, const stack<D, Cont> & rhs)
			{
				return (lhs._c > rhs._c);
			}
			template <class D, class Cont>
			friend bool operator>=(const stack<D, Cont> & lhs, const stack<D, Cont> & rhs)
			{
				return (lhs._c >= rhs._c);
			}

			template<class D, class Cont>
			friend void swap(stack<D, Cont> & x, stack<D, Cont> & y)
			{
				x.swap(y);
			}
	};
}

#endif
