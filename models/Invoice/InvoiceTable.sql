CREATE TABLE IF NOT EXISTS `invoices` (
            `id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
            `studentId` INTEGER NOT NULL,
            `desc` TEXT,
            `paidAmount` TEXT NOT NULL,
            `paidUntil` TEXT NOT NULL,
            FOREIGN KEY ("studentId") REFERENCES students(id)
        )