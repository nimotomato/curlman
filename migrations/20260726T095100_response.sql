CREATE TABLE IF NOT EXISTS response (
    id INTEGER primary key,
    request_id INTEGER NOT NULL,
    created_at TEXT NOT NULL DEFAULT (CURRENT_TIMESTAMP),
    updated_at TEXT NOT NULL DEFAULT (CURRENT_TIMESTAMP),
    deleted_at TEXT,
    status_code integer NOT NULL,
    body text,
    response_time integer NOT NULL,

    FOREIGN KEY request_id REFERENES request(id)
);
