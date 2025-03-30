# Problem Ucztujących Filozofów

## Opis projektu

Projekt implementuje klasyczne zagadnienie synchronizacji znane jako "Problem ucztujących filozofów". Problem ten jest często wykorzystywany do demonstracji zagadnień związanych z synchronizacją wątków i unikaniem zakleszczeń (deadlock) w środowisku wielowątkowym.

## Struktura projektu

Projekt składa się z trzech plików:
- `Mutex.h` - deklaracja klasy Mutex
- `Mutex.cpp` - implementacja metod klasy Mutex
- `main.cpp` - główny plik programu implementujący problem ucztujących filozofów

### Klasa Mutex

Klasa `Mutex` dostarcza mechanizm synchronizacji wątków:

```cpp
class Mutex
{
private: 
    atomic_flag locked = ATOMIC_FLAG_INIT;
    
public:
    void lock();
    void unlock();
};
```

- `locked` - flaga atomowa używana do kontroli dostępu do zasobu
- `lock()` - metoda blokująca mutex, czeka aż zasób będzie dostępny
- `unlock()` - metoda odblokowująca mutex, zwalnia zasób dla innych wątków

### Program główny

Program implementuje klasyczny problem ucztujących filozofów:
- Filozofowie siedzą przy okrągłym stole
- Pomiędzy każdą parą filozofów leży widelec
- Każdy filozof naprzemiennie myśli i je
- Aby zjeść posiłek, filozof musi podnieść oba widelce (lewy i prawy)

#### Rozwiązanie problemu zakleszczeń

W implementacji zastosowano rozwiązanie eliminujące możliwość powstania zakleszczenia:
- Filozofowie o parzystych numerach najpierw podnoszą lewy widelec, a następnie prawy
- Filozofowie o nieparzystych numerach najpierw podnoszą prawy widelec, a następnie lewy

Podejście to zapobiega sytuacji, w której wszyscy filozofowie jednocześnie podnoszą jeden z widelców i czekają w nieskończoność na dostępność drugiego.

## Użycie programu

Program przyjmuje jako argument linii poleceń liczbę filozofów:

```
./program <liczba_filozofów>
```

Na przykład, aby uruchomić program z 5 filozofami:

```
./program 5
```

### Przebieg działania

Każdy filozof wykonuje następujący cykl działań:
1. Myśli (wypisuje komunikat i czeka 1 sekundę)
2. Podnosi widelce (w kolejności zależnej od numeru filozofa)
3. Je (wypisuje komunikat i czeka 1 sekundę)
4. Odkłada widelce

W obecnej implementacji każdy filozof wykonuje ten cykl dokładnie 2 razy.

## Techniczne aspekty implementacji

### Synchronizacja wyjścia do konsoli

Do synchronizacji wypisywania komunikatów na konsolę używany jest dodatkowy mutex `logMutex`, który zapewnia, że komunikaty nie będą się mieszać.

### Implementacja Mutexa

Mutex zaimplementowano przy użyciu atomowej flagi (`atomic_flag`):
- `test_and_set()` z parametrem `memory_order_acquire` do blokowania
- `clear()` z parametrem `memory_order_release` do odblokowywania

W przypadku, gdy mutex jest już zablokowany, wątek oddaje swój czas procesora za pomocą `this_thread::yield()`.

## Autorstwo

Copyright[2025] Alicja Fuks