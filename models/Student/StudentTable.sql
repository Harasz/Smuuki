CREATE TABLE IF NOT EXISTS `students` (
            `id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
            `name` TEXT NOT NULL,
            `surname` TEXT NOT NULL,
            `group` INTEGER NOT NULL,
            `parentName` TEXT,
            `contact` TEXT,
            FOREIGN KEY ("group") REFERENCES groups(id)
        )
