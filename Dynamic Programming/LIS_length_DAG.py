
def LIS_length_at_index(sequence :list) -> int:
    DAG = Seq_To_DAG(sequence)
    return max(longest_path_DAG(DAG,i) for i in range(len(sequence)))
    

def longest_path_DAG(DAG : list[tuple[int]],node : int) -> list[tuple[int]]:
    connected_nodes = []
    for edge in DAG:
        if edge[1] == node:
            connected_nodes.append(edge[0])
    if len(connected_nodes) == 0:
        return 1
    return max([longest_path_DAG(DAG,connected_nodes[i]) for i in range(len(connected_nodes))]) + 1

def Seq_To_DAG(sequence : list) -> list[tuple[int]]:
    DAG : list[tuple[int]] = []
    for i in range(len(sequence)):
        for j in range(i+1,len(sequence)):
            if sequence[i] < sequence[j]:
                DAG.append((i,j))
    return DAG

def main():
    sequence = [5, 2, 8, 6, 3, 6, 9, 7]
    print(LIS_length_at_index(sequence))

if __name__ == "__main__":
    main()