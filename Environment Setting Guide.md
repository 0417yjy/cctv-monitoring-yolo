# Environment Setting Guide
������ ���̵� [��ũ](https://mickael-k.tistory.com/15)
## 1. Visual Studio ��ġ
[VS �ٿ�ε� ��ũ](https://visualstudio.microsoft.com/ko/)  
*���� ����*  
## 2. CUDA & cuDNN ��ġ
### 2.1. �׷���ī�� Ȯ��
#### 2.1.1. ��ġ �����ڿ��� Ȯ��
![device_manager](https://i.imgur.com/FSKpzFx.png)  
[����] - [��ġ ������] - [���÷��� �����]
#### 2.1.2. GPU-Z ���α׷� �̿�
GPU-Z [�ٿ�ε� ��ũ](https://software.naver.com/software/summary.nhn?softwareId=MFS_100082)
### 2.2. CUDA ���� Ȯ��
[CUDA ���� ������Ʈ](https://www.wikiwand.com/en/CUDA#/GPUs_supported)
1. Ctrl + F�� �ڽ��� �׷���ī�带 �˻�
2. CUDA ���� Ȯ��  
��) GTX 1650 -> 7.5  
![cuda_table](https://i.imgur.com/AWt6grr.png)
### 2.3. CUDA SDK ���� Ȯ��
![cuda_sdk_table](https://i.imgur.com/0yrGcXn.png)
### 2.4. CUDA ��ġ
[�ٿ�ε� ��ũ](https://developer.nvidia.com/cuda-toolkit-archive)  
* �ڽ��� Ȯ���� SDK ������ �´� ���� ��ġ (network, local ��� ����)  
* ����Ʈ ���(C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\����)�� ��ġ�Ͽ��ٸ�, ȯ�� ������ �ڵ����� �߰���  
  ![environment_variable_example](https://i.imgur.com/Tm3TgXY.png)
 ȯ�� ���� ����
### 2.5. cuDNN ��ġ
[�ٿ�ε� ��ũ](https://developer.nvidia.com/rdp/cudnn-download)  
*NVIDIA DEVELOPER�� ���� �� �α��� �ʿ�*
1. ![cudnn_download](https://i.imgur.com/rBP7FZI.png)  
�ڽ��� ��ġ�� CUDA ������ �°� cuDNN ��ġ
2. ![copy_paste_cudnn](https://i.imgur.com/XtVbf8w.png)  
cuDNN�� ���� Ǯ�� CUDA�� ��ġ�� ���� �ٿ��ֱ�
## 3. OpenCV ��ġ
1. [�ٿ�ε� ��ũ](https://opencv.org/releases/)  
**3.4.11**���� ��ġ
2. ![opencv_in_c](https://i.imgur.com/mDutkvi.png)
���� Ǯ� ��Ÿ�� opencv ������ ���ϴ� ������ �̵� (���ǻ� C:\�� ����)
3. ![search_environment_variable](https://i.imgur.com/dj1GjHM.png)
[����] - ["ȯ�� ����" �˻�] - [(�Ƹ�)"�ý��� ȯ�� ���� ����" Ŭ��]
`(�����찡 ����� �˼��մϴ�..)`
4. ![system_variables_new](https://i.imgur.com/VV1LjcG.png)
Path�� ����Ŭ�� / Path �����ϰ� "����" ��ư Ŭ��
5. ![add_opencv_path](https://i.imgur.com/8fJJCPx.png)
"���� �����" ��ư ������ **opencv\build\x64\vc14\bin���(��: C:\opencv\build\x64\vc14\bin)** �߰�
## 4. OpenCV �׽�Ʈ
Ŭ���� ������Ʈ�� ���� Visual Studio���� [������Ʈ] - [�Ӽ�]  
*(����Ű: Alt + Enter)*
![c/c++_includepath_](https://i.imgur.com/QmC3Cwm.png)
> **����:** Debug  
> **�÷���:** x64  
> [���� �Ӽ�] - [C/C++] - [�Ϲ�] - [�߰� ���� ���͸�]�� **opencv\build\include���(��: C:\opencv\build\include)** �߰�  
> ���� �������, ���� �ɼǵ��� �߰�  
> > Debug ��� x64  
> > > * [C/C++] - [�Ϲ�] - [�߰� ���� ���͸�]�� **opencv\build\include���(��: C:\opencv\build\include)** �߰�  
> > > * [��Ŀ] - [�Ϲ�] - [�߰� ���̺귯�� ���͸�]�� **opencv\build\x64\vc14\lib ��� �߰�  
> > > * [��Ŀ] - [�Է�] - [�߰� ���Ӽ�]�� **opencv_world3411d.lib'�� �߰�  
> > > 
> > Release ��� x64  
> > > * [C/C++] - [�Ϲ�] - [�߰� ���� ���͸�]�� **opencv\build\include���(��: C:\opencv\build\include)** �߰�  
> > > * [��Ŀ] - [�Ϲ�] - [�߰� ���̺귯�� ���͸�]�� **opencv\build\x64\vc14\lib ��� �߰�  
> > > * [��Ŀ] - [�Է�] - [�߰� ���Ӽ�]�� **opencv_world3411.lib'�� �߰�  

test.cpp ���� (ȯ���� x64���� üũ) -> *��ķ�� ����*
![opencv_test_result](https://i.imgur.com/S9go4Zp.png)