/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:51:20 by leng-chu          #+#    #+#             */
/*   Updated: 2023/01/12 16:49:14 by leng-chu         ###   ########.fr       */
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

template <typename lol>
struct foo
{
	lol a;
	int b;
};

TEST_CASE("Map's max size")
{
	typedef char				T1;
	typedef double				T2;
	typedef int					T3;
	typedef long				T4;
	typedef std::string			T5;
	typedef foo<std::string>	T6;
	typedef ft::map<T1, T2>		FMAP1;
	typedef std::map<T1, T2>	SMAP1;
	typedef ft::map<T3, T4>		FMAP2;
	typedef std::map<T3, T4>	SMAP2;
	typedef ft::map<T5, T6>		FMAP3;
	typedef std::map<T5, T6>	SMAP3;
	typedef ft::map<T2, T6>		FMAP4;
	typedef std::map<T2, T6>	SMAP4;

	FMAP1 f1; SMAP1 s1;
	FMAP2 f2; SMAP2 s2;
	FMAP3 f3; SMAP3 s3;
	FMAP4 f4; SMAP4 s4;

	CHECK(f1.max_size() == s1.max_size());
	CHECK(f2.max_size() == s2.max_size());
	CHECK(f3.max_size() == s3.max_size());
}

TEST_CASE("iterator rev map")
{
	typedef std::map<char, int> SMAP;
	typedef ft::map<char, int> FMAP;

	SMAP	sm;
	FMAP	fm;

	for (char i = 'a'; i <= 'z'; i++)
	{
		sm[i] = 33;
		fm[i] = 33;
	}
	SMAP::reverse_iterator rsit = sm.rbegin();
	SMAP::reverse_iterator rsite = sm.rend();

	rsit--;

	cout << "ori rsit: " << rsit->first << endl;
	cout << "ori rsite: " << rsite->first << endl;
//	while (rsit != rsite)
//		cout << (rsite--)->first << " ";
//	cout << endl;

//	FMAP::reverse_iterator rfit = fm.rbegin();
//	FMAP::reverse_iterator rfite = fm.rend();
	
//	cout << "ori rfit: " << rfit->first << endl;
//	cout << "ori rfite: " << rfite->first << endl;
//	while (rfit != rfite)
//		cout << (rfite--)->first << " ";
//	cout << endl;
}

void	ft_test(void)
{
}

int main(int argc, char **argv)
{
	ft_test();
#ifdef noasan
	system("leaks main");
#endif
	return (doc(&argc, argv));
}
