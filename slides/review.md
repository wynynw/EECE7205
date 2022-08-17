## Binary Tree
左小右大  
搜索：小于搜左边，大于搜右边  
<br>
min degree t>=2
- 每个node至少t-1keys(不含root),至多2t-1
- 有最少key的内部node有t个children
- 非空树的根节点至少有一个key
- non-leaf node最多有2t个children
<br>
Height:h<= logt(n+1/2)

## Graph
(V,E)  
BFS,DFS
<br>
检测cycles
- n个顶点，n-1条边的无向图没有cycles
- 如果堆栈顶部的v有一个仍在堆栈中的邻居并且它不是它的predecessor，则存在cycle

## Spanning Tree
有权重的无向图，找到连接所有顶点且权重和最小的树  
Kruskal mlogm: 所有边按权重排序，枚举每条边a-b,如果ab不连通，就把边加入集合  
Prims ElogV: 每步添加最小边  
single-source shortest paths:从指定顶点出发到所有顶点的最短路径  
Dijkstra：每次找到未访问节点中距离最小的，用该节点更新其他节点的weight  
负权重：s到v之间有负权重cycle，s到v为-无穷  
Bellman-Ford: 返回是否存在负循环的bool