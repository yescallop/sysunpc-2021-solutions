flags
000: can't fell (0)
001: possibly fell left only (1)
010: possibly fell right only (2)
011: possibly fell both ways (3)
101: must fell right
110: must fell left

starts with 2 or 0, ends with 1 or 0

prev->cur (regarding cur)
0->0: can't fell
0->1: N/A
0->2: fell right
0->3: N/A

1->0: can't fell
1->1: N/A
1->2: fell right
1->3: N/A

2->0: N/A
2->1: can't fell
2->2: N/A
2->3: fell right

3->0: N/A
3->1: can't fell
3->2: N/A
3->3: fell right

0,0,0,2,3,3,3,1,0,2,1,2,3,1
