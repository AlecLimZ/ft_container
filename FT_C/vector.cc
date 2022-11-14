/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.cc                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:16:09 by leng-chu          #+#    #+#             */
/*   Updated: 2022/11/14 16:23:34 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myvector.hpp"

template <>
ft_vector::vector<int>::vector(void)
{
	std::cout << "myvector int is constructed" << std::endl;
}

template <>
ft_vector::vector<float>::vector(void)
{
	std::cout << "myvector float is constructed" << std::endl;
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
