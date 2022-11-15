/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.cc                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:16:09 by leng-chu          #+#    #+#             */
/*   Updated: 2022/11/15 19:22:44 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myvector.hpp"

template <typename T, typename Allocator>
ft_vector::vector<T, Allocator>::vector(const Allocator & alloc): capacity(0)
{
	std::cout << "const: alloc" << std::endl;
	std::allocator<T> tmp = alloc;
	v = tmp.allocate(capacity);
}

template <typename T, typename Allocator>
ft_vector::vector<T, Allocator>::vector(size_t count, const T & value, const Allocator & alloc): capacity(count)
{
	std::cout << "const: count & value, alloc" << std::endl;
	std::cout << "count: " << count << std::endl;
	std::cout << "count type: " << typeid(count).name() << std::endl;
	std::cout << "value: " << value << std::endl;
	std::cout << "value type: " << typeid(value).name() << std::endl;
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
