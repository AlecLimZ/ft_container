/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:56:45 by leng-chu          #+#    #+#             */
/*   Updated: 2022/11/17 19:57:21 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>

using std::cout;
using std::endl;
using std::cin;

namespace	ft
{
	template <typename T, class Allocator = std::allocator<T> >
	class vector
	{
		/*** MEMBER TYPES ***/
		typedef T						value_type;
		typedef Allocator				allocator_type;
		typedef allocator_type&			reference;
		typedef const allocator_type&	const_reference;
		typedef allocator_type*			pointer;
		typedef const allocator_type*	const_pointer;
		typedef size_t					size_type;
		typedef ptrdiff_t				difference_type;
		/*** END OF MEMBER TYPES ***/
		
		/*** ATTRIBUTES ***/
		size_type		capacity;
		allocator_type	myalloc;
		/*** END OF ATTRIBUTES ***/
		
		public:
			value_type	*myar;
			/*** MEMBER FUNCTIONS ***/

			// constructor
			explicit vector(const allocator_type & alloc = allocator_type())
				: capacity(0), myalloc(alloc)
			{
				myar = myalloc.allocate(capacity);
			}

			explicit vector(size_type count,
					const value_type & value = value_type(),
					const Allocator & alloc = allocator_type())
				: capacity(count), myalloc(alloc)
			{
				myar = myalloc.allocate(capacity);
				for (size_type i = 0; i < count; i++)
					myalloc.construct(myar + i, value);
				cout << "capacity: " << capacity << endl;
				cout << "myar[0]: " << myar[0] << endl;
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
			~vector(void) { cout << "destructor" << endl; }

			// operator=
			vector & operator=(vector const & rhs);
			/*** END OF MEMBER FUNCTIONS ***/

			/*** ITERATORS ***/
			/*** END OF ITERATORS ***/

			/*** CAPACITY ***/
			/*** END OF CAPACITY ***/
			
			/*** ELEMENT ACCESS ***/
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
