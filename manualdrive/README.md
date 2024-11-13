# 실습과제 1
## 주행영상
> https://youtu.be/9gOvNd_9TE8

## 코드설명

https://github.com/YbSain/CVworkspace/blob/2df4ee9f1ff04aa0fc901310740f546b9d71ef3f/manualdrive/main.cpp#L16-L22

     nvarguscamerasrc sensor-id=0

처음에 나오는 이 요소는 NVIDIA Jetson의 카메라 센서를 사용하는 GStreamer 소스이다.    
1. ```nvarguscamerasrc``` NVIDIA사의 Argus카메라 드라이버를 이용하여 카메라 데이터를 캡쳐하는 사항이다.    
2. ```sensor-id=0``` 2번 문단은 해당부분은 사용하려는 카메라 장치의 *ID*를 나타낸다.(0번 카메라 센서 사용)      

## 

     video/x-raw(memory:NVMM), width=(int)640, height=(int)360, format=(string)NV12, framerate=(fraction)30/1


2열 부분의 ```video/x-raw(memory:NVMM)``` 는 ```NVMM``` 메모리 유형을 사용하여 비디오 데이터를 메모리에 할당한다.    
NVMM은 NVIDIA메모리로, GPU가 더 빠르게 접근하도록 최적화 된 메모리임

     nvvidconv flip-method=0

1. ```nvvidconv```는 비디오 변환 요소로, 비디오 스트림을 변환한다.    
2. ```flip-method=0```은 비디오 프레임을 뒤집지 않도록 설정함.(90, 180, 또는 수평/수직 뒤집기가 가능함)    


### 코드에 영상파일저장 코드 추가하기
