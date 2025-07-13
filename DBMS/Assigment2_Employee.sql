CREATE DATABASE te_db;
USE te_db;
CREATE TABLE Dept (
        Dept_id INT PRIMARY KEY,
		Dept_name VARCHAR(50) NOT NULL,
		Dept_location VARCHAR(50)
     );
CREATE TABLE Employee (
         Emp_id INT PRIMARY KEY,
         Dept_id INT,
         Emp_fname VARCHAR(50),
         Emp_lname VARCHAR(50),
         Emp_Position VARCHAR(50),
         Emp_salary DECIMAL(10,2),
         Emp_JoinDate DATE,
         FOREIGN KEY (Dept_id) REFERENCES Dept(Dept_id) ON DELETE CASCADE
    );
CREATE TABLE Project(
		Proj_id INT PRIMARY KEY,
        Dept_id INT,
        Proj_Name VARCHAR(40), 
        Proj_Location VARCHAR(30), 
        Proj_cost INT, 
        Proj_year INT,
        FOREIGN KEY(Dept_id) REFERENCES Dept(Dept_id) ON DELETE CASCADE
);
INSERT INTO Dept(Dept_id,Dept_name,Dept_location) values (1,"Computer","London"), 
(2,"IT","New Work") ,(3,"Finance","India") ,(4,"Marketing","UK") ,(5,"HR","Mumbai") ,
 (6,"SDE","Pune");
INSERT INTO Employee(Emp_id,Dept_id,Emp_fname,Emp_lname,Emp_Position,Emp_salary,EMp_JoinDate) 
values 
(115,1,'Sayali','Pawar','Tester',50000,'1978-6-21'),
(117,6,'Shivani','Pangal','Software Engineer',100000,'1993-2-18'),
 (113,4,'Hima','Muthe','Marketing Head',1500000,'1982-6-19'),
(110,5,'Priya','Pawar','HR',100000,'1983-9-19'),
(105,1,'Priyanka','Pawar','Tester',50000,'12-6-21'),
(107,6,'Shivashri','Patil','Software Engineer',100000,'13-2-24'), 
(103,4,'Akanksha','Muthe','Marketing Head',1500000,'2-6-21'),
(104,5,'Sakshi','Pawar','HR',100000,'3-9-24');
INSERT INTO Project (Proj_id, Dept_id, Proj_Name, Proj_Location, Proj_cost, Proj_year) 
VALUES
(201, 1, 'Library Management System', 'London', 50000, 2004),
(202, 2, 'E-commerce Website', 'New York', 150000, 2007),
(203, 3, 'Finance Tracker', 'India', 75000, 2021),
(204, 4, 'Marketing Analytics', 'UK', 120000, 2023),
(205, 5, 'Employee Portal', 'Mumbai', 90000, 2005),
(206, 6, 'SDE Automation Tool', 'Pune', 200000, 2024);
SELECT * FROM Employee WHERE Dept_id IN( SELECT Dept_id FROM Dept WHERE Dept_name IN('Computer','IT')) AND (LOWER(Emp_fname) LIKE 'p%' OR LOWER(Emp_fname) LIKE 'h%');
SELECT COUNT(DISTINCT Emp_Position) AS Num_Position FROM Employee;
SELECT * FROM Employee WHERE YEAR(EMp_JoinDate)<1985;
DELETE FROM Employee WHERE YEAR(Emp_JoinDate) IN (2,3); -- FOR WRONG COLOUMN ADDED
UPDATE Employee SET Emp_salary = Emp_salary +(Emp_salary * 0.10);
SET SQL_SAFE_UPDATES = 0;
DELETE FROM Dept WHERE Dept_location = "Mumbai";
SELECT Proj_Name FROM Project WHERE Proj_Location="Pune";
SELECT * FROM Project WHERE Proj_cost BETWEEN 100000 AND 500000;
SELECT * FROM Project WHERE Proj_cost = (SELECT MAX(Proj_cost) FROM Project);
SELECT Emp_id, Emp_fname,Emp_lname FROM Employee ORDER BY Emp_lname DESC;
SELECT Proj_name,Proj_Location,Proj_cost FROM Project WHERE Proj_year IN (2004,2005,2007);


