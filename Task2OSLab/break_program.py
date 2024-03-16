
#Program to try and create so many processes that fork fails.

import os
import subprocess as sp

def main():
    monster_string : str = "ft" * 50000
    print("Monster string created")
    result = os.system("make compile")
    print("Make complete with result: ", result)
    command = "./father " + monster_string
    sp.run(command, shell=True)
    return

if __name__ == "__main__":
    main()
