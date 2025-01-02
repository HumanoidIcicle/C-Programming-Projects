#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define MAX 100
#define PRACTICE 10
#define TEST 15
int menu();
int menu2();
int addition(int *a, int*b);
int subtraction(int*a, int*b);
void check_answer(int correct);
int random_add_sub(int *a, int *b);
int generate_questions(int choice2,int *pa, int *pb);
void practice(int *pa, int *pb, int choice2, int limit);
void test(int choice2, int *a, int *b, int *a_values, int *b_values, int *results);

int main(void) {
	srand(time(NULL));
	char name[15];
	int a, b, *pa = &a, *pb = &b;

	printf("Enter your name:");
	scanf("%s", name);
	name[0] = toupper(name[0]);
	printf("Welcome, %s", name);
	while (1) {
		int choice = menu();
		if (choice == 1){
			printf("You can choose to do practices on: ");
			int choice2 = menu2();
			practice(pa, pb, choice2, PRACTICE);
		}
		else if (choice == 2) {
			printf("Take a test on: ");
			int choice2 = menu2();
			int a_values[TEST], b_values[TEST], results[TEST];
			test(choice2, pa, pb , a_values, b_values, results);
		}
		else if (choice == 3) break;
		else printf("\nChoice not on the menu. Select again.");
	}
	return 0;
}

int menu(){
	int choice;
	printf("\nYou can choose:\n\t1. Do a practice\n"
		"\t2. Complete a test\n\t3. Quit the program");
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
	printf("\t%d + %d = ", *a, *b);
	return sum;
}
int subtraction(int*a, int*b) {
	*a = rand()%MAX;
	*b = rand()%(*a +1 );
	int diff = *a - *b;
	printf("\t%d - %d = ", *a, *b);
	return diff;
}
int random_add_sub(int *a, int *b) {
	int correct;
	int question = rand() % 2 +1;
	if (question == 1) correct = addition(a, b);
	else correct = subtraction(a, b);
	return correct;
}
int generate_questions(int choice2,int *pa, int *pb) {
	int correct = 0;
	if (choice2 == 1) correct = addition(pa, pb);
	else if (choice2 == 2) correct = subtraction(pa, pb);
	else if (choice2 == 3) correct = random_add_sub(pa, pb);
	return correct;
}
void practice(int *pa, int *pb, int choice2, int limit) {
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
void test(int choice2, int *a, int *b, int a_values[], int b_values [],int results[]) {
	float score = 0;
	int users[TEST];
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
}
