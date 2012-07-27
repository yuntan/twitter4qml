CREATE TABLE IF NOT EXISTS Coordinate (
    coordinates_id INTEGER KEY NOT NULL
    , sequence INTEGER NOT NULL DEFAULT 0
    , x NUMBER NOT NULL
    , y NUMBER NOT NULL
    , FOREIGN KEY(coordinates_id) REFERENCES Coordinates(coordinates_id) ON DELETE CASCADE
);
