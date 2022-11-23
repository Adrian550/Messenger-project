# Мессенджер 


## Установка зависимостей
* Скачать Qt
```
vcpkg install qt:x64-windows-static
vcpkg integrate install
```
* Скачать Boost
```
vcpkg install boost:x64-windows-static
```

## Компиляция мессенджера

### Visual Studio

```
git clone https://github.com/Adrian550/Messenger-project.git
cd Messenger-project
cd Client

Visual studio: Download plugin Qt VS Tools
open Client.pro in Visual Studio(Qt VS Tools)
```

### Qt Creator

```
git clone https://github.com/Adrian550/Messenger-project.git
cd Messenger-project
cd Client
open Client.pro in Qt Creator
```

## Настройка сервера
1) Открыть 5555 порт на сервере.
2) Перенести файлы сервера с библиотеками на сервер.
3) Запустить сервер.

## Настройка клиента
1) Заменить данные для подключения к серверу в локальной БД.
2) Запустить client.exe

## Запуск
### Клиент
```
cd client/release

./client.exe
```
### Сервер
```
cd server/release

./client.exe
```

## Тесты

Запуск тестов

```
vcpkg install boost-test:x64-windows-static
```

```cd tests```

* Откройте файл проект .sln

* Установите платформу x64 и конфигурация release

* Скомпилируйте проект и посмотрите результаты тестов


## Авторы

- [Подыниногин Андрей](https://github.com/Adrian550)
- [Чесноков Артем](https://github.com/RTMchs)

## Лицензия

Этот проект лицензирован по лицензии AGPL-3.0 license - см. [LICENSE.md ](LICENSE.md ) файл для получения подробной информации
