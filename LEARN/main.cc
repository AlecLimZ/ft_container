/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:31:37 by leng-chu          #+#    #+#             */
/*   Updated: 2022/12/19 20:30:28 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

namespace ft
{
	template <class T>
	struct is_integral
	{
		static const bool value = std::numeric_limits<T>::is_integer;
	};
}

using std::lexicographical_compare;

int main()
{
	char a[] = "Apple";
	string c = "Apple";
	string d = "apartment";
	char b[] = "apartment";

	cout << lexicographical_compare(a, a + 5, b, b + 9);
	cout << endl;
	cout << lexicographical_compare(c.begin(), c.end(), d.begin(), d.end());
	cout << endl;
	return (0);
}
