/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:31:37 by leng-chu          #+#    #+#             */
/*   Updated: 2023/01/03 17:50:33 by leng-chu         ###   ########.fr       */
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

template<typename T>
typedef struct s_rbt
{
	int	black;
	int	red;
	T	node;
}	t_rbt;

class RedBlackTree
{
	protected:
	public:
		RedBlackTree(void){}
		~RedBlackTree(void){}
		RedBlackTree(const RedBlackTree & rhs)
		{
			nullNode = new RedBlackNode;
			nullNode->left = nullNode->right = nullNode;

			header = new RedBlackNode{rhs.header->element};
			header->left = nullNode;
			header->right = clone(rhs.header->right);
		}
		void	printTree() const
		{
			if (header->right == nullptr)
				cout << "Empty tree" << endl;
			else
				printTree(header->right);
		}
		void	printTree(RedBlackNode *t) const
		{
			if (t != t->left)
			{
				printTree(t->left);
				cout << t->element << endl;
				printTree(t->right);
			}
		}

};

int main()
{
	return (0);
}
