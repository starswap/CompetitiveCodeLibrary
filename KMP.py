def KMP(STRING,PATTERN):
    
    lps = [0 for i in range(len(PATTERN))]
    i = 0
    j = 1
    while j < len(lps): # O(M)
        if PATTERN[i] != PATTERN[j]:
            j += 1
            if i > 0:
                i = lps[i-1]
        else:
            lps[j] = i+1
            i += 1
            j += 1

    s = 0
    p = 0
    while s < len(STRING):
        if STRING[s] != PATTERN[p] and p > 0:
            p = lps[p-1]
        else:
            s += 1
            p += 1
        
        if p == len(lps):
            return True
        
    return False
