#include <stdio.h>
#include <iostream>
#include "malloc.h"

#define MAX_N 100
#define MAX_STR_LEN 15
#define MAX_NUM_HASH 200

char *mystrcpy(char *dest, const char *src);
int mystrcmp(const char *dest, const char *src);

typedef struct plan_t_
{
	int unique;
	char name[MAX_STR_LEN];
	int val;
	struct plan_t_ *prev;
	struct plan_t_ *next;
}plan_t;

typedef struct grp_t_
{
	plan_t head[MAX_NUM_HASH];
}grp_t;

int N;
char in_name[MAX_N][MAX_STR_LEN] = {};
int in_val[MAX_N] = {};
int in_grpid[MAX_N] = {};

grp_t grp[10];

unsigned long myhash(const char *str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
	{
		hash = (((hash << 5) + hash) + c) % MAX_NUM_HASH;
	}
	return hash % MAX_NUM_HASH;
}

int find_hash(grp_t *g, const char *target)
{
	int ret = 0;
	int i;
	char *dest;

	for (i = 0; i < 200; i++)
	{
		dest = &g->head[i].name[0];
		if (mystrcmp(dest, target) == 0)
		{
			ret = i;
			goto exit;
		}
	}
exit:
	return ret;
}

int add_plan(int idx)
{
	int ret = 0;
	int grp_id;
	unsigned long hash_tmp;
	char *str_tmp;
	int i;
	plan_t *p;
	grp_t *g;
	char *g_str;
	plan_t *head;

	p = (plan_t *)malloc(sizeof(plan_t));
	grp_id = in_grpid[idx];
	g = &grp[grp_id];

	str_tmp = &p->name[0];
	p->val = in_val[0];
	mystrcpy(str_tmp, &in_name[0][0]);

	hash_tmp = myhash(str_tmp);
	g_str = &g->head[hash_tmp].name[0];

	if ((is_first_item(g_str) != 1) && (hash_verify(g_str, str_tmp) != 1))
	{
		hash_tmp = find_hash(g, str_tmp);
	}

	if (g_str[0] == NULL)
	{
		mystrcpy(g_str, str_tmp);
	}
	head = &g->head[hash_tmp];
	list_add(head, p);
	return ret;
}

int mystrcmp_one(const char *dest, const char *target)
{
	int i = 0;
	int ret = 0;

	if (dest[0] == target[0]) {
		ret = 0;
	}
	else if (dest[0] > target[0]) {
		ret = -1;
	}
	else {
		ret = 1;
	}
	return ret;
}

int hash_verify(char *dest, char *target)
{
	int ret = 0;
	if (mystrcmp_one(dest, target) == 1) {
		ret = 1;
	} else {
		ret = 0;
	}
	return ret;
}

int is_first_item(const char *str)
{
	int ret = 0;
	if (str[0] == '\0')
	{
		ret = 1;
	}
	return ret;
}

void list_add(plan_t *head, plan_t *target)
{
	target->prev = head;
	target->next = head->next;
	head->next->prev = target;
	head->next = target;
	target->unique = 1;
}

void list_del(plan_t *target)
{
	target->prev->next = target->next;
	target->next->prev = target->prev;
	target->next = target;
	target->prev = target;
	target->unique = 0;
}

int _init()
{
	int ret = 0;
	int i, j;
	grp_t *g_ptr;
	g_ptr = &grp[0];
	plan_t *head;
	for (i = 0; i < 10; i++) {
		head = (g_ptr + i)->head;
		for (j = 0; j < 200; j++) {
			(head + j)->next = NULL;
			(head + j)->prev = NULL;
			(head + j)->name[0] = '\0';
		}
	}
	return ret;
}

int main(void)
{
	int ret = 0;
	int i;
	printf("dongju start\n");
	freopen("hash_t2.txt", "r", stdin);
	scanf("%d", &N);
	printf("N(%d)\n", N);
	_init();
	for (i = 0; i < N; i++) {
		scanf("%d", &in_grpid[i]);
		scanf("%s", &in_name[i][0]);
		scanf("%d", &in_val[i]);
		printf("grpid(%d), name(%s), val(%d)\n", in_grpid[i], &in_name[i][0], in_val[i]);
		add_plan(i);
	}
	return ret;
}

char *mystrcpy(char *dest, const char *src)
{
	char *ret;
	int i = 0;
	int j = 0;
	
	while ( *(src+i) != '\0')
	{
		//printf("src[%d] = %c\n", i, src[i]);
		dest[j++] = src[i++];
	}
	dest[j] = '\0';
	ret = dest;	
	return ret;
}

int mystrcmp(const char *dest, const char *src)
{
	int ret = 0;
	int i = 0;	

	while (dest[i] != '\0' || src[i] != '\0')
	{
		if (dest[i] != src[i])
		{
			ret = dest[i] - src[i];
			break;
		}
		else if (dest[i] == src[i])
		{
			ret = 0;			
		}
		i++;
	}	
	return ret;
}