# !echo "Hello world" >> example.txt

def open_file():
    # Open the file in read mode
    file = open("example.txt", "r")

    # Read the entire contents of the file
    contents = file.read()

    print("-"*40)
    # Print the contents of the file
    print(contents)

    # Close the file
    file.close()

def write_to_file():
# Open the file in write mode
    file = open("example.txt", "w")

    # Write data to the file
    file.write("Hello, world!")

    # Close the file
    file.close()

open_file()
write_to_file()
open_file()

import os

# List the contents of the current directory
for filename in os.listdir("."):
    # Get the full path of the file/directory
    path = os.path.join(".", filename)
    # Check if the path is a directory
    if os.path.isdir(path):
        print(f"{filename} is a directory")
    # Otherwise, it must be a file
    else:
        print(f"{filename} is a file")

print("-"*40)

def even_numbers(numbers):
    return [num for num in numbers if num % 2 == 0]

result = even_numbers([1, 2, 3, 4, 5, 6])
print(result)

print("-"*40)

def common_elements(list1, list2):
    return list(set(list1) & set(list2))

result = common_elements([1, 2, 3, 4], [3, 4, 5, 6])
print(result)

print("-"*40)

def unique_numbers(numbers):
    seen = set()
    for num in numbers:
        if num not in seen:
            seen.add(num)
            yield num

numbers = [1, 2, 2, 1, 1, 3, 4, 4, 5, 6, 6, 7, 7]
for unique_num in unique_numbers(numbers):
    print(unique_num)

print("-"*40)

def homework(input_str):
    return {x: input_str.count(x) for x in set(input_str)}
print(homework('apple'))

print("-"*40)
my_string = 'appleee heheh '

sample_dictionary={}
for x in (my_string):
    if x in sample_dictionary:
        sample_dictionary[x] = sample_dictionary.get(x) + 1
    else:
        sample_dictionary[x] = 1
print(sample_dictionary)

print("-"*40)

print({x: "test".count(x) for x in set("test")})