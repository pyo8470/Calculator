#include<iostream>
using namespace std;
template<typename type>
class node{
public:
	node<type>() { this->prev = NULL; this->next = NULL; this->data = NULL; }
	node<type>(type data){ this->prev = NULL; this->next = NULL; this->data = data; }
	node<type>(type data, node* prev, node* next) { this->prev = prev; this->next = next; this->data = data; }
	~node(){}
	void set_data(const type& new_data) { this->data = new_data; }
	void set_next(node* new_next) { this->next = new_next; }
	void set_prev(node* new_prev) { this->prev = new_prev; }
	type get_data()const { return data;}
	const node* get_next()const { return next; }
	node* get_next() { return next; }
	const node* get_prev()const { return prev; }
	node* get_prev() { return prev; }
private:
	type data;
	node<type>* next;
	node<type>* prev;
};
template<typename type>
node<type>* head_ptr;
template<typename type>
node<type>* tail_ptr;
template<typename type>
void list_head_insert(node<type>*& head_ptr, const type entry) {
	node<type>* newnode = new node<type>(entry);
	if (head_ptr == NULL)// 아무 노드도 없을때
		tail_ptr<type> = NULL;
	else {
		newnode->set_next(head_ptr);//새로운 노드가 가리키는 next-> 원래 head_ptr가 가리키던 노드.
		head_ptr->set_prev(newnode);// 원래 앞에있던 node의 prev==null에서 newnode를 가리키도록.
	}
	head_ptr = newnode;
}
template<typename type>
void list_copy(const node<type>* source_ptr, node<type>*& head_ptr, node<type>*& tail_ptr) {
	head_ptr = NULL;
	tail_ptr = NULL;
	if (source_ptr == NULL)   return;
	list_head_insert(head_ptr, source_ptr->data()); 
	tail_ptr = head_ptr;
	source_ptr = source_ptr->link();
	while (source_ptr != NULL) {
		list_insert(tail_ptr, source_ptr->data()); tail_ptr = tail_ptr->link();
		source_ptr = source_ptr->link();
	}
}
template<typename type>
void list_head_remove(node<type>*& head_ptr) {
	if (head_ptr == NULL) {
		cout << "list is empty";
		return;
	}
	node<type>* remove;
	remove = head_ptr;
	head_ptr = head_ptr->get_next();
	delete remove;
}
