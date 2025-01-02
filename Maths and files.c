#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX 100
#define PRACTICE 10
#define TEST 3

typedef struct {
    char name[15];
    float result;
    char test_type[25];
    unsigned short int  sec:  5,
                        min:  6,
                        hour: 5,
                        day:  5,
                        month:4,
                        year: 7;
} student;

int menu();
int menu2();
void test_time(student* user);
int addition(int *a, int*b);
int subtraction(int*a, int*b);
void check_answer(int correct);
int random_add_sub(int *a, int *b);
char *type_of_operation(int choice2);
int generate_questions(int choice2, int *pa, int *pb);
void option1_practice(int *pa, int *pb, int limit);
void display_history(char filename[], char name[]);
float test(int choice2, int *a, int *b);
void print_results(student* user);
void save_to_textFile(char* filename, student* user);
void top2_scores(char filename[], float *p_top1, float *p_top2);

int main(void) {
    srand(time(NULL));
    int a, b, *pa = &a, *pb = &b;
    char name[15];
    printf("Enter your name:");
    scanf("%s", name);
    name[0] = toupper(name[0]);

    float top1, top2;
    char filename[] = "TestResults.txt";
    printf("The size of structure is: %llu\n", sizeof(student));
    printf("Welcome, %s", name);
    while (1) {
        int choice = menu();
        if (choice == 1) option1_practice(pa, pb, PRACTICE);
        else if (choice == 2) {
            printf("Take a test on:");
            int choice2 = menu2();
            student user;
            strcpy(user.name, name);
            strcpy(user.test_type, type_of_operation(choice2));
            user.result = test(choice2, pa, pb);
            test_time(&user);
            save_to_textFile(filename, &user);
        }
        else if (choice == 3) {
            top2_scores(filename, &top1, &top2);
        }
        else if (choice == 4) {
            display_history(filename, name);
        }
        else if (choice == 5) break;
        else printf("\nChoice not on the menu. Select again.");
    }
    return 0;
}

void save_to_textFile(char filename[], student* user) {
    FILE *file = fopen(filename, "a");
    fprintf(file, "%s %.1f %s %lu %lu %lu %02lu %02lu %02lu\n",
            user->name, user->result, user->test_type, user->year+1900, user->month+1,
            user->day, user->hour, user->min, user->sec);
    fclose(file);
}
void display_history(char filename[], char name[]) {
    FILE *file = fopen(filename, "r");
    unsigned long year, month, day, hour, min, sec;
    student user;
    while (fscanf(file, "%s %f %s %lu %lu %lu %lu %lu %lu",
                  user.name, &user.result, user.test_type,
                  &year, &month, &day, &hour, &min, &sec) == 9) {
        user.year = year;
        user.month = month;
        user.day = day;
        user.hour = hour;
        user.min = min;
        user.sec = sec;

        if (strcmp(user.name, name) == 0) {
            print_results(&user);
        }
    }
    fclose(file);
}
void print_results(student* user) {
    printf("\t----------------------------------\n");
    printf("\tName : %s\n", user->name);
    printf("\tScore: %.1f\n", user->result);
    printf("\tType : %s\n", user->test_type);
    printf("\tDate : %lu-%lu-%lu %lu:%lu:%lu\n",
           user->year+1920, user->month, user->day,
           user->hour, user->min, user->sec);
    printf("\t----------------------------------\n");
}
void top2_scores(char filename[], float *p_top1, float *p_top2) {
    FILE *file = fopen(filename, "r");
    *p_top1 = *p_top2 = -1;
    unsigned long year, month, day, hour, min, sec;
    student user;

    while (fscanf(file, "%s %f %s %lu %lu %lu %lu %lu %lu",
                  user.name, &user.result, user.test_type,
                  &year, &month, &day, &hour, &min, &sec) == 9) {
        if (user.result > *p_top1) {
            *p_top2 = *p_top1;
            *p_top1 = user.result;
        } else if (user.result > *p_top2 && user.result < *p_top1) {
            *p_top2 = user.result;
        }
    }
	printf("Top marks are: %.1f and %.1f\n", *p_top1, *p_top2);
    fclose(file);

    FILE *fil = fopen(filename, "r");
    student c_user;
    unsigned long yr, mon, dy, hr, mn, sc;
    while (fscanf(file, "%s %f %s %lu %lu %lu %lu %lu %lu",
                  c_user.name, &c_user.result, c_user.test_type,
                  &yr, &mon, &dy, &hr, &mn, &sc) == 9) {
        c_user.year = yr;
        c_user.month = mon;
        c_user.day = dy;
        c_user.hour = hr;
        c_user.min = mn;
        c_user.sec = sc;

        if (c_user.result == *p_top1 || c_user.result == *p_top2) {
            print_results(&c_user);
        }
                  }
    fclose(fil);
}
void test_time(student* user) {
    time_t t = time(NULL);
    struct tm *local_time = localtime(&t);
    user->year = local_time->tm_year;
    user->month = local_time->tm_mon;
    user->day = local_time->tm_mday;
    user->hour = local_time->tm_hour;
    user->min = local_time->tm_min;
    user->sec = local_time->tm_sec;
}

int menu(){
	int choice;
	printf("\nYou can choose:\n\t1. Do a practice\n"
		"\t2. Complete a test\n\t3. Display top 2 results\n"
		"\t4. Display my history\n\t5. Quit the program");
	printf("\nEnter your choice:");
	scanf("%d", &choice);
	return choice;
}
int menu2() {
	int choice;
	printf("\n\t1. Addition only\n\t2. Subtractions only\n\t3. Addition and subtractions");
	printf("\nYour choice:");
	scanf("%d", &choice);
	return choice;
}
int addition(int *a, int*b) {
	*a = rand() % MAX;
	*b = rand() % (MAX - *a + 1);
	int sum = *a + *b;
	printf("  %d + %d = ", *a, *b);
	return sum;
}
int subtraction(int*a, int*b) {
	*a = rand()%MAX;
	*b = rand()%(*a +1 );
	int diff = *a - *b;
	printf("  %d - %d = ", *a, *b);
	return diff;
}
int random_add_sub(int *a, int *b) {
	int correct;
	int question = rand() % 2 +1;
	if (question == 1) correct = addition(a, b);
	else correct = subtraction(a, b);
	return correct;
}
char* type_of_operation(int choice2) {
	if (choice2 ==1) return "Addition";
	if (choice2 ==2) return "Subtraction";
	return "Addition/Subtraction";
}
int generate_questions(int choice2,int *pa, int *pb) {
	int correct = 0;
	if (choice2 == 1) correct = addition(pa, pb);
	else if (choice2 == 2) correct = subtraction(pa, pb);
	else if (choice2 == 3) correct = random_add_sub(pa, pb);
	return correct;
}
void option1_practice(int *pa, int *pb, int limit) {
	printf("You can choose to do practices on: ");
	int choice2 = menu2();
	for (int i = 1; i < limit+1; i++){
		printf("\n%d.", i);
		int correct = generate_questions(choice2,pa, pb);
		check_answer(correct);
	}
}
void check_answer(int correct) {
	char good[6][25] = {"Very good!", "Excellent!", "Nice work!", "Well done!",
		"Great!", "Keep up the good work!"};
	char bad[5][25] = {"No. Please try again.", "Wrong. Try once again.",
		"Dont give up!", "No. Keep trying.", "Sorry, it is not right."};
	int user;
	printf("\nAnswer:");
	scanf("%d", &user);

	while (user != correct) {
		printf("%s", bad[rand() % 5]);
		printf("\nAnswer:");
		scanf("%d", &user);
	}
	if (user == correct) printf("%s", good[rand() % 6]);
}
float test(int choice2, int *a, int *b) {
	float score = 0;
	int users[TEST], a_values[TEST], b_values[TEST], results[TEST];
	for (int i = 0; i < TEST; i++) {
		printf("\n%d.", i+1);
		int user, correct = generate_questions(choice2,a, b);
		scanf("%d", &user);
		if (user == correct) score += 1;
		a_values[i] = *a;
		b_values[i] = *b;
		results[i] = correct;
		users[i] = user;
	}
	float final = (score/TEST)*100;
	printf("\nYou scored %.2f on this test.", final);
	printf("\nNr\tQuestion\tYour answer\tCorrect answers");
	for (int i = 0; i < TEST; i++) printf("\n%-7d %-2d %c %-10d %-15d %-15d", i+1,
			a_values[i],(results[i] <= a_values[i])?'-':'+' , b_values[i], users[i], results[i]);
	return final;
}

