/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:31:37 by leng-chu          #+#    #+#             */
/*   Updated: 2022/11/14 16:44:15 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "learn.hpp"

using std::allocator;

int main(void)
{
	{
		allocator<int> alloc;
		int *p = alloc.allocate(1);
		alloc.deallocate(p, 1);

		using traits_t = std::allocator_traits<decltype(alloc)>;
		p = traits_t::allocate(alloc, 1);
		traits_t::construct(alloc, p, 7);
		std::cout << *p << '\n';
		traits_t::deallocate(alloc, p, 1);
		std::cout << *p << '\n';
	}
	{
		std::allocator<std::string>alloc;
		using traits_t = std::all
	}
}
