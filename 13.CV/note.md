
### 1. Скачайте и распакуйте
Скачайте и распакуйте архив с исходными кодами из материалов вебинара.

### 2. Используйте docker
*-nix:
```
docker run --rm -ti -v $(pwd):/usr/src/app sdukshis/cppml
```
windows:
```
docker run --rm -ti -v ${pwd}:/usr/src/app sdukshis/cppml
```

### 3. Соберите проект и запустите тесты
```
cmake -B build
cmake --build build
```