
def minCostToClimbTo(step : int,steps_at_a_time :int,cost : list) -> tuple:
    known_costs = [0] * len(cost)
    min_cost_path = []
    for i in range(0,steps_at_a_time):
        known_costs[i] = cost[i]
    for i in range(2,step+1):
        #set min cost to max int in python language
        min_cost = float('inf')
        min_option = None
        for j in range(i-steps_at_a_time,i):
            if known_costs[j] < min_cost:
                min_cost = known_costs[j]
                min_option = j
        if min_option not in min_cost_path:
            min_cost_path.append(min_option)
        known_costs[i] = cost[i] + min_cost
    min_cost_path.append(step)
    return (known_costs[step],min_cost_path)


if __name__ == "__main__":
    cost = [0, 3, 2, 4, 6, 1, 1, 5, 3]
    step = 8
    print(minCostToClimbTo(step,2,cost))