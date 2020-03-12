# Leader Election
Erick Juarez juarez.erick16@csu.fullerton.edu

# Running the program 
## Compile
compile source code to make an executable called *select-leader* with the following command:

``` mpic++ leader-election.cpp -o select-leader```

## Execute 
Run executable file with 20 Processors with the following command: 

``` mpirun -n 20 ./select-leader```

Replace 20 with the number of processors to run teh program; tested up to 80 processors

note that you need to run the program with at least 2 processors

# Problem Descripion  
## Ring topology 

Given a destributed system with N processes, communication in a ring is achieved with the following rules: 
- Process of rank K (k > 0) receives the message from the process of rank k-1
- Process of rank K (K >= 0) sends a message to the process of rank k+1

## Concurrent two leader electoin algorithm

1. Process 0 generates a random value `V0`:
   - if `V0` is even, Process 0 sends `V0` *and* `9999` to process 1
   - if `V0` is odd, Process 0 sends `V0` *and* `9990` to process 1 
 
2. Process 1 receives `V0` and (`9999` or `9990`) from Process 0 and generates a random value `V1`: 
    - if `V1` is odd, it compares it with the odd value received from Process 0\*   
    - if `V1` is even, it compares it with the even value received from Process 0
     
     
       \**`V1` will be compared to `V0` if they are both odd or both even.*
      *`V1` will be compared to `9990` if `V1` is even and `V0` is odd.*
      *`V1` will be compared to `9999` if `V1` is odd and `V0` is even.*
    - The smallest value from the comparason and the other unchanged value will be sent to Process 2
  3. Process 2 and all the following processes will do the same check  
  
  4. Values will travel the entire ring then back to Process 0. 
  
  5. The Process that generated the smallest even number will be declared President by Process 0
  
  6. The Process that generated the smallest odd number will be declared Vice-president by Process 0
 
 ## Pseudocode

 1. Initialize Communicator environment and variables

   - int `even` , int `even_rank`    
   - int `odd` , int `odd_rank` 


2. If Rank is 0 
   - Generate random number 

   - If random number is even: 
      - `even` = random number , `even_rank` = 0 
      - `odd` = 9999, `odd_rank` = 0 

   - Else if random number is odd 
      - `even` = 9990, `even_rank` = 0
      - `odd` = random number, `odd_rank` = 0 

   - Use blocking communication to send `even`, `even_rank`, `odd`, `odd_rank` to Rank 1 

      **The following code will run after All other ranks finish execution*

   - Use blocking communication to receive `even`, `even_rank`, `odd`, `odd_rank` from last Rank

   - Declare President and Vice-president 
      - President will be `even_rank` and Vice-president will be `odd_rank`

3. Else if Rank not Equal to 0 

   - Rank receives `even`, `even_rank`, `odd`, `odd_rank` from Rank - 1 

   - Rank Generates a random value

   - If random value is even 
      - If random value is smaller than `even` 
         - `even` = random value , `even_rank` = Rank that generated this value 

   - If random value is odd 
      - If random value is smaller than `odd`
         - `odd` = random value , `odd_rank` = Rank that generated this value 

   - Use blocking communication to send `even`, `even_rank`, `odd`, `odd_rank` to Rank + 1 

4. Finalize Communication 
 
## Screenshots 

### Full screen 
![alt text](https://github.com/EvilErick16/HPC/blob/master/leader-election/Full_Screen_SC.jpg)

### 10 Processors 
![alt text](https://github.com/EvilErick16/HPC/blob/master/leader-election/n10_sc.jpg)

### 50 Processors 
![alt text](https://github.com/EvilErick16/HPC/blob/master/leader-election/n50_sc.jpg)