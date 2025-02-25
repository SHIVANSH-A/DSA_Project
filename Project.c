#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void dataTransferFromFile(); // Use in main() To Transfer User data from file // allUser Node is created
void createNode(char *username, char *password, int contact, char *history_code);
struct History *allcateHistory();
void insertHistory(struct History *history, int code);
int deleteHistory(struct History *history);
struct Cart *allocateCart();
void updateHistory(struct History *history, int code); // Use in main() to update history
void dataTranferRestaurant();                          // Use in main() to Transfer Restaurant Rating from file // restaurant node is created
void splitRatingOrders();
struct Menu *createMenu(char name[]);
void splitNameCost();
struct Menu *getUpdatedMenu(struct Menu *menu);
int signUp(); // Use in main() to sign up // currentUser node is created
void assignValuesToSignUpCurrentUser(char username[], char password[], int contact);
int signIn(); // Use in main() to sign in // currentUser node is created
int isRegisteredUserName(char *username);
int isPasswordCorrect(char *username, char *password);
void assignValuesToSignInCurrentUser(char username[], char password[]);
int getContact(char userName[]);
struct History *getHistory(int contact);
void searchRecommendation(char name[]); // gives reccommendation of restaurant name by first letter when user inputs wrong name
struct Restaurant *searchRestaurent(char restaurant_Name[]);
int searchFoodName(char name[]);
int foodNameAssistance();
void FoodMenu();
void foodSelection();
void getTopRatedRestaurant();
void displayHistoryCodeToMenu(int code);
void display();
void displayCurrentUser();
void displayHistory(struct History *history);
void displayRestaurant();
void displayCart();
void writeUserDataToFile();

struct User
{
    char *userName;
    char *password;
    int contact;
    struct History *history;
    struct User *next;
};

struct History
{
    int front;
    int rear;
    int size;
    int *arr;
};

struct Menu
{
    char name[50];
    int cost;
    int code;
    struct Menu *next;
};

struct Restaurant
{
    char name[50];
    float rating;
    int orders;
    struct Menu *menu;
    struct Restaurant *next;
};

struct Cart
{
    int top;
    int *arr;
    int size;
};

int cost = 0;
int code = 100; // Restaurant Food code to track history
struct Cart *cart = NULL;
struct Restaurant *restaurant = NULL; // head node of restaurants
struct User *allUser = NULL;          // head node of linked carrying all users info
struct User *currentUser = NULL;      // current node
struct Restaurant *currentRestaurant = NULL;

void dataTransferFromFile()
{
    FILE *file = fopen("UserData.txt", "r");
    if (file == NULL)
    {
        printf("\nError opening file");
        exit(0);
    }

    char line[100];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        char *username = strtok(line, ",");
        char *password = strtok(NULL, ",");
        int contact = atoi(strtok(NULL, ","));
        char *history_code = strtok(NULL, ",");
        createNode(username, password, contact, history_code);
    }
    fclose(file);
}

void createNode(char *username, char *password, int contact, char *history_code)
{
    struct User *newNode = (struct User *)malloc(sizeof(struct User));
    newNode->userName = strdup(username);
    newNode->password = strdup(password);
    newNode->contact = contact;
    newNode->history = allcateHistory();
    char *code = (strtok(history_code, "-"));
    int i = 0;
    while (i < 5 && code != NULL)
    {
        i++;
        insertHistory(newNode->history, atoi(code));
        code = strtok(NULL, "-");
    }
    newNode->next = NULL;
    if (allUser == NULL)
    {
        allUser = newNode;
    }
    else
    {
        struct User *ptr = allUser;
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = newNode;
    }
}

struct History *allcateHistory()
{
    struct History *history = (struct History *)malloc(sizeof(struct History));
    history->front = -1;
    history->rear = -1;
    history->size = 5;
    history->arr = (int *)malloc(sizeof(int) * history->size);
    return history;
}

void insertHistory(struct History *history, int code)
{
    if (history->front == (history->rear + 1) % history->size)
        printf("\nQueue is full");
    else if (history->front == -1)
    {
        history->front = 0;
        history->arr[++history->rear] = code;
    }
    else
    {
        history->rear = (history->rear + 1) % history->size;
        history->arr[history->rear] = code;
    }
}

int deleteHistory(struct History *history)
{
    if (history->front == history->rear)
    {
        int temp = history->arr[history->front];
        history->front = -1;
        history->rear = -1;
        return temp;
    }
    else
    {
        int temp = history->arr[history->front];
        history->front++;
        return temp;
    }
}

struct Cart *allocateCart()
{
    cart = (struct Cart *)malloc(sizeof(struct Cart));
    cart->top = -1;
    cart->size = 10;
    cart->arr = (int *)malloc(sizeof(int) * cart->size);
    return cart;
}

void pushCart(int code)
{
    if (cart->top == cart->size - 1)
    {
        printf("\nStack is full");
    }
    else
    {
        cart->top++;
        cart->arr[cart->top] = code;
    }
}

int popCart()
{
    if (cart->top == -1)
    {
        printf("\nStack is empty");
        return -1;
    }
    else
    {
        int temp = cart->arr[cart->top];
        cart->top--;
        return temp;
    }
}

void updateHistory(struct History *history, int code)
{
    deleteHistory(history);
    insertHistory(history, code);
}

void dataTranferRestaurant()
{
    FILE *file = fopen("Restaurant.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file\n");
        exit(0);
    }
    char line[300];
    struct Restaurant *temp_restaurant = NULL;
    struct Menu *temp_menu = NULL;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        char *str = strtok(line, ",");
        int count = 0;
        while (str != NULL)
        {
            if (count == 0)
            {
                struct Restaurant *newRestaurant = (struct Restaurant *)malloc(sizeof(struct Restaurant));
                strcpy(newRestaurant->name, str);
                newRestaurant->menu = NULL;
                newRestaurant->next = NULL;
                if (temp_restaurant == NULL)
                {
                    restaurant = newRestaurant;
                    temp_restaurant = newRestaurant;
                }
                else
                {
                    temp_restaurant->next = newRestaurant;
                    temp_restaurant = newRestaurant;
                }
                temp_menu = NULL;
                count++;
            }
            else
            {
                if (temp_menu == NULL)
                {
                    temp_menu = createMenu(str);
                    temp_restaurant->menu = temp_menu;
                }
                else
                {
                    temp_menu->next = createMenu(str);
                    temp_menu = temp_menu->next;
                }
            }
            str = strtok(NULL, ",");
        }
    }
    fclose(file);
    splitNameCost();
    splitRatingOrders();
}

void splitRatingOrders()
{
    struct Restaurant *ptr = restaurant;
    char str[50];
    while (ptr != NULL)
    {
        strcpy(str, ptr->name);
        char *name = strtok(str, "-");
        float rating = atof(strtok(NULL, "-"));
        int orders = atoi(strtok(NULL, ""));
        strcpy(ptr->name, name);
        ptr->rating = rating;
        ptr->orders = orders;
        ptr = ptr->next;
    }
}

struct Menu *createMenu(char name[])
{
    struct Menu *newMenu = (struct Menu *)malloc(sizeof(struct Menu));
    if (newMenu == NULL)
    {
        printf("Memory allocation error\n");
        exit(0);
    }
    strcpy(newMenu->name, name);
    newMenu->code = code++;
    newMenu->next = NULL;
    return newMenu;
}

void splitNameCost()
{
    struct Restaurant *ptr = restaurant;
    while (ptr != NULL)
    {
        ptr->menu = getUpdatedMenu(ptr->menu);
        ptr = ptr->next;
    }
}

struct Menu *getUpdatedMenu(struct Menu *menu)
{
    struct Restaurant *ptr = restaurant;
    struct Menu *ptr_menu = menu;
    while (ptr_menu != NULL)
    {
        char *str = strdup(ptr_menu->name);
        char *name = strtok(str, "-");
        int cost = atoi(strtok(NULL, ""));
        strcpy(ptr_menu->name, name);
        ptr_menu->cost = cost;
        ptr_menu = ptr_menu->next;
    }
    return menu;
}

int signUp()
{
    char username[100], password[100], re_password[100];
    int contact;
    printf("\nEnter User Name - ");
    scanf("%s", username);
    if (isRegisteredUserName(username) == 1)
    {
        printf("\nEntered Username is not Valid");
        printf("\nTry Again Another Username");
        return -1;
    }
    printf("\nEnter Contact - ");
    scanf("%d", &contact);
    printf("\nEnter Password - ");
    scanf("%s", password);
    printf("\nConfirm Password - ");
    scanf("%s", re_password);
    if (stricmp(password, re_password) != 0)
    {
        printf("\nEntered Password is Incorrect\nPlease Re-Enter the Password");
        return -1;
    }
    printf("\nSign Up Successfully");
    assignValuesToSignUpCurrentUser(username, password, contact);
}

void assignValuesToSignUpCurrentUser(char username[], char password[], int contact)
{
    currentUser = (struct User *)malloc(sizeof(struct User));
    currentUser->userName = strdup(username);
    currentUser->password = strdup(password);
    currentUser->contact = contact;
    currentUser->history = allcateHistory();
}

int signIn()
{
    char username[100], password[100], re_password[100];
    printf("\nEnter User Name - ");
    scanf("%s", username);
    if (isRegisteredUserName(username) == -1)
    {
        printf("\nEntered Username is not Valid");
        printf("\nTry Again Another Username");
        return -1;
    }
    printf("\nEnter Password - ");
    scanf("%s", password);
    if (isPasswordCorrect(username, password) == -1)
    {
        printf("\nEnter Password is Incorrect");
        return -1;
    }
    printf("\nLogin Successfully");
    assignValuesToSignInCurrentUser(username, password);
}

int isRegisteredUserName(char *username)
{
    struct User *ptr = allUser;
    while (ptr != NULL)
    {
        if (strcmp(ptr->userName, username) == 0)
            return 1;
        ptr = ptr->next;
    }
    return -1;
}

int isPasswordCorrect(char *username, char *password)
{
    struct User *ptr = allUser;
    while (ptr != NULL)
    {
        if (strcmp(password, ptr->password) == 0)
            return 1;
        ptr = ptr->next;
    }
    return -1;
}

void assignValuesToSignInCurrentUser(char username[], char password[])
{
    currentUser = (struct User *)malloc(sizeof(struct User));
    currentUser->userName = strdup(username);
    currentUser->password = strdup(password);
    currentUser->contact = getContact(username);
    currentUser->history = getHistory(currentUser->contact);

}

int getContact(char username[])
{
    struct User *ptr = allUser;
    while (ptr != NULL)
    {
        if (stricmp(ptr->userName, username) == 0)
            return ptr->contact;
        ptr = ptr->next;
    }
}

struct History *getHistory(int contact)
{
    struct User *ptr = allUser;
    while (ptr != NULL)
    {
        if (contact == ptr->contact)
        {
            return ptr->history;
        }
        ptr = ptr->next;
    }
}

void searchRecommendation(char name[])
{
    printf("\nSearch Not Found");
    printf("\nHere are Some Recommendations for Restraunts- \n");
    struct Restaurant *ptr = restaurant;
    while (ptr != NULL)
    {
        if (name[0] == ptr->name[0])
        {
            printf("Restraunt: %s\t", ptr->name);
            printf("Rating: %f\t\n", ptr->rating);
        }
        ptr = ptr->next;
    }
}

struct Restaurant *searchRestaurent(char restaurant_Name[])
{
    struct Restaurant *temp = restaurant;
    while (temp != NULL)
    {
        if (stricmp(temp->name, restaurant_Name) == 0)
        {
            return temp;
        }
        else
        {
            temp = temp->next;
        }
    }
    return temp;
}

int searchFoodName(char name[])
{
    struct Restaurant *ptr1 = restaurant;
    int flag = 0;
    while (ptr1 != NULL)
    {
        struct Menu *ptr2 = ptr1->menu;
        while (ptr2 != NULL)
        {
            if (stricmp(ptr2->name, name) == 0)
            {
                printf("\nRestaurant - %s\t%s - Cost - %d", ptr1->name, name, ptr2->cost);
                flag++;
            }
            ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }
    return flag;
}

int foodNameAssistance(char name1[], char name2[])
{
    if (stricmp(name1, name2) == 0)
        return 1;

    int i = 0;
    int count = 0;
    while (i < 3 && name1[i] != '\0' && name2[i] != '\0')
    {
        if (name1[i] == name2[i])
            count++;
        i++;
    }
    if (count == 3)
        return 1;

    return -1;
}

void FoodMenu()
{
    struct Menu *temp = currentRestaurant->menu;
    printf("\n\n !! Menu !! \n\n");
    while (temp != NULL)
    {
        printf("%s\t %d", temp->name, temp->cost);
        printf("\n");
        temp = temp->next;
    }
}
void foodSelection()
{
    char foodname[50]; 
    printf("\nWelcome to %s Cart", currentRestaurant->name);
    printf("\nEnter 'e' to exit the cart");
    printf("\nEnter 'r' to remove an item from the cart");
    
    while (1) {
        printf("\n\nEnter Food Name: ");
        scanf("%s", foodname);
        
        if (foodname[0] == 'e') {
            break;
        }
        
        if (foodname[0] == 'r') {
            int itemCode = popCart();
            if (itemCode == -1) {
                printf("\nCart is empty. Nothing to remove.");
                continue;
            }
            
            updateHistory(currentUser->history, itemCode);
            
            struct Menu *temp = currentRestaurant->menu;
            int found = 0;
            
            while (temp != NULL) {
                if (itemCode == temp->code) {
                    printf("\n%s has been removed from your cart", temp->name);
                    found = 1;
                    break;
                }
                temp = temp->next;
            }
            
            if (!found) {
                printf("\nItem with code %d was removed from your cart", itemCode);
            }
            continue;
        }
        
        struct Menu *temp = currentRestaurant->menu;
        int found = 0;
        
        while (temp != NULL) {
            if (foodNameAssistance(foodname, temp->name) == 1) {
                printf("\n%s has been added to your cart", temp->name);
                updateHistory(currentUser->history, temp->code);
                cost += temp->cost;
                pushCart(temp->code);
                found = 1;
                break;
            }
            temp = temp->next;
        }
        
        if (!found) {
            printf("\nItem not found. Please try again.");
        }
    }
    printf("\nExiting food selection.\n");
}
void getTopRatedRestaurant()
{
    struct Restaurant *temp = restaurant;
    float rating = 0;
    int order = 0;
    struct Restaurant *temp2;
    while (temp != NULL)
    {
        if (temp->rating > rating && temp->orders > order)
        {
            rating = temp->rating;
            order = temp->orders;
            temp2 = temp;
        }
        temp = temp->next;
    }
    printf("\nTop rated restaurant: %s", temp2->name);
    printf("\nIts rating: %f", temp2->rating);
}

void displayHistoryCodeToMenu(int c)
{
    struct Restaurant *ptr1 = restaurant;
    while (ptr1 != NULL)
    {
        struct Menu *ptr2 = ptr1->menu;
        while (ptr2 != NULL)
        {
            if (c == ptr2->code)
                printf("\n Resataurant Name - %s\tFood Item - %s\tcost - %d", ptr1->name, ptr2->name, ptr2->cost);
            ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }
}

void display()
{
    struct User *ptr = allUser;
    while (ptr != NULL)
    {
        printf("\nName - %s", ptr->userName);
        printf("\nPassword - %s", ptr->password);
        printf("\nContact - %d", ptr->contact);
        printf("\nHistory - ");
        displayHistory(ptr->history);
        ptr = ptr->next;
    }
}

void displayCurrentUser()
{
    struct User *ptr = currentUser;
    while (ptr != NULL)
    {
        printf("\nName - %s", ptr->userName);
        printf("\nPassword - %s", ptr->password);
        printf("\nContact - %d", ptr->contact);
        printf("\nHistory - ");
        displayHistory(ptr->history);
        ptr = ptr->next;
    }
}

void displayHistory(struct History *history)
{
    printf("\n User History - ");
    if (history == NULL)
        printf("\nCart is Empty");
    int i = history->front;
    while (i != history->rear)
    {
        displayHistoryCodeToMenu(history->arr[i]);
        i = (i + 1) % history->size;
    }
    displayHistoryCodeToMenu(history->arr[i]);
}

void displayRestaurant()
{
    printf("\nDisplay Restaurant - ");
    struct Restaurant *ptr = restaurant;
    while (ptr != NULL)
    {
        printf("\nName - %s", ptr->name);
        printf("\nRating - %f", ptr->rating);
        printf("\nOrders - %d", ptr->orders);
        struct Menu *menu = ptr->menu;
        while (menu != NULL)
        {
            printf("\n  Menu Name - %s", menu->name);
            printf("\n  Cost - %d", menu->cost);
            printf("\n Menu code - %d", menu->code);
            menu = menu->next;
        }
        ptr = ptr->next;
    }
}

void displayCart()
{
    if (cart == NULL || cart->top == -1)
    {
        printf("\nCart is Empty");
        return;
    }

    printf("\nDisplay Cart - ");
    for (int i = cart->top; i >= 0; i--)
    {
        displayHistoryCodeToMenu(cart->arr[i]);
    }
}

void writeUserDataToFile()
{
    FILE *file = fopen("UserData.txt", "a");

    if (file == NULL)
    {
        printf("\nError opening file");
        exit(1);
    }

    fprintf(file, "\n%s,%s,%d,", currentUser->userName, currentUser->password, currentUser->contact);
    fclose(file);
}

int main()
{
    currentRestaurant = (struct Restaurant *)malloc(sizeof(struct Restaurant));
    if (currentRestaurant == NULL) {
        printf("Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    dataTransferFromFile();
    dataTranferRestaurant();
    allocateCart();
    
    printf("Welcome To Zwiggy\n\n");
    
    while (1) {
        printf("\nPress 1 for Sign-in\nPress 2 for Sign-up\nSelect Option: ");
        int signup_signin;
        if (scanf("%d", &signup_signin) != 1) {
            while (getchar() != '\n');
            printf("Please enter a valid number\n");
            continue;
        }
        
        if (signup_signin == 1) {
            if (signIn() == -1) {
                printf("Sign-in failed. Please try again.\n");
                continue;
            }
            
            while (1) {
                printf("\nEnter 1 to Search Restaurants\n"
                       "2 Top Rated Restaurants\n"
                       "3 for Your Order History\n"
                       "4 display cart\n"
                       "5 To get Total bill\n"
                       "6 to exit\n"
                       "Choose Option: ");
                
                int choice;
                if (scanf("%d", &choice) != 1) {
                    while (getchar() != '\n');
                    printf("Please enter a valid number\n");
                    continue;
                }
                
                switch (choice) {
                    case 1: {
                        while (1) {
                            printf("\n\nSearch Food Name or Restaurant: ");
                            char name[100];
                            scanf("%s", name);
                            
                            currentRestaurant = searchRestaurent(name);
                            int flag = searchFoodName(name);
                            
                            if (currentRestaurant == NULL && flag == 0) {
                                searchRecommendation(name);
                                continue;
                            } else if (currentRestaurant == NULL) {
                                printf("No matches found. Try a different search term.\n");
                                continue;
                            } else {
                                FoodMenu();
                                foodSelection();
                                break;
                            }
                        }
                        break;
                    }
                    case 2:
                        getTopRatedRestaurant();
                        break;
                    case 3:
                        displayHistory(currentUser->history);
                        break;
                    case 4:
                        displayCart();
                        break;
                    case 5:
                        printf("\nTotal Cost: %d\n", cost);
                        break;
                    case 6:
                        printf("\nOrder is Placed Successfully\n");
                        printf("Bill Amount: %d\n", cost);
                        printf("Thank You\n");
                        
                        free(currentRestaurant);
                        return EXIT_SUCCESS;
                    default:
                        printf("Please enter a valid option (1-6)\n");
                }
            }
        } else if (signup_signin == 2) {
            if (signUp() == -1) {
                printf("Sign-up failed. Please try again.\n");
                continue;
            }
            
            writeUserDataToFile();
            printf("Sign-up successful! Please sign in.\n");
            continue;
        } else {
            printf("Please enter 1 or 2\n");
        }
    }
    
    free(currentRestaurant);
    return EXIT_SUCCESS;
}