/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:31:37 by leng-chu          #+#    #+#             */
/*   Updated: 2022/12/20 14:08:12 by leng-chu         ###   ########.fr       */
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

int main()
{
	char foo[] = "Apple";
	char bar[] = "apartment";

	cout << boolalpha;
	cout << "Comparing foo and bar lexicographically (foo < bar)" << endl;
	cout << "Using default comparison (operator<): " << endl;
	cout << std::lexicographical_compare(foo, foo + 5, bar, bar + 9) << endl;
	cout << ft::lexicographical_compare(foo, foo + 5, bar, bar + 9) << endl;
	cout << endl;

	cout << "Using mycomp as comparison object: " << endl;
	cout << std::lexicographical_compare(foo, foo + 5, bar, bar + 9, mycomp) << endl;
	cout << ft::lexicographical_compare(foo, foo + 5, bar, bar + 9, mycomp) << endl;
	cout << endl;

	vector<string> v1;
	v1.push_back("One");
	v1.push_back("Two");
	v1.push_back("Three");

	vector<string> v2;
	v2.push_back("one");
	v2.push_back("two");
	v2.push_back("three");

	bool result;
	result = lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end());
	bool result2;
	result2 = ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end());

	if (result == true)
		cout << "std: v1 is less than v2." << endl;
	if (result2 == true)
		cout << "ft: v1 is less than v2." << endl;
	v1[0] = "two";
	result = lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end());
	result2 = ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end());
	if (result == false)
		cout << "std: v1 is not less than v2." << endl;
	if (result2 == false)
		cout << "ft: v1 is not less than v2." << endl;
	return (0);
}
