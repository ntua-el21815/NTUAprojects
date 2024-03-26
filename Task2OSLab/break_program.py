
#Program to try and create so many processes that fork fails.

import os
import subprocess as sp
from time import *

def main():
    monster_string : str = "ft" * 50000
    print("Monster string created")
    result = os.system("make compile")
    print("Make complete with result: ", result)
    input("Press Enter to break the program!")
    command = "./gates " + monster_string
    sp.run(command, shell=True)
    return

if __name__ == "__main__":
    main()
