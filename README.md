# littlec

## building the program.
```bash
make lexer
```

## Test the Data Set.
```bash
make million
```

## million
> Runs the 100,000 word Data set

## end
> End the program  
> Denoted with a 'end;'

## Comparators
> '~' -> equal to  
> '|' -> not equal to  
> '>' -> greater than  
> '<' -> less than  

## operators
> '*' -> multiply  
> '/' -> divide  
> '+' -> add  
> '-' -> subtract  
> '{var_name}++' -> increment  
> '{var_name}--' -> decrement  
  

## var Declarations
> 'int {var_name} = {var_data};'  
>     - creates a new integer variable  
> 'char {var_name} = '{var_data}';'  
>     - creates a new character variable  
> 'string {var_name} = "{var_data}";'  
>     - creates a new string variable  


## while
> 'while {var} {comp} {second_var} {'  
>     - compares the {var} with {second_var} using the {comp} comparator.  
>     - Will execute code in the while loop aslong as the comparator is returning __true__  
  
## If
> 'if {var} {comp} {second_var} {'  
>     - compares the {var} with {second_var} using the {comp} comparator.  
>     - Will execute code in the i loop if the comparator is returning __true__  

# print
> 'print {var}'  
>     - Prints the variables data.  

# The interpreter will tell you if there is a syntax error.  

## If Statement Example
```c++
int x = 1;
int y = 2;
if x < y {
    print x;
}
end;
```
## Nested If Statement Example
```c++
int a = 3;
int b = 3;
int c = 2;
if a ~ b {
    print a;
    if c < b {
        print b;
    }
}
end;
```

## While Loop Statement Example
```c++
int x = 3;
int y = 5;
while x < y {
    print x;
    x++;
}
end;
```
