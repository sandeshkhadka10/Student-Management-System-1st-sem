#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> // for getch()
#include <unistd.h> // for sleep()

struct Student 
{
    char name[50];
    int id;
    char year[50];
    char address[50];
    char email[50];
    char phonenumber[50];
    float gpa;
    float totalAmount;
    float paidAmount;
    float dueAmount;
};

const char *filename = "students_records.dat";

// Function prototypes
void AddStudent();
void DisplayAllStudents();
void SearchStudent();
void EditStudentDetails();
void DeleteStudent();
int Login()
{
	char username[50];
    char password[50];

    printf("\n\t\tUsername: ");
    scanf("%s", username);

    printf("\t\tPassword: ");
    scanf("%s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "12345") == 0)
    {
        printf("\n\t\tLogin successful\n");
        printf("\n\t\tLogging in . . . .\n");
		sleep(3);
        return 1; 
    }
    else
    {
        printf("\n\t\tLogin failed! Invalid username or password.\n");
        return 0; 
    }
}

int main()
{
    char choice, x;
    int loggedIn = 0; 

    while (1)
    {
        system("cls");
        printf("\t\t\t\t\t<== STUDENT MANAGEMENT SYSTEM ==>\n");
        printf("\t\t*********************************************************************************\n");

        if (!loggedIn)
        {
            printf("\n\t\tLogin to continue:\n");
            loggedIn = Login();
            if (!loggedIn)
            {
                printf("\n\t\tPress any key to retry...\n");
                getch();
                continue;
            }
        }

        while (1) 
        {
        	flag:
        	system("cls");
            printf("\t\t\t\t\t<== Student Management System ==>\n");
            printf("\t\t*********************************************************************************\n");
            fflush(stdin);
            printf("\n\t\ta. Add Student\n");
            printf("\t\tb. Display All Students\n");
            printf("\t\tc. Search Student\n");
            printf("\t\td. Edit Student Details\n");
            printf("\t\te. Delete Student\n");
            printf("\t\tf. Exit\n");
            printf("\n\t\tEnter your choice(a-f): ");
            scanf(" %c", &choice); 
            
            switch (choice) 
            {
                case 'a':
                    AddStudent();
                    break;
                    
                case 'b':
                    DisplayAllStudents();
                    break;
                    
                case 'c':
                    SearchStudent();
                    break;
                    
                case 'd':
                    EditStudentDetails();
                    break;
                    
                case 'e':
                    DeleteStudent();
                    break;
                    
                case 'f':
                    printf("\t\tPress Y to exit and any other character to cancel: ");
                    fflush(stdin);
                    scanf(" %c", &x); 
                    if (x == 'Y' || x == 'y')
                    {
                        exit(0);
                	}
                    else
                    {
                        goto flag;
                    }
                    break;

                default:
                    printf("\n\t\tInvalid Choice!\n");
                    printf("\t\tPlease Enter from a to f\n");
                    printf("\t\tPress any key to retry");
                    getch();
                    goto flag;
            }
            
            printf("\n\t\tPress any key to continue");
            getch(); 
        }
    }
    
    return 0;
}
void AddStudent()
{
    char another;
    do
    {
        struct Student newstudent;
        system("cls");
        printf("\t\t\t\t\t<== Add Student Information ==>\n\n");
       
        printf("\n\t\tName: ");
        fflush(stdin);
        gets(newstudent.name);

        printf("\n\t\tId no: ");
        scanf("%d", &newstudent.id);

        printf("\n\t\tCourse and Semester: ");
        fflush(stdin);
        gets(newstudent.year);

        printf("\n\t\tAddress: ");
        fflush(stdin);
        gets(newstudent.address);
        
        printf("\n\t\tEmail: ");
        fflush(stdin);
        gets(newstudent.email);
        
        printf("\n\t\tPhone no: ");
        fflush(stdin);
        gets(newstudent.phonenumber);
    
        printf("\n\t\tGPA: ");
        fflush(stdin);
        scanf("%f", &newstudent.gpa);

        printf("\n\t\tPaid Amount: ");
        scanf("%f", &newstudent.paidAmount);

        newstudent.totalAmount = 790000; // Fixed total amount
        newstudent.dueAmount = newstudent.totalAmount - newstudent.paidAmount;
        
        printf("\t\t____________________________________________________");
       
        FILE *file = fopen(filename, "ab");
        if (file == NULL) 
        {
            printf("\t\tUnable to open file.\n");
            return;
        }

        fwrite(&newstudent, sizeof(struct Student), 1, file);
        fclose(file);
        
        printf("\n\t\tDo you want to add another record?(Y/any other character): ");
        fflush(stdin);
        scanf(" %c", &another);
    } 
    while (another == 'y' || another == 'Y');
}

void DisplayAllStudents()
{
    system("cls");
    printf("\t\t\t\t\t<== Student Records ==>\n\n");

    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        printf("\t\tUnable to open file.\n");
        return;
    }

    struct Student newstudent;
    int recordsFound = 0; // Initialize a variable to track if any records were found

    while (fread(&newstudent, sizeof(struct Student), 1, file))
    {
        recordsFound = 1; // Records were found
        printf("\n\t\tStudent Name       :    %s", newstudent.name);
        printf("\n\t\tId                 :    %d", newstudent.id);
        printf("\n\t\tClass and Semester :    %s", newstudent.year);
        printf("\n\t\tAddress            :    %s", newstudent.address);
        printf("\n\t\tEmail              :    %s", newstudent.email);
        printf("\n\t\tPhone number       :    %s", newstudent.phonenumber);
        printf("\n\t\tGPA                :    %.2f", newstudent.gpa);
        printf("\n\t\tTotal Amount       :    Rs %.2f", newstudent.totalAmount);
        printf("\n\t\tPaid Amount        :    Rs %.2f", newstudent.paidAmount);
        printf("\n\t\tDue Amount         :    Rs %.2f", newstudent.dueAmount);
        printf("\n\t\t____________________________________");
    }
        

    fclose(file);

    // Check if no records were found and display a message
    if (recordsFound==0)
    {
        printf("\n\t\tNo records found.\n");
    }
}

void SearchStudent()
{
    int search = 0, found = 0;
    system("cls");
    printf("\t\t\t\t\t<== Search Student ==>\n\n");

    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        printf("\t\tUnable to open file.\n");
        return;
    }

    struct Student newstudent;

    printf("\n\t\tEnter the ID you want to search: ");
    scanf("%d", &search);

    while (fread(&newstudent, sizeof(struct Student), 1, file))
    {
        if (newstudent.id == search)
        {
            found = 1;
            printf("\n\t\tStudent Name         : %s", newstudent.name);
            printf("\n\t\tID                   : %d", newstudent.id);
            printf("\n\t\tClass and Semester   : %s", newstudent.year);
            printf("\n\t\tAddress              : %s", newstudent.address);
            printf("\n\t\tEmail                : %s", newstudent.email);
            printf("\n\t\tPhone number         : %s", newstudent.phonenumber);
            printf("\n\t\tGPA                  : %.2f", newstudent.gpa);
            printf("\n\t\tTotal Amount         : Rs %.2f", newstudent.totalAmount);
            printf("\n\t\tPaid Amount          : Rs %.2f", newstudent.paidAmount);
            printf("\n\t\tDue Amount           : Rs %.2f", newstudent.dueAmount);
            printf("\n\t\t____________________________________");
    }
    }

    if (found != 1)
    {
        printf("\n\t\tRecord not found\n");
    }
    fclose(file);
}

void EditStudentDetails()
{
    system("cls");
    printf("\t\t\t\t\t<== Edit Student Details ==>\n\n");

    int id = 0, found = 0, updated = 0;
    printf("\t\tEnter ID to Edit: ");
    scanf("%d", &id);

    struct Student updatedStudent;

    FILE *file = fopen(filename, "rb+");
    if (file == NULL)
    {
        printf("\t\tUnable to open file.\n");
        return;
    }

    struct Student newstudent;

    while (fread(&newstudent, sizeof(struct Student), 1, file))
    {
        if (newstudent.id == id)
        {
            updatedStudent = newstudent;
            found = 1;
            break;
        }
    }

    if (found != 1)
    {
        printf("\n\t\tStudent with ID %d not found.\n", id);
        fclose(file);
        return;
    }

    int choice;
    int repeatMenu = 1;

    do
    {
        system("cls");
        printf("\t\t\t\t\t<== Edit Student Details ==>\n\n");
        printf("\t\tSelect fields to update:\n");
        printf("\t\t1. Name\n");
        printf("\t\t2. ID\n");
        printf("\t\t3. Semester\n");
        printf("\t\t4. Address\n");
        printf("\t\t5. Email\n");
        printf("\t\t6. Phone Number\n");
        printf("\t\t7. GPA\n");
        printf("\t\t8. Paid Amount\n");
        printf("\t\t9. Exit\n");
        printf("\t\tEnter your choice (1-9): ");

        scanf("%d", &choice);
        fflush(stdin);

        switch (choice)
        {
            case 1:
                printf("\n\t\tEnter Updated Name: ");
                fflush(stdin);
                gets(updatedStudent.name);
                updated = 1;
                break;

            case 2:
                printf("\n\t\tEnter Updated ID: ");
                scanf("%d", &updatedStudent.id);
                updated = 1;
                break;

            case 3:
                printf("\n\t\tEnter Updated Semester: ");
                fflush(stdin);
                gets(updatedStudent.year);
                updated = 1;
                break;

            case 4:
                printf("\n\t\tEnter Updated Address: ");
                fflush(stdin);
                gets(updatedStudent.address);
                updated = 1;
                break;

            case 5:
                printf("\n\t\tEnter Updated Email: ");
                fflush(stdin);
                gets(updatedStudent.email);
                updated = 1;
                break;

            case 6:
                printf("\n\t\tEnter Updated Phone number: ");
                gets(updatedStudent.phonenumber);
                updated = 1;
                break;

            case 7:
                printf("\n\t\tEnter Updated GPA: ");
                scanf("%f", &updatedStudent.gpa);
                updated = 1;
                break;

            case 8: // Payment Amount Update
                printf("\n\t\tEnter Updated Payment Amount: ");
                scanf("%f", &updatedStudent.paidAmount);
                updatedStudent.dueAmount = updatedStudent.totalAmount - updatedStudent.paidAmount;
                updated = 1;
                break;

            case 9:
                if (updated == 1)
                {
                    printf("\n\t\tStudent details successfully updated.\n");
                }
                else
                {
                    printf("\n\t\tNo updates were made.\n");
                }
                repeatMenu = 0;
                break;

            default:
                printf("\n\t\tInvalid choice!");
                printf("\n\t\tPress any key to retry");
                getch();
                break;
        }
    } while (repeatMenu);

    fclose(file); // Close the file after editing

    file = fopen(filename, "rb+");
    if (file == NULL) 
    {
        printf("\t\tUnable to open file.\n");
        return;
    }

    while (fread(&newstudent, sizeof(struct Student), 1, file))
    {
        if (newstudent.id == id)
        {
            fseek(file, -((long int)sizeof(struct Student)), SEEK_CUR);
            fwrite(&updatedStudent, sizeof(struct Student), 1, file);
            break;
        }
    }

    fclose(file);
}

void DeleteStudent()
{
    int search = 0, found = 0;
    system("cls");
    printf("\t\t\t\t\t<== Delete Student Record ==>\n\n");

    printf("\t\tEnter the ID you want to delete: ");
    scanf("%d", &search);

    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        printf("\t\tUnable to open file.\n");
        return;
    }

    FILE *tempFile = fopen("temp.dat", "wb");
    if (tempFile == NULL)
    {
        printf("\t\tUnable to create temporary file.\n");
        fclose(file);
        return;
    }

    struct Student newstudent;
    fflush(stdin);

    while (fread(&newstudent, sizeof(struct Student), 1, file))
    {
        if (newstudent.id != search)
        {
            fwrite(&newstudent, sizeof(struct Student), 1, tempFile);
        }
        else
        {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(filename);
    rename("temp.dat", filename);

    if (found)
    {
        printf("\t\tStudent with ID %d deleted successfully.\n", search);
    }
    else
    {
        printf("\t\tStudent with ID %d not found.\n", search);
    }
}


