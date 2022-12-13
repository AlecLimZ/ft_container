/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:51:20 by leng-chu          #+#    #+#             */
/*   Updated: 2022/12/13 15:59:38 by leng-chu         ###   ########.fr       */
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
	const int size = 5;
//	std::vector<int> vct(size);
//	std::vector<int>::iterator it = vct.begin();
//	std::vector<int>::const_iterator ite = vct.begin();
	ft::vector<int> vct(size);
	ft::vector<int>::iterator it = vct.begin();
	ft::vector<int>::const_iterator ite = vct.begin();
	for (int i = 0; i < size; ++i)
	{
		it[i] = (size - i) * 5;
	}
	cout << *it << endl;
	it = it + 5;
	cout << "it + 5: " << *it << endl;
	it = 1 + it;
	cout << "1 + it: " << *it << endl;
	it = it - 4;
	cout << "it - 4: " << *it << endl;
	cout << *(it += 2) << endl;
	(void)ite;
}

TEST_CASE("Iterator & const iterator")
{
	std::vector<int> vstd;
	ft::vector<int> vft;

	for (int i = 1; i <= 7; ++i)
	{
		vstd.push_back(i);
		vft.push_back(i);
	}
	typedef std::vector<int>::iterator stditer;
	typedef ft::vector<int>::iterator ftiter;
	typedef std::vector<int>::const_iterator cstditer;
	typedef ft::vector<int>::const_iterator cftiter;

	// iterator & const iterator parameter constructor
	stditer sit = vstd.begin();
	stditer site = vstd.end();
	ftiter fit = vft.begin();
	ftiter fite = vft.end();

	cstditer csit = vstd.begin();
	cstditer csite = vstd.end();
	cftiter cfit = vft.begin();
	cftiter cfite = vft.end();

	// iterator & const iterator default constructor
	stditer dit, dite;
	ftiter dfit, dfite;

	cstditer cdit, cdite;
	cftiter cdfit, cdfite;
	
	// iterator & const iterator assign constructor
	dit = sit; dite = site;
	dfit = fit; dfite = fite;

	cdit = csit; cdite = csite;
	cdfit = cfit; cdfite = cfite;

	// iterator & const iterator copy constructor
	stditer stdc(dit);
	stditer stdce(dite);
	ftiter ftc(dfit);
	ftiter ftce(dfite);

	cstditer cstdc(cdit);
	cstditer cstdce(cdite);
	cftiter cftc(cdfit);
	cftiter cftce(cdfite);

	SUBCASE("iterator & const iterator[] operator")
	{
		CHECK(stdc[0] == ftc[0]);
		CHECK(stdc[1] == ftc[1]);
		CHECK(stdc[2] == ftc[2]);
	
		CHECK(cstdc[0] == cftc[0]);
		CHECK(cstdc[1] == cftc[1]);
		CHECK(cstdc[2] == cftc[2]);
	}

	SUBCASE("iterator & const iterator bool")
	{
		CHECK((ftc == dfit) == (stdc == dit));
		CHECK((ftc != dfit) == (stdc != dit));
		CHECK((ftc == dfite) == (stdc == dite));
		CHECK((ftc > dfite) == (stdc > dite));
		CHECK((ftc < dfite) == (stdc < dite));
		CHECK((ftc < dfite) == (stdc < dite));
		CHECK((ftc > dfite) == (stdc > dite));
		CHECK((ftc >= dfite) == (stdc >= dite));
		CHECK((ftc <= dfite) == (stdc <= dite));
		CHECK((ftc <= dfite) == (stdc <= dite));
		CHECK((ftc >= dfite) == (stdc >= dite));
		
		CHECK((cftc == cdfit) == (cstdc == cdit));
		CHECK((cftc != cdfit) == (cstdc != cdit));
		CHECK((cftc == cdfite) == (cstdc == cdite));
		CHECK((cftc != cdfite) == (cstdc != cdite));
		CHECK((cftc > cdfite) == (cstdc > cdite));
		CHECK((cftc < cdfite) == (cstdc < cdite));
		CHECK((cftc < cdfite) == (cstdc < cdite));
		CHECK((cftc > cdfite) == (cstdc > cdite));
		CHECK((cftc >= cdfite) == (cstdc >= cdite));
		CHECK((cftc <= cdfite) == (cstdc <= cdite));
		CHECK((cftc <= cdfite) == (cstdc <= cdite));
		CHECK((cftc >= cdfite) == (cstdc >= cdite));
	}

	SUBCASE("iterator & const iterator *operator, ++operator")
	{
		while (stdc != stdce && ftc != ftce)
			CHECK(*++stdc == *++ftc);
		while (cstdc != cstdce && cftc != cftce)
			CHECK(*++cstdc == *++cftc);
	}

	SUBCASE("iterator & const iterator *opeator, --operator")
	{
		while (stdc != vstd.begin() && ftc != vft.begin())
			CHECK(*--stdc == *--ftc);
		while (cstdc != vstd.begin() && cftc != vft.begin())
			CHECK(*--cstdc == *--cftc);
	}

	SUBCASE("iterator & const iterator *operator, operator++")
	{
		while (stdc != stdce && ftc != ftce)
			CHECK(*stdc++ == *ftc++);
		while (cstdc != cstdce && cftc != cftce)
			CHECK(*cstdc++ == *cftc++);
	}

	SUBCASE("iterator & const iterator *operator, operator--")
	{
		while (stdc != vstd.begin() && ftc != vft.begin())
			CHECK(*stdc-- == *ftc--);
		while (cstdc != vstd.begin() && cftc != vft.begin())
			CHECK(*cstdc-- == *cftc--);
	}

	SUBCASE("iterator & const iterator *operator, operator+=")
	{
		while (stdc != stdce && ftc != ftce)
		{
			stdc += 1; ftc += 1;
			CHECK(*stdc == *ftc);
		}
		while (cstdc != cstdce && cftc != cftce)
		{
			cstdc += 1; cftc += 1;
			CHECK(*cstdc == *cftc);
		}
	}

	SUBCASE("iterator & const iterator *operator, operator-=")
	{
		while (stdc != vstd.begin() && ftc != vft.begin())
		{
			stdc -= 1; ftc -= 1;
			CHECK(*stdc == *ftc);
		}
		while (cstdc != vstd.begin() && cftc != vft.begin())
		{
			cstdc -= 1; cftc -= 1;
			CHECK(*cstdc == *cftc);
		}
	}
	SUBCASE("iterator & const iterator operator-, operator+")
	{
		stditer stdplus = stdc + 2;
		ftiter ftplus = ftc + 2;
		CHECK(*stdplus == *ftplus);
		stdc += 3;
		ftc += 3;
		stditer stdm = stdc - 2;
		ftiter ftm = ftc - 2;
		CHECK(*stdm == *ftm);

		cstditer cstdplus = cstdc + 2;
		cftiter cftplus = cftc + 2;
		CHECK(*cstdplus == *cftplus);
		cstdc += 3;
		cftc += 3;
		cstditer cstdm = cstdc - 2;
		cftiter cftm = cftc - 2;
		CHECK(*cstdm == *cftm);

		// friend X operator+(size_t n, const X & other)
		stditer stdtry = 2 + stdc;
		ftiter fttry = 2 + ftc;
		CHECK(*stdtry == *fttry);
		
		cstditer cstdtry = 2 + cstdc;
		cftiter cfttry = 2 + cftc;
		CHECK(*cstdtry == *cfttry);

		CHECK((stdtry - stdc) == (fttry - ftc));
		CHECK((cstdtry - cstdc) == (cfttry - cftc));
	}
}

int main(int argc, char **argv)
{
	test();
#ifdef noasan
	system("leaks main");
#endif
	return (doc(&argc, argv));
}
