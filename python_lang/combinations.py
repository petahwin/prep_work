import sys

def comb(my_set, k):
    global count
    count = 0
    def comb_(pool, acc, n, k):
        global count
        if n < k:
            return
        elif k == 0:
            count += 1
            print acc
            return
        else:           # C(n,k) = C(n - 1, k-1) + C(n - 1, k)
            comb_(pool[1:], acc, n-1, k)
            acc.append(pool[0])
            comb_(pool[1:], acc, n-1, k-1) 
            acc.pop()
    comb_(my_set, [], len(my_set), k)
    print "Count = %d" % count

def main():
    print "Hello world"
    my_set = ['a', 'b', 'c', 'd']
    comb(my_set, 0)

if __name__ == "__main__":
    main()

# How do I do this iteratively?

