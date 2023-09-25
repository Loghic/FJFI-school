print("Hello")
n = 1
print ("N =", n+1)
n = 1.2
print("N =", n+1)
n = 'abc'
print("N =", n+str(1))

b = True
b = False

a = [10, 20, 30]

for i in range (len(a)):
    print("a[", i , "] = ", a[i], sep ="")

# for j in a:
#     print(j)

i = 0
print("[", end="")
for t in a:
    if i > 0:
        print(", ", end="")
    print(t, end="")
    i = i + 1
print("]")

i = 0
a = 2*a
print("[", end="")
for t in a:
    if i > 0:
        print(", ", end="")
    print(t, end="")
    i = i + 1
print("]")


d = {1 : "jednicka", 2 : "dvojka"}
print(d[1])
s = { }
s["one"] = "jedna"
s["two"] = "dva"
s["three"] = "tri"
print(s['one'])

for x in s:
    print("s[",x, "] = ", s[x], sep="")

for k in s.keys():
    print(k, "...", s[k])

print("O.K.")