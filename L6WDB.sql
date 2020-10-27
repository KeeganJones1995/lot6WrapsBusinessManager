--Keegan Jones

DROP TABLE IF EXISTS STAFF;

CREATE TABLE STAFF	(
	staff_id	INTEGER	NOT NULL,
	first_name	TEXT	NOT NULL,
	last_name	TEXT	NOT NULL,
	phone1		TEXT	NOT NULL,
	age 		INTEGER	NOT NULL,
	position	TEXT	NOT NULL,
	pay_rate	REAL	NOT NULL,
	phone2		TEXT,
	email		TEXT,
	insta		TEXT,	
	u_name		TEXT	NOT NULL,
	password	TEXT	NOT NULL,
	primary key	(staff_id)
);

DROP TABLE IF EXISTS CLIENT;

CREATE TABLE CLIENT	(
	client_id	INTEGER	NOT NULL,
	first_name	TEXT	NOT NULL,
	last_name	TEXT	NOT NULL,
	phone1		TEXT	NOT NULL,
	age 		INTEGER	NOT NULL,
	phone2		TEXT,
	email		TEXT,
	insta		TEXT,
	primary key(client_id)
);
	
DROP TABLE IF EXISTS VEHICLE;

CREATE TABLE VEHICLE	(
	vehicle_id	INTEGER	NOT NULL,
	owner_id	INTEGER	NOT NULL,
	orig_color	TEXT	NOT NULL,
	num_doors	TEXT	NOT NULL,
	make 		TEXT	NOT NULL,
	model		TEXT	NOT NULL,
	year_made	TEXT	NOT NULL,
	v_type		TEXT	NOT NULL,
	primary key(vehicle_id),
	foreign key(owner_id) references CLIENT(client_id) on delete cascade
);

DROP TABLE IF EXISTS ASSET;

CREATE TABLE ASSET	(
	obj_id		INTEGER	NOT NULL,
	obj_name	TEXT	NOT NULL,
	colour		TEXT,
	price		REAL	NOT NULL,
	date_bought	TEXT	NOT NULL,
	amnt_bought	REAL,
	amnt_used	REAL,
	wrap		BOOL	NOT NULL,
	primary key(obj_id)
);

DROP TABLE IF EXISTS JOB;
CREATE TABLE JOB	(
	job_id			INTEGER	NOT NULL,
	emp_id			INTEGER	NOT NULL,
	emp_name		TEXT	NOT NULL,
	job_type		TEXT	NOT NULL,
	quote			REAL,
	client_id		INTEGER	NOT NULL,
	client_name		TEXT	NOT NULL,
	final_cost		REAL,
	vehicle_id		INTEGER	NOT NULL,
	vehicle_name	TEXT	NOT NULL,
	details			TEXT,	
	tools_used		TEXT,
	progress		TEXT	NOT NULL,
	paid			TEXT	NOT NULL,
	primary key(job_id),
	foreign key(emp_id) references STAFF(staff_id) on delete cascade,
	foreign key(client_id) references CLIENT(client_id) on delete cascade,
	foreign key(vehicle_id) references VEHICLE(vehicle_id) on delete cascade
);


begin transaction;
insert or replace into STAFF(staff_id, first_name, last_name, phone1, age, position, pay_rate, phone2, email, insta, u_name, password)
	values(1000, 'Keegan','Jones', '519-222-8107', 24, 'Technical Administrator', 42.69, '', 'keeganmackjones@gmail.com', '@mackavellidajones', 'jonk', '8107');
insert or replace into STAFF(staff_id, first_name, last_name, phone1, age, position, pay_rate, phone2, email, insta, u_name, password)
	values(1001, 'Zachary','Fronchak', '519-589-5011', 24, 'CEO/Head Installer', 42.69, '', 'fronchak9@gmail.com', '@lot6wraps', 'fronk', 'lot6');
insert or replace into CLIENT(client_id, first_name, last_name, phone1, age, phone2, email, insta)
	values(1000, 'Anthony','Sangers', '519-895-6016', 23, '', '','@anthonysangers');
insert or replace into CLIENT(client_id, first_name, last_name, phone1, age, phone2, email, insta)
	values(1001, 'Drew','Wilson', '519-222-8120', 23, '','','@andy_will');	
insert or replace into CLIENT(client_id, first_name, last_name, phone1, age, phone2, email, insta)
	values(1002, 'Sean','Lunt', '519-841-1267', 24, '','','@sean_lunt');
insert or replace into CLIENT(client_id, first_name, last_name, phone1, age, phone2, email, insta)
	values(1003, 'Conbar','Buchanan', '613-875-1615', 24, '','','@connayr');
insert or replace into VEHICLE(vehicle_id, owner_id, orig_color, num_doors, make, model, year_made, v_type)
	values(1000, 1002, "Red", "4", "Ford", "Ranger", 2004, "Truck");  
insert or replace into VEHICLE(vehicle_id, owner_id, orig_color, num_doors, make, model, year_made, v_type)
	values(1001, 1000, "Red", "4", "Pontiac", "Vibe", 2004, "Car");
insert or replace into VEHICLE(vehicle_id, owner_id, orig_color, num_doors, make, model, year_made, v_type)
	values(1002, 1001, "Silver", "4", "GMC", "Sierra", 2010, "Truck"); 
insert or replace into VEHICLE(vehicle_id, owner_id, orig_color, num_doors, make, model, year_made, v_type)
	values(1004, 1000, "Silver", "4", "Honda", "Pilot", 2015, "Van/SUV");
insert or replace into VEHICLE(vehicle_id, owner_id, orig_color, num_doors, make, model, year_made, v_type)
	values(1005, 1002, "Green", "2", "Toyota", "Tacoma", 2009, "Truck");
insert or replace into VEHICLE(vehicle_id, owner_id, orig_color, num_doors, make, model, year_made, v_type)
	values(1006, 1003, "Yellow", "4", "Toyota", "Prius", 2017, "Car");
insert or replace into ASSET(obj_id, obj_name, colour, price, date_bought, amnt_bought, amnt_used, wrap)
	values(1000, "Vinyl Wrap", "Matte Black", 289.98, "15-09-20", 600.0 , 400.0, true);  	
insert or replace into ASSET(obj_id, obj_name, colour, price, date_bought, amnt_bought, amnt_used, wrap)
	values(1001, "Vinyl Wrap", "Red", 311.8, "22-08-20", 500.0 , 289.7, true);
end transaction;





