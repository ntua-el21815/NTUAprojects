
def sumToN(end : int):
    known_sums = [0 for i in range(end+1)]
    for i in range(1,end +1):
        known_sums[i] = known_sums[i-1] + i
    return known_sums[end]

if __name__ == "__main__":
    print(sumToN(1000000))