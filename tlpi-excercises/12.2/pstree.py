"""
This program parses proc tree files to generate a parent child process tree
like pstree(1)
"""

import sys
import psutil

def print_tree(parent, indent=''):
    p = psutil.Process(parent)
    print indent + "{}-{}".format(p.pid, p.name())
    if p.children() == []:
        return
    for x in range(0, len(p.children())):
        print '|-'
        print_tree(p.children()[x].pid, indent + '\t')

def main():
    """
    prints of the pstree
    """
    print_tree(1)

if __name__ == "__main__":
    main()
