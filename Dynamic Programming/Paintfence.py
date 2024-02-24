
def waysToPaintFence(posts : int):
    #Objective Function f(i,j) -> How many ways to paint i number of fence posts with two colors blue and green
    #One color cannot repeat more than two times.j is the ending color
    #Initial conditions f(0) = 1,f(1) = 1
    #f(i) = 2*(f(i-1) + f(i-2)) for the two colors
    dp = [[0] * (posts + 1)] * 2
    dp[0][0] = 1
    dp[1][0] = 1
    dp[0][1] = 1
    for i in range(2,posts + 1):
        dp[0][i] = dp[0][i-1] + dp[1][i-2]
        dp[1][i] = dp[0][i-2] + dp[0][i-1]
    return dp[0][posts] + dp[1][posts]

if __name__ == "__main__":
    posts = 4
    print(waysToPaintFence(posts))