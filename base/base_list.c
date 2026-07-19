static inline U0
list_init(ListNode *head)
{
        HintAssert(head != NIL);

        head->next = head;
        head->prev = head;
}

static inline U0
list_add(ListNode *head, ListNode *new) {

        HintAssert(head != NIL &&
                   new  != NIL &&
                   head->next->prev == head);
        
        new->next = head->next;
        new->prev = head;
        head->next->prev = new;
        head->next = new;
}

static inline U0
list_del(ListNode *prev, ListNode *next)
{
        HintAssert(prev != NIL && next != NIL);

        next->prev = prev;
        prev->next = next;

        DBG_Invalidate(next->prev);
        DBG_Invalidate(prev->next);
}

static inline U0
list_replace(ListNode *old, ListNode *new)
{
        
}
