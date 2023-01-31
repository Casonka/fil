
<h1><p align="center"> 
Fast Initialization Library(FIL) for STM32 microcontrollers
</p></h1>
<h1><p align="center"> 
Библиотека быстрой инициализации для микроконтроллеров STM32
</p></h1>
<h3><p align="center"> 
<img width=30% src = https://github.com/Casonka/FIL/blob/main/images/Logo.png>
</p></h3>

## Что такое FIL ?

<h3>Аннотация</h3>

Библиотека быстрой инициализации разрабатывается в структурном подразделении [Донского государственного технического университета](https://donstu.ru/) - [Ресурсный центр робототехники](https://github.com/RCR-DSTU). Библиотека FIL предназначена для начинающих специалистов в области встраиваемых систем, предоставляя набор API функций. Благодаря возможности создания карты портов и конфигурации настроек, проект настраивается с минимальными временными затратами и максимально повышая гибкость и вариативность сценариев исполнения. Архитектура разрабатываемого продукта поддерживает принцип модульности - возможность подключения и исключения секторов библиотеки. Таким образом список предоставляемых функций и макро определений может динамически изменяться и зависит от требуемой периферии микроконтроллера, которая указана в конфигурационных файлах. Помимо этого, библиотека поддерживает внедрение сторонних middleware библиотек через External manager.

Первое официальное упоминание продукта представлено в [статье](https://donstu.ru/news/nauka/studenty-dgtu-predstavili-svoi-proekty-na-kongresse-molodykh-uchenykh/) в новостной ленте ДГТУ. Также проект был [протестирован](https://dzen.ru/media/donstu/v-resursnom-centre-robototehniki-dgtu-studentov-obuchaiut-na-mobilnyh-robotah-sobstvennogo-proizvodstva-63a19964c98aaa3ae26cade1) с участием студентов Т-университета, в рамках ведения элективного курса "Введение в робототехнику". Использование FIL при разработке ПО для [беспилотного серийного автомобиля](https://github.com/Casonka/Robocross), также, было успешно и позволило занять 3-е место на всероссийских открытых испытаниях беспилотных транспортных средств ["РОБОКРОСС 2022"](https://www.russianrobotics.ru/competition/robocros/).

<h3>Цель и назначение продукта</h3>
Цель, преследуемая при разработе продукта - уменьшения времени разработки ПО за счет повышения абстракции программного кода с минимальными затратами ресурсов вычислительной техники. Продукт позволяет исключить временные издержки за счет исключения инициализации со стороны пользователя. При этом существует вариативность и для опытных пользователей за счет наличия команд изменения регистровых переменных.
Проблему, решение которой преследуется с самого момента основания проекта - существенное снижение порога начинающих при освоении встраиваемых систем. 
Область применения продукта можно рассматривать для сферы робототехнических и мехатронных систем, а также для встраиваемых систем для интернет-вещей (умные дома).

<h3>Архитектурное строение библиотеки</h3>

Архитектуру созданного продукта представляет собой взаимодействие элементов, как на рисунке ниже. Основной участок взаимодействия пользователя и продукта это карта портов и конфигурационный файл, они участвуют в процессе сборки проекта и предоставлении необходимого набор API функций ядра библиотеки FIL. Основополагающий фактор - наличие периферийной библиотеки [CMSIS](https://developer.arm.com/tools-and-software/embedded/cmsis), определения которой используются ядром и самим пользователем.

<p align="center"> 
<img src=https://github.com/Casonka/FIL/blob/main/images/Architecture.jpg>
</p>

На данный момент проект поддерживает линейки контроллеров, прилагаемых в таблице. Основная целевая группа проекта - архитектура линейки ARM Cortex-M, на которой в большинстве реализованы микроконтроллеры STM32. В частности, планируется оптимизация под архитектуру Cortex M4 и M3.

| Модель контроллера | Статус оптимизации |
| ------ | ------ |
| Cortex-M4 STM32F407 | Оптимизировано |
| Cortex-M4 STM32F401 | Оптимизировано |
| Cortex-M3 STM32F103 | В разработке |

<h3>Поддержка middleware</h3>

В последний релизных версиях библиотеки FIL был добавлен External Manager - линкер-файл для внешних библиотек. Таким образом, интеграция в проект будет происходить с минимальным количеством ошибок и не будет нарушен принцип модульности. Некоторый перечень внешних библиотек предоставляется Ресурсным центром робототехники, однако есть инструкция по установке собственных разработок, смотрите [здесь]().

## Лицензирование

Продукт имеет лицензию [Apache-License 2.0](https://github.com/Casonka/FIL/blob/main/LICENSE).

## Установка 

Для удобной и максимально быстрой установки были созданы ветки репозитория по средам разработки. Таблица содержит все текущие на данный момент времени проверенные программы для разработки ПО для микроконтроллеров STM32.

|  | Название среды | Ссылка на инструкцию по установке |
| ------ | ------ | ------ |
| <img width=20% src=https://github.com/Casonka/FIL/blob/main/images/EmBitz.png> | EmBitz | [Гайд по установке](https://github.com/Casonka/FIL-EmBitzDeploy) |
| <img width=20% src=https://github.com/Casonka/FIL/blob/main/images/Eclipse.png> | Eclipse Embedded | [Гайд по установке](https://github.com/Casonka/FIL-EclipseDeploy) |

## Конфигурация и настройка библиотеки 

Одна из основных идей, продвигаемых в рамках разработки библиотеки быстрой инициализации - создание конигурации проекта с минимальными временными затратами и повышении абстракции участка инициализации периферии микроконтроллера. Реализовано это через конфигурацию - файл с настройками, в том числе параметры для middleware библиотек и их подключение. Такой модульный подход позволил повысить возможности для отладки - при необходимости можно с легкостью и удобством выключить/включить параметры.

Из числа параметров выделяются две категории:
- Основные параметры - параметры включающие непосредственно секцию периферии микроконтроллера. От их состояния зависит включение файла в общую сбору через #include директиву. Они выполнены в виде макроопределений, поэтому изменение значения производится с максимальной быстротой, в отличие от комментирования команд. Основные существующие на данных момент параметры:

```sh
#define __configUSE_RCC                   0
#define __configUSE_GPIO                  0
#define __configUSE_TIM                   0
#define __configUSE_USART                 0
#define __configUSE_DMA                   0
#define __configUSE_I2C                   0
#define __configUSE_SPI                   0
#define __configUSE_ADC                   0
#define __configUSE_EXTI                  0
#define __configUSE_RTC                   0
```

- Дополнительные параметры - расширяющие возможности, открываемые основными параметрами, а также модификация значений по умолчанию, в число которых могут входить, например, частоты интерфейсов обмена данными, делители частот и так далее. Список данных параметров гораздо обширнее, в виду гибкой системы сценариев настройки, поэтому будут приведены некоторые популярные параметрические константы:

```sh
#define __configADC_DIVIDER             3
#define __configCALC_I2C_SCANNING       1
#define __configI2C_FindListSize        3
#define __configI2C_TIMEOUT             5000
```
По умолчанию, при успешной установке библиотеки запущена демонстрационная версия конфигурации. Найти её можно в файле Conf.h в директории с конфигурацией (Configuration). Она включена для общего понимания принципа функционирования библиотеки и её возможностей.

> Ознакомиться с полным списком параметров конфигурации можно в [специальном документе]().
<h3>Создание собственных конфигураций</h3>

Выходя за рамки простой демонстрационной версии, возникает необходимость разработки управляющей программы для роботов, небольших узлов или модулей. Возможности библиотеки позволяют создать собственную версию проекта с указанием необходимых параметров. В данном разделе содержится инструкция по созданию собственной конфигурации.

Если обратиться к файлу-селектору конфигураций, то можно заметить параметр, отвечающий за подключенный проект. 

<p align="center"> 
<img src=https://github.com/Casonka/FIL/blob/main/images/Selector.jpg>
</p>

По умолчанию, включена тестовая конфигурация, поэтому если вы нацелены создать собственную, следуйте следующим указаниям:

- В файле BoardSelection.h измените параметр _configUSEBoards на значение 1;
- Теперь, найдите и откройте файл Configuration.h в той же директории с селектором;
- Файл будет содержать только основные параметры, далее можно добавлять свои параметры и модифицировать ключевые макросы Board_Config и другие.

<h3>External Manager и как его подключить</h3>

В последних версиях библиотеки был введен файл External Manager, заача которого - обеспечить максимальную модульность при подключении сторонних и middleware библиотек, не относящихся к основным файлам ядра FIL. Список пополняется, поскольку с появлением новых задач центра создаются новые оптимизированные под библиотеку драйвера.

Перед тем, как скачивать и подключать библиотеки, убедитесь что в структуре вашего проекта присутствует папка External. Тем не менее, ниже будет приведена инструкция по установке внешний библиотек, для установки External Manager файла посетите [репозиторий установки](https://github.com/Casonka/FIL-External_Manager).

Ниже приведены существующие на данный момент макросы, при выставлении в 1 которых произойдет подключение различных внешних драйверов.

```sh
#define EXTERNAL_REGULATOR              __configEXT_REGULATOR
#define EXTERNAL_MATRIX                 __configEXT_MATRIX
#define EXTERNAL_KINEMATICS             __configEXT_KINEMATICS
#define EXTERNAL_FILTERS                __configEXT_FILTERS
#define EXTERNAL_SSD1306                __configEXT_SSD1306
#define EXTERNAL_MPU9250                __configEXT_MPU9250
#define EXTERNAL_ModBus                 __configEXT_ModBus
#define EXTERNAL_TCS3472                __configEXT_TCS3472
```
Для подключения необходимого драйвера необходимо объявить параметр с приставкой __config в вашем конфигурационном файле. Заходим в файл Configuration.h и добавляем параметр в секцию с optional parameters, как на фрагменте кода ниже. Значение аргумента делать равным 1, если вам требуется указанная библиотека, для временного отключения измените значение на 0.

```sh
/*! Place for new optional settings */

#define __configEXT_SSD1306               1
```
Полный список драйверов, также, приведен в репозитории [External Manager](https://github.com/Casonka/FIL-External_Manager).

<h3>Планы по дальнейшему развитию FIL</h3>

В дальнейшем планируется расширять линейку микроконтроллеров, добавив поддержку на микроконтроллер STM32F103 (Blue Pill). После проведения тестирования и оптимизации в файлы ядра будут добавлены интерфейсы SPI, CAN. В процессе разработки могут быть добавлены функции для упрощения отладки кода. Также время будет уделено для адаптирования некоторых внешних библиотеки для использования в проектах с FIL. 
