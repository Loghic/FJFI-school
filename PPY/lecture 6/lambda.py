add = lambda x, y: x + y
result = add(5,10)
print(result)

my_list = [(2, 'b'), (1, 'a'), (3, 'c'), (4, 'a')]
sorted_list = sorted(my_list, key=lambda x:x[1])
print(sorted_list)

numbers = [1,2,3,4,5]
squares = list(map(lambda x: x**2, numbers))
print(squares)

numbers = [1,2,3,4,5]
even_numbers = list(filter(lambda x: x % 2 == 0, numbers))
print(even_numbers)

from functools import reduce
numbers = [1,2,3,4,5]
product = reduce(lambda x, y: x*y, numbers)
print(product)

numbers = [1,2,3,4]
letters = ['a', 'b', 'c', 'a']
zipped = list(zip(numbers, letters))
print(zipped)

sorted_list = sorted(my_list, key = lambda x: x[1])
print(sorted_list)