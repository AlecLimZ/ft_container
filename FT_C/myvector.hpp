/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myvector.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:56:45 by leng-chu          #+#    #+#             */
/*   Updated: 2022/11/15 18:45:10 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>

namespace	ft_vector
{
	template <typename T, class Allocator = std::allocator<T> >
	class vector
	{
		size_t	capacity;
		public:
			T 		*v;
			// constructor
			explicit vector(const Allocator & alloc = Allocator());
			explicit vector(size_t count, const T & value = T(), const Allocator & alloc = Allocator());
			template<class InputIt>
				vector( InputIt first, InputIt last, const Allocator & alloc = Allocator());
			vector(vector const & other);

			// destructor
			~vector(void);

			// operator=
			vector & operator=(vector const & rhs);
	};
}
#endif
