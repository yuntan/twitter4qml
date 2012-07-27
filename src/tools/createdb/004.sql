CREATE TABLE IF NOT EXISTS User (
    user_id INTEGER PRIMARY KEY AUTOINCREMENT
    , created_at TEXT
    , description TEXT
    , favourites_count INTEGER
    , follow_request_sent BOOLEAN
    , followers_count INTEGER
    , following BOOLEAN
    , friends_count INTEGER
    , geo_enabled BOOLEAN
    , id_str TEXT NOT NULL UNIQUE
    , is_translator BOOLEAN
    , lang TEXT
    , listed_count INTEGER
    , location TEXT
    , name TEXT
    , notifications BOOLEAN
    , profile_image_url TEXT
    , protected BOOLEAN
    , screen_name TEXT NOT NULL
    , show_all_inline_media BOOLEAN
    , statuses_count INTEGER
    , time_zone TEXT
    , url TEXT
    , utc_offset INTEGER
    , verified BOOLEAN
);
