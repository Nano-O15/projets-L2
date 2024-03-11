use std::default::Default;

use dotenv::dotenv;
use std::env;

pub struct Config {
    pub db_user: String,
    pub db_pass: String,
    pub db_name: String,

    pub host: String,
    pub port: String
}

impl Default for Config {
    fn default() -> Self {
        dotenv().ok();

        return Config {
            db_user: env::var("MYSQL_USER").expect("Couldn't load the MYSQL_USER environment variable"),
            db_pass: env::var("MYSQL_PASS").expect("Couldn't load the MYSQL_PASS environment variable"),
            db_name: env::var("DB_NAME").expect("Couldn't load the DB_NAME environment variable"),

            host: env::var("HOST").expect("Couldn't load the HOST environment variable"),
            port: env::var("PORT").expect("Couldn't load the PORT environment variable")
        }
    }
}