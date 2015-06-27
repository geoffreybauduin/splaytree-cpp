/* 
* @Author: Geoffrey Bauduin
* @Date:   2015-04-13 16:56:58
* @Last Modified by:   Geoffrey Bauduin
* @Last Modified time: 2015-04-13 16:57:30
*/

#ifndef		__TESTER_HPP__
# define	__TESTER_HPP__

# include	<vector>
# include	<string>
# include	<utility>
# include	<functional>
# include	"SplayTree.hpp"

class Tester {

private:
	std::vector< std::pair<std::string, bool> >		_tests;

	void		executeTest(const std::string &, SplayTree<int> *, std::function<bool (SplayTree<int> *)>);

public:
	Tester(void);
	~Tester(void);

	void	run(void);
	void	dump(void) const;
	int		exit(void) const;

};

#endif