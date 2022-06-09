## 공부한 방법
1. 프로젝트문서를 훑어보고 모르는 개념을 공부한다.\
  a. google검색을 기본으로 한다.\
  b. Makefile에 대한 1일 동료학습세션을 진행해보았다.
2. 각 함수를 구현한다. 그 과정에서 다음의 출처를 이용한다.\
  a. **man page** : 함수의 기본 동작, return value를 파악한다.\
  b. **C명세**: 각 헤더에 대한 챕터를 통해 함수가 만들어진 의도를 파악한다.\
  c. **동료의 코드**: 참고하는 시점은 1차완성 후 개선하려고 할 때, 혹은 아예 시작하지 못하고 있을 때로 한다.\
  d. **타교육생이 제작한 tester**: tester가 어떤 인자들을 넣어 테스트하는지 참고하여 함수의 활용을 이해한다.
3. 동료평가를 준비한다.\
  a. 혼자서 말로 설명해본다.\
  b. 설명하지 못하는 부분은 보통 코드에 개선할 여지가 있는 것이므로 이유를 찾아 개선한다.\
  c. 만든 함수를 실제로 어떻게 사용할 수 있는지, 왜 그러한 기능을 갖는지까지 설명할 수 있도록 한다.
4. 공부한 내용을 글로 정리한다.
5. 경계한 것\
  a. 42서울 슬랙에 남아있는 질답쓰레드와 42서울 교육생의 과제 관련 블로그글에 지나치게 의지하는 것을 지양\
  b. 다른 교육생이 만든 테스터로 정오를 미리 확인할 뿐 함수의 실제 활용은 이해하지 못하고 제출하는 것을 지양

## 이번 프로젝트를 위해 새로 공부한 개념

### `static`키워드
- **정적변수static variable**는 전역변수의 일부 특징을 갖습니다.
  - 프로그램 시작 시부터 종료 시까지 수명이 유지됩니다. (수명이란 변수가 기억장소를 할당받는 기간입니다.)
  - 특정한 값으로 초기화했을 경우 Data영역에, 초기화하지 않았거나 기본값(0, NULL)으로 초기화했을 경우 0으로 초기화되면서 BSS에 할당됩니다.
- 하위함수를 `static`키워드로 선언하면 **파일 간의 독립성**을 유지할 수 있습니다.
  - 외부에 동일한 함수명이 있어도 충돌하지 않습니다.
  - 외부 .c파일로부터의 원치 않는 접근을 막을 수 있습니다.

### `const`키워드
- `const`는 **사용자**의 실수를 방지하기 위해 제공되는 키워드입니다.
  - 기계를 위한 기능이 아니므로 기계어코드는 `const`의 유무와 무관하게 동일합니다.
  - `const`로 선언된 변수의 값을 바꾸려고 한다면 추가적인 방법이 필요합니다.
    - `const int data0;`는 `*(int *)(&data0) = 10;`처럼 할 수 있습니다.
    - `const int *pointer1 = &data1;`는 `pointer1`이 가리키는 값 `data1`을 **적어도** `pointer1`로 접근했을 때는 바꿀 수 없다는 의미입니다. (예시: `*ponter1 = 10;` (불가능))
    (실제로 `data1`은 `const`로 선언된 변수일 수도, 아닐 수도 있겠지만요.)
    만약 `data1`이 수정가능한 변수라면, 언제든지 새로운 포인터를 선언하여 그 값을 변경할 수 있습니다. (예시: `int *pointer2 = data1;` `*pointer2 = 10;`(가능))
- 포인터 변수에서 `const`의 위치에 따른 의미는 다음과 같습니다.
  - `const void *p`, `void const *p`는 동일하게, p가 가리키는 값을 const화 합니다.
  - `void * const p`는 p 자체를 const화 합니다.
- C언어는 함수오버로딩을 지원하지 않아서 함수가 타입안정성을 해할 수밖에 없는 문제를 갖습니다.
  - 일반적으로 함수에서, 입력받은 인자가 `const`이면 반환도 `const`로, 입력이 쓰기가능하다면 반환도 쓰기가능하도록 합니다. (타입안정성)
  - 그런데 C언어는 같은 이름의 함수를 (여기서는 const용, 아닌 거 용으로) 중복하여 정의할 수 없기 때문에 `const`로 받아 쓰기가능한 타입을 반환하는 안을 채택하고 있습니다.

### NULL pointer
- NULL pointer는 유효하지 않은 메모리주소입니다. NULLpointer를 역참조하는 것은 잘못된 메모리 접근입니다. 그러니 포인터를 역참조하기 전에 NULL인지 확인해야겠지요.
- 의미를 갖지 않는 메모리주소를 전달하고 싶을 때 NULLpointer를 전달할 수 있습니다.

### char
- C명세에서 byte는 "addressable unit이며 시스템의 default character set을 저장할 수 있어야"하고, 
char 또한 "시스템의 default character set을 저장할 수 있어야" 한다고 정의하고 있으므로, byte와 char은 같은 단위라고 유추할 수 있습니다.
- POSIX에서 `CHAR_BIT == 8`입니다. (C명세에서는 모든 구현체에서 `CHAR_BIT ≥ 8`라고 정의하고 있습니다.)

### `restrict`한정자
- 기본적으로 같은 메모리 공간을 가리키거나 겹치는지 확인하는데, 그러면 성능이 떨어지지요.
만약 두 포인터가 다른 메모리공간을 가리키고 있음을 프로그래머가 확인했다면, restrict를 붙여 또 확인하지 않도록 최적화할 수 있습니다.

### statement, expression
- **statement**(조건문, 서술)는  `return 3;`처럼 실행가능한 최소한의 코드 조각을 의미합니다. 컴파일러가 보고 이해하고 실행할 수 있는 것입니다.
- **expression**(표현식, 수식)은 `2 + 3`처럼 그 중에 평가가 가능해서 하나의 값으로 표현(환원)이 가능한 것입니다.
- expression이 statement에 포함됩니다.

### 로케일locale
- 사용자 인터페이스에서 사용되는 언어, 지역 설정, 출력 형식 등을 정의하는 문자열입니다.
- 형식은 다음과 같습니다. `language[_territory][.codeset][@modifier]` (우리는 주로 `ko_KR.UTF-8`)
- 특정 언어의 입출력에 영향을 주는 경우가 있어서, 영어 이외의 언어를 사용하는 경우 적절한 값을 지정해야 합니다.
- 디바이스마다 다르게 되어 있습니다.

### int와 자료형
- int는 가장 빠르게 처리할 수 있는 자료형입니다.
  - 다시 말해, 자료형 int == 대상 프로세서가 가장 효율적으로 작업하는 정수 유형 == CPU가 처리하기에 가장 적합한 크기의 정수 자료형
  - 지금은 사실상 거의 의미가 없지만, 새로운 CPU가 나올 수도 있으므로 여전히 의미가 있습니다.
- C는 자료형에 맞는 엄밀한 처리 대신 int형 위주의 수식계산을 가정했으므로, 숫자타입들은 다음과 같은 특징을 지니게 됩니다.
  - char 타입 또한 1바이트 크기의 **숫자**타입입니다.
  - 'A'같은 문자상수(integer character constant)는 4바이트 int형입니다. (sizeof 연산자로 확인하면 정말로 4바이트!)
  - 모든 리터럴(상수)은 실제로 int아니면 double입니다. char, short 등도 모두 int로 간주합니다.

### 라이브러리
- **컴파일**은 전처리-컴파일-어셈블-링크의 4단계로 이루어져 있습니다.
  - **전처리**: 주석을 제거하고, `#include`, `#define` 등을 치환합니다.
  - **컴파일**: 고급언어를 어셈블리어로 바꿉니다. 이때 언어와 아키텍쳐에 최적화합니다.
  - **어셈블**: 하나의 파일로 묶기(링크하기) 좋도록 특정한 포멧을 가지고 있는 오브젝트파일을 생성합니다.
    특히 오브젝트파일의 심볼테이블은 오브젝트파일이 참조하고 있는 심볼정보들을 담고 있고, 이들의 주소는 링킹 후 재배치됩니다.
  - **링크**: 재배치가능한 여러 개의 오브젝트파일의 연관관계를 결정하고 재배치해서, 하나의 실행가능한 오브젝트파일로 만듭니다.
- 함수를 묶어 미리 컴파일해놓은 오브젝트파일을 **라이브러리**라고 합니다. 
  이미 컴파일되어있기 때문에 기술 유출을 방지할 수 있고, 컴파일 시간을 단축할 수 있다는 장점이 있습니다. 
  링크과정에서 다른 오브젝트파일과 함께 링크되어 사용됩니다. (사용 예시: `cc main.c libft.a`)

### `ar`유틸리티
  - 여러 오브젝트파일을 단일 아카이브파일로 만드는, unix의 유틸리티입니다.
  - `ar [옵션] [라이브러리이름] [오브젝트파일...]`와 같이 사용합니다.
  - `-r`옵션: 새로운 라이브러리일 때 추가합니다. 이 옵션이 없을 경우 기존 라이브러리가 없으면 `ar: 'libft.a': No such file`와 같은 메시지가 뜨면서 라이브러리가 생성되지 않습니다.
  - `-c`옵션: client. 이 옵션이 없을 경우 `ar: creating libft.a`와 같은 메시지를 띄웁니다.
  - `-s`옵션: 아카이브 인덱스를 생성하여, 링크 속도를 높이고 에러를 방지합니다.

### Makefile
- `make`는 프로그램 빌드 도구로, make의 문법에 따라 작성된 문서를 Makefile이라고 합니다.
  - `make`의 문법은 여러 파일 간의 의존성, 각 파일을 만들기 위해 필요한 명령어를 파악하기 쉽게 서술하고, 수정된 파일만 컴파일하는 등 효율적인 방법으로 동작합니다.
  - Makefile을 통해 반복되는 컴파일과정을 훨씬 간단하게 처리할 수 있습니다.
- **매크로** 사용으로 Makefile을 더욱 잘 활용해볼 수 있습니다.
  - `make`에 pre-defined 되어있는 매크로(`CC`, `AR` 등)의 경우 바로 사용하거나 재정의하여 사용할 수 있고, 대부분(`CFLAGS`, `ARFLAGS` 등)은 우리가 값을 세팅해주어야 합니다.
  - 정의된 매크로는 우리가 꼭 Makefile에 써넣지 않아도, `make`가 동작할 때 내부적으로 사용하게 됩니다. 
    예를 들어, 확장자규칙을 가지고 있어서 파일의 확장자를 보고 적절한 연산을 수행합니다.
  - **매크로 치환**은 다음과 같이 합니다. `$(MACRO_NAME:OLD=NEW)`
- `make`는 타겟파일과 의존파일의 생성시간을 비교하여, 타겟파일이 의존파일보다 최신이라면 해당 타켓파일을 만드는 명령어를 재수행하지 않고(할 필요가 없으므로), 
  이것을 **리링크되지 않는다**고 표현합니다.
  - `bonus : $(OBJS) $(OBJS_BONUS)` 이런 식으로 타겟파일의 자리에 실행명령어를 쓰면, 비교대상이 없어서 `make bonus`했을 때 계속 리링크되므로 주의해야 합니다.
  - 그럴 때는 `ifdef BONUS` `BONUS=true`와 같이 if문을 활용해봅시다.

### 함수포인터
- 함수 포인터는 다음과 같이 선언, 초기화하고 사용합니다.
```
int main(void){
	void (*func_ptr)(int) = &func;
        (*func_ptr)(10);
}
```
  - 함수의 이름은 함수의 주소를 얻는 데에 사용될 수 있으므로, 다음도 가능합니다.
```
int main(void){
	void (*func_ptr)(int) = func;
	func_ptr(10);
}
```
- 일반적인 포인터와 다르게,
  - data가 아닌 **실행가능한 code의 처음**을 가리킵니다.
  - 포인터를 이용해서 메모리를 할당, 해제하지 않습니다.
- 일반적인 포인터처럼,
  - 포인터 배열을 만들 수 있습니다.
```
void (*fun_ptr_arr[])(int, int) = {add, subtract, multiply};
/* add, subtract, multiply은 각각 함수의 이름 */
```
  - 이런 배열을 이용하면 조건문을 대체할 수도 있습니다.
```
int main(void) {
	unsigned int ch;
      	int a = 15, b = 10;
       	scanf("%d", &ch);
        (*fun_ptr_arr[ch])(a, b);
 }
/* 동작시키고 싶은 함수가 무엇인지에 따라 배열인덱스 0, 1, 2 입력 */
```
- 함수포인터를 함수의 인자로 넘기고, 리턴할 수 있습니다.

## Part 1
C 라이브러리 함수를 구현한다.

### 문자를 다루는 함수
`isalpha` `isprint` `isalnum` `isdigit` `isascii` `toupper` `tolower`
- 대부분 `ctype.h`에 있습니다.
- c 값이 적합할 때, non-zero를 반환합니다.
- 인자는 int이고, 값은 unsigned char 또는 EOF의 값으로 표현할 수 있어야 합니다. 그 밖의 값이 들어오는 것은 undefined behavior입니다.
- `isalpha`의 경우, 로케일별로 결과가 달라집니다. POSIX 시스템의 디폴트 로케일인  "C" 로케일을 기준으로 구현했습니다.

### 문자열을 다루는 함수
- 모두 `string.h`에 있습니다.
- `string.h`에는 문자타입의 배열 혹은 문자타입의 배열로 여겨지는 값을 다루기에 편리하도록, `size_t`라는 타입과 `NULL`이라는 매크로가 정의되어 있습니다.
  - `size_t`는 이론상 가장 큰 사이즈를 담을 수 있는 unsigned 데이터 타입입니다. 모든 배열의 인덱스를 보유하도록 보장하지요.
- 모든 경우에서, char*와 void*는 배열의 첫(제일 작은 주소) 문자를 가리킵니다. 객체의 끝을 넘어 배열에 접근하는 행동은 undefined behavior입니다.
- 모든 함수에서 **문자**란 unsigned char라고 해석하면 됩니다.
#### 복사하는 함수
`memcpy` `memmove` `strlcpy`
- 이들 함수는 인자 2개가 모두 NULLpointer일 때만 바로 `return (dst);`하고, 인자가 1개라도 제대로 들어오면 동작을 수행하지요. 
  인자로 NULLpointer가 들어오는 경우를 고려하지 않되, 인자 2개가 모두 NULLpointer면 비교결과가 참이라고 보는 셈입니다.
#### 연결하는 함수
`strlcat`
  - strlcat은 사용자가 적어도 1) dst의 길이는 알고 있을 것이며 2) NUL-terminating string이 들어올 거라고 전제합니다.
  - dst의 유효성에 따라 분기합니다.
    - size -1 에서 NUL이 없을 경우 dst는 유효하지 않습니다. dst는 변경되지 않습니다. dst의 길이는 적어도 size만큼은 될 것이므로 (그 너머까지 있을 경우는 차마 고려하지 않고) dst의 길이를 size로 간주합니다.
    - size - 1 에서 src를 복사해넣을 공간이 있을 경우 dst는 유효합니다. dst는 변경되며 strlcat에 의해 NUL-terminated됩니다.
  - strlcat의 리턴값은 내가 생성하고 싶었던 문자열의 길이를 알려줍니다. 그것은 연결 실패 시 완벽한 연결에 필요한 버퍼사이즈를 의미하기도 하겠지요. 우리는 `return value < sizeof(buf)`면 연결 성공, `return value >= sizeof(buf)`면 buf가 부족하여 뭔가가 잘렸다는 걸 알 수 있습니다.

#### 비교하는 함수
`memcmp` `strncmp`
- 이식성을 위해서는 리턴값의 부호만 활용해야 합니다.
- 컴파일러마다 char의 디폴트가 unsigned char이기도 signed char이기도 하므로, 연산을 수행할 때는 unsigned char로 형변환을 해주어서 더 큰 문자도 비교할 수 있도록 해야 합니다.
#### 탐색하는 함수
`memchr` `strchr` `strrchr` `strnchr`
- 옛날에는 함수 프로토타입에 인자가 명시되지 않았고 인자들을 int로 자동승격하여 사용했기 때문에, 이후에 C언어가 프로토타입을 만들면서 인자의 자료형을 옛날 라이브러리와 맞추는 게 중요했습니다. 때문에 memchr, strchr 또한 찾을 문자를 int로 받는 겁니다.
#### 기타 함수
`memset` `bzero` `strlen`

### 메모리를 다루는 함수
`calloc` `atoi`
- `stdlib.h`에 있습니다.
- 저장의 순서나 연속성은 unspecified입니다.
- malloc(0) 일 때의 동작은 구현에 따릅니다. NULL포인터를 반환하거나, size가 0이 아닌 것처럼 반환합니다. (객체 접근에 사용할 수는 없는 free될 수 있는 포인터)
- 할당 실패 시 NULLpointer를 반환하고, 성공 시 반환된 포인터는 정렬된 다음, 포인터(유형은 상관 없음)에 할당되어서 접근하는 데에 사용됩니다.
- 수명은 할당 시부터 명시적 할당 해제 시까지 입니다.
- `atoi`은 `(int)strtol(str, (char **)NULL, 10)`과 같습니다. `strtol`은 문자열을 long으로 바꿔주는 함수로 오버플로, 언더플로가 발생했을 때 리턴값은 LONG_MIN, LONG_MAX로 고정됩니다. 이에 따라 `atoi`은 1) int범위 이내일 때, 2) int범위를 넘기고 long범위 이내일 때, 3) long범위 넘어갈 때 각각 다르게 리턴합니다.

## Part 2.
특정 기능을 수행하는 새로운 함수를 만든다.

### 파일디스크립터를 인자로 받는 함수
`putchar_fd` `putendl_fd` `putnbr_fd` `putstr_fd`
- 파일디스크립터란 시스템이 파일에 붙이는 별명으로 생각해볼 수 있습니다. 음수가 아닌 정수이며, 0(표준입력), 1(표준출력), 2(표준에러)는 기본으로 배정된 파일디스크립터입니다.
- `open` 함수로 파일을 열면 파일디스크립터 값이 리턴됩니다. (예시: `open("a.txt", WR_ONLY);`)
- `write` 함수를 사용하면 해당 파일로 버퍼가 입력됩니다.
### 함수를 인자로 받는 함수
`strmapi` `striteri`
- 각각 i(인덱스)를 순회하며 mapping(다른 값으로 대응), iteration(반복(하여 적용))한다는 의미입니다.
- `strmapi`에 들어가는 함수의 예시는 다음과 같습니다. (출처: libft-war-machine)
  - 첫번째 인자로 static int배열에 이미 작업한 인덱스를 표시해서 오류를 사전에 체크합니다.
  - 두번째 인자 값을 바꿔서 리턴합니다.
```
char	mapi(unsigned int i, char c)
{
	static int indexArray[11] = {0};

	if (i > 10 || indexArray[i] == 1)
		write(1, "wrong index\n", 12);
	else
		indexArray[i] = 1;
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	else if (c >= 'A' && c <= 'Z')
		return (c + 32);
	else
		return (c);
}
/* 소문자는 대문자로, 대문자는 소문자로 바꿔준다 */
```

### 기타 함수
`split` `strtrim` `substr` `itoa` `strjoin`

## Bonus Part.
연결리스트를 쉽게 다룰 수 있는 함수들을 만든다.

### 연결리스트를 다루는 함수
`lstnew` `lstadd_front` `lstadd_back` `lstlast` `lstdelone` `lstclear` `lstmap` `lstiter`
- `lstdelone`에서 바로 free(lst->content)하는 대신 del함수를 넘겨주는 이유는, 만약 리스트의 content가 구조체를 가리킬 경우 구조체의 멤버들을 모두 프리시켜줄 수 있는 함수가 필요하기 때문입니다. 다음은 그 예시입니다.
```
void    ft_delcontent(void *content) {
  free(content->member1);
  free(content->member2);
  free(content);}
```
- `lstmap`에 넘기는 f함수의 예시는 다음과 같습니다. (출처: libft-war-machine)
```
void    *ft_map(void *c) {
	int   i;
	char  *pouet;

	i = -1;
	pouet = (char *)c;
	while (pouet[++i])
		if (pouet[i] == 'o')
			pouet[i] = 'a';
	return (c);
}
/* 문자가 o일 때 a로 바꿔준다 */
 ```
## 참조
- 컴파일과정: https://bradbury.tistory.com/226
- 라이브러리란: https://bradbury.tistory.com/224?category=1000486
- 정적변수와 전역변수의 공통점과 차이점: https://m.blog.naver.com/xlql555/221850860864
- const의 타입안정성 문제: https://en.wikipedia.org/wiki/Const_(computer_programming)#strchr_problem
- kilee의 Makefile교재: https://www.notion.so/Makefile-5515ac58527c481cb67f00d30a19a7f9
- Makefile의 매크로 기본이해: http://doc.kldp.org/KoreanDoc/html/GNU-Make/GNU-Make-3.html
- 함수포인터: https://www.geeksforgeeks.org/function-pointer-in-c
- strlcat 동작방식: https://stackoverflow.com/questions/33154740/strlcat-is-dst-always-nul-terminated-what-are-size-and-the-returned-value
- strlcat의 리턴값을 활용하는 법: https://www.delorie.com/djgpp/doc/libc/libc_762.html
- 파일 디스크립터 설명: https://blog.naver.com/songblue61/221289713360
- 인자로 넘어가는 함수 예시 출처: https://github.com/y3ll0w42/libft-war-machine
