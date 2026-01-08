#include <stdint.h>
#include "list.h"

#if !defined(__PQ_H__)

#define __PQ_H__
#define MAXPRIO 1024

struct pq
{
    struct list_head bucket[MAXPRIO];
    uint32_t high_mask;               /* Level 1 */
    uint32_t mask[(MAXPRIO+31)/32];   /* Level 2 */
};

void pq_init(struct pq *pq);
void pq_insert(struct pq *pq, struct list_head *entry, uint32_t prio);
struct list_head *pq_del(struct pq *pq);

#endif //__PQ_H__