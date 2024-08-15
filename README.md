Snorlax Protocol Stack
======================

<!-- 이 라이브러리는 그녀가 잘 사용하기를 바라면서 만들 것입니다. -->

Visual Studio Code Port Forwarding 기능을 사용하면 클라이언트와 서버의 개발에 여러 컴퓨터를 사용할 수 있습니다. 다만, Visual Studio Code Port Forwarding 기능은 localhost (127.0.0.1) 로만 포워딩되기 때문에, 외부에서 접근하려면 아래와 같은 파워쉘 명령을 수행해야 두 다른 컴퓨터에서 TCP 연결을 수행할 수 있습니다.

```sh
netsh interface portproxy add v4tov4 listenport=6207 listenaddress=172.30.1.59 connectport=6207 connectaddress=127.0.0.1
netsh interface portproxy delete v4tov4 listenport=6207 listenaddress=172.30.1.59
```
