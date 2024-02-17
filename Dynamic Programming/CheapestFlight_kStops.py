
def findCheapestFlight(cities: int,flights :list[list[int]],src : int, dest: int,stops_permitted: int) -> int:
    min_cost = [float('inf')] * cities
    min_cost[src] = 0
    for i in range(stops_permitted + 1):
        temp_cost = min_cost.copy()
        for s,d,p in flights:
            if min_cost[s] == float('inf'):
                continue
            if min_cost[s] + p < temp_cost[d]:
                temp_cost[d] = min_cost[s] + p
        min_cost = temp_cost
    if min_cost[dest] == float('inf'):
        return -1
    return min_cost[dest]

if __name__ == '__main__':
    cities = 4
    flights = [[0,1,100],[1,2,100],[2,0,100],[1,3,600],[2,3,200]]
    src = 0
    dest = 3
    stops_permitted = 1
    print(findCheapestFlight(cities,flights,src,dest,stops_permitted))