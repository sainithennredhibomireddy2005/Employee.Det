/*Data Structure - II Project

Title: Employee Management System using Binary Search Tree

Description: The Employee Management System using BST is a software application developed to manage employee data within an organization. The 
system utilizes a BST data structure to store and manipulate employee information efficiently. It must provide the following operations:
1. Adding employees,
2. Removing employees,
3. Searching for employees,
4. Displaying employee details
5. Compute salary

Team-3: AP22110010668 - Poojan Patel
        AP22110010674 - Sai Nithenn Redhi
        AP22110010714 - Gopikrishnan Harilal Mini
        AP22110010718 - Adarsh Kumar

*************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent an employee
typedef struct Employee {
    int empId;
    char name[50];
    float salary;
    struct Employee* left;
    struct Employee* right;
}Employee;

//Function Prototypes
Employee *createEmployee(int empId, const char *name, float salary);
Employee *insert(Employee* root, int empId, const char *name, float salary);
Employee *deleteEmployee(Employee *root, int empId);
Employee *search(Employee *root, int empId);
void displaySalary(Employee *employee);
void inOrderTraversal(Employee *root);

//Main function
int main(){
    Employee *root = NULL;

    int choice;
    int empId;
    char name[50];
    float salary;

    //A do-while implementation for displaying the menu
    do{
        //Displaying the menu
        printf("\nEmployee Management System Menu:\n");
        printf("1. Add Employee\n");
        printf("2. Remove Employee\n");
        printf("3. Search for Employee\n");
        printf("4. Display All Employees\n");
        printf("5. Compute Salary\n");
        printf("6. Quit\n");

        //Asking the user to choose from the menu
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        printf("\n");

        //Switch cases associated with each of the feature
        switch (choice){
            case 1: //Adding an employee detail
                    printf("Enter Employee ID: ");
                    scanf("%d", &empId);
                    printf("Enter Employee Name: ");
                    scanf("%s", name);
                    printf("Enter Employee Salary: $");
                    scanf("%f", &salary);
                    root = insert(root, empId, name, salary);
                    break;
                    
            case 2: //Removing an employee detail
                    printf("Enter Employee ID to remove: ");
                    scanf("%d", &empId);
                    root = deleteEmployee(root, empId);
                    if(root!=NULL){
                        printf("Employee with ID %d removed.", empId);
                        printf("\n");
                    }else{
                        printf("No employee details found!\n");
                    }
                    break;

            case 3: //Searching for an employee details
                    printf("Enter Employee ID to search: ");
                    scanf("%d", &empId);
                    Employee *foundEmployee = search(root, empId);
                    if (foundEmployee != NULL){
                        printf("Employee found.\n");
                    }else{
                        printf("Employee not found.\n");
                    }
                    break;

            case 4: //Displaying all employee details
                    printf("Employee Details:\n");
                    inOrderTraversal(root);
                    break;

            case 5: //Computing a salary of an employee
                    printf("Enter Employee ID to display salary: ");
                    scanf("%d", &empId);
                    Employee *empToDisplay = search(root, empId);
                    if (empToDisplay != NULL){
                        displaySalary(empToDisplay);
                    }else{
                        printf("Employee not found.\n");
                    }
                    break;

            case 6: //Ending the program execution
                    printf("Exiting the program...\n");
                    exit(0);

            default://Any other input case is invalid
                    printf("Invalid choice. Please try again.\n");  
        }
    }while (choice != 6);

    return 0;
}

// Function to create a new employee
Employee *createEmployee(int empId, const char *name, float salary){
    Employee *newEmployee = (Employee *)malloc(sizeof(Employee));
    newEmployee->empId = empId;
    strcpy(newEmployee->name, name);
    newEmployee->salary = salary;
    newEmployee->left = newEmployee->right = NULL;
    return newEmployee;
}

// Function to insert an employee into the BST
Employee *insert(Employee *root, int empId, const char *name, float salary){
    if (root == NULL){
        return createEmployee(empId, name, salary);
    }

    if (empId < root->empId){
        root->left = insert(root->left, empId, name, salary);
    }else if (empId > root->empId){
        root->right = insert(root->right, empId, name, salary);
    }

    return root;
}

// Function to delete an employee from the BST
Employee *deleteEmployee(Employee *root, int empId){
    if (root == NULL){
        return root;
    }

    if (empId < root->empId){
        root->left = deleteEmployee(root->left, empId);
    }else if (empId > root->empId){
        root->right = deleteEmployee(root->right, empId);
    }else{
        if (root->left == NULL){
            Employee* temp = root->right;
            free(root);
            return temp;
        }else if (root->right == NULL){
            Employee* temp = root->left;
            free(root);
            return temp;
        }

        Employee *temp = root->right;
        while (temp->left != NULL){
            temp = temp->left;
        }

        root->empId = temp->empId;
        strcpy(root->name, temp->name);
        root->salary = temp->salary;
        root->right = deleteEmployee(root->right, temp->empId);
    }

    return root;
}

// Function to search for an employee in the BST
Employee *search(Employee *root, int empId){
    if (root == NULL || root->empId == empId){
        return root;
    }

    if (empId < root->empId){
        return search(root->left, empId);
    }

    return search(root->right, empId);
}

// Function to compute and display the salary for an employee
void displaySalary(Employee *employee){
    printf("Employee ID: %d, Name: %s, Salary: $%.2f\n", employee->empId, employee->name, employee->salary);
}

// Function to perform an in-order traversal of the BST
void inOrderTraversal(Employee *root){
    if (root != NULL){
        inOrderTraversal(root->left);
        displaySalary(root);
        inOrderTraversal(root->right);
    }
}