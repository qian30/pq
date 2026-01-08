#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "list.h"
#include "pq.h"

struct task
{
    int n;
    uint32_t prio;
    struct list_head list;
};

struct task *create_task(int n, uint32_t prio)
{
    struct task *node = (struct task *)malloc(sizeof(struct task));
    node -> n = n;
    node -> prio = prio;
    list_init (&node -> list);
    return node;
}

int main(){
    struct pq pq;
    pq_init(&pq);
    struct task *node_0 = create_task(0, 35);
    struct task *node_1 = create_task(1, 100);
    struct task *node_2 = create_task(2, 100);
    struct task *node_3 = create_task(3, 26);
    struct task *node_4 = create_task(4, 35);
    struct task *node_5 = create_task(5, 35);
    pq_insert(&pq, &node_0 -> list, node_0 -> prio);
    pq_insert(&pq, &node_1 -> list, node_1 -> prio);
    pq_insert(&pq, &node_2 -> list, node_2 -> prio);
    pq_insert(&pq, &node_3 -> list, node_3 -> prio);
    pq_insert(&pq, &node_4 -> list, node_4 -> prio);
    pq_insert(&pq, &node_5 -> list, node_5 -> prio);
    for(int i = 0; i < 6; i++){
        struct list_head *entry = pq_del(&pq);
        struct task *ptr = list_entry(entry, struct task, list);
        printf("data : %d, prio : %d\n", ptr -> n, ptr -> prio);
    }
}