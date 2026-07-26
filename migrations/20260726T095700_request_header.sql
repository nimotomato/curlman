CREATE TABLE IF NOT EXISTS request_header (
    id INTEGER primary key,
    request_id INTEGER NOT NULL,
    created_at TEXT NOT NULL DEFAULT (CURRENT_TIMESTAMP),
    updated_at TEXT NOT NULL DEFAULT (CURRENT_TIMESTAMP),
    deleted_at TEXT,
    key TEXT NOT NULL,
    value TEXT,

        FOREIGN KEY (request_id) REFERENCES request(id)

);