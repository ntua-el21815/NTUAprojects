
def DAGShortestPath(graph : list[list[tuple[int,int]]] ,start : int = 0 ,end : int = None) -> list[int]:
    if end is None:
        end = len(graph) - 1
    current_best = [float("inf") for _ in range(len(graph))]
    path = [None for _ in range(len(graph))]
    current_best[end] = 0
    for i in range(end-1,start-1,-1):
        for neighbor,weight in graph[i]:
            if current_best[i] > current_best[neighbor] + weight:
                current_best[i] = current_best[neighbor] + weight
                path[i] = neighbor
    path_from_start_to_end = [start]
    current_node = start
    while current_node != end:
        current_node = path[current_node]
        path_from_start_to_end.append(current_node)
    return path_from_start_to_end
    

if __name__ == "__main__":
    # type args struct {
	# 	graph [][]int
	# }

	# var graph [][]int = make([][]int, 10)
	# for i := range graph {
	# 	graph[i] = make([]int, 10)
	# }

	# graph[0][1] = 1
	# graph[0][2] = 2
	# graph[0][3] = 3

	# graph[1][4] = 2
	# graph[1][5] = 1
	# graph[1][6] = 1

	# graph[2][4] = 1
	# graph[2][5] = 2
	# graph[2][6] = 1

	# graph[3][4] = 2
	# graph[3][5] = 3
	# graph[3][6] = 2

	# graph[4][7] = 3
	# graph[4][8] = 2

	# graph[5][7] = 3
	# graph[5][8] = 3

	# graph[6][7] = 1
	# graph[6][8] = 3

	# graph[7][9] = 4
	# graph[8][9] = 3
    # convert above graph to adjacency list in python
    graph = [[] for _ in range(10)]
    graph[0].append((1,1))
    graph[0].append((2,2))
    graph[0].append((3,3))
    
    graph[1].append((4,2))
    graph[1].append((5,1))
    graph[1].append((6,1))

    graph[2].append((4,1))
    graph[2].append((5,2))
    graph[2].append((6,1))

    graph[3].append((4,2))
    graph[3].append((5,3))
    graph[3].append((6,2))
    
    graph[4].append((7,3))
    graph[4].append((8,2))
    
    graph[5].append((7,3))
    graph[5].append((8,3))

    graph[6].append((7,1))
    graph[6].append((8,3))

    graph[7].append((9,4))
    graph[8].append((9,3))

    print(DAGShortestPath(graph,1,7))