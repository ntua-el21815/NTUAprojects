
def findEditDistance(str1 : str, str2 : str) -> int:
    l1 = len(str1) - 1
    l2 = len(str2) - 1
    if l1 == -1:
        return l2 + 1
    if l2 == -1:
        return l1 + 1
    if str1 == str2:
        return 0
    if str1[l1] == str2[l2]:
        return min(findEditDistance(str1[0:l1],str2),findEditDistance(str1,str2[0:l2]),findEditDistance(str1[0:l1],str2[0:l2]))
    return min(findEditDistance(str1[0:l1],str2),findEditDistance(str1,str2[0:l2]),findEditDistance(str1[0:l1],str2[0:l2])) + 1


def findEditDistanceDP(str1 : str, str2 : str) -> int:
    dp = [[0 for i in range(len(str2) + 1)] for j in range(len(str1) + 1)]
    for i in range(len(str1) + 1):
        dp[i][0] = i
    for j in range(len(str2) + 1):
        dp[0][j] = j
    for i in range(1,len(str1) + 1):
        for j in range(1,len(str2) + 1):
            if str1[i - 1] == str2[j - 1]:
                dp[i][j] = min(dp[i-1][j],dp[i][j-1],dp[i-1][j-1])
            else:
                dp[i][j] = min(dp[i-1][j],dp[i][j-1],dp[i-1][j-1]) + 1
    for line in dp:
        print(line)
    return dp[len(str1)][len(str2)]



if __name__ == "__main__":
    str1 = input("Enter the first string: ")
    str2 = input("Enter the second string: ")
    print("The edit distance between the two strings is: ",findEditDistanceDP(str1,str2))