/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:51:20 by leng-chu          #+#    #+#             */
/*   Updated: 2022/12/02 18:21:12 by leng-chu         ###   ########.fr       */
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
	ft::vector<int>::iterator it = myvector.begin();
	ft::vector<int>::iterator ite = myvector.end();

	cout << CYAN;
	for (; it != ite; ++it)
		cout << *it << " ";
	cout << DEF << endl;

//	p = myvector.get_allocator().allocate(5);

//	for (i = 0; i < 5; i++)
//		myvector.get_allocator().construct(&p[i], i);

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
