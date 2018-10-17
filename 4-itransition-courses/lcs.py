import sys

if len(sys.argv) == 1:
    print()
    sys.exit()

pat = sys.argv[1]

for sz in range(len(pat), 0, -1):
    for pos in range(0, len(pat)-sz+1):
        temp = pat[pos:pos+sz]
        found = 1
        for i in range(2, len(sys.argv)):
            if sys.argv[i].find(temp) == -1:
                found = 0
        if found == 1:
            print(temp)
            sys.exit()

print()
