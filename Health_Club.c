
#define YOGA 100
#define CARDIO 300
#define ZUMBA 200
#define WEIGHT 200
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int floors[16];	//floors[i] <= 16 valid

struct member
{
	int id;
	char name[100];
	int age;
	char gender;
	int program[3][4];	//1.[] = 4_program_type -> 2.[] = time -> 3.[] = trainer id
	int trainer_id;	//assigned trainer
	int time;	//assigned time
	int slot_booked;	//keep track of booked slots
	int fees;
	struct member * next;
};

struct trainer
{
	int id;
	char name[100];
	int program[4];
	int record[16];
	int renumeration_earned;	//depends on Schedule_slot()
	struct trainer * next;
};

void Add_member(struct member **head);
void Add_trainer(struct trainer **head);
int check_free_slots(struct trainer *head_t, int time);
int check_floor(int time);
void Schedule_slot(struct member *head_m, struct trainer *head_t);
void Delete_member(struct member **head_ref, struct trainer *head_t);
void Delete_trainer(struct trainer **head_ref, struct member *head_m);
void Print_hour_wise_list(struct member *head_m);
void Search_member(struct member *head);
void Search_trainer(struct trainer *head);
void Print_member_list(struct member *head);
void Print_trainer_list(struct trainer *head);
void swap(struct trainer *a, struct trainer *b);
void sorted_remuneration_list(struct trainer *start);
void Print_sorted_remuneration_list(struct trainer *head_t);
void Print_intersection_list(struct member *head_m);
void free_member_list(struct member *head);
void free_trainer_list(struct trainer *head);
int menu();

void Add_member(struct member **head)
{
	printf("\nADDING MEMBER\n");
	//create a new node
	struct member *newMember = (struct member *) malloc(sizeof(struct member));
	//adding id
	newMember->id = 1000 + rand() % 9000;	//generate random 4 digit id
	//adding name
	printf("\nEnter Member Name : ");
	char temp[100];
	scanf("%s", temp);
	strcpy(newMember->name, temp);
	//adding age
	printf("Enter age : ");
	int age;
	scanf("%d", &age);
	newMember->age = age;
	//adding gender
	char gender;
	printf("Enter gender (M/F/N) : ");
	scanf(" %c", &gender);
	newMember->gender = gender;
	//adding programs
	int program[4];
	printf("\nEnter 1 for YES, 0 for NO");
	printf("\nApply for YOGA : ");
	scanf("%d", &program[0]);
	printf("Apply for CARDIO : ");
	scanf("%d", &program[1]);
	printf("Apply for ZUMBA : ");
	scanf("%d", &program[2]);
	printf("Apply for WEIGHT LIFTING : ");
	scanf("%d", &program[3]);
	for (int i = 0; i < 4; i++)
		newMember->program[0][i] = program[i];
	//adding fees
	int sum = 0;
	(program[0] == 1) ? sum += YOGA: 0;
	(program[1] == 1) ? sum += CARDIO: 0;
	(program[2] == 1) ? sum += ZUMBA: 0;
	(program[3] == 1) ? sum += WEIGHT: 0;
	newMember->fees = sum;

	//intializing time, trainer id
	for (int i = 0; i < 4; i++)
	{
		newMember->program[1][i] = 0;
		newMember->program[2][i] = 0;
	}

	//initalizing slot_booked
	newMember->slot_booked = 0;

	//if head is NULL, EMPTY list
	if (*head == NULL)
		*
		head = newMember;
	//else find last node and add member
	else
	{
		struct member *lastMemeber = *head;

		//last node's mext add will be NULL
		while (lastMemeber->next != NULL)
		{
			lastMemeber = lastMemeber->next;
		}

		//add at th end
		lastMemeber->next = newMember;
	}

	printf("\nMember is added succesfully !\n");
}

void Add_trainer(struct trainer **head)
{
	printf("\nADDING TRAINER\n");
	struct trainer *newTrainer = (struct trainer *) malloc(sizeof(struct trainer));
	//add id
	newTrainer->id = 1000 + rand() % 9000;
	//adding name
	printf("\nEnter Trainer Name : ");
	char temp[100];
	scanf("%s", temp);
	strcpy(newTrainer->name, temp);
	//adding programs
	int program[4];
	printf("\nEnter 1 for YES, 0 for NO");
	printf("\nApply for YOGA : ");
	scanf("%d", &program[0]);
	printf("Apply for CARDIO : ");
	scanf("%d", &program[1]);
	printf("Apply for ZUMBA : ");
	scanf("%d", &program[2]);
	printf("Apply for WEIGHT LIFTING : ");
	scanf("%d", &program[3]);
	for (int i = 0; i < 4; i++)
		newTrainer->program[i] = program[i];
	//initializig record
	for (int i = 0; i < 15; i++)
		newTrainer->record[i] = 0;

	//if head is NULL, EMPTY list
	if (*head == NULL)
		*
		head = newTrainer;
	//else find last node and add member
	else
	{
		struct trainer *lastTrainer = *head;

		//last node's mext add will be NULL
		while (lastTrainer->next != NULL)
		{
			lastTrainer = lastTrainer->next;
		}

		//add at th end
		lastTrainer->next = newTrainer;
	}

	printf("\nTrainer is added Successfully !\n");
}

//check for free slots after prefered time and return free slot
int check_free_slots(struct trainer *head_t, int time)
{
	while (time <= 21)
	{
		if (head_t->record[time - 6] == 0)
		{
			return time;
		}

		time++;
	}

	return 0;
}

//check floors capacity/aviablability
int check_floor(int time)
{
	if (floors[time] <= 10)
	{
		return 1;
	};
	return 0;
}

void Schedule_slot(struct member *head_m, struct trainer *head_t)
{
	struct member *temp_m = head_m;
	struct trainer *temp_t = head_t;

	//printing trainers list
	Print_trainer_list(head_t);
	printf("\n\nEnter prefernce to assign slots :\n");

	//collecting prefered time and trainer data
	while (temp_m != NULL)
	{
		if (temp_m->slot_booked == 0)
		{
			printf("\n+-----------------");
			printf("\n| ID : %d", temp_m->id);
			printf("\n| Name : %s", temp_m->name);
			printf("\n| The operating hours of the club are from 6:00 to 21:00 hrs :");
			int program_time[4];
			int program_trainer[4];
			if (temp_m->program[0][0] == 1)
			{
				printf("\n| -Enter preferred time for YOGA : ");
				scanf("%d", &program_time[0]);
				temp_m->program[1][0] = program_time[0];
				printf("| -Enter preferred trainer ID for YOGA : ");
				scanf("%d", &program_trainer[0]);
				temp_m->program[2][0] = program_trainer[0];

			}
			else if (temp_m->program[0][1] == 1)
			{
				printf("\n| -Enter preferred time for CARDIO : ");
				scanf("%d", &program_time[1]);
				temp_m->program[1][1] = program_time[1];
				printf("| -Enter preferred trainer ID for CARDIO : ");
				scanf("%d", &program_trainer[1]);
				temp_m->program[2][1] = program_trainer[1];
			}
			else if (temp_m->program[0][2] == 1)
			{
				printf("\n| -Enter preferred time for ZUMBA : ");
				scanf("%d", &program_time[2]);
				temp_m->program[1][2] = program_time[2];
				printf("| -Enter preferred trainer ID for ZUMBA : ");
				scanf("%d", &program_trainer[2]);
				temp_m->program[2][2] = program_trainer[2];
			}
			else if (temp_m->program[0][3] == 1)
			{
				printf("\n| -Enter preferred time for WEIGHT LIFTING : ");
				scanf("%d", &program_time[3]);
				temp_m->program[1][3] = program_time[3];
				printf("| -Enter preferred trainer ID for WEIGHT LIFTING : ");
				scanf("%d", &program_trainer[3]);
				temp_m->program[2][3] = program_trainer[3];
			}

			printf("+-----------------\n");
		}

		temp_m = temp_m->next;
	}

	//assigning the slots
	temp_m = head_m;
	while (temp_m != NULL)
	{
		if (temp_m->slot_booked == 0)
		{
			//trying to book preferred slot
			if (temp_m->program[0][0] == 1)
			{
				while (temp_t != NULL)
				{
					if (temp_t->id == temp_m->program[2][0] && temp_t->record[temp_m->program[1][0] - 6] == 0 && check_floor(temp_m->program[1][0] - 6) == 1)	//checking for trainer id anf free slot avialable to trainer
					{
						temp_t->record[temp_m->program[1][0] - 6] = temp_m->id;
						temp_t->renumeration_earned += YOGA;	//calculating renumeration earned
						temp_m->slot_booked = 1;
						temp_m->time = temp_m->program[1][0];
						temp_m->trainer_id = temp_m->program[2][0];
						floors[temp_m->program[1][0] - 6]++;
						break;
					}

					temp_t = temp_t->next;
				}
			}
			else if (temp_m->program[0][1] == 1)
			{
				temp_t = head_t;
				while (temp_t != NULL)
				{
					if (temp_t->id == temp_m->program[2][1] && temp_t->record[temp_m->program[1][1] - 6] == 0 && check_floor(temp_m->program[1][1] - 6) == 1)
					{
						temp_t->record[temp_m->program[1][1] - 6] = temp_m->id;
						temp_t->renumeration_earned += CARDIO;	//calculating renumeration earned
						temp_m->slot_booked = 1;
						temp_m->time = temp_m->program[1][1];
						temp_m->trainer_id = temp_m->program[2][1];
						floors[temp_m->program[1][1] - 6]++;
						break;
					}

					temp_t = temp_t->next;
				}
			}
			else if (temp_m->program[0][2] == 1)
			{
				temp_t = head_t;
				while (temp_t != NULL)
				{
					if (temp_t->id == temp_m->program[2][2] && temp_t->record[temp_m->program[1][2] - 6] == 0 && check_floor(temp_m->program[1][2] - 6) == 1)
					{
						temp_t->record[temp_m->program[1][2] - 6] = temp_m->id;
						temp_t->renumeration_earned += ZUMBA;	//calculating renumeration earned
						temp_m->slot_booked = 1;
						temp_m->time = temp_m->program[1][2];
						temp_m->trainer_id = temp_m->program[2][2];
						floors[temp_m->program[1][2] - 6]++;
						break;
					}

					temp_t = temp_t->next;
				}
			}
			else if (temp_m->program[0][3] == 1)
			{
				temp_t = head_t;
				while (temp_t != NULL)
				{
					if (temp_t->id == temp_m->program[2][3] && temp_t->record[temp_m->program[1][3] - 6] == 0 && check_floor(temp_m->program[1][3] - 6) == 1)
					{
						temp_t->record[temp_m->program[1][3] - 6] = temp_m->id;
						temp_t->renumeration_earned += WEIGHT;	//calculating renumeration earned
						temp_m->slot_booked = 1;
						temp_m->time = temp_m->program[1][3];
						temp_m->trainer_id = temp_m->program[2][3];
						floors[temp_m->program[1][3] - 6]++;
						break;
					}

					temp_t = temp_t->next;
				}
			}

			//booking any trainer slot at the prefered time
			if (temp_m->slot_booked == 0)
			{
				temp_t = head_t;
				while (temp_t != NULL)
				{
					if (temp_m->program[0][0] == 1 && temp_t->program[0] == 1 && check_floor(temp_m->program[1][0] - 6) == 1 && temp_t->record[temp_m->program[1][0] - 6] == 0)
					{
						temp_t->record[temp_m->program[1][0] - 6] = temp_m->id;
						temp_t->renumeration_earned += YOGA;	//calculating renumeration earned
						temp_m->slot_booked = 1;
						temp_m->time = temp_m->program[1][0];
						temp_m->trainer_id = temp_t->id;
						floors[temp_m->program[1][0] - 6]++;
						printf("\n| Mismatched trainer !");
						break;
					}
					else if (temp_m->program[0][1] == 1 && temp_t->program[1] == 1 && check_floor(temp_m->program[1][1] - 6) == 1 && temp_t->record[temp_m->program[1][1] - 6] == 0)
					{
						temp_t->record[temp_m->program[1][1] - 6] = temp_m->id;
						temp_t->renumeration_earned += CARDIO;	//calculating renumeration earned
						temp_m->slot_booked = 1;
						temp_m->time = temp_m->program[1][1];
						temp_m->trainer_id = temp_t->id;
						floors[temp_m->program[1][1] - 6]++;
						printf("\n| Mismatched trainer !");
						break;
					}
					else if (temp_m->program[0][2] == 1 && temp_t->program[2] == 1 && check_floor(temp_m->program[1][2] - 6) == 1 && temp_t->record[temp_m->program[1][2] - 6] == 0)
					{
						temp_t->record[temp_m->program[1][2] - 6] = temp_m->id;
						temp_t->renumeration_earned += ZUMBA;	//calculating renumeration earned
						temp_m->slot_booked = 1;
						temp_m->time = temp_m->program[1][2];
						temp_m->trainer_id = temp_t->id;
						floors[temp_m->program[1][2] - 6]++;
						printf("\n| Mismatched trainer !");
						break;
					}
					else if (temp_m->program[0][3] == 1 && temp_t->program[3] == 1 && check_floor(temp_m->program[1][3] - 6) == 1 && temp_t->record[temp_m->program[1][3] - 6] == 0)
					{
						temp_t->record[temp_m->program[1][3] - 6] = temp_m->id;
						temp_t->renumeration_earned += WEIGHT;	//calculating renumeration earned
						temp_m->slot_booked = 1;
						temp_m->time = temp_m->program[1][3];
						temp_m->trainer_id = temp_t->id;
						floors[temp_m->program[1][3] - 6]++;
						printf("\n| Mismatched trainer !");
						break;
					}

					temp_t = temp_t->next;
				}
			}

			//booking slot at any time by any trainer
			if (temp_m->slot_booked == 0)
			{
				temp_t = head_t;
				while (temp_t != NULL)
				{
					if (temp_m->program[0][0] == 1 && temp_t->program[0] == 1 && check_free_slots(temp_t, temp_m->program[1][0]) != 0 && check_floor(check_free_slots(temp_t, temp_m->program[1][0]) - 6) == 1)
					{
						temp_t->record[check_free_slots(temp_t, temp_m->program[1][0]) - 6] = temp_m->id;
						temp_t->renumeration_earned += YOGA;	//calculating renumeration earned
						temp_m->slot_booked = 1;
						temp_m->time = check_free_slots(temp_t, temp_m->program[1][0]) - 1;
						temp_m->trainer_id = temp_t->id;
						floors[check_free_slots(temp_t, temp_m->program[1][0]) - 6]++;
						printf("\n| Member ID :(%d) assigned to mismatched time &trainer!", temp_m->id);
						break;
					}
					else if (temp_m->program[0][1] == 1 && temp_t->program[1] == 1 && check_free_slots(temp_t, temp_m->program[1][1]) != 0 && check_floor(check_free_slots(temp_t, temp_m->program[1][1]) - 6) == 1)
					{
						temp_t->record[check_free_slots(temp_t, temp_m->program[1][1]) - 6] = temp_m->id;
						temp_t->renumeration_earned += CARDIO;	//calculating renumeration earned
						temp_m->slot_booked = 1;
						temp_m->time = check_free_slots(temp_t, temp_m->program[1][1]) - 1;
						temp_m->trainer_id = temp_t->id;
						floors[check_free_slots(temp_t, temp_m->program[1][1]) - 6]++;
						printf("\n| Member ID :(%d) assigned to mismatched time &trainer!", temp_m->id);
						break;
					}
					else if (temp_m->program[0][2] == 1 && temp_t->program[2] == 1 && check_free_slots(temp_t, temp_m->program[1][2]) != 0 && check_floor(check_free_slots(temp_t, temp_m->program[1][2]) - 6) == 1)
					{
						temp_t->record[check_free_slots(temp_t, temp_m->program[1][2]) - 6] = temp_m->id;
						temp_t->renumeration_earned += ZUMBA;	//calculating renumeration earned
						temp_m->slot_booked = 1;
						temp_m->time = check_free_slots(temp_t, temp_m->program[1][2]) - 1;
						temp_m->trainer_id = temp_t->id;
						floors[check_free_slots(temp_t, temp_m->program[1][2]) - 6]++;
						printf("\n| Member ID :(%d) assigned to mismatched time &trainer!", temp_m->id);
						break;
					}
					else if (temp_m->program[0][3] == 1 && temp_t->program[3] == 1 && check_free_slots(temp_t, temp_m->program[1][3]) != 0 && check_floor(check_free_slots(temp_t, temp_m->program[1][3]) - 6) == 1)
					{
						temp_t->record[check_free_slots(temp_t, temp_m->program[1][3]) - 6] = temp_m->id;
						temp_t->renumeration_earned += WEIGHT;	//calculating renumeration earned
						temp_m->slot_booked = 1;
						temp_m->time = check_free_slots(temp_t, temp_m->program[1][3]) - 1;	//no idea how this is getting incremented
						temp_m->trainer_id = temp_t->id;
						floors[check_free_slots(temp_t, temp_m->program[1][3]) - 6]++;
						printf("\n| Member ID :(%d) assigned to mismatched time &trainer!", temp_m->id);
						break;
					}

					temp_t = temp_t->next;
				}
			}
		}

		temp_m = temp_m->next;
	}

	printf("\n\t\tSlots are scheduled !\n");
}

void Delete_member(struct member **head_ref, struct trainer *head_t)
{
	printf("\nDELETING MEMBER");
	int key;
	printf("\nEnter Member ID : ");
	scanf("%d", &key);
	// Store head node
	struct member *temp = *head_ref, *prev;

	// If head node itself holds the key to be deleted
	if (temp != NULL && temp->id == key)
	{
		*head_ref = temp->next;	// Changed head
		int trainer_id = temp->trainer_id;
		int time = temp->time;
		(time != 0) ? floors[time - 6]--: 0;
		int program;
		for (int i = 0; i < 4; i++)
		{
			if (temp->program[0][i] == 1)
			{
				program = i;
				break;
			}
		}

		struct trainer *temp_t = head_t;
		while (temp_t != NULL)
		{
			if (temp_t->id == trainer_id)
			{
				temp_t->record[time - 6] = 0;	//clearing the record of booked slot
				int deduct = (program == 0) ? YOGA : (program == 1) ? CARDIO : (program == 2) ? ZUMBA : (program == 3) ? WEIGHT : 0;
				temp_t->renumeration_earned -= deduct;	//deduct remuneration earned
			}

			temp_t = temp_t->next;
		}

		free(temp);	// free old head
		printf("\nMEMBER IS REMOVED !");
		return;
	}

	// Search for the key to be deleted, keep track of the
	// previous node as we need to change 'prev->next'
	while (temp != NULL && temp->id != key)
	{
		prev = temp;
		temp = temp->next;
	}

	// If key was not present in linked list
	if (temp == NULL)
		return;

	// Unlink the node from linked list
	prev->next = temp->next;
	int trainer_id = temp->trainer_id;
	int time = temp->time;
	(time != 0) ? floors[time - 6]--: 0;
	int program;
	for (int i = 0; i < 4; i++)
	{
		if (temp->program[0][i] == 1)
		{
			program = i;
			break;
		}
	}

	struct trainer *temp_t = head_t;
	while (temp_t != NULL)
	{
		if (temp_t->id == trainer_id)
		{
			temp_t->record[time - 6] = 0;	//clearing the record of booked slot
			int deduct = (program == 0) ? YOGA : (program == 1) ? CARDIO : (program == 2) ? ZUMBA : (program == 3) ? WEIGHT : 0;
			temp_t->renumeration_earned -= deduct;	//deduct remuneration earned
		}

		temp_t = temp_t->next;
	}

	free(temp);	// Free memory
	printf("\nMEMBER IS REMOVED !");
}

void Delete_trainer(struct trainer **head_ref, struct member *head_m)
{
	printf("\nDELETING MEMBER");
	int key;
	printf("\nEnter Trainer ID : ");
	scanf("%d", &key);

	// Store head node
	struct trainer *temp = *head_ref, *prev;

	// If head node itself holds the key to be deleted
	if (temp != NULL && temp->id == key)
	{
		*head_ref = temp->next;	// Changed head
		for (int i = 0; i < 16; i++)
		{
			if (temp->record[i] != 0)
			{
				struct member *temp_m = head_m;
				while (temp_m != NULL)
				{
					if (temp_m->id == temp->record[i])
					{
						temp_m->slot_booked = 0;
						temp_m->trainer_id = 0;
						temp_m->time = 0;
						floors[i]--;
					}

					temp_m = temp_m->next;
				}
			}
		}

		free(temp);	// free old head
		printf("\nTRAINER ID REMOVED !");
		return;
	}

	// Search for the key to be deleted, keep track of the
	// previous node as we need to change 'prev->next'
	while (temp != NULL && temp->id != key)
	{
		prev = temp;
		temp = temp->next;
	}

	// If key was not present in linked list
	if (temp == NULL)
		return;

	// Unlink the node from linked list
	prev->next = temp->next;
	for (int i = 0; i < 16; i++)
	{
		if (temp->record[i] != 0)
		{
			struct member *temp_m = head_m;
			while (temp_m != NULL)
			{
				if (temp_m->id == temp->record[i])
				{
					temp_m->slot_booked = 0;
					temp_m->trainer_id = 0;
					temp_m->time = 0;
					floors[i]--;
				}

				temp_m = temp_m->next;
			}
		}
	}

	free(temp);	// Free memory
	printf("\nTRAINER ID REMOVED !");
}

void Print_hour_wise_list(struct member *head_m)
{
	struct member * temp_m;
	printf("\nHOURS WISE LIST");
	for (int time = 6; time <= 21; time++)
	{
		printf("\n\nTime slot : %d:00 : %d:00", time, time + 1);
		temp_m = head_m;
		while (temp_m != NULL)
		{
			if (time == temp_m->time)
			{
				printf("\n+------------");
				printf("\n| Member ID : %d | Member Name : %s", temp_m->id, temp_m->name);
				printf("\n| Trainer ID : %d", temp_m->trainer_id);
				printf("\n+------------");
			}

			temp_m = temp_m->next;
		}
	}

	printf("\n");
}

void Search_member(struct member *head)
{
	printf("\n\nSearch Member based on :\n1. ID\n2. Name\n Choice : ");
	int choice;
	scanf("%d", &choice);
	struct member *temp = head;
	if (choice == 1)
	{
		printf("\nEnter MEMBER ID : ");
		int ID;
		scanf("%d", &ID);
		while (temp != NULL)
		{
			if (temp->id == ID)
			{
				printf("\nMEMBER ID : FOUND !");
				printf("\n+-------------");
				printf("\n| ID : %d", temp->id);
				printf("\n| Name : %s", temp->name);
				printf("\n| Age : %d", temp->age);
				printf("\n| Gender : %c", temp->gender);
				printf("\n| Programs :");
				(temp->program[0][0] == 1) ? printf("\n| -YOGA"): 0;
				(temp->program[0][1] == 1) ? printf("\n| -CARDIO"): 0;
				(temp->program[0][2] == 1) ? printf("\n| -ZUMBA"): 0;
				(temp->program[0][3] == 1) ? printf("\n| -WEIGHT LIFTING"): 0;
				printf("\n| Fees : %d", temp->fees);
				printf("\n+-------------");

				return;
			}

			temp = temp->next;
		}

		printf("\nID : Not Found !");
	}
	else if (choice == 2)
	{
		printf("\nEnter Name : ");
		char name[100];
		scanf("%s", name);
		while (temp != NULL)
		{
			if (strcmp(name, temp->name) == 0)
			{
				printf("\nMEMBER NAME : FOUND !");
				printf("\n+-------------");
				printf("\n| ID : %d", temp->id);
				printf("\n| Name : %s", temp->name);
				printf("\n| Age : %d", temp->age);
				printf("\n| Gender : %c", temp->gender);
				printf("\n| Programs :");
				(temp->program[0][0] == 1) ? printf("\n| -YOGA"): 0;
				(temp->program[0][1] == 1) ? printf("\n| -CARDIO"): 0;
				(temp->program[0][2] == 1) ? printf("\n| -ZUMBA"): 0;
				(temp->program[0][3] == 1) ? printf("\n| -WEIGHT LIFTING"): 0;
				printf("\n| Fees : %d", temp->fees);
				printf("\n+-------------");

				return;
			}

			temp = temp->next;
		}

		printf("\nName : Not Found");
	}
}

void Search_trainer(struct trainer *head)
{
	printf("\n\nSearch Trainer based on :\n1. ID\n2. Name\n Choice : ");
	int choice;
	scanf("%d", &choice);
	struct trainer *temp = head;
	if (choice == 1)
	{
		printf("\nEnter TRAINER ID : ");
		int ID;
		scanf("%d", &ID);
		while (temp != NULL)
		{
			if (temp->id == ID)
			{
				printf("\nTRAINER ID : FOUND !");
				printf("\n+------------");
				printf("\n| Trainer ID : %d", temp->id);
				printf("\n| Name : %s", temp->name);
				printf("\n| Program =");
				(temp->program[0] == 1) ? printf("\n|\tYOGA"): 0;
				(temp->program[1] == 1) ? printf("\n|\tCARDIO"): 0;
				(temp->program[2] == 1) ? printf("\n|\tZUMBA"): 0;
				(temp->program[3] == 1) ? printf("\n|\tWEIGHT LIFTING"): 0;
				printf("\n| Renumeration_earned : %d", temp->renumeration_earned);
				printf("\n+------------");

				return;
			}

			temp = temp->next;
		}

		printf("\nTRAINER ID : Not Found !");
	}
	else if (choice == 2)
	{
		printf("\nEnter TRAINER Name : ");
		char name[100];
		scanf("%s", name);
		while (temp != NULL)
		{
			if (strcmp(name, temp->name) == 0)
			{
				printf("\nTRAINER NAME : FOUND !");
				printf("\n+------------");
				printf("\n| Trainer ID : %d", temp->id);
				printf("\n| Name : %s", temp->name);
				printf("\n| Program =");
				(temp->program[0] == 1) ? printf("\n|\tYOGA"): 0;
				(temp->program[1] == 1) ? printf("\n|\tCARDIO"): 0;
				(temp->program[2] == 1) ? printf("\n|\tZUMBA"): 0;
				(temp->program[3] == 1) ? printf("\n|\tWEIGHT LIFTING"): 0;
				printf("\n| Renumeration_earned : %d", temp->renumeration_earned);
				printf("\n+------------");

				return;
			}

			temp = temp->next;
		}

		printf("\nTRAINER Name : Not Found");
	}
}

void Print_member_list(struct member *head)
{
	struct member *temp = head;
	printf("\nLIST OF MEMBERS\n");
	while (temp != NULL)
	{
		printf("\n+-------------");
		printf("\n| ID : %d", temp->id);
		printf("\n| Name : %s", temp->name);
		printf("\n| Age : %d", temp->age);
		printf("\n| Gender : %c", temp->gender);
		printf("\n| Programs :");
		(temp->program[0][0] == 1) ? printf("\n| -YOGA"): 0;
		(temp->program[0][1] == 1) ? printf("\n| -CARDIO"): 0;
		(temp->program[0][2] == 1) ? printf("\n| -ZUMBA"): 0;
		(temp->program[0][3] == 1) ? printf("\n| -WEIGHT LIFTING"): 0;
		printf("\n| Fees : %d", temp->fees);
		printf("\n| Slot booked for today : ");
		if (temp->slot_booked == 1)
			printf("YES");
		else
			printf("NO");
		printf("\n+-------------");

		temp = temp->next;
	}
}

void Print_trainer_list(struct trainer *head)
{
	struct trainer *temp = head;
	printf("\nLIST OF TRAINERS\n");
	while (temp != NULL)
	{
		printf("\n+------------");
		printf("\n| Trainer ID : %d", temp->id);
		printf("\n| Name : %s", temp->name);
		printf("\n| Program =");
		(temp->program[0] == 1) ? printf("\n|-YOGA"): 0;
		(temp->program[1] == 1) ? printf("\n|-CARDIO"): 0;
		(temp->program[2] == 1) ? printf("\n|-ZUMBA"): 0;
		(temp->program[3] == 1) ? printf("\n|-WEIGHT LIFTING"): 0;
		printf("\n| Renumeration_earned : %d", temp->renumeration_earned);
		printf("\n+------------");

		temp = temp->next;
	}
}

void swap(struct trainer *a, struct trainer *b)
{
	//swapping id
	int temp_id = a->id;
	a->id = b->id;
	b->id = temp_id;
	//swapping name;
	char temp_name[100];
	strcpy(temp_name, a->name);
	strcpy(a->name, b->name);
	strcpy(b->name, temp_name);
	//swapping program
	int temp_prog[4];
	for (int i = 0; i < 4; i++)
		temp_prog[i] = a->program[i];
	for (int i = 0; i < 4; i++)
		a->program[i] = b->program[i];
	for (int i = 0; i < 4; i++)
		b->program[i] = temp_prog[i];
	//swapping record
	int temp_record[16];
	for (int i = 0; i < 16; i++)
		temp_record[i] = a->record[i];
	for (int i = 0; i < 16; i++)
		a->record[i] = b->record[i];
	for (int i = 0; i < 16; i++)
		b->record[i] = temp_record[i];
	//swapping renumeration earned
	int temp_remu_earn = a->renumeration_earned;
	a->renumeration_earned = b->renumeration_earned;
	b->renumeration_earned = temp_remu_earn;
}

void sorted_remuneration_list(struct trainer *start)
{
	int swapped, i;
	struct trainer * ptr1;
	struct trainer *lptr = NULL;

	/*Checking for empty list */
	if (start == NULL)
		return;

	do {
		swapped = 0;
		ptr1 = start;

		while (ptr1->next != lptr)
		{
			if (ptr1->renumeration_earned > ptr1->next->renumeration_earned)
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}

			ptr1 = ptr1->next;
		}

		lptr = ptr1;
	}

	while (swapped);
}

void Print_sorted_remuneration_list(struct trainer *head_t)
{
	printf("\nSORTED (SMALLER - to - LARGER)");
	sorted_remuneration_list(head_t);
	Print_trainer_list(head_t);
}

void Print_intersection_list(struct member *head_m)
{
	printf("\nList of members who have been assigned their preferred trainer.\n");
	struct member *temp = head_m;
	while (temp != NULL)
	{
		int i = 0;
		while (i < 3)
		{
			if (temp->program[0][i] == 1)
			{
				break;
			}

			i++;
		}

		if (temp->trainer_id == temp->program[2][i])
		{
			printf("\n+-------------");
			printf("\n| Member ID : %d | Member Name : %s", temp->id, temp->name);
			printf("\n| Trainer ID : %d", temp->trainer_id);
			printf("\n+-------------");
		}

		temp = temp->next;
	}
}

void free_member_list(struct member *head)
{
	struct member *temp = head, *next_member;

	while (temp != NULL)
	{
		next_member = temp->next;
		free(temp);
		temp = next_member;
	}

	printf("\n\nMembers' List is freed !\n");
}

void free_trainer_list(struct trainer *head)
{
	struct trainer *temp = head, *next_trainer;

	while (temp != NULL)
	{
		next_trainer = temp->next;
		free(temp);
		temp = next_trainer;
	}

	printf("\nTrainers' List is freed !\n");
}

int menu()
{
	printf("\nChoose an option :\n");
	printf("\n1. Add_Member\n2. Add_trainer\n3. Schedule_slot\n4. Print_hour_wise_list\n5. Delete_member\n6. Delete_trainer");
	printf("\n7. Search_member\n8. Search_trainer\n9. Print_member_list\n10. Print_trainer_list\n11. Print_sorted_remuneration_list\n12. Print_intersection_list");
	printf("\n0. exit\n\nEnter option No : ");
	int choice;
	scanf("%d", &choice);

	return choice;
}

int main()
{
	struct trainer *head_t = NULL;
	struct member *head_m = NULL;
	int choice = menu();
	while (choice)
	{
		system("cls");
		if (choice == 1)
		{
			Add_member(&head_m);
		}
		else if (choice == 2)
		{
			Add_trainer(&head_t);
		}
		else if (choice == 3)
		{
			Schedule_slot(head_m, head_t);
		}
		else if (choice == 4)
		{
			Print_hour_wise_list(head_m);
		}
		else if (choice == 5)
		{
			Delete_member(&head_m, head_t);
		}
		else if (choice == 6)
		{
			Delete_trainer(&head_t, head_m);
		}
		else if (choice == 7)
		{
			Search_member(head_m);
		}
		else if (choice == 8)
		{
			Search_trainer(head_t);
		}
		else if (choice == 9)
		{
			Print_member_list(head_m);
		}
		else if (choice == 10)
		{
			Print_trainer_list(head_t);
		}
		else if (choice == 11)
		{
			Print_sorted_remuneration_list(head_t);
		}
		else if (choice == 12)
		{
			Print_intersection_list(head_m);
		}

		printf("\n\nChoose an option - \n0. Exit\n1. Return to Main Menu\n Choice : ");
		int choice2;
		scanf("%d", &choice2);
		if (choice2 == 1)
		{
			system("cls");
			choice = menu();
		}
		else
		{
			choice = 0;
		}
	}

	free_member_list(head_m);
	free_trainer_list(head_t);

	return 0;
}