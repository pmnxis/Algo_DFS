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



int main(){
	



	return 0;
}