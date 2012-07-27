CREATE TABLE IF NOT EXISTS Place (
    place_id INTEGER PRIMARY KEY AUTOINCREMENT
    , type TEXT NOT NULL
    , coordinates_id INTEGER NOT NULL
    , country TEXT
    , country_code TEXT
    , full_name TEXT
    , id TEXT
    , name TEXT
    , place_type TEXT
    , url TEXT
    , FOREIGN KEY(coordinates_id) REFERENCES Coordinates(coordinates_id)
);
