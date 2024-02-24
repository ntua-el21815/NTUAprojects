
def LIS_length(sequence : list):
    return max([LIS_length_at_index(sequence,i) for i in range(len(sequence))])

def LIS_length_at_index(sequence : list,index : int) -> int:
    if index == 0:
        return 1
    if len(sequence) == 0:
        return 0
    max_length = 0
    for i in range(0,index):
        new_length = LIS_length_at_index(sequence,i)
        if new_length > max_length and sequence[i] < sequence[index]:
            max_length = new_length
    return max_length + 1

if __name__ == "__main__":
    print(LIS_length([5, 2, 8, 6, 3, 6, 9, 7]))