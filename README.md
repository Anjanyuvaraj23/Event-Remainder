# 🗓️ Event Tracking System (CPP)

A streamlined command-line tool built to manage academic and personal schedules. This application focuses on data persistence and a clean user experience by allowing users to maintain a live list of upcoming events directly from the terminal.

---

## 💡 Project Overview

This system was designed to solve the problem of "volatile" terminal data. By using local file handling, the app ensures that every event you log is stored safely on your machine even after the console is closed.

### 🛠️ Core Utilities
- **Data Persistence:** Integrated I/O system that syncs with `reminders.txt`.
- **Live Status:** Visual indicators to distinguish between "Active" and "Finished" tasks.
- **Smart Validation:** Prevents data corruption by checking title inputs and date formats.
- **Console UI:** High-contrast text and automated screen refreshes for better readability.

---

## ⚙️ Technical Environment

| Component | Specification |
| :--- | :--- |
| **Language** | C++11 / C++17 |
| **Storage** | Flat-file (TXT) Database |
| **Interface** | Command Line (CLI) |
| **Compiler** | GCC / MinGW-w64 |

---

## ✅ Input Security

To maintain a clean database, the following rules are enforced:
- **Heading:** Must contain at least one character (no empty logs).
- **Description:** Required for every entry to provide context.
- **Timestamp:** Strictly follows the `DD-MM-YYYY` standard to ensure chronological sorting.

---

## 🏫 Background

> Developed as a practical implementation of C++ fundamentals during the training program provided by **Cipher Schools**.

---

## 🚀 Installation & Build

### Compile the Source
Use the following command to link libraries statically:
```powershell
g++ EventRemainder.cpp -o RemainderApp -static
