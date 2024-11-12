# 실습과제 1

## 코드설명
        
     while(true)
     {
         gettimeofday(&start,NULL);
 
         cout << "left speed:";
         cin >> leftspeed;
         cout << "right speed:";
         cin >> rightspeed;
         mx.setVelocity(leftspeed, rightspeed); //속도명령 전송
         usleep(20*1000); //20msec sleep
         
         if (ctrl_c_pressed) break; //Ctrl+c 누르면 탈출
 
         gettimeofday(&end1,NULL);
         time1=end1.tv_sec-start.tv_sec +(end1.tv_usec-start.tv_usec)/1000000.0;
         cout << "time:" << time1 << endl; //실행시간 출력
     }

현재 코드에서 가장 핵심인 부분> 속도명령을 입력받은 뒤, **setVelocity** 함수에 값을 입력, _ctrl+c_ 를 입력해서 탈출하는 기능을 추가
마지막 줄에는 실행 시간을 표기함

## 실행 결과

![image](https://github.com/user-attachments/assets/4d07fa2f-89fe-4f66-851c-2ffc7c5dde0a)

## 실습과제 1

### 바로 종료하지 않는 이유

바로 종료하지 않는 이유는 if문에 도달하기 전에 cin에서 코드가 진행중이기 때문이다.

         Dxl mx;
         void ctrlc(int){ ctrl_c_pressed = true; mx.close(), exit(true);}

**Dxl mx;** 는 전역변수로, **void ctrlc**는 내부에 **exit, mx.close**를 추가하여 바로 종료할 수 있게 만들었다.

![image](https://github.com/user-attachments/assets/7081835d-abf9-40cd-8a27-13be426b4c6a)

**mx.close**작업을 하지 않으니, 코드는 종료되어도 기계가 계속 움직여서 수정한 것임.

### 입력한 속도 차이가 클 경우 급가속 또는 급 감속이 되는데 이를 해결할 방안

급가속과 급감속이 되는 이전 속도와 입력된 속도의 차이를 특정 수로 기준잡아서 _ex)25_ 입력받은 속도로 가기 이전에 그 중간속력으로 한번 진행된 뒤, 해당 속도로 간다.
또는 기준보다 속도의 차이가 클 경우, 입력받은 값 까지 +5 또는 -5 (해당 숫자는 자유)씩 반복문으로 속도를 점차 진행시킨다.
