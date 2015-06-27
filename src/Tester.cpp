/* 
* @Author: Geoffrey Bauduin
* @Date:   2015-04-13 16:56:47
* @Last Modified by:   Geoffrey Bauduin
* @Last Modified time: 2015-04-14 15:58:44
*/

#include	<iostream>
#include	<iomanip>
#include	<algorithm>
#include	"Tester.hpp"

Tester::Tester(void): _tests() {

}

Tester::~Tester(void) {

}

void	Tester::executeTest(const std::string &name, SplayTree<int> *graph, std::function<bool (SplayTree<int> *)> fn) {
	this->_tests.push_back(std::make_pair(name, false));
	this->_tests[this->_tests.size() - 1].second = fn(graph);
}

void	Tester::dump(void) const {
	long unsigned int msize = 0;
	unsigned int success = 0;
	for (auto it = this->_tests.begin() ; it != this->_tests.end() ; ++it) {
		msize = std::max(msize, it->first.size());
	}
	for (auto it = this->_tests.begin() ; it != this->_tests.end() ; ++it) {
		std::cout << std::left << std::setfill(' ') << std::setw(msize);
		std::cout << it->first << "\t" << (it->second ? "\033[1;32mPASSED\033[0m" : "\033[1;31mFAILED\033[0m") << std::endl;
		if (it->second) {
			success++;
		}
	}
	std::cout << "Tests passed: " << success << " / " << this->_tests.size() << std::endl;
}

void	Tester::run(void) {
	SplayTree<int> *tree = new SplayTree<int>();
	this->executeTest("Root node should be null at the beginning", tree, std::function<bool (SplayTree<int> *)>([](SplayTree<int> *tree) {
		return tree->getRoot() == NULL;
	}));
	this->executeTest("Searching when there is no node shouldnt do anything", tree, std::function<bool (SplayTree<int> *)>([](SplayTree<int> *tree) {
		tree->search(1);
		return tree->getRoot() == NULL;
	}));
	this->executeTest("Removing an edge from an empty tree shouldnt do anything", tree, std::function<bool (SplayTree<int> *)>([](SplayTree<int> *tree) {
		tree->remove(3);
		return tree->getRoot() == NULL;
	}));
 	this->executeTest("Root node shouldnt be null after first insert(1)", tree, std::function<bool (SplayTree<int> *)>([](SplayTree<int> *tree) {
		tree->insert(1);
		return tree->getRoot() != NULL;
	}));
	this->executeTest("Should splay 3 after insert(3)", tree, std::function<bool (SplayTree<int> *)>([](SplayTree<int> *tree) {
		tree->insert(3);
		return tree->getRoot() && tree->getRoot()->key == 3;
	}));
	this->executeTest("Should splay 2 after insert(2), and have 1 and 3 as children", tree, std::function<bool (SplayTree<int> *)>([](SplayTree<int> *tree) {
		tree->insert(2);
		return tree->getRoot() && tree->getRoot()->key == 2 && tree->getRoot()->left && tree->getRoot()->right &&
			tree->getRoot()->left->key == 1 && tree->getRoot()->right->key == 3;
	}));
	this->executeTest("Should splay 1 after search(1), and have 2 as right child, whilst left child is null", tree, std::function<bool (SplayTree<int> *)>([](SplayTree<int> *tree) {
		tree->search(1);
		return tree->getRoot() && tree->getRoot()->key == 1 && !tree->getRoot()->left && tree->getRoot()->right &&
			tree->getRoot()->right->key == 2;
	}));
	this->executeTest("Should remove(3), and should have 2 as root node afterwards", tree, std::function<bool (SplayTree<int> *)>([](SplayTree<int> *tree) {
		tree->remove(3);
		return tree->getRoot() && tree->getRoot()->key == 2 && tree->getRoot()->left && !tree->getRoot()->right &&
			tree->getRoot()->left->key == 1;
	}));
	this->executeTest("Removing a non-existing edge", tree, std::function<bool (SplayTree<int> *)>([](SplayTree<int> *tree) {
		tree->remove(4);
		return tree->getRoot() && tree->getRoot()->key == 2 && tree->getRoot()->left && !tree->getRoot()->right &&
			tree->getRoot()->left->key == 1;
	}));
	this->executeTest("search(0) - non-existing edge - should splay(1)", tree, std::function<bool (SplayTree<int> *)>([](SplayTree<int> *tree) {
		tree->search(0);
		return tree->getRoot() && tree->getRoot()->key == 1 && !tree->getRoot()->left && tree->getRoot()->right &&
			tree->getRoot()->right->key == 2;
	}));
}

int	Tester::exit(void) const {
	for (auto it = this->_tests.begin() ; it != this->_tests.end() ; ++it) {
		if (it->second == false) {
			return 1;
		}
	}
	return 0;
}