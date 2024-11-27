def floyd_warshall(weights):
    n = len(weights)
    distances = [[float('inf')] * n for _ in range(n)]
    
    for i in range(n):
        for j in range(n):
            distances[i][j] = weights[i][j]
    
    for k in range(n):
        for i in range(n):
            for j in range(n):
                distances[i][j] = min(distances[i][j], distances[i][k] + distances[k][j])
    
    return distances

nodes = ['1', '2', '3', '4', '5']
weights = [
    [0, 3, 8, float('inf'), -4],
    [float('inf'), 0, float('inf'), 1, 7],
    [float('inf'), 4, 0, float('inf'), float('inf')],
    [2, float('inf'), -5, 0, float('inf')],
    [float('inf'), float('inf'), float('inf'), 6, 0],
]

distances = floyd_warshall(weights)

for i, row in enumerate(distances):
    print(f"{nodes[i]}: {row}")
