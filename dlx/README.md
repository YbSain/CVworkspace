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


