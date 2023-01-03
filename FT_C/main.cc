/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:51:20 by leng-chu          #+#    #+#             */
/*   Updated: 2023/01/03 15:21:53 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define DOCTEST_CONFIG_IMPLEMENT
#include "lib.hpp"
#include "vector.hpp"
#include "map.hpp"
#include "doctest.hpp"
#include <map>

using std::string;

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

void	ft_test(void)
{
	typedef std::map<char, int> SMAP;
	typedef ft::map<char, int> FMAP;
	
	SMAP smap;
	FMAP fmap;

	smap['d'] = 10;
	smap['b'] = 30;
	smap['c'] = 50;
	smap['a'] = 70;
	fmap['a'] = 10;
	fmap['d'] = 30;
	fmap['c'] = 50;
	fmap['b'] = 70;

	for (std::map<char, int>::size_type i = 'a'; i <= 'd'; ++i)
		cout << smap[i] << " ";
	cout << endl;

	FMAP::iterator fit = fmap.begin();
	FMAP::iterator fite = fmap.end();
	while (fit != fite)
		cout << (fit++)->first << " ";
	cout << endl;
	
}

int main(int argc, char **argv)
{
	ft_test();
#ifdef noasan
	system("leaks main");
#endif
	return (doc(&argc, argv));
}
