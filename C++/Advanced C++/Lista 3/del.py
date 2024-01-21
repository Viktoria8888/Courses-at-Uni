romans = {"I":  1,
          "V":  5,
          "X": 10,
          "L": 50,
            "C":  100,
            "D": 500,
            "M":  1000}
r = {v: k for k, v in romans.items()}


def recur(n):
    if n == 0:
        return ""
    if (n == 4 or n == 9):
        return r[1] + r[n+1]
    if n == 40 or n == 90:
        return r[10] + r[n+10]
    if n == 400 or n == 900:
        return r[100] + r[n+100]

    for value in sorted(r.keys(), reverse=True):
        if n >= value:
            return r[value] + recur(n - value)
print(recur(100))
