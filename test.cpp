/* 
* @Author: Geoffrey Bauduin
* @Date:   2015-04-13 16:56:58
* @Last Modified by:   Geoffrey Bauduin
* @Last Modified time: 2015-04-13 16:59:00
*/

#include	"headers/Tester.hpp"

int main(void) {
	Tester test;
	test.run();
	test.dump();
	return (test.exit());
}