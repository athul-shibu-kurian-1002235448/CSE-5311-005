def bellman_ford(graph, start):
    distances = {node: float('inf') for node in graph}
    distances[start] = 0

    for _ in range(len(graph) - 1):
        for node in graph:
            for neighbor, weight in graph[node].items():
                if distances[node] + weight < distances[neighbor]:
                    distances[neighbor] = distances[node] + weight

    for node in graph:
        for neighbor, weight in graph[node].items():
            if distances[node] + weight < distances[neighbor]:
                return None, False

    return distances, True

graph = {
    's': {'t': 10, 'y': 5},
    't': {'x': 1, 'y': 2},
    'x': {'z': 6},
    'y': {'t': 3, 'x': 9, 'z': 2},
    'z': {'s': 7, 'x': 4}
}

start_node = 's'
distances, no_negative_cycle = bellman_ford(graph, start_node)

if no_negative_cycle:
    for node, distance in distances.items():
        print(f"Distance from {start_node} to {node}: {distance}")
else:
    print("Graph contains a negative-weight cycle")
