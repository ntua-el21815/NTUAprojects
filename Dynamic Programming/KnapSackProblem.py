
def helpTheThief(objects : list[tuple[int,int]], max_weight : int):
    chosen_items = []
    dp = [[0 for _ in range(max_weight + 1)] for _ in range(len(objects) + 1)]
    for i in range(len(objects)):
        dp[i][0] = 0
    for j in range(max_weight + 1):
        dp[0][j] = 0
    for i in range(1,len(objects) + 1):
        for j in range(1,max_weight + 1):
            weight,value = objects[i-1]
            if j-weight < 0:
                dp[i][j] = dp[i-1][j]
            else:
                if dp[i-1][j-weight] + value > dp[i-1][j]:
                    dp[i][j] = dp[i-1][j-weight] + value
                else:
                    dp[i][j] = dp[i-1][j]
    for i in range(len(objects),0,-1):
        if dp[i][max_weight] != dp[i-1][max_weight]:
            chosen_items.append(i)
            max_weight -= objects[i-1][0]
    return chosen_items


if __name__ == "__main__":
    objects = [(6,30),(3,14),(4,16),(2,9)]
    max_weight = 10
    print(helpTheThief(objects,max_weight))