"""
Personne ne semble avoir fait de scripts pour convertir
ça en base de données, donc on l'a fait.
"""
import mysql.connector as mysql

db = mysql.connect(
    host = "localhost",
    user = "user",
    password= "password",
    database="anime_voice"
)

cursor = db.cursor()

anime_db_file = "../misc/seiyuu-database.txt"

seiyuu_data = list()


with open(anime_db_file, "r") as f:
    lines = f.read().split("\n\n")

for line in range(len(lines)):
    seiyuu_block = lines[line]
    seiyuu_infos = seiyuu_block.split("\n")

    seiyuu_name = seiyuu_infos[0] # c'est forcément le premier élément
    seiyuu_born_date = None

    seiyuu_name_list = seiyuu_name.split(" ")
    if "(" in seiyuu_name_list[-1]:
        del seiyuu_name_list[-1]
    seiyuu_name = " ".join(seiyuu_name_list)

    # Malheureusement ces 2 là n'existe pas forcément
    seiyuu_gender = seiyuu_infos[1] if len(seiyuu_infos) > 1 else None

    if "/*" in seiyuu_gender:
        seiyuu_gender = seiyuu_gender.replace("/*", "").replace("*/", "").strip()

    if len(seiyuu_infos) > 2:
        seiyuu_born_date = seiyuu_infos[2] if len(seiyuu_infos) > 2 else None
        if "/*" in seiyuu_born_date:
            seiyuu_born_date = seiyuu_born_date.replace("/*", "").replace("*/", "").strip()

    print(f"{seiyuu_name} - {seiyuu_gender} - {seiyuu_born_date}")

    seiyuu_data.append((seiyuu_name, seiyuu_gender, seiyuu_born_date))


cursor.executemany("INSERT INTO seiyuu (name, gender, born_date) VALUES (%s, %s, %s)", seiyuu_data)
db.commit()

cursor.close()
