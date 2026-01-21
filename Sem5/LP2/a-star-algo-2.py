def find_pos(state,value):
    for i in range(3):
        for j in range(3):
            if state[i][j] == value:
                return i,j

def manhattan(state,goal):
    h=0
    for i in range(3):
        for j in range(3):
            if state[i][j] != 0:
                gx, gy = find_pos(goal, state[i][j]) #goal=3*3 matrix , state[i][j] = value to search returns x,y 
                h += abs(i-gx) + abs(j-gy) # |current_row - goal_row|+|current_columns-goal_column|
    return h

def get_neighbours(state):
    neighbours = []
    x, y = find_pos(state,0) #find the blank tile

    moves = [(-1,0), (1,0), (0,-1), (0,1)] # up down left right

    for dx, dy in moves:
        nx, ny = x + dx, y + dy # new row and column for blank tile
        if 0 <= nx < 3 and 0 <= ny < 3: #make sure inside puzzle
            new_state = [row[:] for row in state] # instead of new_state = state this point same memory location
            new_state[x][y], new_state[nx][ny] = new_state[nx][ny], new_state[x][y] #swap 
            neighbours.append(new_state)

    return neighbours

def a_star(start,goal):
    open_list = [] # will append initial matrix,g(n),h(n),f(n)
    closed_list = []

    h_start = manhattan(start,goal)
    open_list.append((start, 0, h_start, h_start)) # appends initial matrix, g(n)=0, h(n),f(n) at first f(n)=h(n)

    while open_list: #run until penlist now empty
        #open_list=([[2,8,3],[1,6,4],[7,0,5]],0,5,5) ->[x[0],x[1],x[2],x[3]]
        current = min(open_list, key = lambda x: x[3]) # find minimum f value 
        open_list.remove(current)  #remove from openlist since calculated 

        state, g, h, f = current

        print("Current state:")
        for row in state:
            print(row)
        print(f"g={g}, h = {h}, f = {f}\n")

        if state == goal:
            print("Goal reached!")
            print("Final f(n) =", f)
            return

        closed_list.append(state) #visited state append in closed list
        for neighbour in get_neighbours(state):
            if neighbour in closed_list: #if neighbour already visited
                continue

            new_g = g+1 #next iteration depth increases
            new_h = manhattan(neighbour,goal) #calculate h for new neighbour
            new_f=new_g+new_h

            open_list.append((neighbour, new_g, new_h, new_f))

if __name__ == "__main__":
    initial_state = [
        [2,8,3],
        [1,6,4],
        [7,0,5]
    ]   

    goal_state = [
        [1,2,3],
        [8,0,4],
        [7,6,5]
    ]      

    a_star(initial_state, goal_state )  