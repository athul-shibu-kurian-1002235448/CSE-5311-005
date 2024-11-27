import heapq

def dijkstra(graph, start):
    queue = []
    distances = {node: float('inf') for node in graph}
    distances[start] = 0
    heapq.heappush(queue, (0, start))

    while queue:
        current_distance, current_node = heapq.heappop(queue)

        if current_distance > distances[current_node]:
            continue

        for neighbor, weight in graph[current_node].items():
            distance = current_distance + weight

            if distance < distances[neighbor]:
                distances[neighbor] = distance
                heapq.heappush(queue, (distance, neighbor))

    return distances


graph = {
    's': {'t': 10, 'y': 5},
    't': {'x': 1, 'y': 2},
    'x': {'z': 6},
    'y': {'t': 3, 'x': 9, 'z': 2},
    'z': {'s': 7, 'x': 4}
}

start_node = 's'
distances = dijkstra(graph, start_node)

for node, distance in distances.items():
    print(f"Distance from {start_node} to {node}: {distance}")
