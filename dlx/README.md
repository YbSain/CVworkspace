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

### 바로 종료하지 않는 이유

바로 종료하지 않는 이유는 if문에 도달하기 전에 cin에서 코드가 진행중이기 때문이다.

         Dxl mx;
         void ctrlc(int){ ctrl_c_pressed = true; mx.close(), exit(true);}

**Dxl mx;** 는 전역변수로, **void ctrlc**는 내부에 **exit, mx.close**를 추가하여 바로 종료할 수 있게 만들었다.

![image](https://github.com/user-attachments/assets/7081835d-abf9-40cd-8a27-13be426b4c6a)

**mx.close**작업을 하지 않으니, 코드는 종료되어도 기계가 계속 움직여서 수정한 것임.

