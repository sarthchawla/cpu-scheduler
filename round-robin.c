#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct node//structure of doubly circular linked list 
{
    int burst_time, pid, s;
    struct node *next;
    struct node *pre;
};
struct node *insert(struct node *start, int burst_time, int pid, int sp)
//to insert specific field values in linked list
{
    struct node *n = (struct node *)malloc(sizeof(struct node)), *ptr;
    n->burst_time = burst_time;
    n->pid = pid;
    n->s = sp;
    if (start == NULL)
    {
        start = n;
        n->pre = start;
    }
    else
    {
        ptr = start;
        while (ptr->next != start)
        {
            ptr = ptr->next;
        }
        ptr->next = n;
        n->pre = ptr;
    }
    n->next = start;
    start->pre = n;
    return start;
}
void print(struct node *start)//to print the linked list in desired format 
{
    struct node *ptr = start;
    int j = 1;
    printf("%d\t%d\t%d\t%d\n", j, ptr->pid, ptr->burst_time, ptr->s);
    ptr = ptr->next;
    j++;
    while (ptr != start)
    {
        printf("%d\t%d\t%d\t%d\n", j, ptr->pid, ptr->burst_time, ptr->s);
        ptr = ptr->next;
        j++;
    }
    printf("\n");
}
struct node *delete (struct node *start, struct node *ptr)
//to delete a process after it has been completed...deleting its node
{
    struct node *p1 = ptr->pre, *p2 = ptr->next;
    //printf("here c %d n %d p %d\n",ptr->pid,p1->pid,p2->pid);
    if (p1->pid == p2->pid)
    {

        //ptr=p2;
        return start;
    }
    p1->next = p2;
    p2->pre = p1;
    free(ptr);
    return start;
}
struct node *schedule(struct node *start, int q, int cpu_life)
//to perform the round robin scheduling algorithm with provided quantum and cpu life
{
    struct node *ptr = start, *chart = NULL;
    int p, c = 0, i, b, j = 1, id = 4, pt = 2;
    while (ptr->next != ptr->pre || ptr->burst_time != 0 && c <= cpu_life)
    {
        p = 0;
        if (ptr->burst_time != 0)
        {
            while (p++ != q && ptr->burst_time != 0)
            {
                ptr->burst_time = (ptr->burst_time) - 1;
            }
        }
        i = ptr->pid;
        b = ptr->burst_time;
        //ptr = ptr->next;
        //printf("exe=id=%d p=%d b.left=%d\n", i, p - 1, b);
        if (b == 0)
        {
            ptr = ptr->next;
            //printf("dlt-> id=%d p=%d current=%d next=%d pre=%d\n", i, p - 1, ptr->pre->pid, ptr->pre->next->pid, ptr->pre->pre->pid);
            //if(ptr->pre!=start)
            start = delete (start, ptr->pre);
            //printf("dlt 1-> id=%d p=%d current=%d next=%d pre=%d\n\n", i, p - 1, ptr->pid, ptr->next->pid, ptr->pre->pid);
        }
        else
        {
            ptr = ptr->next;
        }
        c = c + p - 1;
        if (c > cpu_life)
        {
            break;
        }
        chart = insert((chart), p - 1, i, c);
        if (j % pt == 0)
        {
            int y = ((rand() % 100) + 1);
            start = insert(start, y, id++, 0);
            printf("\nnew insertions of process with id %d and burst time %d at S.no %d\n", id - 1, y, j);
            pt = pt * 2;
        }
        j++;
        //print(start);
    }
    //print(chart);
    return chart;
}
int main()
{
    struct node *start = NULL;
    int c = 0;
    int i = 1, q, life;
    srand(time(0));
    life = (rand() % (200 - 50 + 1)) + 50;
    printf("\nrandomly assigned cpu's life is %d\n\nfirst 3 random input in round robin algo are\n", life);
    srand(1);
    while (c < 3)
    {
        start = insert(start, ((rand() % 100) + 1), i++, 0);
        c++;
    }
    printf("\nS.no\tid  burst time\tserving time\n");
    print(start);
    printf("enter qunatum\n");
    scanf("%d", &q);
    if (q > life)
    {
        printf("error: time quantum is more than cpu life\n");
    }
    else
    {
        start = schedule(start, q, life);
        printf("\ngantt chart->\nS.no\tid  burst time\tserving time\n");
        print(start);
    }
    return 0;
}