#![allow(unreachable_code)]
#[macro_use]

extern crate rouille;
extern crate serde;

mod config;
mod database;
mod routes;

use crate::routes::handle_routes;

use std::sync::{Arc, Mutex};

fn main() {
    let config = config::Config::default();

    let url = format!(
        "mysql://{}:{}@{}/{}", 
        config.db_user, config.db_pass, config.host, config.db_name
    );
    let db = {
        let db = database::Database::new(url);
        Arc::new(Mutex::new(db.expect("Failed to connect to database")))
    };

    let server_url = format!("{}:{}", config.host, config.port);
    
    println!("Now listening on {}", server_url);
    
    rouille::start_server(server_url, move |request| {        
        let mut db = db.lock().expect("Couldn't lock database");

        let response = handle_routes(&request, &mut db);

        response
    });
}
