
def waysToClimb(num_of_stairs : int, steps_at_a_time : int) -> int:
    dp = [0] * (steps_at_a_time)
    dp[0] = 1 
    for i in range(1,num_of_stairs + 1):
        dp[i%steps_at_a_time] = sum(dp[0:i])
    return dp[num_of_stairs%steps_at_a_time]


        
if __name__ == "__main__":
    print(waysToClimb(5,2))