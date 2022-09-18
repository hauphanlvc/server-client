Build and run server
- New version
    ```
    cd $(git rev-parse --show-toplevel) &&  \
    docker compose -f ./docker/docker-compose.yml down && \
    docker compose -f ./docker/docker-compose.yml up -d --build && \
    docker attach server --sig-proxy=false
    ```
- Old version
    ```
    cd $(git rev-parse --show-toplevel) && \
    docker-compose -f ./docker/docker-compose.yml down && \
    docker-compose -f ./docker/docker-compose.yml up -d --build && \
    docker attach server --sig-proxy=false
    ```

Build and run client

- Using docker

    on lab:
    ```
    cd $(git rev-parse --show-toplevel) && \
    docker build -t client:v1 -f ./docker/Dockerfile_client . && \
    docker run --rm -it \
    -e SERVER_IP=192.168.122.239 \
    -e SERVER_PORT=31234 \
    client:v1
    ```
    on localhost:
    ```
    cd $(git rev-parse --show-toplevel) && \
    docker build -t client:v1 -f ./docker/Dockerfile_client . && \
    docker run --rm -it \
    -e SERVER_IP=$(hostname -I | awk '{print $1}') \
    -e SERVER_PORT=1234 \
    client:v1
    ``` 
- Not using docker

    on lab:
    ``` 
    source ./scripts/build_run_client.sh 192.168.122.239 31111
    ```
    on localhost:
    ``` 
    source ./scripts/build_run_client.sh localhost 1234
    ```

- See server log in k8s : 
```
kubectl -n soldiers-ext logs deploy/server server
```

- Create client desktop shortcut:
```
cd $(git rev-parse --show-toplevel) && \
source scripts/create_client_shortcut.sh
```
- Run client with qt:
 on lab:
    ``` 
    source ./scripts/run_client_qt.sh 192.168.122.239 31111
    ```
    on localhost:
    ``` 
    source ./scripts/run_client_qt.sh localhost 1234
    ```