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

//  for using uint8_t
#ifndef uint8_t
typedef unsigned char 	uint8_t;
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

node * makeNode(int _number);
void  insertNode(node ** table, int _axis, int _number);
bool * createSharedLog(int quanity);
node ** createTable(int quanity);
void lincleLink(node ** table, int from, int dest);
void inputRule(node ** table);
void log(int input);
void setDFSpriority(bool * sharedLog, int * DepthTrack, node ** table, int row);
node * getDFSpriority(bool * sharedLog, int * DepthTrack, node ** table, int row);
void startDFScustom(bool * sharedLog, node ** table, int nodeAmount, int StartPoint);
void DFScustom(bool * sharedLog, int * DepthTrack, node ** table, int row);
void DFS_origin(bool * sharedLog, node ** table, int row);
void logTable(node ** table, int nodeAmount);


int main(){
	int i = 0, inputAmount = 0 ,TableWidth = 0, EnterNodeNumber = 0;
	node ** table;
	bool * sharedLog;
	scanf("%d", &TableWidth);
	scanf("%d", &inputAmount);
	scanf("%d", &EnterNodeNumber);

	sharedLog = createSharedLog(TableWidth);
	table = createTable(TableWidth);
	for (i = 0; i < inputAmount; i++) {
		inputRule(table);
	}
	//  (bool * sharedLog, node ** table, int nodeAmount, int StartPoint) 
	//logTable(table, TableWidth);
	startDFScustom(sharedLog, table, TableWidth, EnterNodeNumber);
//	BFS(sharedLog, table, EnterNodeNumber);
//	DFS(sharedLog, table, EnterNodeNumber);
		STOP
	return 0;
}

node * makeNode(int _number) {
	node * temp = (node *)malloc(sizeof(node));
	temp->link = NULL;
	temp->number = _number;
	return temp;
}

void  insertNode(node ** table, int _axis, int _number) {
	int ii;
	node * seek, *preseek;
	node * newElement = makeNode(_number);

	preseek = NULL;
	seek = table[_axis];


	while (1) {
		if (seek == NULL && preseek == NULL) {
			//table[_axis] = newElement;
			table[_axis] = newElement;
			return;
		}

		if (seek == NULL && preseek != NULL) {
			preseek->link = newElement;
			return;
		}

		if (seek->number == _number)return;

		if (seek->number < _number) {
			preseek = seek;
			seek = seek->link;
			continue;
		}

		if (seek->number > _number && preseek == NULL) {
			newElement->link = seek;
			table[_axis] = newElement;
			return;
		}

		if (seek->number > _number) {
			newElement->link = seek;
			preseek->link = newElement;
			return;
		}
	}

}

bool * createSharedLog(int quanity) {
	int ii;
	bool * sharedLog = (bool *)malloc(sizeof(int)*(quanity + 1));
	for (ii = 0; ii <= quanity; ii++) {
		sharedLog[ii] = 0;
	}
	return sharedLog;
}

node ** createTable(int quanity) {
	int ii;
	node ** table = (node **)malloc(sizeof(node *)*(quanity + 1));
	for (ii = 0; ii <= quanity; ii++) {
		table[ii] = NULL;
	}
	return table;
}

void lincleLink(node ** table, int from, int dest) {
	if (table == NULL)goto Exception;

	//  자기자신이 from, dest인 입력은 한번만 수행
	insertNode(table, from, dest);
	if (from != dest) insertNode(table, dest, from);

	return;
Exception:
	printf("lincleLink Func - error detected\n");
	return;
}

void inputRule(node ** table) {
	int left, right;
	scanf("%d %d", &left, &right);
	lincleLink(table, left, right);
}

void log(int input) {
	if (input > 0)printf("%d", input);
	else printf(" ");
}

void setDFSpriority(bool * sharedLog, int * DepthTrack, node ** table, int row) {
	node * seek;
	int currentDist;

	seek = table[row];
	currentDist = DepthTrack[row];
	while (1) {
		if (seek == NULL)break;
		if (sharedLog[seek->number] == 0 && DepthTrack[seek->number] == -1)	DepthTrack[seek->number] = currentDist + 1;
		seek = seek->link;
	}
}

node * getDFSpriority(bool * sharedLog, int * DepthTrack, node ** table, int row) {
	node * seek, *currentMin;
	int currentMinDist, currentMinNum;
	int seekDist, seekNum;

	seek = table[row];
	currentMinDist = -1;
	currentMinNum = -1;
	currentMin = NULL;

	while (1) {
		if (seek == NULL)break;
		//  이미 탐색한 항목으로 선정대상에서 제외.
		if (sharedLog[seek->number] != 0) { seek = seek->link; continue; }

		if (currentMinDist == -1) goto deferredFunc;

		if (currentMinDist >= DepthTrack[seek->number] && currentMinNum > seek->number) goto deferredFunc;

		if (currentMinDist > DepthTrack[seek->number]) goto deferredFunc;

		seek = seek->link; continue;

		//  Go Lang에서 Defer이라는게 있길래 한번 분기 이름으로 써봄
		//  DEFERRED Part
	deferredFunc:
		currentMinDist = DepthTrack[seek->number];
		currentMinNum = seek->number;
		currentMin = seek;
		seek = seek->link;
		continue;
		//  DEFERRED END
	}
	//  while end

	if (currentMinDist == -1 || currentMinNum == -1)return NULL;
	else return currentMin;
}

void startDFScustom(bool * sharedLog, node ** table, int nodeAmount, int StartPoint) {
	int ii;
	bool * DepthTrack = (int *)malloc(sizeof(int)*(nodeAmount + 1));
	for (ii = 0; ii <= nodeAmount; ii++) {
		DepthTrack[ii] = -1;
	}
	DepthTrack[StartPoint] = 0;
	DFScustom(sharedLog, DepthTrack, table, StartPoint);
	//for (ii = 0; ii <= nodeAmount; ii++)printf("\n%d  - %d", ii, DepthTrack[ii]);
	return;
}

void DFScustom(bool * sharedLog, int * DepthTrack, node ** table, int row) {
	node * seek, *newPortal;
	int currentDist;

	log(row);
	sharedLog[row] = 1;

	seek = table[row];
	currentDist = sharedLog[row];

	setDFSpriority(sharedLog, DepthTrack, table, row);

	seek = table[row];
	while (1) {
		if (seek == NULL)return;

		newPortal = getDFSpriority(sharedLog, DepthTrack, table, row);
		if (newPortal == NULL)return;

		if (sharedLog[newPortal->number] == 0){
			log(-1);
			DFScustom(sharedLog, DepthTrack, table, newPortal->number);
		}
	}
	return;
}

void DFS_origin(bool * sharedLog, node ** table, int row) {
	node * seek = table[row];
	int i = 0;

	log(row);
	sharedLog[row] = 1;

	while (1) {
		if (seek == NULL)return;

		if (sharedLog[seek->number] == 0) {
			log(-1);
			DFS_origin(sharedLog, table, seek->number);
		}
		seek = seek->link;
	}
}

void logTable(node ** table, int nodeAmount) {
	int logcount, i;
	node * temp;
	printf(" --- Adjacency List ---");
	for (i = 1; i < nodeAmount + 1; i++) {
		printf("\ntable [ %d ] -", i);
		temp = table[i];
		if (table == NULL) {
			continue;
		}
		logcount = 0;
		while (temp != NULL) {
			printf(" -> %d", temp->number);
			logcount++;
			if (logcount > nodeAmount + 2) {
				printf("loopproblem;\n");
			}
			temp = temp->link;
		}
	}
	printf("\n\n");
}
