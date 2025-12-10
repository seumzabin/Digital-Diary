# 📔 Digital Diary – C Console Application

A simple, file-based **Digital Diary** system written in C.  
This program allows users to **Sign Up**, **Log In**, and manage their:

- 🗓 Planner entries  
- 📋 To-Do list  
- 📝 Journal logs  

All data is stored locally using text files.  
A masked-password input system provides basic privacy during login.

---

## 🚀 Features

### 🔐 User Authentication
- Create an account with username & masked password (`*` shown instead of characters).
- Login system with limited attempts.
- User credentials stored in `users.txt`.

### 🗓 Planner
- Add, view, edit, and delete planner entries.
- Entries saved in `planner.txt`.

### 📋 To-Do List
- Add, view, edit, and delete tasks.
- Stored in `todo.txt`.

### 📝 Journal
- Add personal journal logs.
- View, edit, and delete notes.
- Stored in `journal.txt`.

---

## 📂 File Structure (Auto-Generated)

| File | Purpose |
|------|---------|
| `users.txt` | Stores username & password pairs |
| `planner.txt` | Stores planner entries |
| `todo.txt` | Stores to-do items |
| `journal.txt` | Stores journal logs |




## 🛠 Requirements

- C Compiler (GCC, MinGW, CodeBlocks, Visual Studio, etc.)
- Windows OS (because `conio.h` & `getch()` are used)
- Terminal/Console to run the program

---

## 🧰 Compilation & Run

### Using GCC:
```bash
gcc diary.c -o diary.exe
./diary.exe


<img width="508" height="708" alt="Screenshot 2025-12-10 230917" src="https://github.com/user-attachments/assets/6d4ebfa9-ba4b-4393-947a-862de0188a07" />
<img width="618" height="716" alt="Screenshot 2025-12-10 230934" src="https://github.com/user-attachments/assets/0accec1d-c9fc-4135-a2ac-2c7d6b9fd79e" />
<img width="764" height="120" alt="Screenshot 2025-12-10 230950" src="https://github.com/user-attachments/assets/5a44322f-7124-43bc-bf3a-93dda606d15c" />

