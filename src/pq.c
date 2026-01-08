#include "list.h"
#include "pq.h"

#ifndef NULL
#define NULL (void *)0
#endif

void pq_init(struct pq *pq){
    for (int i = 0; i < MAXPRIO; i++){
        list_init(&pq -> bucket[i]);
    }
    pq->high_mask = 0;
    for (int j = 0; j < (MAXPRIO+31)/32; j++){
        pq -> mask[j] = 0;
    }
}

static void __set_mask(uint32_t *b, int pos)
{
    *b = *b | (1 << pos);
}
static void __clear_mask(uint32_t *b, int pos)
{
    *b = *b & ~(1 << pos);
}

static uint32_t __fls(uint32_t n)
{
    /* De Bruijn multiplication constant for LSB */
    static const uint32_t bitpos[32] = {
        0,  1,  28, 2,  29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4,  8,
        31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6,  11, 5,  10, 9};

    /* 步驟：Isolate LSB -> Multiply -> Shift -> Lookup */
    return bitpos[((n & -n) * 0x077CB531U) >> 27];
}

void pq_insert(struct pq *pq, struct list_head *entry, uint32_t prio){
    list_add(entry, &pq -> bucket[prio]);
    __set_mask(&pq -> mask[prio/32], prio%32); /* (&pq -> mask[prio >> 5], prio & 31) */
    __set_mask(&pq->high_mask, prio / 32);
}

struct list_head *pq_del(struct pq *pq){
    /* 先找到最低 prio，從最後面拿 (del) 
       如果 list 空，要把 mask 清掉 */
    if (pq->high_mask == 0)
        return NULL;

    /* FLS of level 1 mask */
    uint32_t high_idx = __fls(pq->high_mask);

    /* FLS of level 2 mask */
    uint32_t low_idx = __fls(pq->mask[high_idx]);
    
    uint32_t prio = (high_idx * 32) + low_idx;

    struct list_head *entry = pq->bucket[prio].prev;
    list_del(entry);

    if (list_empty(&pq->bucket[prio])) {
        __clear_mask(&pq->mask[high_idx], low_idx); /* Level 2 */
        
        if (pq->mask[high_idx] == 0) {
            __clear_mask(&pq->high_mask, high_idx); /* Level 1 */
        }
    }

    return entry;

}