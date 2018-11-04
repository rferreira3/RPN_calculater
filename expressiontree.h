//my tree node hierarchy 
#ifndef DEFINED_EXPRESSION_TREE_
#define DEFINED_EXPRESSION_TREE_

#include "scanner.h"
#include "stack.h"

class ExpressionTree {
	// 1. Add tree node hierarchy . . .  
	//plain node
	class Node {
		//eval 
	public:
		Node() {};
		Token token;
		virtual int evaluate() const = 0; // pure virtual
		//print 
		virtual void print(std::ostream& os, int depth, char link) const = 0; // pure virtual

		static void spaces(int depth) {
			while (depth) {
				depth--;
				std::cout << ' ';
			}
		}
	};

	class operator_node : public Node {
	public:
		operator_node(Node* right, Node* left) : left(left), right(right) {}; //constrsuctor
		Node *left;
		Node *right;


	};

	class plus_node : public operator_node {
	public:
		plus_node(Node* right, Node* left) : operator_node(right, left) {}; //constrsuctor

		int evaluate() const override {
			auto answer = left->evaluate() + right->evaluate();
			return answer;
		}
		void print(std::ostream& os, int depth, char link) const override
		{
			Node *left = this->left;
			Node *right = this->right;
			if (this)
			{
				right->print(os, depth + 5, '/');
				spaces(depth);
				std::cout << link << '(' << '+' << ')' << '\n';
				left->print(os, depth + 5, '\\');
			}
		}


	};

	class times_node : public operator_node {
	public:
		times_node(Node* right, Node* left) : operator_node(right, left) {};//constrsuctor

		int evaluate() const override { return left->evaluate() * right->evaluate(); }
		void print(std::ostream& os, int depth, char link) const override
		{
			Node *left = this->left;
			Node *right = this->right;
			if (this)
			{
				right->print(os, depth + 5, '/');
				spaces(depth);
				std::cout << link << '(' << '*' << ')' << '\n'; //this->token.symbol
				left->print(os, depth + 5, '\\');
			}
		}



	};

	class number_node : public Node {
	public:

		//int _data;
		number_node(int _data) : _data(_data) {};
		int _data;
		int evaluate() const override { return _data; }
		void print(std::ostream& os, int depth, char link) const override
		{
			spaces(depth);
			std::cout << link << '(' << _data << ')' << '\n'; //this->token.value
		}


	};

	// 2. Add instance variable(s) to maintain the state of the tree . . .
	Node *root; //

public:

	// 3. Add a default constructor (makes an empty tree) . . .
	ExpressionTree()
	{
		root = nullptr;
	}

	// 4. Add a constructor that builds a tree from a token 
	//    sequence . . .
	ExpressionTree(TokenSequence tok)
	{
		Stack<Node*, 256> list;

		for (auto token : tok)
		{
			Node* nn = nullptr;
			if (token.symbol == '$')
			{
				nn = new number_node(token.value);
				//list.push(nn);
			}
			else if (token.symbol == '+')
			{
				auto operand_2 = list.pop();
				auto operand_1 = list.pop();
				nn = new plus_node(operand_1, operand_2);

			}
			else if (token.symbol == '*')
			{
				auto operand_2 = list.pop();
				auto operand_1 = list.pop();
				nn = new times_node(operand_1, operand_2);

			}
			list.push(nn);
		}
		root = list.pop();

	}



	// 5. Add a destructor that cleans up the memory held by the
	//    tree's nodes . . .
	~ExpressionTree()
	{
		delete root; //not correct still needs fixing 
	}

	// 6. Add an evaluate method that returns the integer value of the
	//    expression tree
	int evaluate()
	{
		return root->evaluate();
	}

	// 7. Add a friend function to permit sending the tree to
	//    std::cout with the << operator . . .
	friend std::ostream& operator<<(std::ostream& os, const ExpressionTree& t) 
	{
		t.root->print(os, 0, '-');
		return os;
	}

	

};

#endif
