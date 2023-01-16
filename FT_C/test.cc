/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:51:20 by leng-chu          #+#    #+#             */
/*   Updated: 2023/01/16 13:58:49 by leng-chu         ###   ########.fr       */
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
	typedef std::map<int, std::string>	SMAP;
	typedef ft::map<int, std::string>	FMAP;
	typedef std::pair<int, std::string> spair;
	typedef ft::pair<int, std::string>	fpair;

	SMAP 	sm;
	FMAP	fm;

	sm.insert(sm.begin(), spair(1337, "beauty"));
	sm.insert(sm.end(), spair(1000, "Hello"));
	sm.insert(sm.end(), spair(1500, "World"));
	
	fm.insert(fm.begin(), fpair(1337, "beauty"));
	fm.insert(fm.end(), fpair(1000, "Hello"));
	fm.insert(fm.end(), fpair(1500, "World"));

	SMAP::iterator it = sm.begin();
	SMAP::iterator ite = sm.end();
	cout << "===STD===" << endl;
	while (it != ite)
	{
		cout << it->first << "=>" << it->second << endl;
		it++;
	}
	
	FMAP::iterator fit = fm.begin();
	FMAP::iterator fite = fm.end();
	cout << "===FT===" << endl;
	while (fit != fite)
	{
		cout << fit->first << "=>" << fit->second << endl;
		fit++;
	}
}

int main(int argc, char **argv)
{
	ft_test();
#ifdef noasan
	system("leaks main");
#endif
	return (doc(&argc, argv));}
