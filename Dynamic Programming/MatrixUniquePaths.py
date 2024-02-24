
def findUniquePathMatrix(length : int, width : int) -> int:
    known_ways = [[0] * (length+1)] * (width+1)
    known_ways[1][1] = 1
    for i in range(1,width+1):
        for j in range(1,length+1):
            if i>1 and j>1:
                known_ways[i][j] = known_ways[i-1][j] + known_ways[i][j-1]
            elif i>1:
                known_ways[i][j] = known_ways[i-1][j]
            elif j>1:
                known_ways[i][j] = known_ways[i][j-1]
    return known_ways[width][length]

if __name__ == "__main__":
    print(findUniquePathMatrix(3,4))