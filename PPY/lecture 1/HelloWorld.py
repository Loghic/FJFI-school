print("Hello World!")

x = "Hello World!"

if 1 > 0:
    print("One is more than zero")
else:
    print("Zero is more than one")
print("...sound correct")

print('One' if 1 > 0 else 'Zero')

z = []

for i in range(len(x)):
    pos = len(x) - (i+1)
    z.append(x[pos])

string = ','.join(str(j) for j in z)

print(string)