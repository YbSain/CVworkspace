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

### 속도조절
https://github.com/YbSain/CVworkspace/blob/2df4ee9f1ff04aa0fc901310740f546b9d71ef3f/manualdrive/main.cpp#L72-L84

속도 조절에 관한 코드이다.
## 코드에 영상파일저장 코드 추가하기

     VideoWriter savefile("manualdrive.avi", VideoWriter::fourcc('X', '2', '6', '4'), (double)30, true);
     savefile.write(frame);

두 줄을 적절한 위치에 배정해서 영상 파일로 저장할 수 있다.


결론
현재 코드 구조는 잘 구성되어 있지만, 성능 최적화와 실시간 반응성 향상을 위해 몇 가지 개선이 필요합니다. 이미지 처리 속도를 높이거나, 모터 제어의 변화를 부드럽게 하고, 비디오 처리와 모터 제어를 병렬로 처리하는 방법을 고려하면 더 매끄러운 동작을 얻을 수 있을 것입니다. 또한, 멀티스레딩을 통해 비디오 프레임을 읽고 모터 속도를 제어하는 시간을 병렬로 처리하는 방법을 적용하면 더욱 효율적이고 안정적인 시스템을 만들 수 있습니다.





