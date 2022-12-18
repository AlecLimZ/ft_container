/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:51:20 by leng-chu          #+#    #+#             */
/*   Updated: 2022/12/18 23:50:56 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.hpp"
#include "vector.hpp"
#include <sstream>

using std::string;

template <typename A>
void	pstd(std::vector<A> p)
{
	for (typename std::vector<A>::size_type i = 0; i < p.size(); ++i)
		cout << p[i] << " ";
	cout << endl;
	cout << "std size: " << p.size() << " | " << "std capacity: " << p.capacity() << endl;
}

template <typename A>
void	pft(ft::vector<A> p)
{
	for (typename ft::vector<A>::size_type i = 0; i < p.size(); ++i)
		cout << p[i] << " ";
	cout << endl;
	cout << "ft size: " << p.size() << " | " << "ft capacity: " << p.capacity() << endl;
	cout << endl;
}
void	ft_test(void)
{
	 // This test checks if vector works with iterators tagged as std::input_iterator_tag
	std::vector<char> sv;
	ft::vector<char> fv;
	 
	 std::istringstream str("1 2 3 4 5 6 7");
	 std::istreambuf_iterator<char> it(str), end;
	 
	 fv.assign(it, end);
	 pft(fv);

	 std::istringstream lol("1 2 3 4 5 6 7");
	 std::istreambuf_iterator<char> itf(lol), endf;
	 sv.assign(itf, endf);
	 pstd(sv);
}

int main()
{
	ft_test();
#ifdef noasan
	system("leaks main");
#endif
	return (0);
}
