use rouille::{Response, Request};

use serde::Serialize;

use regex::Regex;

use crate::database::models::{AnimeCharacters, Animes, Anime};

#[derive(Serialize)]
struct Res {
    error: bool,
    message: String
}

pub fn new_anime_characters_struct(res: Vec<(i64, String, String)>) -> Result<AnimeCharacters, String> {
    if res.len() == 0 {
        return Err(String::from("No anime was found"));
    }

    let mut characters: Vec<String> = vec![];

    let anime_id = res.clone()[0].0; // anime_id
    let anime_name = &res.clone()[0].1; // anime_name

    for r in res.clone() {
        characters.push(r.2); // character_name
    }

    Ok(
        AnimeCharacters {
            anime_id: anime_id,
            anime_name: anime_name.to_string(),
            characters: characters
        }
    )
}

pub fn animes_routes(request: &Request, db: &mut crate::database::Database, api_key_type: String) -> Response {
    router!(request,
            
        (GET) (/animes/id/{id: i64}) => {

            let res = db.get_anime_by_id(id);

            match res {
                Ok(res) => match res {
                    Some(anime) => Response::json(&anime),
                    None => Response::empty_404()
                },
                Err(_) => Response::text("There was an error retrieving the anime").with_status_code(500),
            }

        },

        (GET) (/animes/name/{id: String}) => {
            let re = Regex::new(r"^[a-zA-Z ]*$").expect("Regex failed for anime");

            if !re.is_match(&id) {
                return Response::empty_400();
            } else if id.len() < 2 {
                return Response::text("You must enter at least 2 chars").with_status_code(400);
            } else if id.len() > 30 {
                return Response::text("You must enter no more than 30 chars").with_status_code(413);
            }

            let res = db.get_animes_by_name(id);
            
            match res {
                Ok(res) => match res {
                    Some(animes) => Response::json(&animes),
                    None => Response::empty_404()
                },
                Err(_) => Response::text("There was an error retrieving the animes").with_status_code(500),
            }
        },

        (GET) (/animes/name/{name: String}/characters) => {
            let re = Regex::new(r"^[a-zA-Z ]*$").expect("Regex failed for anime");

            if !re.is_match(&name) {
                return Response::empty_400();
            } else if name.len() < 2 {
                return Response::text("You must enter at least 2 chars").with_status_code(400);
            } else if name.len() > 30 {
                return Response::text("You must enter no more than 30 chars").with_status_code(413);
            }

            let res = db.get_characters_by_anime_name(name);
            match res {
                Ok(res) => match res {
                    Some(anime_characters) => match new_anime_characters_struct(anime_characters) {
                        Ok(anime_characters) => Response::json(&anime_characters),
                        Err(e) => Response::text(e).with_status_code(404)
                    },
                    None => Response::empty_404()
                },
                Err(_) => Response::text("There was an error retrieving the characters from the anime name").with_status_code(500),
            }
        },

        (POST) (/animes/new) => {
            if api_key_type != "admin" {
                return Response::text("").with_status_code(401)
            }

            let animes: Animes = try_or_400!(rouille::input::json_input(&request));

            let res = db.add_animes(animes);

            match res {
                Ok(_) => Response::text("Animes were added").with_status_code(201),
                _ => Response::text("There was a problem adding the animes").with_status_code(500)
            }
        },

        (PUT) (/animes/update) => {
            if api_key_type != "admin" {
                return Response::text("").with_status_code(401)
            }

            let anime: Anime = try_or_400!(rouille::input::json_input(&request));

            let res = db.update_anime(anime);

            match res {
                Ok(_) => Response::text("Anime was updated"),
                _ => Response::text("There was a problem adding the anime").with_status_code(500)
            }
        },

        _ => Response::empty_404()
    )
}