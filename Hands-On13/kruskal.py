def kruskal(V, E):
    A = set()
    parent = {}
    rank = {}
    for v in V:
        parent[v] = v
        rank[v] = 0
    edges = sorted(E, key=lambda edge: edge[2])
    for (u, v, w) in edges:
        if find_set(u, parent) != find_set(v, parent):
            A.add((u, v, w))
            union(u, v, parent, rank)
    return A

def find_set(u, parent):
    if parent[u] != u:
        parent[u] = find_set(parent[u], parent)
    return parent[u]

def union(u, v, parent, rank):
    u_root = find_set(u, parent)
    v_root = find_set(v, parent)
    if rank[u_root] < rank[v_root]:
        parent[u_root] = v_root
    else:
        parent[v_root] = u_root
        if rank[u_root] == rank[v_root]:
            rank[u_root] += 1

V = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'}
E = [
    ('A', 'B', 4),
    ('A', 'H', 8),
    ('B', 'C', 8),
    ('B', 'H', 11),
    ('C', 'D', 7),
    ('C', 'F', 4),
    ('C', 'I', 2),
    ('D', 'E', 9),
    ('D', 'F', 14),
    ('E', 'F', 10),
    ('F', 'G', 2),
    ('G', 'H', 1),
    ('G', 'I', 6),
    ('H', 'I', 7)
]

A = kruskal(V, E)
print("Edges in the Minimum Spanning Tree:")
for edge in A:
    print(edge)
