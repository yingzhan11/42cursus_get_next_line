# About my code
At first, I tried to use linked list to write this function, unfortunately there is memory leak problem in two francinette test (read_error test when BUFFER_SIZE is 10 and 10000).

I tried to fix it, but cannot do. So I change to the common method with static char *array.

I also upload the linked list version, may know how to fix it in the future.

# IMPORTANT!
1.**Check memory leak!!! Everywhere!!!**

2.Use ssize_t for the return value of read function, not size_t, because the error value is -1.

3.for Bonus part, check fd, the max is OPEN_MAX

# Useful Links
**fd** https://www.codequoi.com/en/handling-a-file-by-its-descriptor-in-c/

**read()** https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/

**EOF** https://ruslanspivak.com/eofnotchar/

**static variables** https://www.codequoi.com/en/local-global-static-variables-in-c/

**get_next_line tutorial** https://www.youtube.com/watch?v=8E9siq7apUU&t=1s
_This tutorial use linked list, so it would have memory leak, but the logical is same with using a static variable_
