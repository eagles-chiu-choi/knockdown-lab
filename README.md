# Knockdown Lab

체력과 탄약을 관리하며 움직이는 장애물을 피해 표적을 제거하는 Unreal Engine 5.6 C++ 1인칭 슈팅 프로토타입입니다.

## 프로젝트 배경

[Epic Games의 공식 C++ 튜토리얼](https://dev.epicgames.com/documentation/unreal-engine/code-a-firstperson-adventure-game-in-unreal-engine)을 기반으로 제작한 학습·확장 프로젝트입니다.

- 튜토리얼 기반: 1인칭 캐릭터 제어, 아이템 데이터와 획득, 도구 장착, 조준과 기본 발사체.
- 추가·확장: 공 획득·소비와 발사 제한, 체력·회복, 이동 레이저, 마네킹 행동과 피격 반응, 승패 처리, 아이템 재생성 관리.

탄약·회복 아이템·공은 공식 문서에서도 확장 과제로 제안합니다.

## 개발 환경 및 실행

- Unreal Engine 5.6
- C++ / Blueprint
- Visual Studio의 Unreal C++ 빌드 환경
- Git LFS

```powershell
git lfs install
git clone https://github.com/eagles-chiu-choi/knockdown-lab.git
cd knockdown-lab
git lfs pull
```

## 에셋과 도구

Unreal 에셋(`.uasset`, `.umap`)은 Git LFS로 관리합니다. 포함된 외부 에셋과 VisualStudioTools 플러그인은 각 원 출처의 라이선스를 따릅니다.
