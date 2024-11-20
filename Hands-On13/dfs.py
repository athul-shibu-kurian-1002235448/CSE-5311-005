def dfs(graph, start, visited=None):
    if visited is None:
        visited = set()
    visited.add(start)
    for neighbor in graph[start]:
        if neighbor not in visited:
            dfs(graph, neighbor, visited)
    return visited

graph = {
    'A': ['B', 'H'],
    'B': ['A', 'H', 'C'],
    'C': ['B', 'I', 'F', 'D'],
    'D': ['C', 'F', 'E'],
    'E': ['D', 'F'],
    'F': ['G', 'C', 'D', 'E'],
    'G': ['H', 'I', 'F'],
    'H': ['A', 'B', 'I', 'G'],
    'I': ['H', 'C', 'G']
}

visited_nodes = dfs(graph, 'A')
print(visited_nodes)
