# 📘 **Student Record Management System (SRMS)**

A console-based **Student Record Management System** developed in **C language**.
This system allows Admin, Staff, and Users to securely manage and view student data with role-based access control.

The project demonstrates the use of:

* File handling
* Secure login
* Sorting algorithms
* CRUD operations
* Backup handling
* Password protection

---

## 🚀 **Features**

### 🔐 **Secure Login System**

* Password is hidden while typing (`*`)
* 3 login attempts before access is denied
* Supports 3 roles:

  * **Admin**
  * **Staff**
  * **User**

---

### 👨‍🏫 **Admin Features**

Admins have full access:

* Add new student records
* Display all students
* Search student by roll number
* Update student details
* Delete a student
* Sort students by roll, name, or marks
* Create a backup of student data
* Change password
* Logout

---

### 👩‍💼 **Staff Features**

Staff members have limited rights:

* Display students
* Search student
* Sort students
* Logout

---

### 👤 **User Features**

Users have basic access:

* View students
* Search students
* Change their own password
* Logout

---

## 🛠 **Technologies Used**

* C Programming
* File Handling
* Conditional Statements
* Loops & Arrays
* Sorting (Bubble Sort)
* `conio.h` for password masking


**Login Credentials**(Hardcoded Version)

| Role  | Username | Password |
| ----- | -------- | -------- |
| Admin | admin    | admin123 |
| Staff | staff    | staff123 |
| User  | user     | user123  |


* Password encryption
* GUI-based interface
* Database integration (MySQL / SQLite)
* Report generation (PDF/CSV)
* Cloud-based student storage


* File operations (`fopen`, `fprintf`, `fscanf`)
* Role-based access handling
* Masked password input
* Sorting & searching logic
* Modular program structure
* Backup & restore functionality


Developed by:Sai Hasitha 
Reg No: AP24110010908
B.Tech – SRM University AP
