/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:51:20 by leng-chu          #+#    #+#             */
/*   Updated: 2023/01/18 17:13:48 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define DOCTEST_CONFIG_IMPLEMENT
#include "lib.hpp"
#include "vector.hpp"
#include "map.hpp"
#include "doctest.hpp"
#include <list>
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

	for (char i = 'a'; i <= 'z'; ++i)
	{
		sm[i] = 77;
		fm[i] = 77;
	}
	
	SMAP::reverse_iterator rsit = sm.rbegin();
	SMAP::const_reverse_iterator rsite = sm.rend();
	FMAP::reverse_iterator rfit = fm.rbegin();
	FMAP::const_reverse_iterator rfite = fm.rend();

	while (rfit != rfite && rsit != rsite)
		CHECK((rfit++)->first == (rsit++)->first);
	rsit = sm.rbegin();
	rfit = fm.rbegin();
	while (rfit != rfite && rsit != rsite)
	{ rfite--; rsite--;}
	rfite = fm.rend();
	rsite = sm.rend();
	while (++rfit != rfite && ++rsit != rsite)
		CHECK((rfit)->first == (rsit)->first);
	rsit = sm.rbegin();
	rfit = fm.rbegin();
	while (--rfite != rfit && --rsite != rsit);
	rfite = fm.rend();
	rsite = sm.rend();
	while (rfit != rfite && rsit != rsite)
	{
		CHECK((rfit != rfite) == (rsit != rsite));
		rfit++; rfite--;
		rsit++; rsite--;
	}
	CHECK((rfit == rfite) == (rsit == rsite));
}

TEST_CASE("Element Access")
{
	typedef std::map<std::string, char> SMAP;
	typedef ft::map<std::string, char> FMAP;

	SMAP mymap;
	FMAP fmap;
	
	mymap["alpha"] = 11;
	mymap["beta"] = 22;
	mymap["gamma"] = 33;
	
	fmap["alpha"] = 11;
	fmap["beta"] = 22;
	fmap["gamma"] = 33;
	
	SMAP::iterator sit = mymap.begin();
	SMAP::iterator site = mymap.end();
	FMAP::iterator fit = fmap.begin();
	FMAP::iterator fite = fmap.end();
	while (sit != site && fit != fite)
	{
		CHECK(sit->first == fit->first);
		CHECK(sit->second == fit->second);
		sit++;
		fit++;
	}

	mymap.at("alpha") = 10;
	mymap.at("beta") = 20;
	mymap.at("gamma") = 30;
	
	fmap.at("alpha") = 10;
	fmap.at("beta") = 20;
	fmap.at("gamma") = 30;
  
	sit = mymap.begin();
	fit = fmap.begin();
	while (sit != site && fit != fite)
	{
		CHECK(sit->first == fit->first);
		CHECK(sit->second == fit->second);
		sit++;
		fit++;
	}
}

TEST_CASE("Modifiers")
{
	typedef std::map<char, int>	SMAP;
	typedef ft::map<char, int>	FMAP;

	SUBCASE("insert")
	{
		SMAP 	sm;
		FMAP	fm;

		sm.insert(std::pair<char, int>('a', 100));
		sm.insert(std::pair<char, int>('z', 200));
		fm.insert(ft::pair<char, int>('a', 100));
		fm.insert(ft::pair<char, int>('z', 200));

		CHECK(sm['a'] == fm['a']);

		std::pair<std::map<char, int>::iterator, bool> ret;
		ret = sm.insert(std::pair<char, int>('z', 500));
		ft::pair<ft::map<char, int>::iterator, bool> fret;
		fret = fm.insert(ft::pair<char, int>('z', 500));
		CHECK(ret.second == fret.second);
		CHECK(ret.first->second == fret.first->second);

		// second insert
		SMAP::iterator it = sm.begin();
		SMAP::iterator ite = sm.end();
		FMAP::iterator fit = fm.begin();
		FMAP::iterator fite = fm.end();
		sm.insert(it, std::pair<char, int>('b', 300));
		sm.insert(it, std::pair<char, int>('c', 400));
		sm.insert(it, std::pair<char, int>('k', 444));
		

		fm.insert(fit, ft::pair<char, int>('b', 300));
		fm.insert(fit, ft::pair<char, int>('c', 400));
		fm.insert(fit, ft::pair<char, int>('k', 444));

		while (it != ite && fit != fite)
		{
			CHECK(it->first == fit->first);
			CHECK(it->second == fit->second);
			it++;
			fit++;
		}

		// third insert function version
		SMAP sa;
		FMAP fa;
		sa.insert(sm.begin(), sm.find('c'));
		fa.insert(fm.begin(), fm.find('c'));

		it = sm.begin();
		fit = fm.begin();
		while (it != ite)
		{
			CHECK(it->first == fit->first);
			CHECK(it->second == fit->second);
			it++;
			fit++;
		}
		it = sa.begin();
		ite = sa.end();
		fit = fa.begin();
		fite = fa.end();
		while (it != ite && fit != fite)
		{
			CHECK(it->first == fit->first);
			CHECK(it->second == fit->second);
			it++;
			fit++;
		}

		// operator copy & copy constructor
		SMAP sc(sm);
		FMAP fc(fm);

		it = sc.begin();
		ite = sc.end();
		fit = fc.begin();
		fite = fc.end();
		while (it != ite && fit != fite)
		{
			CHECK(it->first == fit->first);
			CHECK(it->second == fit->second);
			it++;
			fit++;
		}

		SMAP so;
		FMAP fo;

		so = sc;
		fo = fc;
		
		it = sc.begin();
		ite = sc.end();
		fit = fc.begin();
		fite = fc.end();
		while (it != ite && fit != fite)
		{
			CHECK(it->first == fit->first);
			CHECK(it->second == fit->second);
			it++;
			fit++;
		}
	}

	SUBCASE("erase")
	{
		typedef std::map<char, int> SMAP;
		typedef ft::map<char, int> FMAP;

		SMAP sm;
		FMAP fm;
		int k = 10;

		for (char i = 'a'; i <= 'f'; ++i)
		{
			sm[i] = k;
			fm[i] = k;
			k += 10;
		}

		SMAP::iterator sit = sm.find('b'), site = sm.end();
		FMAP::iterator fit = fm.find('b'), fite = fm.end();
		sm.erase(sit);
		sm.erase('c');
		
		fm.erase(fit);
		fm.erase('c');
		
		sit = sm.find('e');
		fit = fm.find('e');

		sm.erase(sit, sm.end());
		fm.erase(fit, fm.end());

		sit = sm.begin();
		fit = fm.begin();
		while (sit != site && fit != fite)
		{
			CHECK(sit->first == fit->first);
			CHECK(sit->second == fit->second);
			sit++;
			fit++;
		}
	}

	SUBCASE("Swap")
	{
		std::map<char, int> s1, s2;
		ft::map<char, int> f1, f2;

		s1['x'] = 100;
		s1['y'] = 200;
		s2['a'] = 11;
		s2['b'] = 22;
		s2['c'] = 33;
		
		f1['x'] = 100;
		f1['y'] = 200;
		f2['a'] = 11;
		f2['b'] = 22;
		f2['c'] = 33;

		s1.swap(s2);
		f1.swap(f2);

		std::map<char, int>::iterator it = s1.begin(), ite = s1.end();
		ft::map<char, int>::iterator fit = f1.begin(), fite = f1.end();
		while (it != ite && fit != fite)
		{
			CHECK(it->first == fit->first);
			CHECK(it->second == fit->second);
			it++;
			fit++;
		}
		it = s2.begin();
		ite = s2.end();
		fit = f2.begin();
		fite = f2.end();
		while (it != ite && fit != fite)
		{
			CHECK(it->first == fit->first);
			CHECK(it->second == fit->second);
			it++;
			fit++;
		}
	}

	SUBCASE("clear")
	{
		std::map<char, int> sm;
		ft::map<char, int> fm;

		sm['x'] = 100;
		sm['y'] = 200;
		sm['z'] = 300;
		
		fm['x'] = 100;
		fm['y'] = 200;
		fm['z'] = 300;

		std::map<char, int>::iterator it = sm.begin(), ite = sm.end();
		ft::map<char, int>::iterator fit = fm.begin(), fite = fm.end();
		while (it != ite && fit != fite)
		{
			CHECK(it->first == fit->first);
			CHECK(it->second == fit->second);
			it++;
			fit++;
		}

		sm.clear();
		fm.clear();
		sm['a'] = 1101;
		sm['b'] = 2202;
		
		fm['a'] = 1101;
		fm['b'] = 2202;

		it = sm.begin();
		ite = sm.end();
		fit = fm.begin();
		fite = fm.end();
		while (it != ite && fit != fite)
		{
			CHECK(it->first == fit->first);
			CHECK(it->second == fit->second);
			it++;
			fit++;
		}
	}
}

TEST_CASE("Operations")
{
	typedef std::map<char, int> SMAP;
	typedef ft::map<char, int> FMAP;

	SMAP sm;
	SMAP::iterator mit;
	
	FMAP fm;
	FMAP::iterator fit;

	sm['a'] = 50;
	sm['b'] = 100;
	sm['c'] = 150;
	sm['d'] = 200;

	fm['a'] = 50;
	fm['b'] = 100;
	fm['c'] = 150;
	fm['d'] = 200;
	
	mit = sm.find('b');
	fit = fm.find('b');
	CHECK(mit->first == fit->first);
	CHECK(mit->second == fit->second);

	SUBCASE("count")
	{
		std::map<char, int> sm;
		ft::map<char, int> fm;
		char c;
		char fc;

		sm['a'] = 101;
		sm['c'] = 202;
		sm['f'] = 303;
		
		fm['a'] = 101;
		fm['c'] = 202;
		fm['f'] = 303;

		for (c = 'a', fc = 'a'; c < 'h'; c++, fc++)
			CHECK(sm.count(c) == fm.count(fc));
	}

	SUBCASE("lower_bound")
	{
		std::map<char, int> sm;
		std::map<char, int>::iterator itlow, itup;
		ft::map<char, int> fm;
		ft::map<char, int>::iterator fitlow, fitup;

		int n = 20;
		for (char i = 'a'; i <= 'e'; i++)
		{
			sm[i] = n;
			fm[i] = n;
			n += 20;
		}

		itlow = sm.lower_bound('b');
		sm.erase(itlow);
		itlow = sm.lower_bound('b');
		sm.erase(itlow);
		itlow = sm.lower_bound('b');
		sm.erase(itlow);

		fitlow = fm.lower_bound('b');
		fm.erase(fitlow);
		fitlow = fm.lower_bound('b');
		fm.erase(fitlow);
		fitlow = fm.lower_bound('b');
		fm.erase(fitlow);

		std::map<char, int>::iterator it = sm.begin(), ite = sm.end();
		ft::map<char, int>::iterator fit = fm.begin(), fite = fm.end();
		(void)ite;
		while (fit != fite)
		{
			CHECK(it->first == fit->first);
			CHECK(it->second == fit->second);
			it++;
			fit++;
		}
	}
	SUBCASE("upper_bound")
	{
		std::map<char, int> sm;
		std::map<char, int>::iterator itupper, itup;
		ft::map<char, int> fm;
		ft::map<char, int>::iterator fitupper, fitup;

		int n = 20;
		for (char i = 'a'; i <= 'h'; i++)
		{
			sm[i] = n;
			fm[i] = n;
			n += 20;
		}

		itupper = sm.upper_bound('b');
		sm.erase(itupper);
		itupper = sm.upper_bound('b');
		sm.erase(itupper);
		itupper = sm.upper_bound('b');
		sm.erase(itupper);

		fitupper = fm.upper_bound('b');
		fm.erase(fitupper);
		fitupper = fm.upper_bound('b');
		fm.erase(fitupper);
		fitupper = fm.upper_bound('b');
		fm.erase(fitupper);

		std::map<char, int>::iterator it = sm.begin(), ite = sm.end();
		ft::map<char, int>::iterator fit = fm.begin(), fite = fm.end();
		(void)ite;
		while (fit != fite)
		{
			CHECK(it->first == fit->first);
			CHECK(it->second == fit->second);
//			cout << "it: " << it->first << " => " << it->second << endl;
//			cout << "fit: " << fit->first << " => " << fit->second << endl;
			it++;
			fit++;
		}
	}
	SUBCASE("equal_range")
	{
		std::map<char, int> sm;
		ft::map<char, int> fm;

		sm['a'] = 10;
		sm['b'] = 20;
		sm['c'] = 30;
		
		fm['a'] = 10;
		fm['b'] = 20;
		fm['c'] = 30;

		std::pair<std::map<char, int>::iterator, std::map<char, int>::iterator> ret;
		ft::pair<ft::map<char, int>::iterator, ft::map<char, int>::iterator> fret;
		ret = sm.equal_range('b');
		fret = fm.equal_range('b');

		CHECK(ret.first->first == fret.first->first);
		CHECK(ret.first->second == fret.first->second);
		
		CHECK(ret.second->first == fret.second->first);
		CHECK(ret.second->second == fret.second->second);
	}
}

TEST_CASE("Observers")
{
	SUBCASE("key_comp")
	{
		std::map<char, int> sm;
		std::map<char, int>::key_compare mycomp = sm.key_comp();
		
		ft::map<char, int> fm;
		ft::map<char, int>::key_compare ftcomp = fm.key_comp();

		sm['a'] = 100;
		sm['b'] = 200;
		sm['c'] = 300;
		fm['a'] = 100;
		fm['b'] = 200;
		fm['c'] = 300;

		char highest = sm.rbegin()->first;
		char fhighest = fm.rbegin()->first;

		std::map<char, int>::iterator it = sm.begin();
		ft::map<char, int>::iterator fit = fm.begin();
		do
		{
			CHECK(it->first == fit->first);
			CHECK(it->second == fit->second);
		} while (mycomp((*it++).first, highest)
				&& ftcomp((*fit++).first, fhighest));
		cout << endl;
	}

	SUBCASE("value_compare")
	{
		std::map<char, int> sm;
		ft::map<char, int> fm;

		sm['x'] = 1001;
		sm['y'] = 2002;
		sm['z'] = 3003;
		
		fm['x'] = 1001;
		fm['y'] = 2002;
		fm['z'] = 3003;

		std::pair<char, int> highest = *sm.rbegin(); // last element
		ft::pair<char, int> fhighest = *fm.rbegin(); // last element
		
		std::map<char, int>::iterator it = sm.begin();
		ft::map<char, int>::iterator fit = fm.begin();
		do
		{
			CHECK(it->first == fit->first);
			CHECK(it->second == fit->second);
		}
		while (sm.value_comp()(*it++, highest)
				&& fm.value_comp()(*fit++, fhighest));
	}
}

TEST_CASE("Non-member fucntions")
{
	SUBCASE("Operator")
	{
		typedef std::map<int, char> SM;
		typedef ft::map<int, char> FM;

		SM salice, sbob, seve;
		FM falice, fbob, feve;

		for (int i = 1; i <= 3; i++)
		{
			sbob[i] = 96 + i;
			seve[i] = 96 + i;
			fbob[i] = 96 + i;
			feve[i] = 96 + i;
		}
		for (int i = 7; i <= 10; i++)
		{
			salice[i] = 123 - i;
			falice[i] = 123 - i;
		}
		SM::iterator it = salice.begin(), ite = salice.end();
		FM::iterator fit = falice.begin(), fite = falice.end();
		while (it != ite)
		{
			CHECK(it->first == fit->first);
			CHECK(it->second == fit->second);
			it++;
			fit++;
		}
		
		(++(++salice.begin()))->second = 42;
		(++(++falice.begin()))->second = 42;

		cout << std::boolalpha;
		CHECK((salice == sbob) == (falice == fbob));
		CHECK((salice != sbob) == (falice != fbob));
		CHECK((salice < sbob) == (falice < fbob));
		CHECK((salice <= sbob) == (falice <= fbob));
		CHECK((salice > sbob) == (falice > fbob));
		CHECK((salice >= sbob) == (falice >= fbob));
		
		cout << "\n" << endl;
		CHECK((salice == seve) == (falice == feve));
		CHECK((salice != seve) == (falice != feve));
		CHECK((salice < seve) == (falice < feve));
		CHECK((salice <= seve) == (falice <= feve));
		CHECK((salice > seve) == (falice > feve));
		CHECK((salice >= seve) == (falice >= feve));
	}
}

void	ft_test(void)
{
	ft::map<char, int> fm;

	fm['a'] = 3;
	fm['b'] = 1;
	fm['c'] = 4;

	ft::map<char, int>::const_iterator it = fm.begin();
	//ft::map<char, int>::iterator it = fm.begin();
	std::advance(it, 2);
	cout << it->first << "=>" << it->second << endl;
}

int main(int argc, char **argv)
{
	ft_test();
#ifdef noasan
	system("leaks main");
#endif
	return (doc(&argc, argv));
}
