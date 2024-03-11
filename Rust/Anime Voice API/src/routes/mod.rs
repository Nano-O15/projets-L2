mod characters;
mod seiyuus;
mod animes;

extern crate serde_json;

use serde::Deserialize;

use std::error::Error;
use std::fs::File;
use std::io::BufReader;

use rouille::{Response, Request};

use regex::Regex;

#[derive(Deserialize, Debug)]
struct ApiKeys {
    basic_keys: Vec<String>,
    admin_keys: Vec<String>
}

fn read_api_keys_from_file(path: &str) -> Result<ApiKeys, Box<dyn Error>> {
    let file = File::open(path)?;
    let reader = BufReader::new(file);
  
    let api_keys = serde_json::from_reader(reader)?;
  
    Ok(api_keys)
  }

pub fn handle_routes(request: &Request, db: &mut crate::database::Database) -> Response {
    let allowed_http_methods = vec!["GET", "POST", "PUT", "DELETE"];
    let access_token = request.header("x-access-token").unwrap_or("No access token");
    let re = Regex::new(r"^[a-zA-Z0-9_]*$").expect("Regex failed for x-access-token");

    let api_key_type: String;

    if access_token == "No access token" {
        return Response::text("Your API Key is missing").with_status_code(401)
    } else if !re.is_match(&access_token) || access_token.len() != 32 {
        return Response::empty_400()
    }

    // the error should never occurs hence why we stop processing in case it happens
    let api_keys = read_api_keys_from_file("./src/api_keys.json").expect("Problem loading api keys");

    let route: Vec<String> = request.url().split("/").map(str::to_string).collect();
    
    if api_keys.basic_keys.contains(&String::from(access_token)) {
        api_key_type = String::from("basic");
    } else if api_keys.admin_keys.contains(&String::from(access_token)) {
        api_key_type = String::from("admin");
    } else {
        return Response::text("Your api key could not be found").with_status_code(401)
    }

    if !allowed_http_methods.contains(&request.method()) {
        return Response::text("").with_status_code(405) // not allowed
    } else if route[1] == "characters" {
        return characters::characters_routes(request, db, api_key_type);
    } else if route[1] == "seiyuus"{
        return seiyuus::seiyuus_routes(request, db, api_key_type);
    } else if route[1] == "animes" {
        return animes::animes_routes(request, db, api_key_type);
    }

    Response::empty_404()
}
