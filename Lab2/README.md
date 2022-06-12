## CSCI-UA 202 Lab02

*Yuheng Lu, yl7789, April 2022*

1. To compile main.c file, run the command:
   - cc -o lab02 main.c
   
2. To run the complied file, run the command:
   - ./lab02 n SA q(optional) R1<sub>1</sub> B1<sub>1</sub> R2<sub>1</sub> B2<sub>1 </sub>... R1<sub>n</sub> B1<sub>n</sub> R2<sub>n</sub> B2<sub>n </sub>
   
   - n: The number of processes.
   
   - SA: The scheduling algorithm to use. 1 signifies FIFO; 2 signifies RR with
   
     quantum q. 
   
   - q: quantum, needed to be specified only running RR scheduling (SA = 2)
   
   - R1<sub>1</sub> B1<sub>1</sub> R2<sub>1</sub> B2<sub>1 </sub>... R1<sub>n</sub> B1<sub>n</sub> R2<sub>n</sub> B2<sub>n </sub>: The four running and blocking times for each process. Note that all four values for P<sub>i</sub> are given before any values for P<sub>i</sub>+1. Remember that each P<sub>i</sub> runs a third time, in order to terminate. Since that last run is always for 1 time unit, no input is needed for its specification.
   
   - Here is are the examples of how to run the examples from pdf document; the first line will run in FIFO scheduling; the second line will run in RR scheduling:
   
     ```
     ./lab02 2 1 3 2 3 2 3 2 3 2
     ./lab02 2 2 2 3 2 3 2 3 2 3 2
     ```

