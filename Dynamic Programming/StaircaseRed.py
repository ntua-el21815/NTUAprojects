
def waysToClimbRedSteps(num_of_stairs : int, steps_at_a_time : int,red_stairs : list) -> int:
    dp = [0] * (steps_at_a_time)
    dp[0] = 1
    for i in range(1,num_of_stairs+1):
        if i in red_stairs:
            dp[i%steps_at_a_time] = 0
        else:
            dp[i%steps_at_a_time] = sum(dp[0:(num_of_stairs+1)%steps_at_a_time])
    return dp[num_of_stairs%steps_at_a_time]

if __name__ == "__main__":
    print(waysToClimbRedSteps(2,2,[1]))