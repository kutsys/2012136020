Lab-8 : Multi-threading
1. 아래와 같은 mproc2 프로그램을 작성한다. 
- 학번과 이름을 화면에 출력한다.
- pthread 라이브러리를 사용하여 Lab-7의 subproc을 10개의 thread로 실행시킨다. 
- 각 함수 호출 카운트 값이 20이 되면 해당 쓰레드를 종료시킨다. 
- 10개의 쓰레드가 모두 종료되면 “Finished (thread)”를 출력한다.
