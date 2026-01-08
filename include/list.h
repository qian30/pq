#if !defined(__LIST_H__)

#define __LIST_H__

#include <stddef.h>

#define CONTAINER_OF(ptr, type, member) \
    (type *) ((char *) ptr - offsetof(type, member))

#define list_entry(ptr, type, member) \
    CONTAINER_OF(ptr, type, member)

struct list_head
{
    struct list_head *prev;
    struct list_head *next;
};

static inline void list_init(struct list_head *entry)
{
    entry -> prev = entry;
    entry -> next = entry;
}

static inline void list_add(struct list_head *new, struct list_head *head)
{
    head -> next -> prev = new;
    new -> next = head -> next;
    head -> next = new;
    new -> prev = head;
}
static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
    head -> prev -> next = new;
    new -> prev = head -> prev;
    new -> next = head;
    head -> prev = new;
}
static inline void list_del(struct list_head *entry) //delete 前後都可，給的指標對就好
{
    entry -> prev -> next = entry -> next;
    entry -> next -> prev = entry -> prev;
    list_init(entry);
}
static inline int list_empty(const struct list_head *head)
{
    return head -> next == head;
}

#endif //__LIST_H__