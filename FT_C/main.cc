/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:51:20 by leng-chu          #+#    #+#             */
/*   Updated: 2022/12/07 17:25:43 by leng-chu         ###   ########.fr       */
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
	typedef ft::vector<int> fvector;
	fvector mv;
	mv.push_back(0);
	mv.push_back(1);
	mv.push_back(2);
	mv.push_back(3);
	mv.push_back(4);
	mv.push_back(5);
	
//	ft::vector<int>::iterator it = mv.begin();
	ft::vector<int>::iterator it = mv.begin() + 3;

	ft::vector<int>::reverse_iterator revit(it);
//	ft::vector<int>::iterator ite = mv.end();

	cout << CYAN;
//	for (; it != ite; ++it)
//		cout << *it << " ";
	cout << "*it == " << *it << endl;
	cout << "*revit == " << *revit << endl;
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
