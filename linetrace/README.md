# 유튜브 링크 

https://youtu.be/uKRLkhhVYKI

# 정리

https://github.com/YbSain/CVworkspace/blob/a0ea67aa84102feed9ac5c457ffd2c65a42abfba/linetrace/main.cpp#L11-L21

동작 및 함수에 관련된 파트들이다.

https://github.com/YbSain/CVworkspace/blob/a0ea67aa84102feed9ac5c457ffd2c65a42abfba/linetrace/main.cpp#L32-L47

해당 파트에서 cap으로 "7_it_ccw_100rpm_in.mp4" 영상을 입력받고, 그것을 gstream으로 윈도우즈의 powershell 환경에서 확인할 수 있게 만들었다.

writer2는 사이즈를 640, 90으로 따로 조절 해 주었음.

https://github.com/YbSain/CVworkspace/blob/0889c5afc8b5aceb50e80173acf98271cf089b5f/linetrace/main.cpp#L61

메인 코드 내부에서 while(true) 반복문 시작과 동시에 시간을 측정시키기 위해 사용되었다.

https://github.com/YbSain/CVworkspace/blob/0889c5afc8b5aceb50e80173acf98271cf089b5f/linetrace/main.cpp#L67-L69

해당 과정은 원본 > Roi범위 > GrayScale > 밝기 조절 > 이진화 > 잡음관리까지 포함시킨 Mat makethresh()를 사용하였고, 추후 레이블링을 하기 위해서 clone()을 만들어, GrayScale영상을 하나 구비 해 두었다.

https://github.com/YbSain/CVworkspace/blob/0889c5afc8b5aceb50e80173acf98271cf089b5f/linetrace/main.cpp#L100-L123

위에서 사용된 makethresh() 내부 모습인데, 640x360 중 높이가 90cm인 하단 부분을 Roi범위로 지정하고 싶어, y점을 270으로 지정하였다.

Mat frame은 원본영상을 그대로 받아두었고, mean()함수를 사용하여 기존 영상의 밝기를 변수에 초기화한 뒤, 원하는 밝기를 선정하여서

밝기 계산을 위한 값 = 원하는 밝기 - 현재 밝기를 사용하여 현재 밝기가 원하는 밝기보다 밝을 경우 음수 값이 나오고, 어두울 경우 양수 값이 나오는데

converTo() 함수를 이용하여 같은 영상조건으로 해당 수치만큼 셈하도록 만들었음.

이후에는 이진화 및, 잡음 추가 작업이 이루어져있다.



