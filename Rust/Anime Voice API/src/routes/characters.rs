use rouille::{Response, Request};

use serde::Serialize;

use regex::Regex;

use crate::database::models::{Character, Characters};

#[derive(Serialize)]
struct Res {
    error: bool,
    message: String
}

pub fn characters_routes(request: &Request, db: &mut crate::database::Database, api_key_type: String) -> Response {

    router!(request,
            
        (GET) (/characters/id/{id: i64}) => {

            let res = db.get_character_by_id(id);

            match res {
                Ok(res) => match res {
                    Some(character) => Response::json(&character),
                    None => Response::empty_404()
                },
                Err(_) => Response::text("There was an error retrieving the character").with_status_code(500),
            }

        },

        (GET) (/characters/name/{id: String}) => {
            let re = Regex::new(r"^[a-zA-Z ]*$").expect("Regex failed for characters");

            if !re.is_match(&id) {
                return Response::empty_400();
            } else if id.len() < 2 {
                return Response::text("You must enter at least 2 chars").with_status_code(400);
            } else if id.len() > 30 {
                return Response::text("You must enter no more than 30 chars").with_status_code(413);
            }

            let res = db.get_character_by_name(id);

            match res {
                Ok(res) => match res {
                    Some(characters) => Response::json(&characters),
                    None => Response::empty_404()
                },
                Err(_) => Response::text("There was an error retrieving the characters").with_status_code(500)
            }
        },

        (POST) (/characters/new) => {
            if api_key_type != "admin" {
                return Response::text("").with_status_code(401)
            }

            let characters: Characters = try_or_400!(rouille::input::json_input(&request));

            let res = db.add_characters(characters);

            match res {
                Ok(_) => Response::text("Characters were added").with_status_code(201),
                _ => Response::text("There was a problem adding the characters").with_status_code(500)
            }
        },

        (PUT) (/characters/update) => {
            if api_key_type != "admin" {
                return Response::text("").with_status_code(401)
            }

            let character: Character = try_or_400!(rouille::input::json_input(&request));

            let res = db.update_character(character);

            match res {
                Ok(_) => Response::text("Character was updated"),
                _ => Response::text("There was a problem adding the character").with_status_code(500)
            }
        },

        _ => Response::empty_404()
    )
}