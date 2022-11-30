/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:51:20 by leng-chu          #+#    #+#             */
/*   Updated: 2022/11/30 15:34:14 by leng-chu         ###   ########.fr       */
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
	ft::vector<int> myvector(5,4);
	ft::vector<int> myvector2;
//	int *p;
	unsigned int i;
	ft::vector<int>::iterator it;

//	p = myvector.get_allocator().allocate(5);

//	for (i = 0; i < 5; i++)
//		myvector.get_allocator().construct(&p[i], i);

	std::cout << "The allocated array contains:";
	for (i = 0; i < 5; i++) std::cout << ' ' << myvector[i];
	std::cout << '\n';

//	for (i = 0; i < 5; i++)
//		myvector.get_allocator().destroy(&p[i]);
//	myvector.get_allocator().deallocate(p, 5);

}

int main(int argc, char **argv)
{
	test();
#ifdef noasan
	system("leaks main");
#endif
	return (doc(&argc, argv));
}
