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

//  노드와 큐시스템의 최소 골격
struct node {
	struct node * link;
	int number;
}typedef node;

//  최소단위 노드 생성
node * makeNode(int _number);

// table[_axis] ,_axis의 인접리스트에 노드 삽입
void  insertNode(node ** table, int _axis, int _number);

//  방문 동적리스트 생산
bool * createSharedLog(int quanity);

//   인접리스트를 qunity행만큼 만듭니다.
node ** createTable(int quanity);

//  삽입을 하기전 양방향에 명령을 하도록 변환
void lincleLink(node ** table, int from, int dest);

//  scanf를 탑재하여 자동으로 데이터베이스를 받습니다.
void inputRule(node ** table);

//  로깅 , 한칸(blank)를 만들수도있고 아니면 그냥 input을 뿌려줄수도잇고.
void log(int input);

//  인접리스트를 탐색할때 인접리스트와 최소거리 테이블의 값을 고려하여 가장 조건에 부합하는 인접리스트의 노드를 리턴함
node * getDFSpriority(bool * sharedLog, int * DepthTrack, node ** table, int row);

//  DFS알고리즘을 수행하기 직전 초기 설정을 미리한후 DFS알고리즘을 재귀로 돌립니다. 
void startDFScustom(bool * sharedLog, node ** table, int nodeAmount, int StartPoint);

//  재귀형태의 DFS알고리즘 
void DFScustom(bool * sharedLog, int * DepthTrack, node ** table, int row);

//  디버그용함수
void logTable(node ** table, int nodeAmount);

//  노드테이블 소멸자
void nodeTableDestructor(node ** table, int nodeAmount);

// 노드관계 소멸자
void nodeChainDestructor(node * target);

//  큐의 기본 골격 생성
node ** createQue(int row);

//  새로운 큐를 넣습니다. other ADT name (push)
void enqueue(node ** table, int row, int val);

//  큐를 꺼냅니다. other ADT name (pop)
int dequeue(node ** table, int row);

//  custom DFS 를 하기직전 BFS알고리즘을 활용한 최소 거리 테이블을 만듭니다.
int * CreateDistTable_BFS(node ** table, int nodeAmount, int StartPoint);

//  BFS재귀 알고리즘
void routineBFS(node ** table, int * DepthTrack, bool * sharedLog, int row);

//  프로그램 시작지점
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

	startDFScustom(sharedLog, table, TableWidth, EnterNodeNumber);

	nodeTableDestructor(table, TableWidth);
	free(sharedLog);

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

		if (seek->number == _number) { 
			free(newElement);
			return;
		}

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

node * getDFSpriority(bool * sharedLog, int * DepthTrack, node ** table, int row) {
	node * seek, *currentMin;
	int currentMinDist, currentMinNum;
	int seekDist, seekNum;

	seek = table[row];
	currentMinDist = -1;
	currentMinNum = -1;
	currentMin = NULL;
	
	while (seek != NULL) {
		//  탐색포인터가 NULL이 아닌경우에만 WHILE이 동작합니다.
		if (sharedLog[seek->number] != 0) { seek = seek->link; continue; }
		//  사용할수 없는 노드는 그냥 패스해버립니다.
		//  해당 조건 : 이미 탐색한 노드

		//  deferredFunc분기 : 최적의 조건에 합당하는 노드를 현재 탐색중인 노드로 교체한다.

		if (currentMinDist == -1) goto deferredFunc;
		//  현재최적보다 최소거리거나 같거나 정점숫자가 작으면 교체
		if (currentMinDist >= DepthTrack[seek->number] && currentMinNum > seek->number) goto deferredFunc;
		//  현재최적보다 최소거리면  교체 
		if (currentMinDist > DepthTrack[seek->number]) goto deferredFunc;

		//  인접행렬에서 다음 노드를 탐색한다.
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

	//  만약 최적의 정점을 못찾으면 그냥 NULL을 리턴하고 아니면 현재최적의 노드주소값을 리턴
	if (currentMinDist == -1 || currentMinNum == -1)return NULL;
	else return currentMin;
}

void startDFScustom(bool * sharedLog, node ** table, int nodeAmount, int StartPoint) {
	int ii;
	//  BFS알고리즘을 사용하여 DepthTrack , 최소거리 테이블을 만듭니다.
	int * DepthTrack = CreateDistTable_BFS(table, nodeAmount, StartPoint);
	//  DFS 재귀를 시작합니다.
	DFScustom(sharedLog, DepthTrack, table, StartPoint);
	//  최소 거리 테이블을 소멸시킵니다.
	free(DepthTrack);
	return;
}

void DFScustom(bool * sharedLog, int * DepthTrack, node ** table, int row) {
	node * seek, *newPortal;
	int currentDist;

	//  방문한거 아니면 출력함
	if (sharedLog[row] == 0) { 
		log(row);
		sharedLog[row] = 1;
	}
	else return;

	seek = table[row];
	currentDist = sharedLog[row];

	seek = table[row];
	while (1) {
		if (seek == NULL)return;

		//  인접행렬에서 재귀할 정점찾고 없으면 그냥 끝냄, 없어질때까지 계속 반복
		newPortal = getDFSpriority(sharedLog, DepthTrack, table, row);
		if (newPortal == NULL)return;
		else{
			log(-1);
			DFScustom(sharedLog, DepthTrack, table, newPortal->number);
			continue;
		}
	}
	return;
}

//  디버그용 함수
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

void nodeTableDestructor(node ** table, int nodeAmount) {
	int ii;
	for (ii = 0; ii <= nodeAmount; ii++) nodeChainDestructor(table[ii]);
}

void nodeChainDestructor(node * target) {
	if (target == NULL)return;
	else{
		nodeChainDestructor(target->link);
		free(target);
	}
}

node ** createQue(int row) {
	int ii;
	node ** temp = (node **)malloc(sizeof(node *)*(row + 1));
	for (ii = 0; ii <= row; ii++) {
		temp[ii] = NULL;
	}
	return temp;
}

void enqueue(node ** table, int row, int val) {
	node * seek;
	node * newElement = makeNode(val);
	
	if (table[row] == NULL) {
		table[row] = newElement;
		return;
	}
	else {
		seek = table[row];
		while (seek != NULL) {
			if (seek->link == NULL) {
				seek->link = newElement;
				break;
			}
			else {
				seek = seek->link;
			}
		}
	}
}

int dequeue(node ** table, int row) {
	node * newFront;
	node * temp;
	int bye = 0;
	temp = table[row];

	if (temp == NULL)return 0;
	temp = table[row];
	bye = temp->number;
	table[row] = table[row]->link;
	free(temp);
	return bye;
}

//  최소거리 테이블 생성시작하는 함수
int * CreateDistTable_BFS(node ** table, int nodeAmount, int StartPoint) {
	int ii;
	int * DepthTrack = (int *)calloc(1,sizeof(int)*(nodeAmount + 1));
	bool * sharedLog = (bool * )calloc(1,sizeof(int)*(nodeAmount + 1));
	for (ii = 0; ii <= nodeAmount; ii++) {
		DepthTrack[ii] = -1;
		sharedLog[ii] = 0;
	}
	//  지정해둔 초기값으로 둘다 초기화
	//  pdf에 시작노드의 거리와 시작노드의 거리, 즉 자기자신의 거리를 0으로 간주했기에.
	//  스타트포인트를 0으로 지정하고 그다음부터 1,2,3,4,5, 이렇게 늘어남, 방문하지않은노드는 -1로 표기
	DepthTrack[StartPoint] = 0;
	
	//재귀시작
	routineBFS(table, DepthTrack, sharedLog, StartPoint);
	// 소멸및 테이블주소 줌
	free(sharedLog);
	return DepthTrack;
}

//  재귀 알고리즘
void routineBFS(node ** table, int * DepthTrack, bool * sharedLog,  int row) {
	node ** currentQue = createQue(0);
	node * seek;  /*  자기주변 간선을 탐색할때 쓰는 임시 노드포인터  */
	int currentDist;
	int gear = 0;  /*  BFS 를 위해 넣엇던 큐를 차례대로 꺼낼때 간선에 이어지는정점의 숫자를 임시로 쓰기위해 사용  */
	
	sharedLog[row] = 1;
	seek = table[row];
	currentDist = DepthTrack[row];
	//  자기주변의 모든 간선을 탐색하되, 탐색하지않앗거나 새 최소거리가 더 작으면 값을대체하거나 추가함.
	while (seek != NULL) {
		if (DepthTrack[seek->number] == -1 || DepthTrack[seek->number] > currentDist + 1) {
			DepthTrack[seek->number] = currentDist + 1;
			enqueue(currentQue, 0, seek->number);
		}
		seek = seek->link;
	}

	//  디큐를 계속 하여 0이 나올때까지(비엇다 신호), 재귀를 다시실행함
	while (gear = dequeue(currentQue, 0)) routineBFS(table, DepthTrack, sharedLog, gear);
	return;
}