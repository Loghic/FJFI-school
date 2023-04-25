import numpy as np
a = np.array([1,2,3,4,5])
print(a[2:4])
b = np.array([[1,2,3],[4,5,6],[7,8,9]])
print(b)
a = np.zeros((3,4))
print(a)

c = np.random.rand(2,3,4)
print(c)

a = np.array([1,2,3], dtype=np.int32)
print(a)

b = np.array([1.0,2.0,3.0], dtype=np.float64)
print(b)

a = np.random.rand(1000,1000)
b = np.random.rand(1000,1000)
print(a.dtype)


c = np.dot(a,b)
a = a.astype(np.float32)
b = b.astype(np.float32)
c = np.dot(a,b)

a = np.random.randint(0,100, size=1_000_000)
b = a*2

a = [i for i in range(1_000_000)]
b = [i*2 for i in a]