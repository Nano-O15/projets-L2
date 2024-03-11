use rouille::{Response, Request};

use serde::Serialize;

use regex::Regex;

use crate::database::models::{Seiyuus, Seiyuu};

#[derive(Serialize)]
struct Res {
    error: bool,
    message: String
}

#[derive(Serialize)]
pub struct SeiyuuCharacters {
    pub seyiuu_id: i64,
    pub seiyuu_name: String,
    pub characters: Vec<String>
}

pub fn new_seiyuu_characters_struct(res: Vec<(i64, String, String)>) -> Result<SeiyuuCharacters, String> {
    if res.len() == 0 {
        return Err(String::from("The seiyuu you are looking for could not be found"));
    }

    let mut characters: Vec<String> = vec![];

    let seyiuu_id = res.clone()[0].0; // anime_id
    let seiyuu_name = &res.clone()[0].1; // anime_name

    for r in res.clone() {
        characters.push(r.2); // character_name
    }

    Ok(
        SeiyuuCharacters {
            seyiuu_id: seyiuu_id,
            seiyuu_name: seiyuu_name.to_string(),
            characters: characters
        }
    )
}

pub fn seiyuus_routes(request: &Request, db: &mut crate::database::Database, api_key_type: String) -> Response {
    router!(request,
            
        (GET) (/seiyuus/id/{id: i64}) => {

            let res = db.get_seiyuu_by_id(id);

            match res {
                Ok(res) => match res {
                    Some(seiyuu) => Response::json(&seiyuu),
                    None => Response::empty_404()
                },
                Err(_) => Response::text("There was an error retrieving the seiyuu").with_status_code(500),
            }

        },

        (GET) (/seiyuus/name/{id: String}) => {
            let re = Regex::new(r"^[a-zA-Z ]*$").expect("Regex failed for seiyuus");
            
            if !re.is_match(&id) {
                return Response::empty_400();
            } else if id.len() < 2 {
                return Response::text("You must enter at least 2 chars").with_status_code(400);
            } else if id.len() > 30 {
                return Response::text("You must enter no more than 30 chars").with_status_code(413);
            }

            let res = db.get_seiyuus_by_name(id);

            match res {
                Ok(res) => match res {
                    Some(seiyuus) => Response::json(&seiyuus),
                    None => Response::empty_404()
                },
                Err(_) => Response::text("There was an error retrieving the seiyuus").with_status_code(500)
            }
        },

        (GET) (/seiyuus/name/{name: String}/characters) => {
            let re = Regex::new(r"^[a-zA-Z ]*$").expect("Regex failed for anime");

            if !re.is_match(&name) {
                return Response::empty_400();
            } else if name.len() < 2 {
                return Response::text("You must enter at least 2 chars").with_status_code(400);
            } else if name.len() > 30 {
                return Response::text("You must enter no more than 30 chars").with_status_code(413);
            }

            let res = db.get_characters_by_seiyuu(name);
            match res {
                Ok(res) => match res {
                    Some(anime_characters) => match new_seiyuu_characters_struct(anime_characters) {
                        Ok(anime_characters) => Response::json(&anime_characters),
                        Err(e) => Response::text(e).with_status_code(404)
                    },
                    None => Response::empty_404()
                },
                Err(_) => Response::text("There was an error retrieving the characters from the anime name").with_status_code(500),
            }
        },

        (POST) (/seiyuus/new) => {
            if api_key_type != "admin" {
                return Response::text("").with_status_code(401)
            }

            let seiyuus: Seiyuus = try_or_400!(rouille::input::json_input(&request));

            let res = db.add_seiyuus(seiyuus);

            match res {
                Ok(_) => Response::text("Seiyuus were added").with_status_code(201),
                _ => Response::text("There was a problem adding the seiyuus").with_status_code(500)
            }
        },

        (PUT) (/seiyuus/update) => {
            if api_key_type != "admin" {
                return Response::text("").with_status_code(401)
            }

            let seiyuu: Seiyuu = try_or_400!(rouille::input::json_input(&request));

            let res = db.update_seiyuu(seiyuu);

            match res {
                Ok(_) => Response::text("Seiyuu was updated"),
                _ => Response::text("There was a problem adding the seiyuu").with_status_code(500)
            }
        },

        _ => Response::empty_404()
    )
}