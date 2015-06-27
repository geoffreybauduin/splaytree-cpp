/* 
* @Author: Geoffrey Bauduin
* @Date:   2015-04-13 13:10:46
* @Last Modified by:   Geoffrey Bauduin
* @Last Modified time: 2015-04-13 16:09:32
*/

#include	<iostream>
#include	"SplayTree.hpp"

int main(void) {
	SplayTree<int> *tree = new SplayTree<int>();
	bool running = true;
	while (running) {
		int choice;
		std::cout << "SplayTree operations:" << std::endl;
		std::cout << "\t1. Insert" << std::endl;
		std::cout << "\t2. Delete" << std::endl;
		std::cout << "\t3. Search" << std::endl;
		std::cout << "\t4. Exit" << std::endl;
		std::cout << "Enter you choice: ";
		std::cin >> choice;
		int input;
		switch (choice) {
			case 1:
				std::cout << "\tEnter value to be inserted: ";
				std::cin >> input;
				std::cout << std::endl;
				tree->insert(input);
				break;
			case 2:
				std::cout << "\tEnter value to be removed: ";
				std::cin >> input;
				std::cout << std::endl;
				tree->remove(input);
				break;
			case 3:
				std::cout << "\tEnter value to be searched: ";
				std::cin >> input;
				std::cout << std::endl;
				tree->search(input);
				break;
			case 4:
				running = false;
				break;
			default:
				std::cout << "Bad command" << std::endl;
				break;
		}
		std::cout << std::endl << std::endl;
		tree->print();
		std::cout << std::endl << std::endl;
	}
	return 0;
}