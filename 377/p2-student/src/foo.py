

def find_pair( arr, n ):
    for i in range(len(arr)):
        target = n - arr[i]
        for j in range(len(arr)):
            if  i != j and arr[j] == target:
                return (i, j)
    return "not found"



def find_pair_hash( arr, n ):
    locs = {}
    for i in range(len(arr)):
        locs[ arr[i] ] = i
        target = n - arr[n]
        if target in locs:
            return (i, locs[target])
    return "not found"

