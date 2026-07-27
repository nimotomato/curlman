CREATE TABLE IF NOT EXISTS response (
    id INTEGER PRIMARY KEY,
    request_id INTEGER NOT NULL,
    created_at TEXT NOT NULL DEFAULT (CURRENT_TIMESTAMP),
    updated_at TEXT NOT NULL DEFAULT (CURRENT_TIMESTAMP),
    deleted_at TEXT,
    status_code INTEGER NOT NULL,
    body TEXT,
    response_time INTEGER NOT NULL,
    FOREIGN KEY (request_id) REFERENCES request(id)
);