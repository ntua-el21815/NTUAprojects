
def getPath(profits,m,n):
    if m==0 and n==0:
        return []
    elif m > 0 and n==0:
        return getPath(profits,m-1,n) + [(m,n+1)]
    elif m==0 and n>0:
        return getPath(profits,m,n-1) + [(m+1,n)]
    else:
        if profits[m-1][n] > profits[m][n-1]:
            return getPath(profits,m-1,n) + [(m,n+1)]
        else:
            return getPath(profits,m,n-1) + [(m+1,n)]

def mostProfitPath(matrix : list[list[int]]) -> list[list[int]]: 
    known_profits = matrix
    for i in range(0,len(matrix)):
        for j in range(0,len(matrix[0])):
            if i > 0 and j > 0:
                if known_profits[i][j-1] > known_profits[i-1][j]:
                    known_profits[i][j] += known_profits[i][j-1]
                elif known_profits[i-1][j] > known_profits[i][j-1]:
                    known_profits[i][j] += known_profits[i-1][j] 
            elif i>0 and j==0:
                known_profits[i][j] += known_profits[i-1][0]
            elif j>0 and i==0:
                known_profits[i][j] += known_profits[0][j-1]                               
    return (getPath(known_profits,len(matrix)-1,len(matrix[0])-1),known_profits[len(matrix)-1][len(matrix[0])-1])

if __name__ == "__main__":
    print(mostProfitPath([[1,4,1],[2,2,5],[9,3,9],[4,13,2]]))