# Description: This file contains the implementation of the DAG shortest path algorithm.
# It also contains the implementation of the DAG longest path algorithm.

def topologicalSort(graph : dict[str : list[str]]) -> list[str]:
    n = len(graph)
    visited = {vertex : False for vertex in graph}
    top_order = []
    for vertex in graph:
        if not visited[vertex]:
            top_order += dfs(graph,visited,vertex)
    return top_order[::-1]

def dfs(graph : dict[str : list[str]],visited : list[bool] ,vertex : int):
    top_order = []
    visited[vertex] = True
    for neighbor,weight in graph[vertex]:
        if not visited[neighbor]:
            top_order += dfs(graph,visited,neighbor)
    top_order.append(vertex)
    return top_order

def DAGShortestPath(graph : dict[str : list[str]], top_order : list[str],start : str = None,end : str = None) -> list[int]:
    if start is None:
        start = top_order[0]
    if end is None:
        end = top_order[-1]
    num_vertices = len(top_order)
    current_best = {vertex : float('inf') for vertex in top_order}
    prev = {vertex : None for vertex in top_order} 
    current_best[end] = 0
    for vertex in top_order[::-1]:
        for (neighbor,weight) in graph[vertex]:
            if current_best[vertex] > current_best[neighbor] + weight:
                current_best[vertex] = current_best[neighbor] + weight
                prev[vertex] = neighbor
    path_from_start_to_end = [start]
    current_node = start
    while current_node != end:
        current_node = prev[current_node]
        path_from_start_to_end.append(current_node)
    return (path_from_start_to_end,current_best[start])
    
def DAGLongestPath(graph : dict[str : list[str]], top_order : list[str],start : str = None,end : str = None) -> list[int]:
    if start is None:
        start = top_order[0]
    if end is None:
        end = top_order[-1]
    num_vertices = len(top_order)
    current_best = {vertex : -float('inf') for vertex in top_order}
    prev = {vertex : None for vertex in top_order} 
    current_best[end] = 0
    for vertex in top_order[::-1]:
        for (neighbor,weight) in graph[vertex]:
            if current_best[vertex] < current_best[neighbor] + weight:
                current_best[vertex] = current_best[neighbor] + weight
                prev[vertex] = neighbor
    path_from_start_to_end = [start]
    current_node = start
    while current_node != end:
        current_node = prev[current_node]
        path_from_start_to_end.append(current_node)
    return (path_from_start_to_end,current_best[start])

if __name__ == '__main__':
    graph = {
        'A' : [('B',3),('C',6)],
        'B' : [('C',4),('D',4),('E',11)],
        'C' : [('D',8),('G',11)],
        'D' : [('E',-4),('F',5),('G',2)],
        'E' : [('H',9)],
        'F' : [('H',1)],
        'G' : [('H',2)],
        'H' : []
    }
    top_order = topologicalSort(graph)
    start = top_order[0]
    end = top_order[-1]
    longest_path = DAGLongestPath(graph,top_order,start,end)
    print(longest_path[0],f"The length of the longest path from {start} to {end} is",longest_path[1])