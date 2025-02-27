# littlec

## LinkedList Class (ll.h, "LL")
### Main memory controller :: O(n)
//Info
### Functions

##### long int insertData(int data)
    - Inserts Data to the Main Memory Controller
    - Returns the ID that is associated to the data (long int)
    - If you would like to manually change the memory
        > Reinterpret the ID as a (ptr)

##### bool removeData(long int ID)
    - Removes the Data associated to the ID
    - returns if it was successful

##### int* find(long int ID)
    - Returns the Pointer to the stored Data associated to the ID
    - returns `nullptr` if the ID is invalid.

#### ONLY USE THE GIVEN FUNCTIONS
