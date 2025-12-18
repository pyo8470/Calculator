# Calculator
# 실행 결과![실행결과](https://user-images.githubusercontent.com/84065357/159284631-cc7b4088-1019-47cb-9231-105b5d23963d.png)

간단한 **중위표기 → 후위표기 변환 계산기** 프로젝트입니다.
자료구조(스택, 이중연결리스트) 수업/과제용으로 구현된 C++ 콘솔 계산기입니다. 

## 🧠 사용된 자료구조

* **Stack (스택)** — 직접 구현
* **Double Linked List (이중 연결 리스트)** — 강의 시간 구현 코드 활용
* Stack 연산: `push`, `pop`, `top`, `empty` 직접 작성 

## 📌 주요 기능

* **중위 수식(Infix) → 후위 수식(Postfix) 변환**
* **괄호 처리**
* **소수점 지원**
* **후위식 계산 기능**
* **직접 구현한 스택 기반 구조 사용** 

## ⚙️ 빌드 & 실행

### 🎯 요구사항

* C++ 컴파일러 (g++, clang++ 등)
* Linux / macOS / Windows 환경 모두 가능

### 🛠️ 빌드

```bash
git clone https://github.com/pyo8470/Calculator.git
cd Calculator
g++ -std=c++17 -o calculator StackAndCalculator.cpp
```

### ▶️ 실행

```bash
./calculator
```

## 📝 사용 예시

```
Input: (3.5 + 2) * 4
Output: 22
```

> 프로그램은 stdin으로 수식을 받고, 후위표기 변환 후 계산 결과를 출력합니다.

## 📂 파일 구조

```
.
├── StackAndCalculator.cpp    — 계산기 메인 소스
├── doubleLinkedList.h        — 이중 연결 리스트 헤더
└── README.md
```


