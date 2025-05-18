# Parallel-File-Encryption-and-Decryption


## TEAM MEMBERS :
### 1) Misty Grover
### 2) Ashmita Barthwal
### 3)Vanshika Nag

## Overview:

This project implements a C++-based tool for file encryption and decryption using a simple ASCII-based algorithm. It is designed with a modular and object-oriented approach to ensure clarity, maintainability, and scalability. The project also considers the possibility of parallel execution to optimize performance.

## 🔧 Features

- Object-Oriented Design using a dedicated `Cryption` class
- Modular code structure with `.hpp` and `.cpp` separation
- ASCII-based encryption/decryption logic
- Secure file handling using C++ standard library (`<fstream>`)
- Input validation and error handling
- Maintains original file by writing output to new files
- Parallelization for improved speed

## 🧠 Design Strategy

- **Language:** C++
- **Approach:** Object-Oriented Programming (OOP)
- **Structure:** Header and source file separation
- **Encapsulation:** All encryption/decryption logic inside `Cryption` class
- **Namespaces:** Used to prevent conflicts and improve code maintainability

## 🔐 Encryption / Decryption Logic

- Each character in the input file is modified using a basic mathematical pattern (e.g., ASCII value shift)
- Encrypted output is stored in a new file to preserve original content
- Decryption applies the reverse transformation to restore the original file

## 📁 File Handling

- Uses `<fstream>` for reading and writing files
- Performs file existence checks and input validation
- Creates separate encrypted and decrypted files

## 💻 Technologies and Tools Used

- **Language:** C++
- **IDE:** Visual Studio Code (VS Code)
- **Compiler:** g++ (MinGW or VS Code integrated terminal)
- **Version Control:** Git

## 🚀 Getting Started

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/your-repo-name.git
