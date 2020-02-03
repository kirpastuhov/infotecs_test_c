Infotecs Test Task in C
===

## Table of Contents
* [Infotecs Test Task in C](#Infotecs-Test-Task-in-C)
     * [Table of Contetns](#Table-of-Contetns)
     * [Getting started](#Getting-started)
     * [Test task description](#Test-task-description)
     * [Examples](#Examples)

## Getting started
Get yourself a copy and start the server by pasting the following lines into your terminal:

``` 
git clone https://github.com/kirpastuhov/infotecs_test_c.git
cd infotecs_test_c/
make
./server
```
You may need to install [mhash](http://mhash.sourceforge.net)


## Test task description
Write a web server that implements the HTTP 1.0 protocol. Requirements:
    
###  1. The server supports up to 1,000 parallel connections
### 2. The total request processing speed on a processor comparable to an Intel Xeon E5-2620 2.10GHz is at least 70,000 requests/second.
### 3. POST request, responses 200 and 404, and Content-type - application/json have been implemented.
### 4. The POST server receives data on request, calculates two hash functions (GOST R 34.11-94 and SHA512) from these data and returns the result.
### 5. At the input of the POST request with the following json-content:
    {
        "data":"hhadhskfhjdkslhfklashdfklashdfklashdfklashdfklashdfklashdfklashdfklashdklashdfklashdf"
    }
### where data is the data from which hash functions must be calculated; the maximum data size is 1,024 bytes.
### 6. There is an answer with the following json-content at the output:
```
{ 
"sha512"
"4adfbbf00cd146301af5f0661b55d13439a14f6755b6dd03ad5ccf5efc85c812347f1050f2e481620d7a7ba588a5df5f30bc04f896903ae09217a6e6d4abd",
"gost" "b75a0ac84397a0b2329316e333a58338a32a0ec2cc6e0e9843f9cfa80eb696f0."
}
```
### where sha512 is the SHA512 hash sum from the submitted data, GOST hash sum from the submitted data.

## Examples
```
curl  -X POST -H 'Content-type: application/json' --data '{"data":"abc"}' 'localhost:8000/hashes'
```

![](https://i.imgur.com/iGMns8g.png)
