#include <stdio.h>
#include <string.h>
#include <math.h>
#define MAX_LINE_LENGTH 100
#define MAX_CHARACTER_LENGTH 50
#define MAX_CHARACTER_BUFFER 100
#define MAX_NAMES 40
// Function of attendance for taking present and absent
void attendance(unsigned int id_person_pick,unsigned int pick_choice_attendance);

// Function to add bonus or minus to a student's total marks
void add_bonus_or_minus(unsigned int id_person, unsigned int pick, unsigned int amount);

// Function to read a specific line from the file
void file_handling_reading_line(unsigned int lineNumber);

// Function to write data to the file
void file_handling_writing(void);

// Function to read all data from the file
void file_handling_reading(void);

// Function to enter names into the array and return the updated count
int enter_names(char user[MAX_CHARACTER_LENGTH], int count);

// Function to handle data, copying names to the structure
void handling_data(void);

// Structure to represent student information
typedef struct {
    char student_name[MAX_CHARACTER_LENGTH];
    int id;
    int present;
    int absent;
    int minus;
    int bonus;
    int total_mark;
} student_t;

// Array of structures to store student information
student_t student[6];

// Array to store names entered by the user
char name[MAX_NAMES][MAX_CHARACTER_LENGTH];
char (*ptr)[MAX_CHARACTER_LENGTH];  // Declare a pointer to an array of characters
int count = 0;
unsigned int id = 0;
unsigned int id_pick;
unsigned int line_number = 1;
unsigned int choice;
unsigned int pick_choice;
unsigned int amount_pick;

int main() {
    // Assign the pointer to the array
    count = enter_names("kareem ahmed", count);
    count = enter_names("hamdy ayman", count);
    count = enter_names("nada mohamed", count);
    count = enter_names("shahd yesen", count);
    count = enter_names("mustafa ashraf", count);
    count = enter_names("adnan adel", count);
    // Write data to the file
    file_handling_writing();
    handling_data();
    // Copy names to the structure
    
    
    label:
    printf("1- show whole data 2- pick one of them 3-give bonus or minus 4- attendance \n");
    printf("Choice : ");
    scanf("%i", &choice);
    
    switch (choice) {
        case 1:
            // Read and display all data from the file
            file_handling_reading();
            break;
        case 2:
            printf("please enter id or which line to read: ");
            scanf("%i", &pick_choice);
            // Read and display data for a specific line
            file_handling_reading_line(pick_choice + 1);
            break;
        case 3:
            printf("please enter id of required person: ");
            scanf("%i", &id_pick);
            printf("please enter bonus or minus 1- bonus 2- minus: ");
            scanf("%i", &pick_choice);
            printf("please enter amount: ");
            scanf("%i", &amount_pick);
            // Add bonus or minus to the selected person
            add_bonus_or_minus(id_pick, pick_choice, amount_pick);
            break;
		default:
			printf("please enter id of required person: ");
            scanf("%i", &id_pick);
            printf("please enter bonus or minus 1-present 2- absent: ");
            scanf("%i", &pick_choice);
			attendance(id_pick,pick_choice);
		break;
    }
    
    printf("=====================================================\n");
    goto label;
    
    return 0;
}

// Function to enter names into the array and return the updated count
int enter_names(char user[MAX_CHARACTER_LENGTH], int count) {
    ptr = name;
    strcpy(ptr[count], user);
    count++;
    return count;
}

// Function to write data to the file
void file_handling_writing(void) {
    FILE *fp_write;
    fp_write = fopen("filename.txt", "w");

    if (fp_write == NULL) {
        printf("Error opening file for writing.\n");
    }
    
    fprintf(fp_write, "%s", "Id  Name\t\n");
    
    for (int i = 0; i < count; i++) {
        fprintf(fp_write, "%d  ", ++id);
        fprintf(fp_write, "%s\n", name[i]);
    }

    fclose(fp_write);
}

// Function to read all data from the file
void file_handling_reading(void) {
    FILE *fp_read;
    char ch[MAX_CHARACTER_BUFFER];

    fp_read = fopen("filename.txt", "r");

    if (fp_read == NULL) {
        printf("Error opening file for reading.\n");
    }

    while (fgets(ch, sizeof(ch), fp_read) != NULL) {
        printf("%s", ch);
    }

    fclose(fp_read);
}

// Function to read a specific line from the file
void file_handling_reading_line(unsigned int lineNumber) {
    FILE *line_read;
    char line[MAX_LINE_LENGTH];
    int integerArray[MAX_LINE_LENGTH];  // Assuming you want to store integers in an array

    line_read = fopen("filename.txt", "r");

    if (line_read != NULL) {
        while (fgets(line, MAX_LINE_LENGTH, line_read) != NULL && lineNumber > 1) {
            lineNumber--;
        }

        if (lineNumber == 1) {
			
            // Extract integer from the line (assuming it's the first integer in the line)
            int integerValue;
            sscanf(line, "%d", &integerValue);
            
            // Store the integer in the array
            integerArray[0] = integerValue;
            
			// Display the read line
            printf("Name: %s \n", student[integerArray[0] - 1].student_name);
			
            // You can now use the 'line' and 'integerArray' as needed
            // For example, you can copy them to other arrays if necessary
            char textArray[MAX_LINE_LENGTH];
            strcpy(textArray, line);
            
            // Print the copied line and integer
            printf("id: %d\n", integerArray[0]);
        } else {
            printf("Error: Unable to read the desired line.\n");
        }
		
		if ((student[integerArray[0]].absent != 6 && student[integerArray[0]].absent <= 6))
		{
			printf("bonus: %i\n", student[integerArray[0]].bonus);
			printf("minus: %i\n", student[integerArray[0]].minus);
			printf("total_mark: %i\n", student[integerArray[0]].total_mark);
			printf("absent: %i\n", student[integerArray[0]].absent);
			printf("present: %i\n", student[integerArray[0]].present);
			if((student[integerArray[0]].absent == 2) || ((student[integerArray[0]].absent == 4))){
				printf("warning this person behvior will fired him\n");	
			}
			else
			{}
		
		printf("State: he has a chance to be a member\n");
			// Display additional information from the student structure
		}
		else{
				printf("State: Fired\n");
		}
        fclose(line_read);
    } else {
        perror("Error opening file");
    }
}

// Function to handle data, copying names to the structure
void handling_data(void) {
    for (int index = 0; index < count; index++) {
        strcpy(student[index].student_name, name[index]);
        student[index].id = index + 1;
    }
}

// Function to add bonus or minus to a student's total marks
void add_bonus_or_minus(unsigned int id_person, unsigned int pick, unsigned int amount) {
    switch (pick) {
        case 1:
            student[id_person].bonus += amount;
            break;
        case 2:
            student[id_person].minus += amount;
            break;
        default:
            printf("please pick only 1 or 2\n");
            break;
    }
    
   student[id_person].total_mark = (student[id_person].bonus - student[id_person].minus);
}

void attendance(unsigned int id_person_pick,unsigned int pick_choice_attendance)
{
	switch(pick_choice_attendance)
	{	
		case 1:
		student[id_person_pick].present +=1;
		break;
		case 2:
		student[id_person_pick].absent +=1;
		break;
	}
}