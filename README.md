# Algo_DFS
INIT

Algo-DFS
2015년도 세종대학교 나중채 알고리즘 3번째 실습 과제

과제관련 문서 : http://bin.jvnv.net/f/zuZJm/%EA%B3%BC%EC%A0%9CP3-DFS.pdf

DFS알고리즘을 구현하되 현재시점에서 다른 간선으로 갈때 우선순위를 

1. 시작지점과의 최단 거리가 가장 짧은 정점을 우선
2. 정점이 가지고있는 숫자가 가장 작은것을 우선

위와 같은 조건으로 시행.

대략적 프로그래밍 고비 
1. 인접리스트를 위한 ADT 작성,
2. 교수님이 제시한 우선순위를 
Func DFS( some parm . . .  ){
  setNearEdgeDist//  in this Edge, set neighborhood's DIST
  while( unchecked edge exist ){
    DFS( getBestEdge );
  }
  exit
}

이런식으로 그냥 해결하면 될줄알았는데 교수님이 원하는것은 DFS한 재귀만으로 구할수있는(예측가능한) 

최소 간선이 아니라 실제의 최종적 최소 간선이라는걸 깨닫고 

DFS이전에 BFS로 실제적 최종적 최소 간선 리스트를 만들어서 처리.

-> 이러니 됨 ㄱ-
