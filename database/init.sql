DROP DATABASE IF EXISTS CHAT_SERVICE;
CREATE DATABASE CHAT_SERVICE;
USE CHAT_SERVICE;

CREATE TABLE IF NOT EXISTS USER 
(
    username VARCHAR(100) PRIMARY KEY,
    name VARCHAR(100),
    password VARCHAR(256) NOT NULL,
    is_deleted BOOLEAN DEFAULT false,
    color_id INTEGER DEFAULT 0
);

CREATE TABLE IF NOT EXISTS ROOM 
(
    id INTEGER NOT NULL PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(100),
    count INTEGER NOT NULL,
    is_deleted BOOLEAN DEFAULT false,
    is_chat_room BOOLEAN DEFAULT false,
	admin VARCHAR(100) NOT NULL	
);
ALTER TABLE ROOM ADD CONSTRAINT FK_admin FOREIGN KEY (admin) REFERENCES USER(username);
CREATE TABLE IF NOT EXISTS PARTICIPATION
(
    username VARCHAR(100) NOT NULL,
    room_id INTEGER NOT NULL,
    PRIMARY KEY (username, room_id),
    FOREIGN KEY (username) REFERENCES USER(username),
    FOREIGN KEY (room_id) REFERENCES ROOM(id)
);

CREATE TABLE IF NOT EXISTS MESSAGE
(
    id INTEGER NOT NULL PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(100) NOT NULL,
    room_id INTEGER NOT NULL,
    content VARCHAR(1000) NOT NULL, 
    time DATETIME,  
    FOREIGN KEY (username) REFERENCES USER(username),
    FOREIGN KEY (room_id) REFERENCES ROOM(id),
    is_deleted BOOLEAN DEFAULT false
);

SET GLOBAL log_bin_trust_function_creators = 1;

DROP FUNCTION IF EXISTS func_create_room_1_1;
DELIMITER //
CREATE FUNCTION func_create_room_1_1(user_1 varchar(100), user_2 varchar(100))  
RETURNS INT
BEGIN
    DECLARE new_room_id INTEGER;
    INSERT INTO ROOM(name, count, admin) VALUES(CONCAT(user_1, '#', user_2), 0, user_1);
    SELECT id
    INTO new_room_id
    FROM ROOM
    WHERE name = CONCAT(user_1, '#', user_2);

    INSERT INTO PARTICIPATION VALUES(user_1 , new_room_id);
    INSERT INTO PARTICIPATION VALUES(user_2 , new_room_id);

    RETURN new_room_id;
END //
DELIMITER ;

INSERT INTO USER(username, name, password, color_id) VALUES ('tcl', 'Trinh Cong Luan', SHA2('1', 256), 1);
INSERT INTO USER(username, name, password, color_id) VALUES ('nhp', 'Nham Hong Phuc', SHA2('1', 256), 3);
INSERT INTO USER(username, name, password, color_id) VALUES ('pth', 'Phan Trong Hau', SHA2('1', 256), 4);
INSERT INTO USER(username, name, password, color_id) VALUES ('nqk', 'Nguyen Quoc Khanh', SHA2('1', 256), 5);
INSERT INTO USER(username, name, password, color_id) VALUES ('ldv', 'Luu Duc Vu', SHA2('1', 256), 0);
INSERT INTO USER(username, name, password, color_id) VALUES ('nhkd', 'Nguyen Huynh Khanh Duy', SHA2('1', 256), 1);
INSERT INTO USER(username, name, password, color_id) VALUES ('kl', 'Khang Lam', SHA2('1', 256), 2);

DROP TRIGGER IF EXISTS after_participation_insert;
DELIMITER $$
CREATE TRIGGER after_participation_insert
AFTER INSERT ON PARTICIPATION
FOR EACH ROW
BEGIN
UPDATE ROOM
SET count = (SELECT COUNT(room_id) FROM PARTICIPATION WHERE room_id = NEW.room_id)
WHERE id = NEW.room_id;
END$$
DELIMITER ;

DROP TRIGGER IF EXISTS after_participation_delete;
DELIMITER $$
CREATE TRIGGER after_participation_delete
AFTER DELETE ON PARTICIPATION
FOR EACH ROW
BEGIN
UPDATE ROOM
SET count = (SELECT COUNT(room_id) FROM PARTICIPATION WHERE room_id = OLD.room_id)
WHERE id = OLD.room_id;
END$$
DELIMITER ;

INSERT INTO ROOM(name, count, admin) VALUES('Default', 0, 'tcl');
INSERT INTO ROOM(name, count, admin, is_chat_room) VALUES('Oxi', 0, 'pth', true);
INSERT INTO ROOM(name, count, admin, is_chat_room) VALUES('Test', 0, 'nhkd', true);

INSERT INTO PARTICIPATION VALUES('tcl',1);
INSERT INTO PARTICIPATION VALUES('nhp',1);
INSERT INTO PARTICIPATION VALUES('pth',2);
INSERT INTO PARTICIPATION VALUES('nqk',2);
INSERT INTO PARTICIPATION VALUES('ldv',2);
INSERT INTO PARTICIPATION VALUES('nhkd',3);
INSERT INTO PARTICIPATION VALUES('tcl',3);
INSERT INTO PARTICIPATION VALUES('kl',3);
INSERT INTO PARTICIPATION VALUES('nhp',3);

INSERT INTO MESSAGE(username, room_id, content, time) VALUES('tcl', 1, 'Hello', now());
INSERT INTO MESSAGE(username, room_id, content, time) VALUES('nhp', 1, 'Hi', now());
INSERT INTO MESSAGE(username, room_id, content, time) VALUES('nqk', 2, 'Dek', now());
