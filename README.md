# Zwiggy - Food Delivery System

## Project Overview
Zwiggy is a console-based food delivery system written in C that simulates a real-world food ordering application. It allows users to sign up, log in, browse restaurants, search for food items, place orders, view order history, and manage their cart.

## Features
- **User Authentication**
  - Sign up with username, password and contact number
  - Sign in with existing credentials
  - Data persistence using file system

- **Restaurant Management**
  - View restaurant details including ratings and orders
  - Search restaurants by name
  - Find top-rated restaurants
  - View restaurant menus with food items and prices

- **Food Ordering**
  - Add food items to cart
  - Remove items from cart
  - View cart contents
  - View total bill amount
  - Place orders

- **User History**
  - Track order history
  - View previous orders with details

- **Smart Search**
  - Search for food items across all restaurants
  - Get recommendations when search fails
  - Fuzzy search for food names

## Data Structures Used
- **Linked Lists**: Used for restaurant and user management
- **Queues**: Implemented for order history tracking
- **Stacks**: Used for cart management
- **File Handling**: For persistent data storage

## Project Structure
The project consists of several key data structures:

1. **User**: Stores user information including username, password, contact details, and order history
2. **Restaurant**: Contains restaurant details, ratings, and menu items
3. **Menu**: Stores food items with their names, prices, and unique codes
4. **History**: Implements a circular queue to track order history
5. **Cart**: Implements a stack to manage the current order

## How to Compile and Run
```bash
# Compile the program
gcc Project.c

# Run the program
./zwiggy
```

## Required Files
- **UserData.txt**: Stores user information in CSV format
- **Restaurant.txt**: Stores restaurant and menu information

## File Formats
### UserData.txt
```
username,password,contact,history_codes
```
Where history_codes is a hyphen-separated list of food item codes.

### Restaurant.txt
```
restaurant_name-rating-orders,food_item1-price1,food_item2-price2,...
```

## Usage Guide
1. Launch the application
2. Sign up or sign in
3. Choose from the main menu options:
   - Search restaurants or food items
   - View top-rated restaurants
   - Check order history
   - View cart contents
   - Get total bill
   - Exit and place order

## Functions Overview
- **User Management**:
  - `signUp()`: Register new users
  - `signIn()`: Authenticate existing users
  - `isRegisteredUserName()`: Check if username exists
  - `isPasswordCorrect()`: Validate password

- **Restaurant & Food Management**:
  - `searchRestaurent()`: Find restaurants by name
  - `searchFoodName()`: Search for food items
  - `searchRecommendation()`: Get similar restaurant suggestions
  - `getTopRatedRestaurant()`: Find highest-rated restaurant

- **Cart Operations**:
  - `allocateCart()`: Initialize the cart
  - `pushCart()`: Add items to cart
  - `popCart()`: Remove items from cart
  - `displayCart()`: Show cart contents

- **History Management**:
  - `allcateHistory()`: Initialize history queue
  - `insertHistory()`: Add items to history
  - `deleteHistory()`: Remove items from history
  - `updateHistory()`: Update the history queue
  - `displayHistory()`: Show order history

- **File Operations**:
  - `dataTransferFromFile()`: Load user data
  - `dataTranferRestaurant()`: Load restaurant data
  - `writeUserDataToFile()`: Save user data

## Limitations
- Console-based interface
- Limited error handling
- No encryption for user passwords
- No support for payment methods

## Future Enhancements
- Implement a graphical user interface
- Add secure password storage
- Incorporate payment system integration
- Implement delivery tracking
- Add user reviews and ratings
- Implement better search algorithms

## Contributors
- Tejas-Barde
- Shivansh Dubey
