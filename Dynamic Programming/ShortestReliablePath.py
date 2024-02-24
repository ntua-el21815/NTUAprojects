
def findShortestRelPath(num_of_nodes : int,graph : list[list[tuple[int,int]]], start : int , end : int , max_hops : int) -> int:
    if not error_handling:
        return -1
    min_dist = [float('inf')] * num_of_nodes
    temp_dist = [float('inf')] * num_of_nodes
    temp_dist[start] = min_dist[0] = 0
    for i in range(max_hops + 1):
        for node,neighbors in enumerate(graph):
            for neighbor in neighbors:
                if min_dist[node] + neighbor[1] < min_dist[neighbor[0]]:
                    temp_dist[neighbor[0]] = min_dist[node] + neighbor[1]
        min_dist = temp_dist
    if min_dist[end] == float('inf'):
        return -1
    return min_dist[end]


def error_handling(nodes: int,start: int,end :int):
    if start > nodes:
        return False
    if end > nodes:
        return False
    return True


def findShortestRelPathDP(num_of_nodes: int ,graph : list[list[tuple[int,int]]] , start : int , end : int , max_hops : int) -> int:
    dp = [[float("inf") for _ in range(max_hops + 1)] for _ in range(num_of_nodes)]
    for i in range(0,num_of_nodes):
        if i == start:
            dp[i][0] = 0
            continue
        dp[i][0] = float("inf")
    for node in range(num_of_nodes):
        for i in range(1,max_hops + 1):
            possible_paths = [dp[u][i-1] + weight for u in range(num_of_nodes) for neighbor,weight in graph[u] if neighbor == node]
            if len(possible_paths) == 0:
                dp[node][i] = dp[node][i-1]
            else:
                dp[node][i] = min(dp[node][i-1],min(possible_paths))
    if dp[end][max_hops] == float("inf"):
        return -1
    return dp[end][max_hops]
                


if __name__ == '__main__':
    graph = [[(1,100),(2,500)] , [(2,100)] , []]
    print(findShortestRelPathDP(3,graph,0,2,2))