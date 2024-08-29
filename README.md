Snorlax Protocol Stack
======================

<!-- 이 라이브러리는 그녀가 잘 사용하기를 바라면서 만들 것입니다. -->

Visual Studio Code Port Forwarding 기능을 사용하면 클라이언트와 서버의 개발에 여러 컴퓨터를 사용할 수 있습니다. 다만, Visual Studio Code Port Forwarding 기능은 localhost (127.0.0.1) 로만 포워딩되기 때문에, 외부에서 접근하려면 아래와 같은 파워쉘 명령을 수행해야 두 다른 컴퓨터에서 TCP 연결을 수행할 수 있습니다.

```sh
netsh interface portproxy add v4tov4 listenport=6207 listenaddress=172.30.1.59 connectport=6207 connectaddress=127.0.0.1
netsh interface portproxy delete v4tov4 listenport=6207 listenaddress=172.30.1.59
```

- DEVELOPMENT ENV (UBUNTU)

```sh
$ sudo apt install cmake
$ sudo apt install build-essential
```
- BUILD

```sh
$ cmake -DCMAKE_BUILD_TYPE=Debug -B build
$ cmake --build build --target all
```


> 코드를 짜는 것에 있어서 약자를 쓰지 않고, 함수의 길이가 길더라도 소스를 유추할 수 있도록, 
> 이름을 정하기로 하였습니다.
> 이렇게 짜고 나니, 변수나 함수의 길이가 길어서 가독성이 떨어지는 경향이 있다.
> 요즘 모니터들이 가로 방향으로 길게 나오기 때문에,
> 큰 지장이 없다.
> 다만, 창을 분할하여 사용하는 사람들은 조금 코드를 읽기 어려울 것이다.
> 차후에, EXPOSE 할 함수들을 정리할 때, 매크로를 통하여 약자를 지원하도록 하여, 긴 함수와 짧은 매크로를 동시에 사용할 수 있도록 할 것이다.
> 라이브러리의 경우 구조체는 거의 HIDDEN 으로 처리할 것이지만, 상속을 할 수 있도록 구현한 구조체
> 혹은 상속이 필요한 구조체들은 EXPOSE 할 수 있도록 할 것이다.
> typedef 으로 구조체는 약자를 지원하도록 할 것이다.
