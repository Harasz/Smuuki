CREATE TABLE IF NOT EXISTS `groups` (
            `id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
            `name` TEXT NOT NULL UNIQUE,
            `teacher` TEXT NOT NULL,
            `subject` INTEGER NOT NULL
        )