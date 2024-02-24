
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
    for neighbor in graph[vertex]:
        if not visited[neighbor]:
            top_order += dfs(graph,visited,neighbor)
    top_order.append(vertex)
    return top_order


if __name__ == "__main__":
    graph = {"A" : ["D"] , "B" : ["D"] , "C" : ["A","B"] , "D" : ["H" , "G"] , "E" : ["A","D","F"] , "F" : ["K","J"] , "G" : ["I"] , "H" : ["J","I"] , "I" : ["L"] , "J" : ["L","M"] , "K" : ["J"] , "L" : [] , "M" : []} 
    print(topologicalSort(graph))