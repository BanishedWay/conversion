#include<stdio.h>
#include<stdlib.h>

#define MAXN 100
#define TEMP 10
#define OK 1
#define Error 0

typedef int Status;
typedef char Elemtype;
typedef struct node{
	Elemtype* base;
	Elemtype* top;
	int stacksize;
}Sqstack;

Status InitStack(Sqstack& s);
Status Push(Sqstack& s, Elemtype e);
Status Pop(Sqstack& s, Elemtype& e);
Status matching(char* str);
Status Empty(Sqstack& s);
Status DestroyStack(Sqstack& s);

int main()
{
	char* str = (char*)malloc(MAXN * sizeof(char));
	scanf("%s", str);
	if (matching(str) == 1) {
		printf("The string is OK.\n");
	}
	else {
		printf("The string is wrong.\n");
	}
	free(str);
	return 0;
}

Status InitStack(Sqstack& s)
{
	s.base = (Elemtype*)malloc(MAXN * sizeof(Elemtype));
	if (!s.base) {
		exit(0);
	}
	s.top = s.base;
	s.stacksize = MAXN;
	return OK;
}

Status Push(Sqstack& s, Elemtype e)
{
	if (s.top - s.base >= s.stacksize) {
		s.base = (Elemtype*)realloc(s.base, (s.stacksize
			+ TEMP) * sizeof(Elemtype));
		if (!s.base) {
			exit(0);
		}
		s.top = s.base + s.stacksize;
		s.stacksize += TEMP;
	}
	*s.top = e;
	s.top++;
	return OK;
}

Status Pop(Sqstack& s, Elemtype& e)
{
	if (s.top == s.base) {
		return Error;
	}
	s.top--;
	e = *s.top;
	return OK;
}

Status Empty(Sqstack& s)
{
	if (s.top == s.base) {
		return OK;
	}
	else {
		return Error;
	}
}

Status DestroyStack(Sqstack& s)
{
	free(s.base);
	s.base = NULL;
	s.top = NULL;
	s.stacksize = 0;
	if (!s.base) {
		return OK;
	}
	return Error;
}

Status matching(char* str) {
	Sqstack OPND, OPTR;
	InitStack(OPND);
	InitStack(OPTR);
	char* p = NULL;
	Elemtype e, t;
	p = str;
	int flag = 1;
	while (*p != '\0')
	{
		if (*p == '(' || *p == ')' || *p == '[' || *p == ']' || *p == '{' || *p == '}')
		{
			Push(OPTR, *p);
		}
		p++;
	}
	while (OPTR.base != OPTR.top)
	{
		Pop(OPTR, t);
		switch (t)
		{
		case '(':
			if (Empty(OPND)) {
				flag = 0;
			}
			else {
				Pop(OPND, e);
				if (e != ')') {
					flag = 0;
				}
			}
			break;
		case '{':
			if (Empty(OPND)) {
				flag = 0;
			}
			else {
				Pop(OPND, e);
				if (e != '}') {
					flag = 0;
				}
			}
			break;
		case '[':
			if (Empty(OPND)) {
				flag = 0;
			}
			else {
				Pop(OPND, e);
				if (e != ']') {
					flag = 0;
				}
			}
			break;
		default:
			Push(OPND, t);
			break;
		}
	}
	if (!Empty(OPND)) {
		flag = 0;
	}
	DestroyStack(OPND);
	DestroyStack(OPTR);
	return flag;
}