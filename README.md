# Circadian Activity Mapper - DSA Final Project  
### (June Brad C. Masongsong - CS 1202)

Circadian Activity Mapper is a C++ console-based energy tracking and activity analysis system. It helps users record activities based on time segment, activity type, and energy level. The system analyzes the records to identify the user’s peak energy period, lowest energy period, task-fit result, and recommendation for better task scheduling.

---

## Features

- Add activity records
- View all saved activity records
- Show current energy insights
- Analyze energy pattern by time segment
- Identify peak energy period
- Identify lowest energy period
- Check task-fit result
- Delete selected activity record
- Clear all activity records
- Save and load records using file handling

---

## Data Structures Used

- `struct` → stores one activity record  
- `vector` → stores multiple activity records  
- `map` → stores task demand values and grouped energy data  

---

## Libraries Used

- `iostream` → handles input and output using `cin` and `cout`
- `vector` → stores multiple activity records
- `map` → stores task demand and grouped energy data
- `fstream` → saves and loads records using text files
- `iomanip` → formats console table output
- `string` → stores text data such as activity type and time segment

---

## How to Compile

```bash
g++ main.cpp -o main


