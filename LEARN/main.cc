/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:31:37 by leng-chu          #+#    #+#             */
/*   Updated: 2022/12/01 18:42:51 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myclass.hpp"
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

template <typename Random>
Random getRandomElement (Random first, Random last)
{
	ptrdiff_t d = last - first;
	return (first + rand() % d);
}

int main()
{
	vector<int> v(10, 0);

	// iterator
	vector<int>::iterator it;
	it = v.begin();
	*it = 911;
	it++;

	// const_iterator
	vector<int>::const_iterator cit;
	cit = v.begin();

	// *cit = 911;
	cit++;

	// iterator that is constant
	const vector<int>::iterator itc = v.begin();

	// itc = v.begin();
	*itc = 911;
	itc++;
	return (0);
}
