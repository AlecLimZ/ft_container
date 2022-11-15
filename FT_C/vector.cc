/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.cc                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:16:09 by leng-chu          #+#    #+#             */
/*   Updated: 2022/11/15 15:45:09 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myvector.hpp"

template <typename T, typename Allocator>
ft_vector::vector<T, Allocator>::vector(const Allocator & alloc): capacity(0)
{
	std::allocator<T> tmp = alloc;
	v = tmp.allocate(capacity);
}

template <typename T, typename Allocator>
ft_vector::vector<T, Allocator>::vector(size_t count, const T & value, const Allocator & alloc): capacity(count)
{
	std::allocator<T> tmp = alloc;
	v = tmp.allocate(capacity);
	for (size_t i = 0; i < capacity; i++)
		tmp.construct(v + i, value);
}

template <typename T, typename Allocator>
ft_vector::vector<T, Allocator>::~vector(void)
{
	std::cout << "myvector is destructed" << std::endl;
}

template <typename T, typename Allocator>
ft_vector::vector<T, Allocator>::vector(vector const & src)
{
	(void)src;
}

template <typename T, typename Allocator>
ft_vector::vector<T, Allocator> & ft_vector::vector<T, Allocator>::operator=(vector const & rhs)
{
	(void)rhs;
	return (*this);
}

template class ft_vector::vector<int>;
template class ft_vector::vector<float>;
