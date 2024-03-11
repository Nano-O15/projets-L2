use serde::{Serialize, Deserialize};

#[derive(Serialize, Deserialize)]
pub struct Character {
    pub id: Option<i64>,
    pub anime_id: i64,
    pub anime_name: String,
    pub character_name: String,
    pub seiyuu: String,
}

#[derive(Serialize, Deserialize)]
pub struct Characters {
    pub characters: Vec<Character>
}

#[derive(Serialize, Deserialize)]
pub struct Seiyuu {
    pub id: Option<i64>,
    pub name: String,
    pub gender: String,
    pub born_date: Option<String>,
}

#[derive(Serialize, Deserialize)]
pub struct Seiyuus {
    pub seiyuus: Vec<Seiyuu>
}

#[derive(Serialize, Deserialize)]
pub struct Anime {
    pub id: Option<i64>,
    pub anime: String,
    pub air_date: Option<String>,
}

#[derive(Serialize, Deserialize)]
pub struct Animes {
    pub animes: Vec<Anime>
}

#[derive(Serialize)]
pub struct AnimeCharacters {
    pub anime_id: i64,
    pub anime_name: String,
    pub characters: Vec<String>
}
