/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:31:37 by leng-chu          #+#    #+#             */
/*   Updated: 2022/11/17 16:37:32 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TestClass1.hpp"
#include <vector>

using std::allocator;
using std::vector;
using std::string;

void	test(void)
{
	allocator<string> myAllocator;

	string *str = myAllocator.allocate(3);

	myAllocator.construct(str, "Geeks");
	myAllocator.construct(str + 1, "for");
	myAllocator.construct(str + 2, "Geeks");
	str[3] = "WORK?";

	cout << str[0] << str[1] << str[2] << str[3];

	cout << "max size: " << myAllocator.max_size() << endl;
	myAllocator.destroy(str);
	myAllocator.destroy(str + 1);
	myAllocator.destroy(str + 2);
	myAllocator.destroy(str + 3);

	cout << "max size: " << myAllocator.max_size() << endl;
	myAllocator.deallocate(str, 4);
}

int	main(void)
{
	test();
//	system("leaks main");
	return (0);
}
