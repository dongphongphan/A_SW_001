/* Phong - self learning data structure STACK
/  1. Implement stack by using vector
/  2. Implement stack by using link list
*/

#include <iostream>
#include <vector>

struct ListNode {
 int val;
 ListNode *next;
 ListNode() : val(0), next(nullptr) {}
 ListNode(int x) : val(x), next(nullptr) {}
 ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void display(ListNode* head)
{
	ListNode* temp = head;
	std::cout << "display List: ";
	while(temp)
	{
		std::cout << temp->val <<" ";
		temp = temp->next;
	}
	std::cout << std::endl;
	return;
}
void deleteList(ListNode* head)
{
	while(head)
	{
		ListNode* temp = head;
		head = head->next;
		std::cout<< "deleteList " << temp->val << std::endl;
		delete(temp);
	}
	return;
}

ListNode* deleteDuplicates(ListNode* head) 
{
	ListNode* cur = head;
	ListNode* prev = head;
	while(cur)
	{
		if(cur == prev)
		{
			cur = cur->next;
		}
		else
		{
			if(cur->val == prev->val)
			{
				ListNode* tem1 = cur;
				prev->next = cur->next;
				cur = cur->next;
				delete tem1;
			}
			else
			{
				prev = cur;
				cur = cur->next;
			}
		}
	}
	return head;
}
int main(int argc, char** argv) {
	
	ListNode* head = NULL;
	ListNode* tail = NULL;
	for(int i =0; i < 10; i++)
	{
		if(tail == NULL)
		{
			//std::cout<< "Tail NULL" <<std::endl;
			tail = new ListNode(i);
			head = tail;
		}
		else
		{
			tail->next = new ListNode(i/2);
			tail = tail->next;
		}
	}
	display(head);
	deleteDuplicates(head);
	display(head);
	deleteList(head);
	//display(head);
	//display(tail);
}
