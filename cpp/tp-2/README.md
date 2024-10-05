# Build

1. Install boost
2. Build with g++

```shell
g++ -Wall --std=c++17  src/**/*.cpp -o server
```

# Run 

1. You can start the server with the following command. The server will listen on port `5555`

```shell
./server
```

2. You can send requests using the samples .txt files with `netcat`

```shell
nc localhost 5555 < helloworld.txt
```

3. You can also use your browser, for instance try the http://localhost:5555/meme route
