x = 5
print(x)
print("------------------------------")
x = "Hello world!"
print(x)
print("------------------------------")
print(type(x))
print("------------------------------")
x = 5
if x >= 0:
    print("x is positive")
else:
    print("x is negative")

print("------------------------------")
x = -2
if x >= 0:
    print("x is positive")
else:
    print("x is negative")

print("------------------------------")

x = 5
print("x is greater than zero") if x > 0 else print("x is not Greater than zero")
print("------------------------------")

x = -2
print("x is greater than zero") if x > 0 else print("x is not Greater than zero")
print("------------------------------")

print(1 <= 2 <= 3)

print("------------------------------")

print (2 <= 1 <= 3)

print("------------------------------")

x = 5
y = [1,2,3]

if x == 5 and 2 in y:
    print("x is 5 and 2 is in y")
else:
    print("condition not met")

print("------------------------------")

i = 0
while i < 5:
    print(i)
    i += 1

print("------------------------------")

fruits = ["apple", "banana", "cherry"]
for fruit in fruits:
    print(fruit)

print("------------------------------")

for fruit in fruits:
    if fruit == "banana":
        break
    print(fruit)

print("------------------------------")

for fruit in fruits:
    if fruit == "banana":
        continue
    print(fruit)

print("------------------------------")


#Functions
print("\nFUNCTIONS\n")
def add_numbers(x,y):
    return x + y

result = add_numbers(5,3)
print (result)
print("------------------------------")

def greet(name, greeting):
    print(greeting, name)

greet("John", "Hello")
print("------------------------------")

greet(greeting='Hi', name="Alice")

print("------------------------------")

def greet2(name, greeting="Hello"):
    print(greeting, name)

greet2("Bob")
greet2("Anastasia", "Ciao")

print("------------------------------")

def greet3(*names):
    for name in names:
        print("Hello", name)

greet3 ("Alice", "Bob", "Charlie")
print("------------------------------")

def greet4(**kwargs):
    for name, greeting in kwargs.items():
        print (greeting, name)

greet4(Alice="Hi", Bob="Bonjour", Chica="Hola")
print("------------------------------")

print("\nHomework\n")

myStr = 'Hello World'
lenStr = len(myStr)
    
for pos in range(lenStr):
    print(myStr[lenStr-1 - pos], end='')
print("") 

myCnt = 0
myCntPrev = 0

myStr = "Hello how are you"

for mySpace in myStr:
    if mySpace == ' ':
        for pos in range(myCnt-myCntPrev+1):
            if myCntPrev == 0 and pos == 0:
                continue
            print(myStr[myCnt-pos], end='')
        myCntPrev = myCnt+1
    myCnt += 1

for newPos in range(myCnt - myCntPrev):
    if newPos == 0:
        print(' ', end='')
    print(myStr[myCnt - 1 - newPos], end='')

print("")

print("-"*40)

myStr = "Hello World"

for word in myStr.split(' '):
    word[0].lower()
    for pos in range(len(word)):
        printingPos = len(word)-1 - pos
        if 97 <= ord(word[-1]) <= 122:
            shift = ord(word[-1]) - 32 
            uppercase = chr(shift)
            word = word[:-1] + uppercase
        print(word[printingPos], end='')
    
    print(" ", end='')

print("")