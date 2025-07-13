CREATE TABLE PlacementDrive (
    Drive_id INT PRIMARY KEY,
    Pcompany_name VARCHAR(50),
    package DECIMAL(10,2),
    location VARCHAR(50)
);
CREATE TABLE Training (
    T_id INT PRIMARY KEY,
    Tcompany_name VARCHAR(50),
    T_Fee DECIMAL(10,2),
    T_year INT
);
CREATE TABLE Student (
    s_id INT PRIMARY KEY,
    Drive_id INT,
    T_id INT,
    s_name VARCHAR(50),
    CGPA DECIMAL(4,2),
    s_branch VARCHAR(20),
    S_dob DATE,
    FOREIGN KEY (Drive_id) REFERENCES PlacementDrive(Drive_id)
        ON DELETE CASCADE,
    FOREIGN KEY (T_id) REFERENCES Training(T_id)
        ON DELETE CASCADE
);
CREATE VIEW student_view AS SELECT  s.s_id,s.s_name,p.Pcompany_name, s.CGPA FROM Student s JOIN PlacementDrive p ON s.Drive_id =p.Drive_id;
CREATE INDEX idx_cgpa ON Student(CGPA);
INSERT INTO PlacementDrive (Drive_id, Pcompany_name, package, location) VALUES
(1, 'Google', 1200000, 'Bangalore'),
(2, 'Amazon', 1100000, 'Hyderabad'),
(3, 'Microsoft', 1150000, 'Noida'),
(4, 'Accenture', 600000, 'Pune'),
(5, 'IBM', 700000, 'Mumbai');

INSERT INTO Training (T_id, Tcompany_name, T_Fee, T_year) VALUES
(201, 'Scaler', 5000, 2023),
(202, 'GeeksforGeeks', 4000, 2022),
(203, 'GreatLearning', 3500, 2024),
(204, 'edX', 6000, 2023),
(205, 'Skillshare', 3000, 2022);

INSERT INTO Student (s_id, Drive_id, T_id, s_name, CGPA, s_branch, S_dob) VALUES
(11, 1, 201, 'Soham Kulkarni', 8.9, 'CSE', '2002-03-15'),
(12, 2, 202, 'Tanvi Deshmukh', 9.1, 'IT', '2003-10-10'),
(13, 3, 203, 'Yash Patil', 7.8, 'ECE', '2001-11-20'),
(14, 4, 204, 'Snehal Rane', 8.4, 'EEE', '2002-06-25'),
(15, 5, 205, 'Omkar Shinde', 8.0, 'CSE', '2003-02-18'),
(16, 1, 201, 'Aishwarya Nair', 8.6, 'IT', '2002-07-30'),
(17, 2, 202, 'Harshad Joshi', 9.3, 'ECE', '2001-12-12'),
(18, 3, 203, 'Rutuja Pawar', 7.9, 'EEE', '2003-01-05'),
(19, 4, 204, 'Nikhil Gaikwad', 8.2, 'CSE', '2002-09-14'),
(20, 5, 205, 'Vidya More', 8.7, 'IT', '2001-05-09');

SELECT * FROM Student WHERE (s_branch = 'Computer' OR s_branch = 'IT')
AND (s_name LIKE 'A%' OR s_name LIKE 'D%');
SET SQL_SAFE_UPDATES=0;
UPDATE Training SET T_Fee = T_Fee + (T_Fee * 0.15) WHERE T_year = 2019;
SELECT * FROM Student;
DELETE FROM Student WHERE CGPA < 7;
SELECT Pcompany_name FROM PlacementDrive WHERE location = 'Pune' OR location = 'Mumbai';
SELECT s_name FROM Student WHERE CGPA = (SELECT MAX(CGPA) FROM Student);
SELECT s_name, T_id FROM Student ORDER BY (SELECT T_Fee FROM Training WHERE Training.T_id = Student.T_id) DESC;
SELECT 
    (SELECT Pcompany_name FROM PlacementDrive p WHERE p.Drive_id = s.Drive_id) AS Pcompany_name,
    s.s_name,
    (SELECT location FROM PlacementDrive p WHERE p.Drive_id = s.Drive_id) AS location,
    (SELECT package FROM PlacementDrive p WHERE p.Drive_id = s.Drive_id) AS package
FROM Student s
WHERE (SELECT package FROM PlacementDrive p WHERE p.Drive_id = s.Drive_id) IN (30000, 40000, 50000);







