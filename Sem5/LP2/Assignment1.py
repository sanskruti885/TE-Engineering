from collections import deque

# Recursive DFS function
def dfs(graph, vertex, visited):
    visited.add(vertex) #add to visted list and print it
    print(vertex, end=" ")

    for neighbor in graph[vertex]: # 'A' :['B','C']
        if neighbor not in visited: #not visited call function again
            dfs(graph, neighbor, visited)

# BFS function
# add a vertex to queue
#pop it then print it and add its neighbour to the queue
def bfs(graph, start):
    visited = set()
    queue = deque()

    visited.add(start) #mark visited just for start
    queue.append(start) #add to queue

    while queue:
        vertex = queue.popleft() #pop before printing
        print(vertex, end=" ")   #print

        for neighbor in graph[vertex]:
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append(neighbor)

#recursion code
def bfs_recursive(graph, queue, visited):
    if not queue:
        return

    vertex = queue.popleft()
    print(vertex, end=" ")

    for neighbor in graph[vertex]:
        if neighbor not in visited:
            visited.add(neighbor)
            queue.append(neighbor)

    bfs_recursive(graph, queue, visited)


# Input number of vertices and edges
vertices = int(input("Enter number of vertices: "))
edges = int(input("Enter number of edges: "))

graph = {}

print("Enter edges in the form A B if edge A to B:")
for _ in range(edges):
    u, v = input().split() #example A B

    # Undirected graph
    if u not in graph: #create list like graph = {'A':[]}
        graph[u] = []
    if v not in graph: #create list like graph = {'A':[],'B':[]}
        graph[v] = []

# make undirected grapg
    graph[u].append(v) #{'A':['B'],'B':['A']}
    graph[v].append(u)

start = input("Enter starting vertex: ")

print("\nDFS Traversal:")
visited = set()
dfs(graph, start, visited)

print("\n\nBFS Traversal:")
bfs(graph, start)

print("\n\nBFS Recursive Traversal:")
visited_recursive = set([start])       # mark starting vertex as visited
queue_recursive = deque([start])       # initialize queue with start
bfs_recursive(graph, queue_recursive, visited_recursive)

