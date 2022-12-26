/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:31:37 by leng-chu          #+#    #+#             */
/*   Updated: 2022/12/26 17:31:43 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include <iostream>
#include <stdlib.h>
#include "myclass.hpp"
#include "iter.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <array>
#include <unordered_map>
#include <memory> // for unique make
#include <type_traits> // for enable_if
#include <numeric> // for std::reduce & accumulate()
#include <fstream>
#include <cstdlib>
#include <memory>
#include <string>
#include "../FT_C/vector.hpp"
#include <map>

using std::cout;
using std::endl;
using std::cin;
using std::vector;
//using std::iterator_traits;
using std::list;
using std::unordered_map;
using std::string;
using std::ostream;
using std::iterator_traits;
using std::array;
using std::ifstream;
using std::boolalpha;

bool fncomp(char lhs, char rhs)
{
	return (lhs < rhs);
}

struct classcomp
{
	bool operator() (const char & lhs, const char & rhs) const
	{
		return (lhs < rhs);
	}
};

int main()
{
	std::map<char, int> first;

	first['a'] = 10;
	first['b'] = 30;
	first['c'] = 50;
	first['d'] = 70;

	cout << first.size() << endl;
	for (std::map<char, int>::size_type i = 'a'; i < 'd'; ++i)
		cout << first[i] << endl;

	//std::map<char, int> second(first.begin(), first.end());

//	std::map<char, int> third(second);

//	bool(*fn_pt)(char, char) = fncomp;
//	std::map<char, int, bool(*)(char, char)> fifth(fn_pt);
	return (0);
}
