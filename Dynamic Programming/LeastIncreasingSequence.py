from random import randint

def findLisAtIndex(sequence : list,index : int):
    if index == 0 or len(sequence) == 0:
        return (0,[])
    max_length = 0
    increasing_sequences = []
    for i in range(0,index):
        new_length = findLisAtIndex(sequence,i)[0]
        if new_length == 1:
            increasing_sequences.append([sequence[i]])
        if new_length > max_length and sequence[i] < sequence[index]:
            max_length = new_length
            for seq in increasing_sequences:
                if seq[len(seq) - 1] < sequence[i]:
                    seq.append(sequence[i])
    lis = []
    for seq in increasing_sequences:
        if len(seq) == max_length:
            seq.append(sequence[index])
            lis = seq
    return (max_length + 1,lis)


def findLis(sequence : list):
    lis_length = 0
    lis = []
    for i in range(0,len(sequence)):
        lis_at_i = findLisAtIndex(sequence,i)
        lis_length_at_i = lis_at_i[0]
        if lis_length_at_i > lis_length:
            lis_length = lis_length_at_i
            lis = lis_at_i[1]
    return (lis_length,lis)

if __name__ == "__main__":
    sequence = [randint(0,100) for i in range(0,10)]
    print ("The sequence is",sequence)
    lis = findLis(sequence)
    print("The longest increasing subsequence is of length",lis[0],"and is",lis[1])