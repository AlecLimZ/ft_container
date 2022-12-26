/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:31:37 by leng-chu          #+#    #+#             */
/*   Updated: 2022/12/26 14:00:11 by leng-chu         ###   ########.fr       */
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

int main()
{
	ft::vector<int> ftv;
	std::vector<int> stdv;

	for (int i = 1; i <= 7; ++i)
	{
		ftv.push_back(i);
		stdv.push_back(i);
	}

	typedef std::vector<int>::reverse_iterator stditrev;
	typedef ft::vector<int>::reverse_iterator ftitrev;

	stditrev stdb(stdv.end());
	ftitrev ftb(ftv.end());

	cout << "base stdb: " << *(stdb.base()) << endl;
	cout << "base ftb: " << *(ftb.base()) << endl;
}
