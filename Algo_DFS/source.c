#include <stdio.h>
#include <stdlib.h>

//   VISUAL STUDIO 코딩용
#if _MSC_VER >= 1600
#pragma warning(disable:4996)
#include <Windows.h>
#define STOP { printf("\n\n"); system("PAUSE");}
#else
#define STOP {}
#endif

//  C++에는 bool이 있고 C에는 bool이없는것을 고려.
#ifndef __cplusplus
typedef int bool;
#define true   1
#define false 0
#endif


struct node {
	struct node * link;
	int number;
}typedef node;

node * makeNode(int _number) {
	node * temp = (node *)malloc(sizeof(node));
	temp->link = NULL;
	temp->number = _number;
	return temp;
}

void * insertNode(node ** table, int _axis, int _number) {
	int ii;
	node * seek,  * preseek;
	node * newElement = makeNode(_number);
	if (table[_axis] == NULL) {
		table[_axis] = newElement;
	}
	else {
		preseek = NULL;
		seek = table[_axis];
		while (1) {
			// error at under
			if (seek->number == _number)return;
			else if ((seek->number) < _number){
				preseek = seek;
				seek = seek->link;
			}
			else if(seek->number > _number){
				if (preseek == NULL) {
					preseek = newElement;
					newElement->link = seek;
					table[_axis] = preseek;
				}
				else {
					preseek->link = newElement;
					preseek->link->link = seek;
				}
				return;
			}
		}
	}
}

int * createSharedLog(int quanity) {
	int ii;
	int * sharedLog = (int *)malloc(sizeof(int)*(quanity + 1));
	for (ii = 0; ii <= quanity; ii++) {
		sharedLog[ii] = 0;
	}
	return sharedLog;
}

node ** createTable(int quanity){
	int ii;
	node ** table = (node **)malloc(sizeof(node *)*(quanity+1));
	for (ii = 0; ii <= quanity; ii++) {
		table[ii] = NULL;
	}
	return table;
}

void lincleLink(node ** table, int from, int dest) {
	if (table == NULL )goto Exception;
	
	//  자기자신이 from, dest인 입력은 한번만 수행
	insertNode(table, from, dest);
	if (from != dest) insertNode(table, dest, from);

	return;
Exception:
	printf("lincleLink Func - error detected\n");
	return;
}

void checkLogSlot(bool * sharedLog, int nodeAmount, int target) {
	int ii;
	ii = 0;
	if (sharedLog[ii] != 0) {
		return 0;
	}

}

void inputRule(node ** table) {
	int left, right;
	scanf("%d %d", &left, &right);
	lincleLink(table, left, right);
}

void DFS(bool * sharedLog, int	nodeAmount, node ** table, node * seek) {
	node * temp = seek;
	int ii = 0;
	while (temp != NULL) {
		if (sharedLog[temp->number] == 0) {
			//  로깅1회함
			sharedLog[temp->number] = 1;
			printf("%d", seek->number);
			DFS(sharedLog, nodeAmount, table, seek);

		}
		else if (sharedLog[temp->number != 0]) {
			// nothing to do.
		}

		//  다음으로
		temp = temp->link;
	}
}


int main(){
	int i = 0, inputAmount = 0 ,TableWidth = 0, EnterNodeNumber = 0;
	node ** table;
	int * sharedLog;
	scanf("%d", &TableWidth);
	scanf("%d", &inputAmount);
	scanf("%d", &EnterNodeNumber);

	sharedLog = createSharedLog(TableWidth);
	table = createTable(TableWidth);
	for (i = 0; i < inputAmount; EnterNodeNumber) inputRule(table);
	DFS(sharedLog, inputAmount, table, table[EnterNodeNumber]);
	
	return 0;
}