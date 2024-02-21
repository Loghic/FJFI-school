import requests
from duckduckgo_search import DDGS
from pprint import *

url = "https://duckduckgo.com/?q=cat&t=osx&iax=images&ia=images"

# r = requests.get(url)
# # print(r.content) # general content (bytes)
# print(r.text) # decoded text
# print("<img" in r.text.lower())

with DDGS() as ddgs:
    results = [r for r in ddgs.images("cat", max_results=10)]

number = 1
for res in results:
    f = open("cat"+str(number)+".jpg", mode="wb")
    data = requests.get(res["image"]).content
    f.write(data)
    f.close()
    number += 1
    
for res in results:
    print(res['image'])

    

# print(r.content)
