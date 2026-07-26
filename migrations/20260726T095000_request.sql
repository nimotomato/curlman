CREATE TABLE IF NOT EXISTS request (
    id INTEGER primary key,
    created_at TEXT NOT NULL DEFAULT (CURRENT_TIMESTAMP),
    updated_at TEXT NOT NULL DEFAULT (CURRENT_TIMESTAMP),
    deleted_at TEXT,
    method TEXT NOT NULL DEFAULT 'GET'
        CHECK(method IN ('GET', 'POST', 'PATCH', 'DELETE', 'CONNECT', 'HEAD', 'OPTIONS')),
    body text
);