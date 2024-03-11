import requests

url = "http://localhost:8000/characters/name/momo"
req = requests.get(url)

for i in req.json()["characters"]:
    print(i)
