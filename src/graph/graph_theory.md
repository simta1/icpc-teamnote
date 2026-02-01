### 트리의 중심
편심 e(v): 정점 v에서 트리 내의 다른 모든 정점들까지의 거리 중 최댓값   
트리의 중심: 편심이 최소인 정점   
모든 트리는 1개 or 2개의 중심을 가지며 2개라면 그 두 정점은 반드시 인접함   
트리의 지름은 트리의 중심을 지나며 모든 지름은 반드시 트리의 중심을 공유함   
트리의 지름이 짝수라면: 중심은 1개, 지름의 정확히 중간지점이 중심   
홀수라면: 중심은 2개, 지름의 가운데 간선으로 연결된 두 정점이 중심   
즉, 중심이 1개라면 모든 지름은 그 중심을 지나고 2개라면 모든 지름은 그 두 중심을 잇는 간선을 지남   
지름들의 교집합: 트리의 모든 지름이 공유하는 정점들의 집합은 항상 하나의 연결된 경로(Path)를 이룸   
### 오일러의 정리
연결된 평면 그래프에서 $v-e+f=2$ (v:정점, e: 간선, f: 면)
$v \ge 3$인 중복 간선없는 단순 평면 그래프는 $e \le 3v-6$을 만족
2e=각 면에서 변의 개수의 합>= 3f이므로 v-e+f=2와 연립하면 $e \le 3v-6$   
이분그래프라면 사이클의 최소 길이가 4이므로  $2e \ge 4f$, $e \le 2v-4$
### 매칭
Kőnig's theorem: 이분그래프에서 최대매칭=|mvc|
Maximum Independent Set = V - mvc : 서로 간선으로 연결되지 않은 정점들의 모임 중 가장 정점수가 많은것. 일반그래프에선 NP-hard임
misL = L - mvcL, misR = R - mvcR
antichain은 v_in이 misL이고 && v_out이 misR인 v들을 모으면 됨
clique는 complement graph에서의 Independent set과 같음
Dilworth's theorem: 부분 순서 집합(partially ordered set)에서 최대 반사슬(antichain)의 크기는 사슬 분할의 최소 개수와 같음
hall's marriage theorem: 이분그래프 G=(L+R,E)에서 L의 부분집합 S에 대해 이와 연결된 R의 부분집합을 N(S)라 할 때, 이 이분그래프에 perfect matching이 존재할 필요충분조건은 모든 S에 대하여 |S|≤|N(S)|