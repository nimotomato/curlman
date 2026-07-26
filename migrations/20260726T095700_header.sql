CREATE TABLE IF NOT EXISTS header (
    id INTEGER primary key,
    request_id INTEGER foreign key REFERENCES request(id),
    created_at TEXT NOT NULL DEFAULT (CURRENT_TIMESTAMP),
    updated_at TEXT NOT NULL DEFAULT (CURRENT_TIMESTAMP),
    deleted_at TEXT,
    status_code integer NOT NULL,
    body text,
    response_time integer NOT NULL
);