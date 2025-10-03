#include "linked-list.h"

void LinkedList::reverse()
{
  // TODO: Implement the linked list reversal function
  // Don't forget to set tail ptr correctly as well !

  // DO NOT ALLOCATE ANY MEMORY
  if(head == nullptr || head->next==nullptr) return;
  ListNode* p=head->next;
  ListNode* q=head->next->next;
  if(q==nullptr) {
    p->next=head;
    head->next=nullptr;
    head = p;
    return;
  }
  head->next=nullptr;
  while(q!=tail){
    p->next=head;
    head=p;
    p=q;
    q=q->next;
  }  
  p->next = head;
  q->next = p;
  head = q;
  p=head;
  while(p->next!=nullptr){
    p=p->next;
  }
  tail = p;
}