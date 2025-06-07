# HDA Watch Face - Health Data Acquisition Watch Application

스마트워치를 통한 실시간 헬스케어 데이터 수집 및 착용 상태 모니터링 애플리케이션

## 📋 프로젝트 개요

HDA Watch Face는 Tizen 기반 스마트워치에서 동작하는 헬스케어 데이터 수집 애플리케이션입니다. 다양한 센서 데이터를 실시간으로 수집하고, 사용자의 시계 착용 상태를 모니터링합니다.

## ✨ 주요 기능

### 센서 데이터 수집
- **심박수 센서 (HRM)**: 실시간 심박수 측정 및 착용 감지
- **가속도계**: 움직임 및 활동량 측정
- **자이로스코프**: 회전 및 방향 변화 감지
- **압력 센서**: 고도 및 환경 압력 측정
- **조도 센서**: 주변 환경 밝기 측정
- **만보계**: 걸음 수 및 활동 상태 추적
- **수면 모니터**: 수면 상태 감지

### 착용 상태 모니터링
- 심박수 센서를 통한 실시간 착용 감지
- 착용하지 않을 때 자동 알림 시스템
- 단계별 알림 강화 (30분, 90분 간격)
- 사용자 맞춤형 알림 지연 기능

### 데이터 관리
- SQLite 데이터베이스를 통한 로컬 데이터 저장
- 실시간 파일 시스템 기반 데이터 로깅
- Bluetooth GATT를 통한 데이터 전송 지원

### 사용자 인터페이스
- 아날로그 시계 인터페이스
- 실시간 날짜/시간 표시
- 배터리 상태 표시
- 직관적인 터치 인터페이스

## 🏗️ 시스템 아키텍처

```
HDA Watch Face
├── 센서 레이어
│   ├── HRM 센서 (심박수/착용감지)
│   ├── 모션 센서 (가속도계, 자이로스코프)
│   └── 환경 센서 (압력, 조도, 수면모니터)
├── 데이터 처리 레이어
│   ├── SQLite 데이터베이스
│   ├── 파일 시스템 로깅
│   └── 실시간 데이터 스트리밍
├── 통신 레이어
│   ├── Bluetooth GATT 서버
│   └── 앱 간 통신 (App Control)
└── UI 레이어
    ├── 아날로그 시계 페이스
    ├── 알림 시스템
    └── 설정 인터페이스
```

## 🚀 시작하기

### 시스템 요구사항
- **플랫폼**: Tizen 4.0 이상
- **하드웨어**: 심박수 센서, 가속도계, 자이로스코프 지원 스마트워치
- **권한**: 
  - `http://tizen.org/privilege/healthinfo`
  - `http://tizen.org/privilege/mediastorage`
  - Bluetooth 관련 권한

### 빌드 및 설치

1. **개발 환경 설정**
   ```bash
   # Tizen Studio 설치 및 SDK 설정
   # 프로젝트 클론
   git clone https://github.com/yourusername/HDA_watch_face.git
   cd HDA_watch_face
   ```

2. **프로젝트 빌드**
   ```bash
   # Tizen Studio에서 프로젝트 열기
   # 또는 명령줄에서 빌드
   tizen build-native -a arm -t watch-4.0 -C Release
   ```

3. **디바이스 설치**
   ```bash
   # 스마트워치에 설치
   tizen install -n org.example.hda_watch_face.tpk -t [device_name]
   ```

## 📊 데이터 수집 형식

### 센서 데이터 로그 포맷
```
센서타입,타임스탬프,데이터값들...

예시:
0,06-07 14:30:25,100,50,1500,0.8,2.3,1.2,0.5,1  # 만보계
4,06-07 14:30:25,75                              # 심박수
6,06-07 14:30:25.123,0.98,-0.12,9.78            # 가속도계
```

### 데이터베이스 스키마
```sql
CREATE TABLE TizenSensorTable (
    DATA TEXT NOT NULL,      -- 센서 데이터
    CODE INTEGER NOT NULL,   -- 센서 타입 코드
    DATE TEXT NOT NULL,      -- 수집 시간
    ID INTEGER PRIMARY KEY AUTOINCREMENT
);
```

## 🔧 설정 및 커스터마이징

### 알림 설정
- **기본 알림 간격**: 30분 (1800초)
- **지연 알림 옵션**: 30분, 90분
- **일일 알림 시간**: 오전 9시, 오후 3시, 오후 9시

### 센서 설정
```c
// 센서 업데이트 간격 (밀리초)
unsigned int sensor_update_interval = 1000;

// 심박수 기반 착용 감지 임계값
#define HRM_WEARING_THRESHOLD 20
```
**주의사항**: 이 애플리케이션은 연구 목적으로 개발되었으며, 의료진단용으로 사용해서는 안 됩니다.
