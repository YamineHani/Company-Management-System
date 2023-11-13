# Company Management System

## User Manual and Project Description


## 1. Introduction

In today's technologically advanced world, the need for efficient management systems has become essential, especially in handling vast amounts of employee data. The Company Management System is designed to simplify the management of employee records, offering a user-friendly interface for employers to effortlessly track and organize employee information.

## 2. Project Description

### 2.1 Functions

#### 2.1.1 Read File
Upon opening the program, it automatically reads the data from the default file ("company.txt"). If the file doesn't exist, a warning is displayed.

#### 2.1.2 Query
Enables users to search for employees by last name, displaying their information if found. The search is not case-sensitive.

#### 2.1.3 Add
Allows users to add a new employee by entering information field by field. It checks the validity of inputs, ensuring accurate and meaningful data entry.

#### 2.1.4 Modify
Permits users to modify existing employee information by entering the employee's ID. The system displays the current data, allowing modifications field by field.

#### 2.1.5 Delete
Enables users to delete an employee by entering the last and first name (case-insensitive). Deletes all employees with the specified name.

#### 2.1.6 Print and Sort
Prints the entire list of employees in sorted order. Users can choose sorting criteria: last name (A to Z), date of birth (oldest to youngest), or salary (lowest to highest).

#### 2.1.7 Save
Saves all changes to the "company.txt" file, providing a straightforward way to preserve modifications.

### 2.2 Checking Inputs' Validity

#### 2.2.1 Validity of Phone Number
Ensures the phone number follows specified formats, rejecting invalid entries.

#### 2.2.2 Validity of ID
Verifies that the ID is a valid number, not starting with 0.

#### 2.2.3 Validity of Email
Checks if the entered email is in a valid format.

#### 2.2.4 Validity of Name
Ensures that the entered name does not contain any numbers.

#### 2.2.5 Validity of Date of Birth
Validates the entered date of birth, considering year, month, day range, leap years, and varying days in months.

### 2.3 Main Function
The main function presents a menu where users can choose from various commands, each corresponding to specific system functionalities.

## 3. Algorithms

### 3.1 Search Algorithm
Utilizes linear search to find the requested item. If not found, an error message is displayed.

### 3.2 Sort Algorithm
Implements the bubble sort algorithm for sorting employees based on last name, date of birth, or salary.

#### 3.2.1 Sort by Name
Sorts employees by last name (A to Z), considering first names in case of identical last names.

#### 3.2.2 Sort by Birthdate
Sorts employees by age, from oldest to youngest.

#### 3.2.3 Sort by Salary
Sorts employees by salary, from lowest to highest.

## 4. User Manual

1. **File Loading:** The file is loaded by default when the program starts.

2. **Search for an Employee:**
   - Choose option 1.
   - Enter the last name of the employee to search.

3. **Add an Employee:**
   - Choose option 2.
   - Enter new employee data field by field.

4. **Delete an Employee:**
   - Choose option 3.
   - Enter the first and last name of the employee to delete.

5. **Modify Employee:**
   - Choose option 4.
   - Enter the ID of the employee to modify.
   - Modify information field by field.

6. **Print (Sort):**
   - Choose option 5.
   - Sub-menu:
      - A. Print sorted alphabetically.
      - B. Print sorted by date of birth.
      - C. Print sorted by salary.

7. **Save Changes:**
   - Choose option 6.
   - Changes are saved in the "company.txt" file.

8. **Quit:**
   - Choose option 7.
   - Confirm choice (y/n).



## Conclusion

The Company Management System offers a comprehensive solution for managing employee data efficiently. Its user-friendly interface and diverse functionalities make it a valuable tool for employers seeking organized and streamlined employee record management.