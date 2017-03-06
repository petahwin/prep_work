import sys

# [1, 2, 3]
def permutations(my_list):
    global count
    count = 0
    marked = [False for i in range(len(my_list))]
    
    def permutations_(marked, acc, n):
        global count
        if n == 0:
            print acc
            count += 1
            return

        for i in range(len(my_list)):
            if not marked[i]:
                marked[i] = True
                acc.append(my_list[i])
                permutations_(marked, acc, n-1)
                acc.pop()
                marked[i] = False

    permutations_(marked, [], len(my_list))
    print "count = %d" % count

def main():
    print "Hello, world"
    permutations(['a','b','c','d', 'e', 'f'])

if __name__ == "__main__":
    main()

# How do I do this in less than n^n time?
# and how do I do this without an ephemeral marking array?

