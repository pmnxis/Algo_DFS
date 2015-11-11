#include <stdio.h>
#include <stdlib.h>

//   VISUAL STUDIO ÄÚµù¿ë
#if _MSC_VER >= 1600
#pragma warning(disable:4996)
#include <Windows.h>
#define STOP { printf("\n\n"); system("PAUSE");}
#else
#define STOP {}
#endif

struct node {
	node * link;
	int number;
}typedef node;

node * makeNode(int _number) {
	node * temp = (node *)malloc(sizeof(node));
	temp->link = NULL;
	temp->number = _number;
	return temp;
}

node * insertNode(node ** table, int _axis, int _number) {
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

node ** createTable(int quanity){
	int ii;
	node ** table = (node **)malloc(sizeof(node *)*(quanity+1));
	for (ii = 0; ii <= quanity; ii++) {
		table[ii] = NULL;
	}
	return table;
}

void lincleLink(node ** table, int from, int dest) {
	if (table == NULL || from == dest )goto Exception;
	insertNode(table, from, dest);
	insertNode(table, dest, from);

	return;
Exception:
	printf("lincleLink Func - error detected\n");
	return;
}

void DFS(int * sharedLog, int	nodeAmount, node ** table, node ) {


}


int main(){
	



	return 0;
}