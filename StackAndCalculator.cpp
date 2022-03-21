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
	node<item>* top_ptr;//stack의 top
public:
	stack() {//기본생성자 
		top_ptr = NULL;
	}
	stack(const stack<item>& source) {//복사생성자
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
	list_head_insert(top_ptr, entry);//list의 head가 stack의 top이 됨.
}
template<class item>
void stack<item>::pop() {//stack의 top을 제거하려면 list의 head를 제거하면 된다.
	assert(!empty());
	list_head_remove(top_ptr);
}
template<class item>
bool stack<item>::empty()const {//stack이 비었는지 확인
	return top_ptr == NULL;
}
template<class item>
item stack<item>::top() const {//stack의 top의 값을 반환한다.
	assert(!empty());
	return top_ptr->get_data();
}
class evaluator {
public:
	string read_expression();
	string convert_to_postfix(string s);
	double evaluate_postfix(string s);
};
int get_precedence(char a) {//우선순위를 정한다.
	switch (a) {
	case'(': case')': return 0;
	case'+': case'-': return 1;
	case'*': case'/': return 2;
	}
	return -1;
}
bool is_operand(char a) {// 피연산자인지 확인.
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
	cout << "수식을 입력하시오 : ";
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
		if (is_operand(infix[i])) {//피연산자를 소수,변수,숫자로 지정해놓는다.
			while (is_operand(infix[i])&&(i<length)) {//자릿수를 구별해주기 위해 연산자가 나오기 전까지 그냥 출력한다.
				postfix.push_back(infix[i]);
				i++;
			}
			postfix.push_back(' ');//모두 출력한뒤 공백을 통해 구분해준다.
		}
		else if (infix[i] == '(') {//좌괄호가 나올 시 stack에 push
			stack.push(infix[i]);
			i++;
		}
		else if (infix[i] == ')') {//우괄호가 나오는 경우.
			while (stack.top() != '(') {// 좌괄호가 나오기전까지
				postfix.push_back(stack.top());//stack 에 남아있는 모든 연산자들을 출력해준다.
				stack.pop();//그리고 pop
				postfix.push_back(' ');//공백으로 구분해줌.
			}
			stack.pop();//좌괄호도 지워야하기때문에 pop 한번 더.
			i++;
		}
		else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/') {//연산자가 나오는 경우
			while (!stack.empty() && (get_precedence(infix[i]) <= get_precedence(stack.top()))){// stack이 비어있지 않고 stack에 있는 연산자가 들어오는 연산자보다 우선순위가 높은경우
				postfix.push_back(stack.top());//stack에 남아있던 연산자를 출력한다
				postfix.push_back(' ');//공백으로 구분
				stack.pop();//남아있던 연산자를 제거
			}
			stack.push(infix[i]);//이후 들어오려는 연산자를 stack에 push
			i++;
		}
		if ((i == length) && (!stack.empty())) {//맨 마지막
			while (!stack.empty()) {//스택이 비어있지 않은경우 스택의 모든 연산자를 pop함.
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
	string num="";//분리한 수를 넣을 string 변수.
	int i = 0;
	int length = postfix.length();
	double oper1, oper2;
	while (i < length) {
		if (is_operand(postfix[i])) {//postfix에서 숫자를 분리하는 작업.
			while (is_operand(postfix[i]) && postfix[i] != ' ') {
				num.push_back(postfix[i]);
				i++;
			}
			if ((num[0] >= '0' && num[0] <= '9') || num[0] == '.')//숫자인경우
				operand.push(stod(num));
			else if (is_variable(num[0])) {//변수인경우, 변수를 어떻게 설정할 지 물어보고 변수 값을 설정한다.
				cout << num[0] << "의 값을 정하시오 :";
				cin >> num;
				operand.push(stod(num));
			}
			num.clear();
		}
		else if (is_operator(postfix[i])) {//쭉 y어보다가 연산자가 나타날 때
			oper1 = operand.top();// infix 기준: 연산자 오른쪽에 오는 피연산자.
			operand.pop();//operand stack에서 제거
			oper2 = operand.top();// infix 기준 : 연산자 왼쪽에 오는 피연산자.
			operand.pop();//operand stack에서 제거
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
		cout << "종료하고 싶으면 q 입력 계속 할 거면 아무거나 입력";
		char b;
		cin >> b;
		if (b == 'q') { break; }
		cout << endl;
	}
	system("pause");
 }
