# Environment Setting Guide
참조한 가이드  
[YOLO(Darknet) 설치 - Windows ver](https://mickael-k.tistory.com/15)
[HOW TO BUILD OPENCV FOR WINDOWS WITH CUDA](https://lightbuzz.com/opencv-cuda/)

## 1. Visual Studio 설치
[VS 다운로드 링크](https://visualstudio.microsoft.com/ko/)  
*설명 생략*  


## 2. CUDA & cuDNN 설치
### 2.1. 그래픽카드 확인
#### 2.1.1. 장치 관리자에서 확인
![device_manager](https://i.imgur.com/FSKpzFx.png)  
[시작] - [장치 관리자] - [디스플레이 어댑터]
#### 2.1.2. GPU-Z 프로그램 이용
GPU-Z [다운로드 링크](https://software.naver.com/software/summary.nhn?softwareId=MFS_100082)

### 2.2. CUDA 버전 확인
[CUDA 공식 웹사이트](https://www.wikiwand.com/en/CUDA#/GPUs_supported)
1. Ctrl + F로 자신의 그래픽카드를 검색
2. CUDA 버전 확인  
예) GTX 1650 -> 7.5  
![cuda_table](https://i.imgur.com/AWt6grr.png)  

### 2.3. CUDA SDK 버전 확인
![cuda_sdk_table](https://i.imgur.com/0yrGcXn.png)  

### 2.4. CUDA 설치
[다운로드 링크](https://developer.nvidia.com/cuda-toolkit-archive)  
* 자신이 확인한 SDK 버전에 맞는 것을 설치 (network, local 상관 없음)  
* 디폴트 경로(C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\버전)에 설치하였다면, 환경 변수는 자동으로 추가됨  
  ![environment_variable_example](https://i.imgur.com/Tm3TgXY.png)
 환경 변수 예시

### 2.5. cuDNN 설치
[다운로드 링크](https://developer.nvidia.com/rdp/cudnn-download)  
*NVIDIA DEVELOPER에 가입 및 로그인 필요*
1. ![cudnn_download](https://i.imgur.com/rBP7FZI.png)  
자신이 설치한 CUDA 버전에 맞게 cuDNN 설치
2. ![copy_paste_cudnn](https://i.imgur.com/XtVbf8w.png)  
cuDNN을 압축 풀고 CUDA를 설치한 곳에 붙여넣기


## 3. OpenCV 설치
구버전 (CUDA 지원 미포함)
>1. [다운로드 링크](https://opencv.org/releases/)  
> **3.4.11**버전 설치
>2. ![opencv_in_c](https://i.imgur.com/mDutkvi.png)  
>압축 풀어서 나타난 opencv 폴더를 원하는 곳으로 이동 (편의상 C:\로 가정)
>3. ![search_environment_variable](https://i.imgur.com/dj1GjHM.png)  
>[시작] - ["환경 변수" 검색] - [(아마)"시스템 환경 변수 편집" 클릭]
>4. ![system_variables_new](https://i.imgur.com/VV1LjcG.png)  
>Path를 더블클릭 / Path 선택하고 "편집" 버튼 클릭
>5. ![add_opencv_path](https://i.imgur.com/8fJJCPx.png)  
>"새로 만들기" 버튼 누르고 **opencv\build\x64\vc14\bin경로(예: C:\opencv\build\x64\vc14\bin)** 추가  

<s>신버전 (CUDA 지원)</s> dll 포함해서 올려놓음. 이 과정을 거칠 필요 없음..
>1. [OpenCV 3.4.11 소스 다운로드 링크](https://github.com/opencv/opencv/archive/3.4.11.zip)
>2. [cmake 다운로드 링크](https://cmake.org/download/)
>3. cmake 인스톨 시, 환경 변수 추가하는 옵션에서는 **모든 사용자에 대하여 추가**를 권장
>4. 다운로드 받은 OpenCV 소스를 압축 풀고, 압축 푼 디렉토리와 같은 위치에 'build' 빈 폴더를 생성
>5. ![cmake_settings_1](https://i.imgur.com/uJZfrGw.png)
>그림과 같이, Source code는 압축 푼 소스가 있는 경로, build binaries 위치는 새 폴더 'build'의 경로로 지정
>6. ![cmake_settings_2](https://i.imgur.com/ZRFxKac.png)
>그림과 같이, 본인의 Visual Studio 버전에 맞는 것으로 0선택 후 두 번째는 32비트의 경우 Win32를, 64비트의 경우 x64를 지정
>7. ![cmake_settings_3](https://i.imgur.com/QL6LmVN.png)
>Finish를 누르고 기다리면, 다음과 같이 빌드 옵션 체크리스트가 나타남
>8. 다음과 같이 설정할 것 [참고 사이트](https://m.blog.naver.com/PostView.nhn?blogId=msm2570&logNo=221333488789&proxyReferer=https:%2F%2Fwww.google.com%2F)  
>*만약 다시 설정하고 싶다면, [File] - [Delete Cache] 누르면 설정이 초기화된다*
>* 체크
>  * CUDA 사용 시, WITH_CUDA 체크
>  * BUILD_EXAMPLES를 체크 시 예제 소스코드와 빌드된 파일이 제공됨 (안 해도 무방)
>* 체크 해제
>  * test라고 검색 후 전부 체크 해제
>  * 기존에 파이썬이 설치되어 있는 경우, python 검색하여 **BUILD_opencv_python3**, **BUILD_opencv_python_bindings_generator** 체크 해제
>  * package 검색 후 BUILD_PACKAGE 체크 해제
>  * 그 외 안 쓰는 패키지들
>    * 1394, vtk, matlab, lapack
>* 값 입력
>  * install을 검색 후 CMAKE_INSTALL_PREFIX에 build를 지정 (안 해도 무방)
>9. configure 눌러서 opencv_world 체크하고 다시 configure (opencv_world는 마지막에 생성하는 것이 좋음)
>10. Configuring Done이 뜨면 Generate 누름 - 비주얼 스튜디오 솔루션 생성됨
>11. Open Project 누르면 비주얼 스튜디오가 켜지고 해당 솔루션이 불러와짐
>12. ALL_BUILD 항목에 우클릭 후 빌드 - *엄청나게 오래 걸림..*


## 4. OpenCV 테스트
detect_system.sln을 열고 [프로젝트] - [속성]  
*(단축키: Alt + Enter)*  

![c/c++_includepath_](https://i.imgur.com/QmC3Cwm.png)  
> **구성:** Debug  
> **플랫폼:** x64  
> [구성 속성] - [C/C++] - [일반] - [추가 포함 디렉터리]에 **opencv\build\include경로(예: C:\opencv\build\include)** 추가  
> 같은 방식으로, 다음 옵션들을 추가  
> > Debug 모드 x64  
> > > * [C/C++] - [일반] - [추가 포함 디렉터리]에 **opencv\build\include경로(예: C:\opencv\build\include)** 추가  
> > > * [링커] - [일반] - [추가 라이브러리 디렉터리]에 **opencv\build\x64\vc14\lib** 경로 추가  
> > > * [링커] - [입력] - [추가 종속성]에 **opencv_world3411d.lib**를 추가  
> > > 
> > Release 모드 x64  
> > > * [C/C++] - [일반] - [추가 포함 디렉터리]에 **opencv\build\include경로(예: C:\opencv\build\include)** 추가  
> > > * [링커] - [일반] - [추가 라이브러리 디렉터리]에 **opencv\build\x64\vc14\lib** 경로 추가  
> > > * [링커] - [입력] - [추가 종속성]에 **opencv_world3411.lib**를 추가  

opencv_test 폴더의 test.cpp 소스를 가져와 실행 (환경이 x64인지 체크) -> *웹캠이 켜짐*
![opencv_test_result](https://i.imgur.com/S9go4Zp.png)  

## 4. OpenCV와 YOLOv3를 이용한 객체 인식
### 4.1. 일단 테스트
1. OpenCV가 잘 돌아간다는 것을 확인하였으면, test.cpp를 지우고 detect_system/object_detection_yolo.cpp를 가져옴
2. 프로젝트를 빌드하여 exe파일 생성
3. cmd나 다른 터미널 프로그램을 실행해서, 빌드한 exe파일이 있는 디렉토리에 res폴더 내의 **coco.names, yolov3.cfg(혹은 yolov3-tiny.cfg), yolov3.weights, 테스트 파일** 복사 후 이동 (yolov3.weights는 용량이 커 깃허브 레포지토리에 올릴 수 없음)  
[yolov3.weights 다운로드 링크](https://pjreddie.com/media/files/yolov3.weights)
![copy_to_exedirectory](https://i.imgur.com/Y9DM17J.png)
1. 다음 명령어로 테스트
> 테스트 파일이 동영상인 경우,
> ```
> ./detect_system.exe --video=테스트동영상파일이름
> ```
> 테스트 파일이 이미지인 경우,
> ```
> ./detect_system.exe --image=테스트이미지파일이름
> ```
5. *CPU와 yolov3.cfg를 이용하여 아주 느린 속도로 진행되는 것을 볼 수 있음*

### 4.2. oboject_detection_yolo.cpp 수정을 통한 설정 변경
1. 59~60번째 줄
> ```
> net.setPreferableBackend(DNN_BACKEND_OPENCV);
> net.setPreferableTarget(DNN_TARGET_CPU);
> ```
> 로 인하여, 현재 CPU를 사용하므로 앞서 설치했던 GPU를 전혀 사용하지 않아 느림. 이것을 > > GPU를 이용하도록 하면 훨씬 빠를 것으로 예상하지만 현재 알아보는중  

2. 38, 54, 55번째 줄에서도 사용하는 configuration, weights 파일 등을 하드코딩해서 작성했으므로, 이 값들을 변경해서 설정을 만질 수 있음 -> 추후 매개변수로 받도록 할 수도 있을 것