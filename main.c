#include <stdio.h>
#include <stdlib.h>


//Implemented suiing linked lists for stack and queue . stack has linked list whose new element is added at head . In queue its added at end . 





int succ = 0;
int rem = 0;
int fail = 0;

struct node {
    int data;
    struct node *next;
};
int stack_maker(struct node **head, int val) {
    struct node *temp = malloc(sizeof(struct node));

    if (temp == NULL) {
        printf("Memory allocation failed\n");
        return -1;
    }

    temp->data = val;
    temp->next = *head;
    *head = temp;
    return 1;
}
int stack_deleter(struct node **head, int *value) {
    if (*head == NULL) {
        return 0;
    }

    struct node *temp = *head;
    *value = temp->data;
    *head = temp->next;
    free(temp);

    return 1;
}
int queue_maker(struct node **head, struct node **tail, int val) {
    struct node *temp = malloc(sizeof(struct node));

    if (temp == NULL) {
        printf("Memory allocation failed\n");
        return -1;
    }

    temp->data = val;
    temp->next = NULL;

    if (*head == NULL) {
        *head = temp;
        *tail = temp;
    } else {
        (*tail)->next = temp;
        *tail = temp;
        return 1;
    }
}
int queue_deleter(struct node **head, struct node **tail, int *value) {
    if (*head == NULL) {
        return 0;
    }

    struct node *temp = *head;
    *value = temp->data;
    *head = temp->next;

    if (*head == NULL) {
        *tail = NULL;
    }

    free(temp);
    return 1;
}
void free_list(struct node **head) {
    int value;

    while (*head != NULL) {
        stack_deleter(head, &value);
    }
}
int main(void) {
    struct node *queue_head = NULL;
    struct node *queue_tail = NULL;
    struct node *stack_head = NULL;
    struct node *stack_head_temp = NULL;

    int n;

    printf("Enter number of commands: ");
    scanf("%d", &n);

    while (n > 0) {
        int command;

        printf("\n1. Arrive\n");
        printf("2. Pick\n");
        printf("3. Deliver\n");
        printf("4.Exit\n");
        printf("Enter the command: ");
        scanf("%d", &command);

        if (command == 1) {
            int val;

            printf("Enter the value: ");
            scanf("%d", &val);

            if(queue_maker(&queue_head, &queue_tail, val)==-1){printf("Error");
                                                              return 0;}
        }

        else if (command == 2) {
            int val;

            if (!queue_deleter(&queue_head, &queue_tail, &val)) {
                printf("Queue is empty\n");
            } 
            
            else {
                stack_maker(&stack_head, val);
                printf("Picked value: %d\n", val);
            }
        }

        else if (command == 3) {
            int val;
            int removed_count = 0;
            int found = 0;

            printf("Enter the value to deliver: ");
            scanf("%d", &val);

            while (stack_head != NULL) {
                int top_value;

                stack_deleter(&stack_head, &top_value);

                if (top_value == val) {
                    found = 1;
                    succ++;
                    break;
                }

                if(stack_maker(&stack_head_temp, top_value) == -1) {
                    printf("Error occurred while creating temporary stack node\n");
                    return 1;
                }
                removed_count++;
                rem++;
            }

            if (!found) {
                printf("Value not found in stack\n");
                fail++;
            }
            while (stack_head_temp != NULL) {
                int temp_value;

                stack_deleter(&stack_head_temp, &temp_value);
                if(stack_maker(&stack_head, temp_value) == -1) {
                    printf("Error occurred while creating stack node\n");
                    return 1;
                }

                removed_count--;
                //rem--;// since the test cases counted tttotal number of temp used not the current elements iin temp
            }

            if (found) {
                printf("Value delivered successfully\n");
            }
        }
        else if(command ==4){
            break;
        }
        else {
            printf("Invalid command\n");
        }

        n--;
    }

    printf("\nSuccessful deliveries: %d\n", succ);
    printf("Temporarily removed elements: %d\n", rem);
    printf("Failed deliveries: %d\n", fail);

    free_list(&queue_head);
    free_list(&stack_head);
    free_list(&stack_head_temp);

    return 0;
}
