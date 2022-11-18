/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:51:20 by leng-chu          #+#    #+#             */
/*   Updated: 2022/11/18 18:27:53 by leng-chu         ###   ########.fr       */
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
	std::vector<int> stsecond(5, 44);

	mysecond.resize(1, 33);
	cout << "size2: " << stsecond.size() << endl;
	cout << "capacity2: " << stsecond.capacity() << endl;
	mysecond.resize(10, 33);
	mysecond.resize(7, 33);
}

int main(int argc, char **argv)
{
	test();
//	system("leaks main");
	return (doc(&argc, argv));
}
