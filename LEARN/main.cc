/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:31:37 by leng-chu          #+#    #+#             */
/*   Updated: 2022/11/21 17:12:02 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myclass.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <unordered_map>
#include <memory> // for unique make

using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::iterator_traits;
using std::list;
using std::unordered_map;

namespace my
{
	std::atomic_int g_memory_used(0);
	template<typename T>
	class Allocator : public std::allocator<T>
	{
		private:
			using Base		=	std::allocator<T>;
			using Pointer	=	typename std::allocator_traits<Base>::pointer;
			using SizeType	=	typename std::allocator_traits<Base>::size_type;

		public:
			Pointer allocate(SizeType n)
			{
				g_memory_used.fetch_add(n * sizeof(T));
				return Base::allocate(n);
			}
			void deallocate(Pointer p, SizeType n)
			{
				g_memory_used.fetch_sub(n * sizeof(T));
				Base::deallocate(p, n);
			}
	};
}

template <template<typename T, typename AllocT> typename ContainerT>
void test()
{
	cout << __PRETTY_FUNCTION__ << endl;
	cout << "Memory usage before: " << my::g_memory_used.load() << endl;
	ContainerT<int, my::Allocator<int> > container;
	for (int i = 0; i < 1000; ++i)
		cont.insert(end(cont), i);
	cout << "Memory usage after: " << my::g_memory_used.load() << endl;
}

#include <list>
#include <set>

int main(void)
{
	test<std::vector>();
	test<std::list>();
	test<std::set>();
}
