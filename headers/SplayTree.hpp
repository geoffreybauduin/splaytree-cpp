/* 
* @Author: Geoffrey Bauduin
* @Date:   2015-04-13 13:10:46
* @Last Modified by:   Geoffrey Bauduin
* @Last Modified time: 2015-04-13 13:10:51
*/

#ifndef		__SPLAYTREE_HPP__
# define 	__SPLAYTREE_HPP__

# include	<stdexcept>
# include	<iostream>
# include	<iomanip>
# include	<queue>
# include	<algorithm>

# define ZIGZAG(t)	(t[0] == true && t[1] == false)
# define ZIGZIG(t) (t[0] == true && t[1] == true)
# define ZAGZIG(t) (t[0] == false && t[1] == true)
# define ZAGZAG(t) (t[0] == false && t[1] == false)

template<typename T>
class SplayTree {

	struct Node {
		T 		key;
		Node	*left;
		Node	*right;
		Node	*parent;

		Node(T k): key(k), left(NULL), right(NULL), parent(NULL) {}
		virtual ~Node(void) {}
	};

	private:

		/**
		 * Zigs the node
		 */
		void	_zig(Node *x) {
			Node *y = x->parent;
			x->parent = y->parent;
			y->parent = x;
			if (x->parent) {
				if (x->parent->left == y) {
					x->parent->left = x;
				}
				else {
					x->parent->right = x;
				}
			}
			y->left = x->right;
			if (y->left) {
				y->left->parent = y;
			}
			x->right = y;
		}

		/**
		 * Zags the node
		 */
		void	_zag(Node *y) {
			Node *x = y->parent;
			y->parent = x->parent;
			x->parent = y;
			if (y->parent) {
				if (y->parent->left == x) {
					y->parent->left = y;
				}
				else {
					y->parent->right = y;
				}
			}
			x->right = y->left;
			if (x->right) {
				x->right->parent = x;
			}
			y->left = x;
		}

		/**
		 * Recursive search for the node
		 */
		Node 	*_search(T key, Node *root) {
			if (root) {
				this->_last = root;
				if (key < root->key) {
					return this->_search(key, root->left);
				}
				else if (key > root->key) {
					return this->_search(key, root->right);
				}
				else {
					return root;
				}
			}
			return NULL;
		}

		/**
		 * Inserts with a binary search tree behavior
		 */
		void	_binaryInsert(Node *node, Node *root) {
			if (root) {
				if (node->key < root->key) {
					if (root->left == NULL) {
						root->left = node;
						node->parent = root;
					}
					else {
						this->_binaryInsert(node, root->left);
					}
				}
				else if (node->key > root->key) {
					if (root->right == NULL) {
						root->right = node;
						node->parent = root;
					}
					else {
						this->_binaryInsert(node, root->right);
					}
				}
			}
			else {
				// It only goes here if its the first node of the graph
				this->_root = node;
			}
		}

		/**
		 * Splays the corresponding node
		 */
		void	_splay(Node *node) {
			unsigned int size = this->_size(node);
			std::cout << " n(" << node->key << ") = " << size << " ;  r(" << node->key << ") = " << (int) (log10(size) / log10(2)) << std::endl;
			if (node->parent && node->parent->parent == NULL) {
				if (node->parent->left == node) {
					std::cout << "zig" << std::endl;
					this->_zig(node);
				}
				else {
					std::cout << "zag" << std::endl;
					this->_zag(node);
				}
			}
			else if (node->parent && node->parent->parent) {
				bool zz[2];
				zz[0] = node->parent->parent->left == node->parent;
				zz[1] = node->parent->left == node;
				if (ZIGZIG(zz)) {
					std::cout << "zigzig" << std::endl;
					this->_zig(node->parent);
					this->_zig(node);					
				}
				else if (ZAGZAG(zz)) {
					std::cout << "zagzag" << std::endl;
					this->_zag(node->parent);
					this->_zag(node);					
				}
				else if (ZIGZAG(zz)) {
					std::cout << "zigzag" << std::endl;
					this->_zag(node);
					this->_zig(node);
				}
				else { // ZAGZIG
					std::cout << "zagzig" << std::endl;
					this->_zig(node);
					this->_zag(node);
				}		
			}
			size = this->_size(node);
			std::cout << "n'(" << node->key << ") = " << size << " ; r'(" << node->key << ") = " << (int) (log10(size) / log10(2)) << std::endl;
			if (node->parent) {
				this->print();
				this->_splay(node);				
			}
			else {
				this->_root = node;
			}
		}

		void	_print(Node *root) {
			if (!root) return;
			std::queue<Node*> nodesQueue;
			int nodesInCurrentLevel = 1;
			int nodesInNextLevel = 0;
			nodesQueue.push(root);
			while (!nodesQueue.empty()) {
				Node *currNode = nodesQueue.front();
				nodesQueue.pop();
				nodesInCurrentLevel--;
				if (currNode) {
					std::cout << currNode->key << " ";
					nodesQueue.push(currNode->left);
					nodesQueue.push(currNode->right);
					nodesInNextLevel += 2;
				}
				else {
					std::cout << "- ";
				}
				if (nodesInCurrentLevel == 0) {
					std::cout << std::endl;
					nodesInCurrentLevel = nodesInNextLevel;
					nodesInNextLevel = 0;
				}
			}
		}

		void printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const std::deque<Node *> &nodesQueue) {
		  typename std::deque<Node *>::const_iterator iter = nodesQueue.begin();
		  for (int i = 0; i < nodesInThisLevel / 2; i++) {  
		    std::cout << ((i == 0) ? std::setw(startLen-1) : std::setw(nodeSpaceLen-2)) << "" << ((*iter++) ? "/" : " ");
		    std::cout << std::setw(2*branchLen+2) << "" << ((*iter++) ? "\\" : " ");
		  }
		  std::cout << std::endl;
		}
		 
		void printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const std::deque<Node*>& nodesQueue) {
			typename std::deque<Node*>::const_iterator iter = nodesQueue.begin();
			for (int i = 0; i < nodesInThisLevel; i++, iter++) {
				std::cout << ((i == 0) ? std::setw(startLen) : std::setw(nodeSpaceLen)) << "";
				std::cout << ((*iter && (*iter)->left) ? std::setfill('_') : std::setfill(' '));
				std::cout << std::setw(branchLen+2);
				if (*iter) {
					std::cout << (*iter)->key;
				}
				else {
					std::cout << "";
				}
				std::cout << ((*iter && (*iter)->right) ? std::setfill('_') : std::setfill(' ')) << std::setw(branchLen) << "" << std::setfill(' ');
			}
			std::cout << std::endl;
		}
		 
		void printLeaves(int indentSpace, int level, int nodesInThisLevel, const std::deque<Node *> &nodesQueue) {
			typename std::deque<Node *>::const_iterator iter = nodesQueue.begin();
			for (int i = 0; i < nodesInThisLevel; i++, iter++) {
				std::cout << ((i == 0) ? std::setw(indentSpace+2) : std::setw(2*level+2));
				if (*iter) {
					std::cout << (*iter)->key;
				}
				else {
					std::cout << "";
				}
			}
			std::cout << std::endl;
		}
		 
		/**
		 * Pretty print of the graph
		 */
		void printPretty(Node *root, int level, int indentSpace) {
			int h = this->_height(root);
			int nodesInThisLevel = 1;
			int branchLen = 2*((int)pow(2.0,h)-1) - (3-level)*(int)pow(2.0,h-1);
			int nodeSpaceLen = 2 + (level+1)*(int)pow(2.0,h);
			int startLen = branchLen + (3-level) + indentSpace;
			std::deque<Node *> nodesQueue;
			nodesQueue.push_back(root);
			for (int r = 1; r < h; r++) {
				this->printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue);
				branchLen = branchLen/2 - 1;
				nodeSpaceLen = nodeSpaceLen/2 + 1;
				startLen = branchLen + (3-level) + indentSpace;
				this->printNodes(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue);
				for (int i = 0; i < nodesInThisLevel; i++) {
					Node *currNode = nodesQueue.front();
					nodesQueue.pop_front();
					if (currNode) {
						nodesQueue.push_back(currNode->left);
						nodesQueue.push_back(currNode->right);
					}
					else {
						nodesQueue.push_back(NULL);
						nodesQueue.push_back(NULL);
					}
				}
				nodesInThisLevel *= 2;
			}
			this->printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue);
			this->printLeaves(indentSpace, level, nodesInThisLevel, nodesQueue);
		}

		/**
		 * Returns the height at a given node
		 */
		unsigned int _height(Node *root) {
			return !root ? 0 : std::max(this->_height(root->left), this->_height(root->right)) + 1;
		}

		Node 	*_root;
		Node 	*_last;

		/**
		 * Returns the far right node
		 */
		Node 	*_getFarRightNode(Node *root) {
			return (root->right ? this->_getFarRightNode(root->right) : root);
		}

		/**
		 * Returns the size of a given node
		 */
		unsigned int 	_size(Node *root) {
			return root ? 1 + this->_size(root->left) + this->_size(root->right) : 0;
		}

	public:
		SplayTree(void): _root(NULL), _last(NULL) {

		}

		virtual ~SplayTree(void) {

		}

		const Node *getRoot(void) const {
			return this->_root;
		}

		/**
		 * Inserts a new node with the corresponding key
		 */
		void	insert(T key) {
			std::cout << "insert(" << key << ")" << std::endl;
			Node *node = this->_search(key, this->_root);
			if (node == NULL) {
				node = new Node(key);
				this->_binaryInsert(node, this->_root);
			}
			std::cout << "splay(" << node->key << ")" << std::endl;
			this->_splay(node);
		}

		/**
		 * Removes the node with the corresponding key
		 */
		void	remove(T key) {
			Node *node = this->_search(key, this->_root);
			if (node) {
				this->_splay(node);
				if (node->left) {
					node->left->parent = NULL;
					Node *farRight = this->_getFarRightNode(node->left);
					this->_splay(farRight);
					this->_root->right = node->right;
					if (node->right) {
						node->right->parent = this->_root;
					}
				}
				else {
					this->_root = node->right;
					if (node->right) {
						node->right->parent = NULL;
					}
				}
				delete node;
			}
		}

		/**
		 * Finds the node with the corresponding key
		 */
		Node	*search(T key) {
			this->_last = NULL;
			Node *node = this->_search(key, this->_root);
			if (node) {
				std::cout << "splay(" << node->key << ")" << std::endl;
				this->_splay(node);
			}
			else if (this->_last) {
				this->_splay(this->_last);
			}
			return node;
		}

		/**
		 * Prints the graph
		 */
		void	print(void) {
			this->printPretty(this->_root, 1, 0);
		}

		/**
		 * Returns the height of the graph
		 */
		unsigned int height() {
			unsigned int v = this->_height(this->_root);
			std::cout << "height: " << v << std::endl;
			return v;
		}

		/**
		 * Returns the size of a node with the corresponding key
		 */
		unsigned int size(T key) {
			Node *node = this->_search(key, this->_root);
			return this->_size(node);
		}

};

#endif