/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:31:37 by leng-chu          #+#    #+#             */
/*   Updated: 2022/11/28 19:06:42 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myclass.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <unordered_map>
#include <memory> // for unique make
#include <type_traits> // for enable_if

using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::iterator_traits;
using std::list;
using std::unordered_map;
using std::string;
using std::enable_if;
using std::ostream;

// non-type template parameter

template <int N>
class A
{
	public:
	int v{N};
	template<int J> friend ostream& operator<< (ostream &,A<J>&);
};

template <int N = 10>
class B
{
	int v{N};
};

template <int = 10>
class C
{
	int v{0};
};

template <int>
class D
{
	int v{0};
};

template <int, int>
class E
{
	int v{0};
};

template<int J> ostream& operator<< (ostream & o,A<J> & a)
{
	o << "A: " << a.v;
	return (o);
}
int main()
{
	A<19> a{};
	cout << a << endl;
	return (0);
}
