# Лаборатораня работа №1
## Задание:
Прочитать сигнал, полученный от микрофона, показывая размер световой области на светодиодной панели в зависимости от размера принимаемого звука.

## 1. Изучение SPI
SPI — последовательный синхронный стандарт передачи данных в режиме полного дуплекса, предназначенный для обеспечения простого и недорогого высокоскоростного сопряжения микроконтроллеров и периферии. SPI также иногда называют четырёхпроводным интерфейсом.
### 1.1 Интерфейс SPI
В SPI используются четыре цифровых сигнала:
* MOSI — выход ведущего, вход ведомого. Служит для передачи данных от ведущего устройства ведомому.
* MISO — вход ведущего, выход ведомого. Служит для передачи данных от ведомого устройства ведущему.
* SCLK или SCK — последовательный тактовый сигнал. Служит для передачи тактового сигнала для ведомых устройств.
* CS или SS — выбор микросхемы, выбор ведомого.
### 1.2 Прием и передача данных в SPI
![Screenshot of a comment on a GitHub issue showing an image, added in the Markdown, of an Octocat smiling and raising a tentacle.](https://upload.wikimedia.org/wikipedia/commons/b/bb/SPI_8-bit_circular_transfer.svg)

Процесс передачи обычно включает в себя два сдвиговых регистра фиксированного размера, например 8 бит, один сдвиговый регистр для ведущего и один сдвиговый регистр для ведомого. Абстрактно эти два регистра соединены кольцевым способом. Тогда процесс передачи будет включать в себя следующие этапы:

* Шаг 1: Вывод SS с соответствующим ведомым устройством, которое ведущее устройство хочет передавать/принимать, будет записан ведущим на низкий логический уровень.

* Шаг 2: Бит MSB будет передан первым. В течение одного тактового импульса и ведущий, и ведомый транслируют 1 бит и отправляют этот бит ведомому или ведущему устройству, который необходимо передать соответственно. Во время следующего тактового импульса на каждой принимающей стороне бит выбирается на линии и сохраняется как последний младший бит в сдвиговом регистре. После того, как все биты сдвигового регистра были вытолкнуты или приняты, ведущий и ведомый устройства завершили обмен значениями регистра. Если необходимо передать больше данных, сдвиговые регистры перезагружаются и описанный выше процесс повторяется.

* Шаг 3: По завершении ведущий прекращает инверсию часов и перестает выбирать вывод SS соответствующим ведомым устройством. Тогда вывод SS будет записан мастером на высокий логический уровень.
## 2. Светодиодный модуль P10
Изображение светодиодного модуля P10 показано на рисунке ниже.
![Screenshot of a comment on a GitHub issue showing an image, added in the Markdown, of an Octocat smiling and raising a tentacle.](https://led-ekb.ru/image/cache/data/moduli/P10_Single_Outdoor_Module-600x750.jpg)

Принципиальная схема работы светодиодной панели представлена ​​на рисунке ниже.
![Screenshot of a comment on a GitHub issue showing an image, added in the Markdown, of an Octocat smiling and raising a tentacle.](https://habrastorage.org/files/67b/bb8/862/67bbb8862780441586c79c3825618402.gif)

Подключение к матрице в рамках лабораторной работы будет осуществляться путём подключения сигнальных проводов от платы STM32 к специальному кабелю, установленному в крайний левый слот. Распиновку разъёма матрицы: 
![Screenshot of a comment on a GitHub issue showing an image, added in the Markdown, of an Octocat smiling and raising a tentacle.](https://habrastorage.org/r/w1560/files/0bc/02e/643/0bc02e6435c04856a93533bdb10f40e3.jpg)

Там:
* A и B - необходим для переключения между строками
* OE - отвечает за запуск / отключение матрицы 
* SCK - канал для синхронизации частот работы переферии 
* MOSI - канал передачи данных
* SCLK - канал подтверждения конца загрузки байта данных

Логика обновления четверти экрана выглядит следующим образом:
1. Выдаём по SPI данные для сдвиговых регистров. Для одной матрицы 32x16 это 16 байт (16 8-битных регистров).
1. Устанавливаем лог. 0 на ножке nOE.
1. Устанавливаем лог. уровни на ножках A и B в соответствии с обновляемой группой светодиодов (одной из четырёх). Это подаёт +5В на аноды светодиодов выбранной группы.
1. Выдаём на ножку SCLK короткий положительный импульс. Это подаёт землю на катоды светодиодов в соответствии с загруженными в регистры байтами.
1. Устанавливаем лог. 1 на ножке nOE. При этом четверть экрана (одна группа светодиодов) загорается и горит до следующего обновления следующей группы светодиодов.

Повторяем пункты 1-5 с постоянным периодом.

## 3. Настрйока микроконтроллера STM32


![Screenshot of a comment on a GitHub issue showing an image, added in the Markdown, of an Octocat smiling and raising a tentacle.](https://media.discordapp.net/attachments/1033680304692539505/1188547149210861668/OdKleh5M0yo.png?ex=659aebca&is=658876ca&hm=162e69591f935073c35f958be0b5c2dffaec6dfdddce8f4cee154030715d9b56&=&format=webp&quality=lossless&width=514&height=468)
