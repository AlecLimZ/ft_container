/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:51:20 by leng-chu          #+#    #+#             */
/*   Updated: 2023/01/11 12:12:58 by leng-chu         ###   ########.fr       */
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

TEST_CASE("Iterator")
{
	typedef std::map<char, int> SMAP;
	typedef ft::map<char, int> FMAP;

	SMAP	sm;
	FMAP	fm;

	for (char i = 'a'; i <= 'z'; ++i)
	{
		sm[i] = 77;
		fm[i] = 77;
	}
	
//	SMAP::iterator sit = sm.begin();
//	SMAP::iterator site = sm.end();
//	while (sit != site)
//		cout << (sit++)->first << " ";
//	cout << endl;

	SMAP::iterator sit = sm.begin();
	SMAP::iterator site = sm.end();
	FMAP::iterator fit = fm.begin();
	FMAP::iterator fite = fm.end();

	while (fit != fite && sit != site)
		CHECK((fit++)->first == (sit++)->first);
	sit = sm.begin();
	fit = fm.begin();
	while (fit != fite && sit != site)
	{ fite--; site--;}
	fite = fm.end();
	site = sm.end();
	while (++fit != fite && ++sit != site)
		CHECK((fit)->first == (sit)->first);
	sit = sm.begin();
	fit = fm.begin();
	while (--fite != fit && --site != sit);
	fite = fm.end();
	site = sm.end();
	while (fit != fite && sit != site)
	{
		CHECK((fit != fite) == (sit != site));
		fit++; fite--;
		sit++; site--;
	}
	CHECK((fit == fite) == (sit == site));
}

void	ft_test(void)
{}

int main(int argc, char **argv)
{
	ft_test();
#ifdef noasan
	system("leaks main");
#endif
	return (doc(&argc, argv));
}
