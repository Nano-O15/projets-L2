pub mod models;

use mysql::*;
use mysql::prelude::*;

pub struct Database {
    conn: PooledConn
}

impl Database {
    pub fn new(url: String) -> Result<Database> {
        let opts = Opts::from_url(&url)?;
        let pool = Pool::new(opts)?;
        let conn = pool.get_conn()?;

        Ok(Database {
            conn
        })
    }

    pub fn get_character_by_id(&mut self, id: i64) -> Result<Option<models::Character>> {
        let stmt = self.conn.prep("SELECT id, anime_id, anime_name, character_name, seiyuu from characters_list where id=:id")?;
        let res = self.conn.exec_first(&stmt,
            params!{
                "id" => id
            }
        )?;

        Ok(
            res.map(|(id, anime_id, anime_name, character_name, seiyuu)| models::Character {
                id: id,
                anime_id: anime_id,
                anime_name: anime_name,
                character_name: character_name,
                seiyuu: seiyuu,
            })
        )
    }

    pub fn get_character_by_name(&mut self, name: String) -> Result<Option<models::Characters>> {
        let stmt = self.conn.prep("select * from characters_list WHERE character_name LIKE Concat('%',:name,'%')")?;
        let res: Vec<(Option<i64>, i64, String, String, String)> = self.conn.exec(&stmt, params! { "name" => name })?;
        let mut characters: Vec<models::Character> = vec![];

        for r in res {
            characters.push(models::Character{
                id: r.0,
                anime_id: r.1,
                anime_name: r.2,
                character_name: r.3,
                seiyuu: r.4
            });
        }

        Ok(Some(models::Characters {
            characters: characters
        }))
    }
    
    pub fn get_seiyuu_by_id(&mut self, id: i64) -> Result<Option<models::Seiyuu>> {
        let stmt = self.conn.prep("SELECT id, name, gender, born_date from seiyuu where id=:id")?;
        let res = self.conn.exec_first(&stmt,
            params!{
                "id" => id
            }
        )?;

        Ok(
            res.map(|(id, name, gender, born_date)| models::Seiyuu {
                id: id,
                name: name,
                gender: gender,
                born_date: born_date,
            })
        )
    }

    pub fn get_seiyuus_by_name(&mut self, name: String) -> Result<Option<models::Seiyuus>> {
        let stmt = self.conn.prep("select * from seiyuu WHERE name LIKE Concat('%',:name,'%')")?;
        let res: Vec<(Option<i64>, String, String, Option<String>)> = self.conn.exec(&stmt, params! { "name" => name })?;
        let mut seiyuus: Vec<models::Seiyuu> = vec![];

        for r in res {
            seiyuus.push(models::Seiyuu{
                id: r.0,
                name: r.1,
                gender: r.2,
                born_date: r.3,
            });
        }

        Ok(Some(models::Seiyuus {
            seiyuus: seiyuus
        }))
    }

    pub fn get_anime_by_id(&mut self, id: i64) -> Result<Option<models::Anime>> {
        let stmt = self.conn.prep("SELECT id, anime, air_date from anime_list where id=:id")?;
        let res = self.conn.exec_first(&stmt,
            params!{
                "id" => id
            }
        )?;
        
        Ok(res.map(|(id, anime, air_date)| models::Anime {
            id: id,
            anime: anime,
            air_date: air_date,
        }))
    }

    pub fn get_animes_by_name(&mut self, name: String) -> std::result::Result<Option<models::Animes>, mysql::error::Error> {
        let stmt = self.conn.prep("select * from anime_list WHERE anime LIKE Concat('%',:anime,'%')")?;
        let res: Vec<(Option<i64>, String, Option<String>)> = self.conn.exec(&stmt, params! { "anime" => name })?;

        let mut animes: Vec<models::Anime> = vec![];

        for r in res {
            animes.push(models::Anime{
                id: r.0,
                anime: r.1,
                air_date: r.2
            });
        }

        Ok(Some(models::Animes {
            animes: animes
        }))
    }

    pub fn get_characters_by_anime_name(&mut self, name: String) -> Result<Option<Vec<(i64, String, String)>>> {
        let stmt = self.conn.prep("SELECT anime_id, anime_name, character_name FROM characters_list WHERE anime_name = :name")?;
        let res: Vec<(i64, String, String)> = self.conn.exec(&stmt, params! { "name" => name })?;

        Ok(Some(res))
    }

    pub fn get_characters_by_seiyuu(&mut self, name: String) -> Result<Option<Vec<(i64, String, String)>>> {
        let stmt = self.conn.prep(
            "SELECT seiyuu.id, seiyuu.name, characters_list.character_name FROM characters_list INNER JOIN seiyuu ON characters_list.seiyuu = seiyuu.name WHERE seiyuu.name = :name"
        )?;
        let res: Vec<(i64, String, String)> = self.conn.exec(&stmt, params! { "name" => name })?;

        Ok(Some(res))
    }

    pub fn add_characters(&mut self, characters: models::Characters) -> Result<Option<String>> {
        self.conn.exec_batch(
            r"INSERT INTO characters_list (anime_id, anime_name, character_name, seiyuu)
              VALUES (:anime_id, :anime_name, :character_name, :seiyuu)",
            characters.characters.iter().map(|character| params! {
                "anime_id" => character.anime_id,
                "anime_name" => &character.anime_name,
                "character_name" => &character.character_name,
                "seiyuu" => &character.seiyuu,
            })
        )?;

        Ok(Some(String::from("Characters added")))
    }

    pub fn update_character(&mut self, character: models::Character) -> Result<Option<String>> {
        let stmt = self.conn.prep(
            r"UPDATE characters_list SET anime_id = :anime_id, anime_name = :anime_name, character_name = :character_name, seiyuu = :seiyuu
              WHERE id = :id"
        )?;
        self.conn.exec_drop(&stmt,
            params! {
                "id" => character.id,
                "anime_id" => character.anime_id,
                "anime_name" => character.anime_name,
                "character_name" => character.character_name,
                "seiyuu" => character.seiyuu
            }
        )?;

        Ok(Some(String::from("Character updated")))
    }

    pub fn add_animes(&mut self, animes: models::Animes) -> Result<Option<String>> {
        self.conn.exec_batch(
            r"INSERT INTO anime_list (anime, air_date)
              VALUES (:anime, :air_date)",
              animes.animes.iter().map(|anime| params! {
                "anime" => &anime.anime,
                "air_date" => &anime.air_date
            })
        )?;

        Ok(Some(String::from("Animes added")))
    }

    pub fn update_anime(&mut self, anime: models::Anime) -> Result<Option<String>> {
        let stmt = self.conn.prep(
            r"UPDATE anime_list SET anime = :anime, air_date = :air_date
              WHERE id = :id"
        )?;
        self.conn.exec_drop(&stmt,
            params! {
                "id" => anime.id,
                "anime" => &anime.anime,
                "air_date" => &anime.air_date
            }
        )?;

        Ok(Some(String::from("Anime updated")))
    }

    pub fn add_seiyuus(&mut self, seiyuus: models::Seiyuus) -> Result<Option<String>> {
        self.conn.exec_batch(
            r"INSERT INTO seiyuu (name, gender, born_date)
              VALUES (:name, :gender, :born_date)",
              seiyuus.seiyuus.iter().map(|seiyuu| params! {
                "name" => &seiyuu.name,
                "gender" => &seiyuu.gender,
                "born_date" => &seiyuu.born_date
            })
        )?;

        Ok(Some(String::from("Seiyuus added")))
    }

    pub fn update_seiyuu(&mut self, seiyuu: models::Seiyuu) -> Result<Option<String>> {
        let stmt = self.conn.prep(
            r"UPDATE seiyuu SET name = :name, gender = :gender, born_date = :born_date
              WHERE id = :id"
        )?;
        self.conn.exec_drop(&stmt,
            params! {
                "id" => seiyuu.id,
                "name" => &seiyuu.name,
                "gender" => &seiyuu.gender,
                "born_date" => &seiyuu.born_date
            }
        )?;

        Ok(Some(String::from("Seiyuu updated")))
    }
}
