import time 

#Set max recursion depth to unlimited
import sys
sys.setrecursionlimit(100000000)

def fibonacci_memo(n: int,memo = [0,1]) -> int:
    if n < 2:
        return n
    if len(memo) > n:
        return memo[n]
    memo.append(fibonacci_memo(n-1,memo) + fibonacci_memo(n-2,memo))
    return memo[n]


def fibonacci(n: int) -> int:
    a = 0
    b = 1
    for i in range(n):
        a,b = b,a+b
    return a

if __name__ == "__main__":
    #Set precision of timing to nanoseconds
    time.get_clock_info('time').resolution
    timestart = time.time()
    print(fibonacci_memo(5000))
    timeend = time.time()
    print("Time taken to run fibonacci_memo: ",(timeend-timestart)*1000)
    timestart = time.time()
    print(fibonacci(5000))
    timeend = time.time()
    print("Time taken to run fibonacci: ",(timeend-timestart)*1000)