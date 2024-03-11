"""
Personne ne semble avoir fait de scripts pour convertir
ça en base de données, donc on l'a fait.
"""
import re
import mysql.connector as mysql

db = mysql.connect(
    host = "localhost",
    user = "user",
    password= "password",
    database="anime_voice"
)

cursor = db.cursor()

anime_db_file = "../misc/anime-database.txt"

with open(anime_db_file, "r") as f:
    lines = f.read().split("\n\n")

def get_air_date(anime_name):
    if not len(anime_name.split("[")) > 1:
        return None

    try:
        if isinstance(int(anime_name.split("[")[1][:-1]), int):
            return int(anime_name.split("[")[1][:-1])

    except Exception:
        if "-" in anime_name.split("[")[1][:-1]:
            return anime_name.split("[")[1][:-1]


anime_data = list()
characters_data = list()

for line in range(len(lines)):
    anime_block = lines[line]
    anime_name = anime_block.split("\n")[0]
    split_anime_name = anime_name.split(" ")
    air_date = get_air_date(anime_name)

    for index, word in enumerate(split_anime_name):
        try:
            if word[0] == "[" and word[-1] == "]":
                del split_anime_name[index]
        except IndexError:
            pass

    anime_name = " ".join(split_anime_name)

    try:
        print(f"-> Ajout de l'animé: {anime_name}")

        anime_data.append((anime_name, air_date))

        # cursor.execute("INSERT INTO anime_list (anime, air_date) VALUES (%s, %s)", (anime_name, air_date))
        # db.commit()

        for character_seiyuu in anime_block.split("\n")[1:]:
            if character_seiyuu[0] == "#" or "URL" in character_seiyuu:
                continue

            character = character_seiyuu.split("::")[0].strip()
            seiyuu = character_seiyuu.split("::")[1].strip()
            anime_id = line+1 # car line débute à 0 et notre id dans la table anime_list débute à 1 (auto increment)

            print("  -> Ajout personnage - seiyuu")
            print(f"  {character} - {seiyuu}")

            characters_data.append((anime_id, anime_name, character, seiyuu))

            # cursor.execute("INSERT INTO characters_list (anime_id, anime_name, character_name, seiyuu) VALUES (%s, %s, %s, %s)", 
            # (anime_id, anime_name, character, seiyuu))
            # db.commit()

    except Exception as error:
        print(error)


cursor.executemany("INSERT INTO anime_list (anime, air_date) VALUES (%s, %s)", anime_data)
db.commit()

cursor.executemany(
    "INSERT INTO characters_list (anime_id, anime_name, character_name, seiyuu) VALUES (%s, %s, %s, %s)",
    characters_data
)
db.commit()

cursor.close()
