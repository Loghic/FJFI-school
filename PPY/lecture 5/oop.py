import math
class Shape:
    def __init__(self, sides):
        self.sides = sides
    
    def area(self):
        pass

    def perimeter(self):
        pass

    def resize(self, scale):
        for i in range(len(self.sides)):
            self.sides[i] *= scale
    
    def draw (self):
        print (f'Drawing a {str(self)}')
        pass

class Circle(Shape):
    def __init__(self, radius):
        super().__init__([radius])

    def area(self):
        return math.pi * self.sides[0]**2
    
    def perimeter(self):
        return 2 * math.pi * self.sides[0]
    
    def __str__(self):
        return f'square with side length of {self.sides[0]}'
    
class Square(Shape):
    def __init__(self,side,):
        super().__init__([side]*4)

    def area(self):
        return self.sides[0]**2
    
    def perimeter(self):
        return 4 * self.sides[0]
    
    def __str__(self):
        return f'square with side lenght of {self.sides[0]}'
    
class Rectangle(Shape):
    def __init__(self,lenght,width):
        super().__init__([lenght,width,lenght,width])
    
    def area(self):
        return self.sides[0] * self.sides[1]
    
    def perimeter(self):
        return 2 * (self.sides[0] + self.sides[1])
    
    def __str__(self):
        return f'rectangle with side lengths of {self.sides[0]} and {self.sides[1]}'
    

circle = Circle(5)
square = Square(10)
rectangle = Rectangle(10,5)

circle.draw()
square.draw()
rectangle.draw()

# Get the area and perimeter of each shape
print("Circle area:", circle.area()) # Output: Circle area: 78.53981633974483
print("Circle perimeter:", circle.perimeter()) # Output: Circle perimeter: 31.41592653589793
print("Square area:", square.area()) # Output: Square area: 100
print("Square perimeter:", square.perimeter()) # Output: Square perimeter: 40
print("Rectangle area:", rectangle.area()) # Output: Rectangle area: 50
print("Rectangle perimeter:", rectangle.perimeter()) # Output: Rectangle perimeter: 30

circle.resize(2)
square.resize(0.5)
rectangle.resize(1.5)

circle.draw()
square.draw()
rectangle.draw()

print("*"*40)
#Examples from last time

def string_lenghts(strings):
    return {s: len(s) for s in strings}

strings = ['hello', 'world', 'python', 'comprehensions']
result = string_lenghts(strings)
print(result)
print(result['world'])

def unique_words(strings):
    return {word for string in strings for word in string.split()}

strings = ['hello world', 'world python', 'python python']
result = unique_words(strings)
print(result)

def age_to_names(name_to_age):
    names = name_to_age.items()
    ages = name_to_age.values()
    return {age: [name for name, age_ in names if age_ == age] for age in set(ages)}


name_age = {'Alice': 25, 'Bob': 30, 'Charlie': 25, 'David': 35, 'Eve': 30}
result = age_to_names(name_age)
print(result)

def greater_than_average(numbers):
    average = sum(numbers) / len(numbers)
    return (num for num in numbers if num > average)

numbers = [1,2,3,4,5,6,7,8,9,10]
for num in greater_than_average(numbers):
    print(num)

def even_and_divisible_by_three(numbers):
    return {num for num in numbers if num % 2 == 0 and num % 3 == 0}

numbers = [1,2,3,4,5,6,7,8,9,10,12,18]
result = even_and_divisible_by_three(numbers)
print(result)