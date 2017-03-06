import sys
import itertools
# row, col order

# y coord, x coord

"""
  a  b  c  d  e  f  g  h 
8
7
6
5
4
3
2
1

"""
# Init board
chess_board = []
for i in range(8):
    chess_board.append([])
    for j in range(8):
        chess_board[i].append("*")

def inBoundsCell_(cell):
    inBounds_ = lambda x: 0 <= x and x <= 7
    return inBounds_(cell[0]) and inBounds_(cell[1])

def print_board(board):
    assert len(board) == 8, "Col size != 8"
    for row in board:
        assert len(row) == 8, "Row size != 8"
    
    for row in board:
        for cell in row:
            print "%s  " % cell,
        print "\n"

def rookGen(cell):
    assert len(cell) == 2
    x,y = cell
    count = 0
    STOP = 3
    while True:
        if (x,y) == cell:
            count += 1
        if count == STOP:
            break
        if count == 1:
            x = (x + 1) % 8
        elif count == 2:
            y = (y + 1) % 8
        if (x,y) != cell:
            yield (x,y)

def diagGen(cell):
    assert len(cell) == 2
    x,y = cell
    count = 0
    STOP = 3 # number of times we encounter original cell
    while True:
        if (x,y) == cell:
            count += 1 
        if count == STOP:
            break

        if count == 1:
            if x == 7:
                x,y = 7 - y, 0
            elif y == 7:
                x,y = 0, 7 - x
            else:
                x += 1
                y += 1
        elif count == 2:
            if x == 7 or y == 0:
                x,y = y,x
            else:
                x += 1
                y -= 1
        if (x,y) != cell:
            yield (x,y)

def isCollision(board, cell):
    assert len(cell) == 2
    inBoundsCell_(cell)
    diags, rooks = diagGen(cell), rookGen(cell)
    for i in itertools.chain(rooks, diags):
        x,y = i
        if board[x][y] == 'Q':
            return (x,y)
    return ()

def eightQueens(board):
    global count
    count  = 0
    def eightQueens_(board, num):
        global count
        if num == 0:
            count += 1
            print_board(board)
            print "Success!"
            return 
        else:
            for i in range(8):
                board[i][num-1] = 'Q'
                if not isCollision(board, (i, num-1)):
                    eightQueens_(board, num-1)
                board[i][num-1] = '*'
            return
    eightQueens_(board, 8)
    print "count = %d" % count

def main():
    eightQueens(chess_board)

if __name__ == "__main__":
    main()

