# Environment Setting Guide
참조한 가이드 [링크](https://mickael-k.tistory.com/15)
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
1. [다운로드 링크](https://opencv.org/releases/)  
**3.4.11**버전 설치
2. ![opencv_in_c](https://i.imgur.com/mDutkvi.png)  
압축 풀어서 나타난 opencv 폴더를 원하는 곳으로 이동 (편의상 C:\로 가정)
3. ![search_environment_variable](https://i.imgur.com/dj1GjHM.png)  
[시작] - ["환경 변수" 검색] - [(아마)"시스템 환경 변수 편집" 클릭]
`(윈도우가 영어라 죄송합니다..)`
4. ![system_variables_new](https://i.imgur.com/VV1LjcG.png)  
Path를 더블클릭 / Path 선택하고 "편집" 버튼 클릭
5. ![add_opencv_path](https://i.imgur.com/8fJJCPx.png)  
"새로 만들기" 버튼 누르고 **opencv\build\x64\vc14\bin경로(예: C:\opencv\build\x64\vc14\bin)** 추가
## 4. OpenCV 테스트
클론한 프로젝트를 열고 Visual Studio에서 [프로젝트] - [속성]  
*(단축키: Alt + Enter)*
![c/c++_includepath_](https://i.imgur.com/QmC3Cwm.png)  
> **구성:** Debug  
> **플랫폼:** x64  
> [구성 속성] - [C/C++] - [일반] - [추가 포함 디렉터리]에 **opencv\build\include경로(예: C:\opencv\build\include)** 추가  
> 같은 방식으로, 다음 옵션들을 추가  
> > Debug 모드 x64  
> > > * [C/C++] - [일반] - [추가 포함 디렉터리]에 **opencv\build\include경로(예: C:\opencv\build\include)** 추가  
> > > * [링커] - [일반] - [추가 라이브러리 디렉터리]에 **opencv\build\x64\vc14\lib 경로 추가  
> > > * [링커] - [입력] - [추가 종속성]에 **opencv_world3411d.lib'를 추가  
> > > 
> > Release 모드 x64  
> > > * [C/C++] - [일반] - [추가 포함 디렉터리]에 **opencv\build\include경로(예: C:\opencv\build\include)** 추가  
> > > * [링커] - [일반] - [추가 라이브러리 디렉터리]에 **opencv\build\x64\vc14\lib 경로 추가  
> > > * [링커] - [입력] - [추가 종속성]에 **opencv_world3411.lib'를 추가  

test.cpp 실행 (환경이 x64인지 체크) -> *웹캠이 켜짐*
![opencv_test_result](https://i.imgur.com/S9go4Zp.png)  
