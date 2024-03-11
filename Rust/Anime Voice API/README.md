# Anime Voices 

Projet en Rust - Programmation Avancée L2B - 2021

# DESCRIPTION

Notre projet consiste en une API Rest sur le doublage d'animés. 
Son but est de permettre à l'utilisateur de retrouver différents animés, avec les personnages qui en font partie et leur doubleurs. 
Nous avons utilisé le framework web [rouille](https://github.com/tomaka/rouille).

Les autres dépendances utilisées :
``` 
mysql
serde 1.0
serde_json 1.0
dotenv 0.15.0
regex 1
```

# **Installation**

## Compiler et démarrer le programme
```
cargo run
```

## Préparer la base de données
 Créer une base de données `anime_voice` (par défaut) ou autre chose par préférence

 Utiliser le fichier .sql pour créer toutes les tables nécessaires
 
 Pour convertir les fichiers `misc/*.txt`, il faut éxecuter les fichies python qui se trouvent dans le dossiers `scripts`.
 
 Installer les librairies nécessaires avant l'éxécution des scripts de conversion
 
 ```
 pip install -r requirements.txt
 ```

Dans les scripts, il est impératif de remplacer `password = ""` par votre mot de passe qui vous sert de connexion à la base de donnée MySQL, il en est de même pour `user = "root"`

Exécuter les fichiers suivants

 ```
 python3 convert_anime_database.py
 ```
 ```
 python3 convert_seiyuu_database.py
 ```

## Préparer le fichier .env

Renommer le fichier `.env.exemple` en `.env` et modifier les variables d'environnement en fonction de votre installation de MySQL

Les variables d'environnement `HOST` et `PORT` ne nécessitent pas de changement

## Démarrer le serveur

Executer la commande

```
cargo run
```

Ou bien, si l'on veut du hot reload (permettant le rafraîchissement automatique du code et du serveur lors de la sauvegarde d'un fichier), installer `cargo-watch`
```
cargo install cargo-watch
```
Et démarrer le serveur de la sorte
```
cargo watch -x run
```
 

Il est impératif d'inclure le header `x-access-token` dans les requêtes afin de communiquer avec la base données et récupérer les données voulus. A contrario, le serveur renverra `Your API Key is missing`

## Géneration des clés API
Il suffit simplement de modifier le fichier `src/api_keys.json` pour ajouter / supprimer un nombre inifi de clés.

Il n'y a pour le moment aucune génération automatique.

# **REST API**

L'API REST est décrite ci-dessous.

## Récupérer un personnage spécifique (via son id)

### Requête

`GET /characters/id/{id}`

    curl -i -H "x-access-token: AlYt3tE9jdyt4i9NS11PT3QIS2ssVht5" http://localhost:8000/characters/id/1

### Réponse

    HTTP/1.1 200 OK
    Server: tiny-http (Rust)
    Date: Sun,  9 Jan 2022 21:13:54 GMT
    Content-Type: application/json; charset=utf-8
    Content-Length: 118

    {"id":1,"anime_id":1638,"anime_name":"Naruto","character_name":"Hatake Kakashi","seiyuu":"Kazuhiko Inoue"}

## Récupérer un personnage inexistant

### Requête

`GET /characters/id/{id}`

    curl -i -H "x-access-token: AlYt3tE9jdyt4i9NS11PT3QIS2ssVht5" http://localhost:8000/characters/id/999999

### Réponse
    HTTP/1.1 404 Not Found
    Server: tiny-http (Rust)
    Date: Sun,  9 Jan 2022 21:17:47 GMT
    Content-Length: 0

## Récupérer des personnages (via le nom)

### Requête

`GET /characters/name/{name}`

    curl -i -H "x-access-token: AlYt3tE9jdyt4i9NS11PT3QIS2ssVht5" http://localhost:8000/characters/name/naruto

### Réponse

    HTTP/1.1 200 OK
    Server: tiny-http (Rust)
    Date: Sun,  9 Jan 2022 21:42:53 GMT
    Content-Type: application/json; charset=utf-8
    Content-Length: 127

    {"characters":[{"id":21103,"anime_id":1638,"anime_name":"Naruto","character_name":"Uzumaki Naruto","seiyuu":"Takeuchi Junko"}]}

## Ajouter des personnages à la base de donnée (nécessite une clé admin)

### Requête

`POST /characters/new`

    curl -i -X POST http://localhost:8000/characters/new
    -H "content-type: application/json" -H "x-access-token: G2wlg9UPx8oF6QzTiJYI8ca2zwwEhLNs"
    -d '{"characters": [{ "anime_id": 1638, "anime_name": "Naruto",
            "character_name": "Hatake Kakashi","seiyuu": "Kazuhiko Inoue"}]}'

### Réponse

    HTTP/1.1 201 Created
    content-length: 21
    content-type: text/plain; charset=utf-8
    date: Sun,  9 Jan 2022 21:52:27 GMT
    server: tiny-http (Rust)

    Characters were added

## Modifier un personnage de la base de donnée (nécessite une clé admin)

### Requête

`PUT /characters/id/{id}`

    curl -i -X PUT http://localhost:8000/characters/update
    -H "content-type: application/json" -H "x-access-token: G2wlg9UPx8oF6QzTiJYI8ca2zwwEhLNs"
    -d '{ "id": 1, "anime_id": 1, "anime_name": "New anime name",
            "character_name": "New Character","seiyuu": "New Seiyuu"}'

### Réponse
    HTTP/1.1 200 OK
    content-length: 21
    content-type: text/plain; charset=utf-8
    date: Sun,  9 Jan 2022 21:57:31 GMT
    server: tiny-http (Rust)

    Character was updated

## Supprimer un personnage de la base de donnée (nécessite une clé admin)

    A venir


## Récupérer un animé spécifique (via son id)

### Requête

`GET /animes/id/{id}`

    curl -i -H "x-access-token: AlYt3tE9jdyt4i9NS11PT3QIS2ssVht5" http://localhost:8000/animes/id/1

### Réponse

    HTTP/1.1 200 OK
    content-length: 57
    content-type: application/json; charset=utf-8
    date: Sun,  9 Jan 2022 22:00:07 GMT
    server: tiny-http (Rust)

    {"id":500,"anime":"Digimon Adventure 02","air_date":null}

## Récupérer un animé inexistant

### Requête

`GET /animes/id/{id}`

    curl -i -H "x-access-token: AlYt3tE9jdyt4i9NS11PT3QIS2ssVht5" http://localhost:8000/animes/id/999999

### Réponse
    HTTP/1.1 404 Not Found
    Server: tiny-http (Rust)
    Date: Sun,  9 Jan 2022 21:17:47 GMT
    Content-Length: 0

## Récupérer des animés (via le nom)

### Requête

`GET /animes/name/{name}`

    curl -i -H "x-access-token: AlYt3tE9jdyt4i9NS11PT3QIS2ssVht5" http://localhost:8000/animes/name/naruto

### Réponse

    HTTP/1.1 200 OK
    content-length: 57
    content-type: application/json; charset=utf-8
    date: Sun,  9 Jan 2022 22:03:22 GMT
    server: tiny-http (Rust)

    {"animes":[{"id":1638,"anime":"Naruto","air_date":null}]}

## Récupérer les personnages d'un animé spécifique (via son nom)

### Requête

`GET /animes/name/{name}/characters`

    curl -i -H "x-access-token: AlYt3tE9jdyt4i9NS11PT3QIS2ssVht5" http://localhost:8000/animes/name/naruto/characters

### Réponse

    HTTP/1.1 200 OK
    content-length: 1755
    content-type: application/json; charset=utf-8
    date: Sun,  9 Jan 2022 22:04:19 GMT
    server: tiny-http (Rust)

    {"anime_id":1638,"anime_name":"Naruto","characters":["Uzumaki Naruto","Uchiha Sasuke","Haruno Sakura","Iruka","Mizuki", ...]}


## Ajouter des animés à la base de donnée (nécessite une clé admin)

### Requête

`POST /animes/new`

    curl -i -X POST http://localhost:8000/animes/new
    -H "content-type: application/json" -H "x-access-token: G2wlg9UPx8oF6QzTiJYI8ca2zwwEhLNs"
    -d '{"animes":[{"anime":"Naruto","air_date":"1999"},{"anime":"One Piece","air_date":"1999"},{"anime":"Dragon Ball","air_date":"1986"}]}'

### Réponse

    HTTP/1.1 201 Created
    content-length: 17
    content-type: text/plain; charset=utf-8
    date: Sun,  9 Jan 2022 22:08:28 GMT
    server: tiny-http (Rust)

    Animes were added

## Modifier un animé de la base de donnée (nécessite une clé admin)

### Requête

`PUT /animes/update`

    curl -i -X PUT http://localhost:8000/animes/update
    -H "content-type: application/json" -H "x-access-token: G2wlg9UPx8oF6QzTiJYI8ca2zwwEhLNs"
    -d '{"id": 1728, "anime":"Two Pieces","air_date":"1999"}'

### Réponse
    HTTP/1.1 200 OK
    content-length: 17
    content-type: text/plain; charset=utf-8
    date: Sun,  9 Jan 2022 22:12:30 GMT
    server: tiny-http (Rust)

    Anime was updated

## Supprimer un animé de la base de donnée (nécessite une clé admin)

    A venir



## Récupérer un seiyuu spécifique (via son id)

### Requête

`GET /seiyuus/id/{id}`

    curl -i -H "x-access-token: AlYt3tE9jdyt4i9NS11PT3QIS2ssVht5" http://localhost:8000/seiyuus/id/1

### Réponse

    HTTP/1.1 200 OK
    content-length: 82
    content-type: application/json; charset=utf-8
    date: Sun,  9 Jan 2022 22:13:57 GMT
    server: tiny-http (Rust)

    {"id":1,"name":"Abe Atsushi","gender":"M","born_date":"Born: 1981/03/25, Tochigi"}

## Récupérer un seiyuu inexistant

### Requête

`GET /seiyuus/id/{id}`

    curl -i -H "x-access-token: AlYt3tE9jdyt4i9NS11PT3QIS2ssVht5" http://localhost:8000/seiyuus/id/999999

### Réponse
    HTTP/1.1 404 Not Found
    Server: tiny-http (Rust)
    Date: Sun,  9 Jan 2022 21:17:47 GMT
    Content-Length: 0

## Récupérer des seiyuus (via un nom)

### Requête

`GET /seiyuus/name/{name}`

    curl -i -H "x-access-token: AlYt3tE9jdyt4i9NS11PT3QIS2ssVht5" http://localhost:8000/seiyuus/name/yamaguchi

### Réponse

    HTTP/1.1 200 OK
    content-length: 1036
    content-type: application/json; charset=utf-8
    date: Sun,  9 Jan 2022 22:15:03 GMT
    server: tiny-http (Rust)

    {"seiyuus":[{"id":2759,"name":"Yamaguchi Kappei","gender":"M","born_date":"Born: S40/05/23, Fukuoka, Fukuoka"},{"id":2760,"name":"Yamaguchi Katsuko","gender":"F","born_date":"Born: 1973/06/24, Tokyo"}, ...]}

## Récupérer les personnages d'un seiyuu spécifique (via son nom)

### Requête

`GET /seiyuus/name/{name}/characters`

    curl -i -H "x-access-token: AlYt3tE9jdyt4i9NS11PT3QIS2ssVht5" 'http://localhost:8000/seiyuus/name/Yamaguchi Kappei/characters'

### Réponse

    HTTP/1.1 200 OK
    content-length: 1318
    content-type: application/json; charset=utf-8
    date: Sun,  9 Jan 2022 22:28:13 GMT
    server: tiny-http (Rust)

    {"seyiuu_id":2759,"seiyuu_name":"Yamaguchi Kappei","characters":["Takuya","White Prince","Misaki Ryou","Virgil","Arslan","Toto","Inagaki Kappei","Kimiira","Yugo","Rattor","Aono Keita","Tohru","Shibuya","Shester","Kabuto Kouji","Michael","Higashikumaru Kentaro", ...]}

## Ajouter un seiyuu ou des seiyuus à la base de donnée (nécessite une clé admin)

### Requête

`POST /seiyuus/new`

    curl -i -X POST http://localhost:8000/seiyuus/new
    -H "content-type: application/json" -H "x-access-token: G2wlg9UPx8oF6QzTiJYI8ca2zwwEhLNs"
    -d '{"seiyuus":[{"name":"Abe Atsushi","gender":"M","born_date":"Born: 1981/03/25, Tochigi"}, {"name":"Abe Emika","gender":"F","born_date":"Born: ????/03/16, Hokkaidou"}, {"name":"Abe Kokoro","gender":"F","born_date":"Born: ????/11/27, Sapporo"}]}'

### Réponse

    HTTP/1.1 201 Created
    Server: tiny-http (Rust)
    Date: Mon, 10 Jan 2022 20:23:45 GMT
    Content-Type: text/plain; charset=utf-8
    Content-Length: 18

    Seiyuus were added

## Modifier un seiyuu de la base de donnée (nécessite une clé admin)

### Requête

`PUT /seiyuus/update`

    curl -i -X PUT http://localhost:8000/seiyuus/update
    -H "content-type: application/json" -H "x-access-token: G2wlg9UPx8oF6QzTiJYI8ca2zwwEhLNs"
    -d '{"id": 2, "name":"Abe Emika","gender":"F", "born_date":"Born: 1988/03/16, Hokkaidou"}'

### Réponse
    
    HTTP/1.1 200 OK
    Server: tiny-http (Rust)
    Date: Mon, 10 Jan 2022 20:29:28 GMT
    Content-Type: text/plain; charset=utf-8
    Content-Length: 18

    Seiyuu was updated

## Supprimer un seiyuu de la base de donnée (nécessite une clé admin)

    A venir
---

# **LIMITES DU PROJET**

* Pour le moment, il n'existe pas de route pour supprimer quoi que ce soit de la base de données.
* Cette REST API n'a pas de Rate Limit (TODO), quelqu'un de malicieux (ou pas) pourrait la spammer de requêtes.
* Pas de génération automatique des clés API
* Pas d'expiration pour les clés API
