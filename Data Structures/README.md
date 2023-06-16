# Data Structures
The program is designed to simulate transfering data between users. The application allows the user to provide some text which can be later ,,sent" to another user. In reality the message is divided into smaller packages which are randomized and saved to a binary file. After pressing the ,,Receive" button, the data is decoded from the binary file and then presented to the user via textbox. The program is also provided with an option of creating a new file: the binnary file gets deleted and the textbox is cleared. In the bottom right corner there is a console which displays informations about ongoing processes and their execution time.

## Priority Queue
The transfer of packages was implemented by using a priority queue based on a single linked list. It is not the most optimal solution, however the program was designed in aim of sending realtively short messages, therefore the implemented data structure is suitable for this task.

## Compilation
To compile this program the following library is required: wxWidgets 3.2.2.

## Screenshots
![image](https://github.com/Mindflayer77/PAMSI/assets/114955338/5a5631de-45c3-4252-b300-eb03dd2fe6b9)
