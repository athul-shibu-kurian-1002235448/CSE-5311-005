def topological_sort(G):
    color = {u: 'white' for u in G}  
    time = [0]        
    topological_order = []          

    def dfs_visit(u):
        """Inner function to visit vertices recursively."""
        nonlocal time, color, topological_order
        color[u] = 'gray'            
        time[0] += 1                
        for v in G[u]:
            if color[v] == 'white':
                dfs_visit(v)
        color[u] = 'black'   
        time[0] += 1            
        topological_order.insert(0, u)

    
    for u in G:
        if color[u] == 'white':
            dfs_visit(u)

    return topological_order

graph = {
    'undershorts': ['pants', 'shoes'],
    'pants': ['belt', 'shoes'],
    'belt': ['jacket'],
    'shirt': ['tie', 'belt'],
    'tie': ['jacket'],
    'jacket': [],
    'socks': ['shoes'],
    'shoes': [],
    'watch': []
}

order = topological_sort(graph)
print("Topological Order:", order)
