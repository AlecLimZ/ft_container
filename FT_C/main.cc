/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:51:20 by leng-chu          #+#    #+#             */
/*   Updated: 2022/11/18 17:39:02 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define DOCTEST_CONFIG_IMPLEMENT
#include "lib.hpp"
#include "vector.hpp"
#include "doctest.hpp"

int	doc(int *ac, char **av)
{
	doctest::Context context;
	context.addFilter("test-case-exclude", "*math*");
	context.setOption("abort-after", 5);
	context.setOption("order-by", "name");
	context.applyCommandLine(*ac, av);
	context.setOption("no-breaks", true);
	int res = context.run();
	if (context.shouldExit())
		return res;
	int client_stuff_return_code = 0;
	return (res + client_stuff_return_code);
}

void	test(void)
{
//	ft::vector<int> first;
//	std::vector<int> first2;
	ft::vector<int> mysecond(5, 44);
	std::vector<int> stsecond(2, 44);

	cout << "size: " << mysecond.size() << endl;
	cout << "capacity: " << mysecond.max_size() << endl;
	cout << "size2: " << stsecond.size() << endl;
	cout << "capacity2: " << stsecond.capacity() << endl;
	stsecond.resize(3, 33);
	cout << "size2: " << stsecond.size() << endl;
	cout << "capacity2: " << stsecond.capacity() << endl;
	

	cout << "my vector: ";
	for (int i = 0; i < 4; i++)
		cout << mysecond._vec[i] << " ";
	cout << endl;
	cout << "std vector: ";
	for (int i = 0; i < 4; i++)
		cout << stsecond[i] << " ";
	cout << endl;
}

int main(int argc, char **argv)
{
	test();
//	system("leaks main");
	return (doc(&argc, argv));
}
