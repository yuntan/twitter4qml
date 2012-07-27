CREATE TABLE IF NOT EXISTS Tweet (
    tweet_id INTEGER PRIMARY KEY AUTOINCREMENT
    , type TEXT NOT NULL
    , coordinates INTERGER
    , created_at TEXT NOT NULL
    , favorited BOOLEAN DEFAULT false
    , geo INTEGER
    , id_str TEXT NOT NULL UNIQUE
    , in_reply_to_status_id TEXT
    , place INTEGER
    , possibly_sensitive BOOLEAN
    , retweet_count INTEGER
    , retweeted BOOLEAN
    , retweeted_status INTEGER
    , source TEXT
    , text TEXT NOT NULL
    , truncated BOOLEAN
    , from_user INTEGER
    , to_user INTEGER
    , FOREIGN KEY(coordinates) REFERENCES Coordinates(coordinates_id)
    , FOREIGN KEY(place) REFERENCES Place(place_id)
    , FOREIGN KEY(from_user) REFERENCES User(user_id)
    , FOREIGN KEY(to_user) REFERENCES User(user_id)
);
