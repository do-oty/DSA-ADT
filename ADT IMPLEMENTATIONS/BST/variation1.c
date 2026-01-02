#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char String[64];

typedef struct {
    int student_id;
    String name;
    float gpa;
} Student;

typedef struct node {
    Student student;
    struct node *left;
    struct node *right;
} *BST;

void insertStudent(BST *root, Student s) {
    if(*root == NULL) {
        struct node *newNode = malloc(sizeof(struct node));
        newNode->student = s;
        newNode->left = NULL;
        newNode->right = NULL;
        *root = newNode;
    } else if(s.student_id < (*root)->student.student_id) {
        insertStudent(&(*root)->left, s);
    } else if(s.student_id > (*root)->student.student_id) {
        insertStudent(&(*root)->right, s);
    } else {
        // duplicate case
    }
}

Student* findStudent(BST root, int student_id) {
    if(root == NULL) return NULL;
    
    if(student_id < root->student.student_id) {
        return findStudent(root->left, student_id);
    } else if(student_id > root->student.student_id) {
        return findStudent(root->right, student_id);
    } else {
        return &(root->student);
    }
}

BST deleteStudent(BST root, int student_id) {
    if(root == NULL) {
        printf("Student not found!\n");
        return NULL;
    }
    
    if(student_id < root->student.student_id) {
        root->left = deleteStudent(root->left, student_id);
        return root;
    } else if(student_id > root->student.student_id) {
        root->right = deleteStudent(root->right, student_id);
        return root;
    } else {
        if(root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        
        if(root->left == NULL) {
            BST temp = root->right;
            free(root);
            return temp;
        }
        
        if(root->right == NULL) {
            BST temp = root->left;
            free(root);
            return temp;
        }
        
        BST successor = root->right;
        for(; successor->left != NULL; successor = successor->left);
        
        root->student = successor->student;
        root->right = deleteStudent(root->right, successor->student.student_id);
        return root;
    }
}

int countInRange(BST root, int min_id, int max_id) {
    if(root == NULL) return 0;
    
    if(root->student.student_id < min_id) {
        return countInRange(root->right, min_id, max_id);
    } else if(root->student.student_id > max_id) {
        return countInRange(root->left, min_id, max_id);
    } else {
        int count = 1;
        count += countInRange(root->left, min_id, max_id);
        count += countInRange(root->right, min_id, max_id);
        return count;
    }
}

Student* findHighestGPA(BST root) {
    if(root == NULL) return NULL;
    
    Student* leftMax = findHighestGPA(root->left);
    Student* rightMax = findHighestGPA(root->right);
    
    Student* current = &(root->student);
    
    if(leftMax != NULL && leftMax->gpa > current->gpa) {
        current = leftMax;
    }
    if(rightMax != NULL && rightMax->gpa > current->gpa) {
        current = rightMax;
    }
    
    return current;
}

void printAllStudents(BST root) {
    if(root == NULL) return;
    
    printAllStudents(root->left);
    printf("%d\t| %s\n", root->student.student_id, root->student.name);
    printAllStudents(root->right);
}

int main(void) {
    BST root = NULL;
    
    Student s1 = {50, "Alice", 3.8};
    Student s2 = {30, "Bob", 3.5};
    Student s3 = {70, "Cara", 3.9};
    Student s4 = {20, "Dave", 3.2};
    Student s5 = {40, "Eve", 3.7};
    Student s6 = {60, "Frank", 4.0};
    Student s7 = {80, "Grace", 3.6};
    
    insertStudent(&root, s1);
    insertStudent(&root, s2);
    insertStudent(&root, s3);
    insertStudent(&root, s4);
    insertStudent(&root, s5);
    insertStudent(&root, s6);
    insertStudent(&root, s7);
    
    printf("All students (sorted by ID):\n");
    printAllStudents(root);
    
    Student* found = findStudent(root, 40);
    if(found) {
        printf("\nFound: %s (GPA: %.2f)\n", found->name, found->gpa);
    }
    
    int count = countInRange(root, 30, 60);
    printf("Students in range [30, 60]: %d\n", count);
    
    Student* top = findHighestGPA(root);
    if(top) {
        printf("Highest GPA: %s (%.2f)\n", top->name, top->gpa);
    }
    
    return 0;
}

