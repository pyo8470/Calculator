#include<iostream>
#include<assert.h>
#include"Liist.h"
#include<cctype>
#include<string>
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
using namespace std;

template<class item>
class stack {
private:
	node<item>* top_ptr;//stack�� top
public:
	stack() {//�⺻������ 
		top_ptr = NULL;
	}
	stack(const stack<item>& source) {//���������
		node<item>* tail_ptr;
		list_copy(source.top_ptr, top_ptr, tail_ptr);
	}
	void push(const item& entry);
	void pop();
	bool empty() const;
	item top()const;
};
template<class item>
void stack<item>::push(const item& entry) {
	list_head_insert(top_ptr, entry);//list�� head�� stack�� top�� ��.
}
template<class item>
void stack<item>::pop() {//stack�� top�� �����Ϸ��� list�� head�� �����ϸ� �ȴ�.
	assert(!empty());
	list_head_remove(top_ptr);
}
template<class item>
bool stack<item>::empty()const {//stack�� ������� Ȯ��
	return top_ptr == NULL;
}
template<class item>
item stack<item>::top() const {//stack�� top�� ���� ��ȯ�Ѵ�.
	assert(!empty());
	return top_ptr->get_data();
}
class evaluator {
public:
	string read_expression();
	string convert_to_postfix(string s);
	double evaluate_postfix(string s);
};
int get_precedence(char a) {//�켱������ ���Ѵ�.
	switch (a) {
	case'(': case')': return 0;
	case'+': case'-': return 1;
	case'*': case'/': return 2;
	}
	return -1;
}
bool is_operand(char a) {// �ǿ��������� Ȯ��.
	if (isdigit(a) || (a >= 'a' && a <= 'z') || (a >= 'A' && a <='Z') || a == '.')
		return true;
	return false;
}
bool is_variable(char a) {
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
		return true;
	return false;
}
bool is_operator(char a) {
	if (a == '+' || a == '/' || a == '*' || a == '-')
		return true;
	return false;
}
string evaluator::read_expression() {
	string expre;
	cout << "������ �Է��Ͻÿ� : ";
	cin >> expre;
	return expre;
}
string evaluator::convert_to_postfix(string infix) {
	cout << "convert infix to postfix...." << endl;
	string postfix = "";
	const char decimal = '.';
	stack<char> stack;
	int i = 0;
	int length = infix.length();
	while(i<length){
		if (is_operand(infix[i])) {//�ǿ����ڸ� �Ҽ�,����,���ڷ� �����س��´�.
			while (is_operand(infix[i])&&(i<length)) {//�ڸ����� �������ֱ� ���� �����ڰ� ������ ������ �׳� ����Ѵ�.
				postfix.push_back(infix[i]);
				i++;
			}
			postfix.push_back(' ');//��� ����ѵ� ������ ���� �������ش�.
		}
		else if (infix[i] == '(') {//�°�ȣ�� ���� �� stack�� push
			stack.push(infix[i]);
			i++;
		}
		else if (infix[i] == ')') {//���ȣ�� ������ ���.
			while (stack.top() != '(') {// �°�ȣ�� ������������
				postfix.push_back(stack.top());//stack �� �����ִ� ��� �����ڵ��� ������ش�.
				stack.pop();//�׸��� pop
				postfix.push_back(' ');//�������� ��������.
			}
			stack.pop();//�°�ȣ�� �������ϱ⶧���� pop �ѹ� ��.
			i++;
		}
		else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/') {//�����ڰ� ������ ���
			while (!stack.empty() && (get_precedence(infix[i]) <= get_precedence(stack.top()))){// stack�� ������� �ʰ� stack�� �ִ� �����ڰ� ������ �����ں��� �켱������ �������
				postfix.push_back(stack.top());//stack�� �����ִ� �����ڸ� ����Ѵ�
				postfix.push_back(' ');//�������� ����
				stack.pop();//�����ִ� �����ڸ� ����
			}
			stack.push(infix[i]);//���� �������� �����ڸ� stack�� push
			i++;
		}
		if ((i == length) && (!stack.empty())) {//�� ������
			while (!stack.empty()) {//������ ������� ������� ������ ��� �����ڸ� pop��.
				postfix.push_back(stack.top());
				postfix.push_back(' ');
				stack.pop();
			}
		}
	}
	return postfix;
}
double evaluator::evaluate_postfix(string postfix) {
	stack<double> operand;
	stack<char> operat;
	string num="";//�и��� ���� ���� string ����.
	int i = 0;
	int length = postfix.length();
	double oper1, oper2;
	while (i < length) {
		if (is_operand(postfix[i])) {//postfix���� ���ڸ� �и��ϴ� �۾�.
			while (is_operand(postfix[i]) && postfix[i] != ' ') {
				num.push_back(postfix[i]);
				i++;
			}
			if ((num[0] >= '0' && num[0] <= '9') || num[0] == '.')//�����ΰ��
				operand.push(stod(num));
			else if (is_variable(num[0])) {//�����ΰ��, ������ ��� ������ �� ����� ���� ���� �����Ѵ�.
				cout << num[0] << "�� ���� ���Ͻÿ� :";
				cin >> num;
				operand.push(stod(num));
			}
			num.clear();
		}
		else if (is_operator(postfix[i])) {//�� �y��ٰ� �����ڰ� ��Ÿ�� ��
			oper1 = operand.top();// infix ����: ������ �����ʿ� ���� �ǿ�����.
			operand.pop();//operand stack���� ����
			oper2 = operand.top();// infix ���� : ������ ���ʿ� ���� �ǿ�����.
			operand.pop();//operand stack���� ����
			if(postfix[i]=='+')
				operand.push(oper1 + oper2);
			else if (postfix[i] == '-')
				operand.push(oper2 - oper1);
			else if (postfix[i] == '/')
				operand.push(oper2 / oper1);
			else if (postfix[i] == '*')
				operand.push(oper1 * oper2);
			i++;
		}
		else { i++; }
	}
	return operand.top();
}

int main() {
	while (1) {
		evaluator a;
		string infix = a.read_expression();
		string postfix = a.convert_to_postfix(infix);
		cout << "infix -> " << infix << endl;
		cout << "postfix-> " << postfix << endl;
		cout<<"evaluate postfix"<<a.evaluate_postfix(postfix)<<endl;
		cout << "�����ϰ� ������ q �Է� ��� �� �Ÿ� �ƹ��ų� �Է�";
		char b;
		cin >> b;
		if (b == 'q') { break; }
		cout << endl;
	}
	system("pause");
 }