/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:51:20 by leng-chu          #+#    #+#             */
/*   Updated: 2022/11/14 15:04:07 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define DOCTEST_CONFIG_IMPLEMENT
#include "lib.hpp"
#include "doctest.hpp"

int	main(int argc, char **argv)
{
	doctest::Context context;

	context.addFilter("test-case-exclude", "*math*");
	context.setOption("abort-after", 5);
	context.setOption("order-by", "name");

	context.applyCommandLine(argc, argv);

	context.setOption("no-breaks", true);
	int res = context.run();
	if (context.shouldExit())
		return res;
	int client_stuff_return_code = 0;
	return (res + client_stuff_return_code);
}
