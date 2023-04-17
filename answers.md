# CMPS 6100 Lab 10
## Answers

**Name:** 

Place all written answers from `lab-10.md` here.

# Network Exploration (4 pts)

1. Examine the resulting output of ping command. For each of the websites, 
create a table and report average roundtrip time and the time of the day 
when you made the measurements.


2.	Execute nslookup using the following parameters and report the outcome (what is a non-authorative answer?)
  - iana.com
  - nola.com
  - google.com
  - 172.253.62.100

3. Execute `netstat` and wait for it to complete (stop if you wait longer than 5 minutes). Examine the output.
  - In the local or foreign address column you might see an IP address and 
  some additional number (like 61262) separated by a colon or period. What 
  is the meaning of that number?

4. Execute `ip address show`.
  - What devices are listed? (Hint: the first device is `lo`)
    - What is the IPv4 address of the `lo` device?
    - What does the `/8` at the end of the device indicate?
  - What is the IPv4 address of `eth0`?
  - What is the IPv6 address of eth0?

5. In `server.c` what do each of the following calls do?
    - `socket()`
    - `bind()`
    - `listen()`
    - `accept()`

6. In `client.c` what do each of the following calls do?
    - `socket()`
    - `connect()`

# Running the Client/Server

7. What happens to these 5 clients? Do their `connect()`'s fail, or time 
out, or succeed?

8. Now let the first client exit (`ctrl-c`). What happens?