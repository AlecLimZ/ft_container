/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:31:37 by leng-chu          #+#    #+#             */
/*   Updated: 2022/12/23 16:15:04 by leng-chu         ###   ########.fr       */
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

bool mycomp(char c1, char c2)
{
	return tolower(c1) < tolower(c2);
}

namespace ft
{

	template <class InputIt1, class InputIt2>
		bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
				InputIt2 first2, InputIt2 last2)
		{
			while (first1 != last1)
			{
				if (first2 == last2 || *first2 < *first1)
					return (false);
				else if (*first1 < *first2)
					return (true);
				first1++, first2++;
			}
			return (first2 != last2);
		}

	template <class InputIt1, class InputIt2, class Compare>
		bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
				InputIt2 first2, InputIt2 last2, Compare comp)
		{
			while (first1 != last1)
			{
				if (first2 == last2 || !comp(*first1, *first2))
					return (false);
				if (comp(*first1, *first2))
					return (true);
				first1++, first2++;
			}
			return (first2 != last2);
		}

	template <class T>
	struct is_integral
	{
		static const bool value = std::numeric_limits<T>::is_integer;
	};
}

template <typename A>
void	pcout(string msg, A input)
{
	cout << msg << input << endl;
}

int main()
{
	std::istringstream in{"Hello, world"};
	std::istreambuf_iterator<char> it{in}, end;
	std::vector<int> box = {34, 34, 55};
	std::vector<char> lol(1,'a');

		try
		{
			std::vector<char>::iterator first = lol.begin();
		//	std::vector<int>::iterator last = std::uninitialized_copy(box.begin(), box.end(), first);
			std::vector<char>::iterator last = std::uninitialized_copy(it, end, first);

			while (first != last)
				cout << *first++ << " ";
			cout << endl;
			first = lol.begin();
			while (first != last)
				cout << *first++ << " ";
			cout << endl;
			cout << lol.size() << endl;
			cout << lol.capacity() << endl;
		}
		catch(...){}
	return (0);
}
