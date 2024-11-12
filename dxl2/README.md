# 실습과제 2

## 코드 설명

     if (mx.kbhit()) //키보드입력 체크
     {
         char c = mx.getch(); //키입력 받기
         switch(c){
         case 's': vel1 = 0; vel2 = 0; break; //정지
         case 'f': vel1 = 50; vel2 = -50; break; //전진
         case 'b': vel1 = -50; vel2 = 50; break; //후진
         case 'l': vel1 = -50; vel2 = -50; break; //좌회전
         case 'r': vel1 = 50; vel2 = 50; break; //우회전
         default : vel1 = 0; vel2 = 0; break; //정지
         }
         mx.setVelocity(vel1,vel2);
     }
     if (ctrl_c_pressed) break; //Ctrl+c입력시 탈출

해당 코드로 키 입력을 받고, 속도는 50으로 고정하려 ccw와 cw에 맞게 방향을 조절

## 실행 결과

### 's' 상태 및 실행 직후
![image](https://github.com/user-attachments/assets/ee2af0de-6cf0-4ed0-b0be-1f825a4a1378)

### 'f' 상태
![image](https://github.com/user-attachments/assets/691b0f3f-7a79-4aa1-8a4d-b64c14ed6fd8)

### 'b' 상태
![image](https://github.com/user-attachments/assets/62cfcc9a-5f74-4c04-a52b-34da89953324)

### 'l' 상태
![image](https://github.com/user-attachments/assets/28abff5a-3712-4c6e-b764-616cad67f047)

### 'r' 상태
![image](https://github.com/user-attachments/assets/a4e3f869-04a8-47f6-bfd9-4cab88fc30e6)

## 정지 명령을 입력했을 때와 프로그램 종료 이후, 손으로 움직일 때 느낌

정지 및 실행 직후 상태에서는 손으로 움직이려하면 해당방향으로 쉽게 가지 못하게 가로막힌 느낌이 들며,
프로그램을 종료한 이후에는 손으로 움직일 때 힘들이지 않고 움직여진다.

## ctrl+c를 눌렀을 때 실습과제 1과 다른이유

![image](https://github.com/user-attachments/assets/3cffd617-1c07-4960-b972-e86da63a08cd)

실습과제와 다른이유로는 1번은 cout cin 작업으로 키보드 입력을 받아 처리해야하는 코드가 있었고, 이번 예제 2번 코드에서는 키보드 입력만 받았기에 while반복문으로 인해서 ^C 이후 작업이 바로 나오더라도 작업이 바로 종료된 것 같다.



