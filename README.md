Lab-10 : IPC-pipe

####아래와 같은 ipc_producer, ipc_consumer 프로그램을 작성한다. 
- ipc_producer 프로그램은 ‘start’라는 키입력을 받으면 자신의 학번과 PID를
ipc_consumer에 보낸다. 
- ipc_consumer 프로그램은 학번을 받으면 화면에 학번과 ipc_producer의 PID를 화면에
출력하고, 자신의 이름과 자신의 PID를 ipc_producer에 보낸다. 
- 자신의 이름과 ipc_consumer의 PID를 받은 ipc_producer는 화면에 자신의 PID와
  ipc_consumer의 PID, 이름과 학번을 화면에 출력한다. 
  
####ipc_producer와 ipc_consumer의 IPC 방법을 pipe를 사용하여 구현한다. 
